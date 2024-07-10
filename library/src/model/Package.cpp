#include "Package.h"
#include <PackageLocker.h>

Package::Package(const std::string &id, double weight, const BoxSize &size, std::string source_id, std::string destination_id) : _id(id), _weight(weight), _size(size), _destination_locker_id(destination_id), _source_locker_id(source_id){
    _is_archive = false;
}

std::string Package::get_destination_locker_id() const {
    return _destination_locker_id;
}

std::string Package::get_source_locker_id() const {
    return _source_locker_id;
}

Package::~Package() = default;

std::string Package::get_id() const {
    return _id;
}

bool Package::is_archive() const {
    return _is_archive;
}

double Package::get_weight() const {
    return _weight;
}

BoxSize Package::get_size() const {
    return _size;
}

int Package::get_volume() const {
    return std::get<0>(_size) * std::get<1>(_size) * std::get<2>(_size);
}

PackageStatus Package::get_status() const {
    return _status;
}

bool Package::has_status(PackageStatus status) const {
    return status == _status;
}

double Package::get_price() const {
    return get_volume() * 0.4 + get_weight() * 0.6;
}

std::string Package::get_current_location_id() {
    switch (_status) {
        case ready_to_receive:
            return _destination_locker_id;
        case received:
            return "RECEIVED";
        case returned_to_sender:
            return _source_locker_id;
        case waiting_for_delivery:
            return _source_locker_id;
        case returning:
            return _destination_locker_id;
        default:
            return "---";
    }
}

void Package::update_status(PackageStatus status) {
    _status = status;
}

std::string Package::get_status_string() {
    std::string strings[] = {"received", "ready_to_receive", "returning ","waiting_for_delivery","none", "returned_to_sender"};
    return strings[_status];
}

std::string Package::get_info() {
    return "Package: id: " + _id
    + " weight: "
    + std::to_string(_weight)
    + " size: ("
    + std::to_string(std::get<0>(_size))
    + ", "
    + std::to_string(std::get<1>(_size))
    + ", "
    + std::to_string(std::get<2>(_size))
    + ") status: "
    + get_status_string()
    + " to: "
    + get_destination_locker_id()
    + " from: "
    + get_source_locker_id()
    + " currently at: "
    + get_current_location_id()
    + " price: "
    + std::to_string(get_price());
}

void Package::set_archive() {
    _is_archive = true;
}
