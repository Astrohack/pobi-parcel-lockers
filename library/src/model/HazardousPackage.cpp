
#include "HazardousPackage.h"

HazardousPackage::HazardousPackage(const std::string &id, double weight, const BoxSize &size, std::string source_id,
    std::string destination_id, const std::string &threats) : Package(id, weight, size, source_id, destination_id), _threats(threats){
}

double HazardousPackage::get_price() const{
    return Package::get_price() * 1.5;
}

std::string HazardousPackage::get_info() {
    return Package::get_info() + " threats: " + get_threats();
}

std::string HazardousPackage::get_threats() const {
    return _threats;
}
