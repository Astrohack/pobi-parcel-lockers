//
// Created by patryk on 6/10/24.
//

#include "PackageLockerManager.h"
#include "BaseError.h"
#include <PackageLocker.h>

void PackageLockerManager::register_package_locker(const PackageLockerPtr &locker) {
    if(locker == nullptr)
        throw BadRequestException("Locker cannot be nullptr");
    if(!_locker_repo.add(locker))
        throw DuplicateException("Locker with id:" + locker->get_id() + " already exists");
}

void PackageLockerManager::unregister_package_locker(const std::string& id) {
    if (!_locker_repo.remove(_locker_repo.get(id)))
        throw ObjectNotFoundException("Locker with id:" + id + " does not exists");
}

PackageLockerPtr PackageLockerManager::get_package_locker_with_package(const std::string &package_id) {
    PackageLockerPtr locker = _locker_repo.findOneBy([package_id](const PackageLockerPtr& locker) {
        return locker->has_package(package_id);
    });
    return locker;
}

PackageLockerPtr PackageLockerManager::get_package_locker(const std::string &id) {
    PackageLockerPtr locker = _locker_repo.get(id);
    if (locker == nullptr)
        throw ObjectNotFoundException("Locker with id:" + id + " does not exists");
    return locker;
}

std::vector<PackageLockerPtr> PackageLockerManager::get_all_package_lockers() {
    return _locker_repo.findAll();
}

