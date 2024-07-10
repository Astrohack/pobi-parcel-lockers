#include "PackageLocker.h"

#include <iostream>
#include <Package.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>

PackageLocker::~PackageLocker() = default;

PackageLocker::PackageLocker(const std::string &id, const std::string &location, int size) : _id(id), _location(location), _max_size(size){

}

std::string PackageLocker::get_id() const {
    return _id;
}

std::string PackageLocker::get_location() const {
    return _location;
}

int PackageLocker::get_max_size() const {
    return _max_size;
}

int PackageLocker::get_package_count() const {
    return _package_repo.size();
}

std::string PackageLocker::get_info() const {
    return "PackageLocker: id: " + _id
    + " location: " + _location
    + " max size: " + std::to_string(_max_size)
    + " package count: " + std::to_string(get_package_count())
    + " load: " + std::to_string(get_locker_load());
}

double PackageLocker::get_locker_load() const {
    if (_max_size == 0) return 0;
    return get_package_count() / static_cast<double>(get_max_size());
}

bool PackageLocker::has_package(const std::string &package_id) {
    return _package_repo.get(package_id) != nullptr;
}

void PackageLocker::add_package(const PackagePtr &package) {
    _package_repo.add(package);
}

bool PackageLocker::remove_package(const PackagePtr &package) {
    return _package_repo.remove(package);
}

std::string PackageLocker::describe_content() const {
    std::string result;
    _package_repo.foreach([&result](const PackagePtr& package) {
        result += package->get_info() + "\n\r";
    });
    return result;
}

