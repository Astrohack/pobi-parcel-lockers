//
// Created by patryk on 6/10/24.
//

#include "PackageManager.h"

#include <BaseError.h>

PackageManager::PackageManager() {
}

PackageManager::~PackageManager() {
}

void PackageManager::register_package(const PackagePtr &package) {
    if (package == nullptr)
        throw BadRequestException("Package cannot be null");
    if (!_package_repo.add(package))
        throw DuplicateException("Package with id: " + package->get_id() + " already exists in repository");
}

void PackageManager::unregister_package(const std::string &id) {
    get_package(id)->set_archive();
}

PackagePtr PackageManager::get_package(const std::string &id) {
    PackagePtr package = _package_repo.get(id);
    if (!package)
        throw ObjectNotFoundException("Cannot find package with id: " + id);
    return package;
}

std::vector<PackagePtr> PackageManager::get_packages_for_delivery() {
    return _package_repo.findBy([](const PackagePtr& package) {
        return package->has_status(waiting_for_delivery) || package->has_status(returning);
    });
}

std::vector<PackagePtr> PackageManager::get_all_packages() {
    return _package_repo.findAll();
}
