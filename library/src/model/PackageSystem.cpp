#include "PackageSystem.h"

#include <BaseError.h>
#include <Package.h>
#include "Repository.h"
#include "PackageLocker.h"

PackageSystem::PackageSystem() = default;

PackageSystem::~PackageSystem() = default;

void PackageSystem::send_package(const PackagePtr &package) {
    if (!package->has_status(none))
        throw BadRequestException("Cannot send a package that has already been sent");
    try {
        package_manager.get_package(package->get_id());
        return;
    }
    catch (const ObjectNotFoundException& e) {}

    if (package->get_source_locker_id() == package->get_destination_locker_id())
        throw BadRequestException("Destanation and source cannot be the same");

    // check if package fit into locker //
    std::vector<int> pack = {std::get<0>(package->get_size()),
                            std::get<1>(package->get_size()),
                            std::get<2>(package->get_size())};
    std::sort(pack.begin(), pack.end());

    for (int i = 0; i < 3; i++)
        if (pack[i] > 20)
            throw BadRequestException("Package with id: " + package->get_id() + " is too big");
    ////

    // Check if locker is full
    if (package_locker_manager.get_package_locker(package->get_source_locker_id())->get_locker_load() == 1) return;

    package_locker_manager.get_package_locker(package->get_source_locker_id())->add_package(package);
    package_manager.register_package(package);
    package->update_status(PackageStatus::waiting_for_delivery);
}

void PackageSystem::cancel_package(const std::string& id) {
    PackageStatus status = package_manager.get_package(id)->get_status();
    if (status == PackageStatus::ready_to_receive) {
        package_manager.get_package(id)->update_status(PackageStatus::returning);
        return;
    }
    if (status == PackageStatus::waiting_for_delivery) {
        package_manager.get_package(id)->update_status(PackageStatus::returned_to_sender);
        return;
    }
    throw BadRequestException("Cannot cancel package with id: " + id);
}

void PackageSystem::receive_package(const std::string& id) {
    PackagePtr package = package_manager.get_package(id);
    if (!package->has_status(ready_to_receive) && !package->has_status(returned_to_sender))
        throw BadRequestException("Package with id: " + id + " is not ready for receive");

    PackageLockerPtr locker = package_locker_manager.get_package_locker(
                package->has_status(returned_to_sender)? package->get_source_locker_id() : package->get_destination_locker_id()
            );
    locker->remove_package(package);
    package_manager.unregister_package(id);
    package->update_status(received);
}

void PackageSystem::deliver_package(const std::string& id) {
    PackagePtr package = package_manager.get_package(id);

    if (package->get_status() != waiting_for_delivery && package->get_status() != returning)
        throw BadRequestException("Package with id: " + id + " is not viable for delivery");
    PackageLockerPtr locker = package_locker_manager.get_package_locker(
                package->get_status() == returning? package->get_source_locker_id() : package->get_destination_locker_id()
            );
    PackageLockerPtr locker_old = package_locker_manager.get_package_locker(
                package->get_status() == returning?  package->get_destination_locker_id() : package->get_source_locker_id()
            );
    if (locker->get_locker_load() == 1) return;
    locker_old->remove_package(package);
    locker->add_package(package);
    package->update_status(package->has_status(returning)? returned_to_sender : ready_to_receive );
}

void PackageSystem::delivery_iteration() {
    for (const auto& package: package_manager.get_packages_for_delivery()) {
        deliver_package(package->get_id());
    }
}

std::vector<PackagePtr> PackageSystem::get_all_packages() {
    return package_manager.get_all_packages();
}

PackagePtr PackageSystem::get_package(const std::string &id) {
    return package_manager.get_package(id);
}

void PackageSystem::register_locker(const PackageLockerPtr &locker) {
    return package_locker_manager.register_package_locker(locker);
}

void PackageSystem::unregister_locker(const std::string &id) {
    if (package_locker_manager.get_package_locker(id)->get_package_count() != 0)
        throw BadRequestException("Cannot unregister: package locker is not empty");
    return package_locker_manager.unregister_package_locker(id);
}

PackageLockerPtr PackageSystem::get_package_locker(const std::string &id) {
    return package_locker_manager.get_package_locker(id);
}

std::vector<PackageLockerPtr> PackageSystem::get_all_package_lockers() {
    return package_locker_manager.get_all_package_lockers();
}
