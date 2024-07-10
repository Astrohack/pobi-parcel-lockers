#ifndef NORMALPACKAGE_H
#define NORMALPACKAGE_H
#include <Package.h>

/**
 * @brief Traditional package, no additional features.
 */
class NormalPackage : public Package {
public:
    NormalPackage(const std::string &id, double weight, const BoxSize &size, std::string source_id, std::string destination_id);

    ~NormalPackage() override = default;

    double get_price() const override;

    std::string get_info() override;
};

#endif //NORMALPACKAGE_H
