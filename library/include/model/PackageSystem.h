#ifndef PACKAGESYSTEM_H
#define PACKAGESYSTEM_H
#include <Repository.h>

#include "PackageLockerManager.h"
#include "PackageManager.h"

/**
 * @brief Package system manages packages and lockers
 */
class PackageSystem {
private:
    PackageManager package_manager;
    PackageLockerManager package_locker_manager;

public:
    PackageSystem();
    ~PackageSystem();

    /**
     * @brief Loads package into system
     *
     * @param package A shared pointer to the package to be sent.
     * @throws BadRequestException if the package has already been sent or the source locker is full.
     */
    void send_package(const PackagePtr &package);
    /**
     * @brief Cancels a package by updating its status.
     *
     * @param id The identifier of the package to be cancelled.
     * @throws BadRequestException if the package cannot be cancelled.
     */
    void cancel_package(const std::string& id);
    /**
     * @brief Gives package to client and updates its status to received.
     *
     * @param id The identifier of the package to be received.
     * @throws BadRequestException if the package is not ready to be received.
     * @throws ObjectNotFoundException if the package does not exists.
     */
    void receive_package(const std::string& id);

    /**
    * @brief Delivers a package to the appropriate locker.
    *
    * @param id The identifier of the package to be delivered.
    * @throws BadRequestException if the package is not viable for delivery.
    * @throws ObjectNotFoundException if the package does not exists.
    */
    void deliver_package(const std::string& id);

    /**
    * @brief Iterates through packages and delivers them.
    */
    void delivery_iteration();

    /**
    * @brief Retrieves all packages.
    *
    * @return A vector of shared pointers to all packages.
    */
    std::vector<PackagePtr> get_all_packages();

    /**
    * @brief Retrieves a specific package by its identifier.
    *
    * @param id The identifier of the package.
    * @return A shared pointer to the package.
    */
    PackagePtr get_package(const std::string& id);

    /**
    * @brief Registers a new package locker.
    *
    * @param locker A shared pointer to the package locker to be registered.
    */
    void register_locker(const PackageLockerPtr& locker);

     /**
     * @brief Unregisters a package locker.
     *
     * @param id The identifier of the package locker to be unregistered.
     * @throws BadRequestException if the locker is not empty.
     */
    void unregister_locker(const std::string &id);

     /**
    * @brief Retrieves a specific package locker by its identifier.
    *
    * @param id The identifier of the package locker.
    * @return A shared pointer to the package locker.
    */
    PackageLockerPtr get_package_locker(const std::string& id);
    /**
     * @brief Retrieves all package lockers.
     *
     * @return A vector of shared pointers to all package lockers.
     */
    std::vector<PackageLockerPtr> get_all_package_lockers();
};

#endif //PACKAGESYSTEM_H
