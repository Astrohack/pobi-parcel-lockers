//
// Created by patryk on 6/9/24.
//

#include "InsuredPackage.h"

InsuredPackage::InsuredPackage(const std::string &id, double weight, const BoxSize &size, std::string source_id,
    std::string destination_id,  InsuranceClassPtr insurance_class) : Package(id, weight, size, source_id, destination_id), _insurance_class(insurance_class)  {
}

double InsuredPackage::get_price() const {
    return Package::get_price() + get_insurance_value();
}

void InsuredPackage::set_insurance_class(InsuranceClassPtr insurance_class) {
    _insurance_class = insurance_class;
}

std::string InsuredPackage::get_info() {
    return Package::get_info() + " packet class: " + _insurance_class->get_info();
}

double InsuredPackage::get_insurance_value() const {
    return _insurance_class->apply(Package::get_price());
}
