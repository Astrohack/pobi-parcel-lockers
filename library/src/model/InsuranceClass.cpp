//
// Created by patryk on 6/11/24.
//

#include "InsuranceClass.h"

InsuranceClass::~InsuranceClass() = default;

double InsuranceClass::apply(double price) const {
    return 0;
}

std::string InsuranceClass::get_info() {
    return "No insurance";
}

double Default::apply(double price) const{
    return price * 0.1;
}

std::string Default::get_info() {
    return "Basic insurance";
}

double Premium::apply(double price) const{
    return price * 0.4 + 100;
}

std::string Premium::get_info() {
    return "Extended insurance";
}
