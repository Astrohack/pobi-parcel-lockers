
#ifndef PACKAGELOCKERMANAGER_H
#define PACKAGELOCKERMANAGER_H

#include "PackageManager.h"


/**
 * @brief Manages Package locker repository
 */
class PackageLockerManager {
private:
    Repository<PackageLockerPtr> _locker_repo;

public:
    /**
     * @brief Registers a new package locker.
     *
     * @param locker A shared pointer to the package locker to be registered.
     * @throws ObjectNotFoundException if the locker already exists.
     * @throws DuplicateException if the locker cannot be added.
     */
    void register_package_locker(const PackageLockerPtr &locker);

    /**
     * @brief Unregisters a package locker.
     *
     * @param id The identifier of the package locker to be unregistered.
     * @throws ObjectNotFoundException if the locker does not exist.
     */
    void unregister_package_locker(const std::string &id);

    /**
     * @brief Retrieves a specific package locker by its identifier.
     *
     * @param id The identifier of the package locker.
     * @return A shared pointer to the package locker.
     * @throws ObjectNotFoundException if the locker does not exist.
     */
    PackageLockerPtr get_package_locker(const std::string &id);

    /**
    * @brief Retrieves a package locker containing a specific package.
    *
    * @param package_id The identifier of the package.
    * @return A shared pointer to the package locker containing the package.
    */
    PackageLockerPtr get_package_locker_with_package(const std::string &package_id);

    /**
     * @brief Retrieves all package lockers.
     *
     * @return A vector of shared pointers to all package lockers.
     */
    std::vector<PackageLockerPtr> get_all_package_lockers();


};
#endif //PACKAGELOCKERMANAGER_H
