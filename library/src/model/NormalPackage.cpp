#include "NormalPackage.h"

NormalPackage::NormalPackage(const std::string &id, double weight, const BoxSize &size, std::string source_id,
    std::string destination_id) : Package(id, weight, size, source_id, destination_id)  {
}

double NormalPackage::get_price() const{
    return Package::get_price();
}

std::string NormalPackage::get_info() {
    return Package::get_info();
}
