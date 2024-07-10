//
// Created by patryk on 6/9/24.
//

#ifndef INSUREDPACKAGE_H
#define INSUREDPACKAGE_H
#include <Package.h>

#include "InsuranceClass.h"

/**
* @brief Allows selection of insurance class
*/
class InsuredPackage : public Package {
private:
    InsuranceClassPtr _insurance_class;

public:
    InsuredPackage(const std::string &id, double weight, const BoxSize &size, std::string source_id, std::string destination_id, InsuranceClassPtr insurance_class);

    double get_price() const  override;

    ~InsuredPackage() override = default;

    std::string get_info() override;

    void set_insurance_class(InsuranceClassPtr insurance_class);

    double get_insurance_value() const;


};



#endif //INSUREDPACKAGE_H
