//
// Created by patryk on 6/9/24.
//

#ifndef HAZARDOUSPACKAGE_H
#define HAZARDOUSPACKAGE_H
#include <Package.h>

/**
 * @brief Package that is a threat to environment
 */
class HazardousPackage : public Package{
private:
    std::string _threats;
public:
    HazardousPackage(const std::string &id, double weight, const BoxSize &size, std::string source_id, std::string destination_id, const std::string &threats);

    double get_price() const override;

    ~HazardousPackage() override = default;

    std::string get_info() override;

    std::string get_threats() const;
};



#endif //HAZARDOUSPACKAGE_H
