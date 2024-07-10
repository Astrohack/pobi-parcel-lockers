#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H
#include <Repository.h>
#include <typedefs.h>


/**
 * @brief Manages package repository
 */
class PackageManager {
    Repository<PackagePtr> _package_repo;
public:
    PackageManager();
    ~PackageManager();

    /**
     * @brief Registers a new package.
     *
     * @param package A shared pointer to the package to be registered.
     * @throws BadRequestException if the package is null.
     * @throws DuplicateException if the package already exists in the repository.
     */
    void register_package(const PackagePtr& package);

    /**
     * @brief Unregisters a package by archiving it.
     *
     * @param id The identifier of the package to be unregistered.
     * @throws ObjectNotFoundException if the package does not exist.
     */
    void unregister_package(const std::string& id);

    /**
     * @brief Retrieves a specific package by its identifier.
     *
     * @param id The identifier of the package.
     * @return A shared pointer to the package.
     * @throws ObjectNotFoundException if the package cannot be found.
     */
    PackagePtr get_package(const std::string &id);

    /**
     * @brief Retrieves all packages that are either waiting for delivery or being returned.
     *
     * @return A vector of shared pointers to the packages for delivery.
     */
    std::vector<PackagePtr> get_packages_for_delivery();

    /**
    * @brief Retrieves all packages.
    *
    * @return A vector of shared pointers to all packages.
    */
    std::vector<PackagePtr> get_all_packages();
};



#endif //PACKAGEMANAGER_H
