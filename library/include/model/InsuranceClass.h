//
// Created by patryk on 6/11/24.
//

#ifndef SERVICECLASS_H
#define SERVICECLASS_H
#include <string>

class InsuranceClass {
public:
    InsuranceClass() = default;
    virtual ~InsuranceClass();

    virtual double apply(double price) const;

    virtual std::string get_info();
};

/**
 * @brief Type of Insurance class
 */
class Default : public InsuranceClass {
public:
    Default() = default;

    ~Default() override = default;

    double apply(double price) const override;

    std::string get_info() override;
};

/**
 * @brief Type of Insurance class
 */
class Premium : public InsuranceClass {
public:
    Premium() = default;

    ~Premium() override = default;

    double apply(double price) const override;

    std::string get_info() override;
};



#endif //SERVICECLASS_H
