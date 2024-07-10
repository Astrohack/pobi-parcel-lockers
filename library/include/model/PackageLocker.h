#ifndef PACKAGELOCKER_H
#define PACKAGELOCKER_H
#include "Repository.h"
#include "typedefs.h"
#include "string"

/**
 * @brief Class representing package locker
 */
class PackageLocker {
private:
    std::string _id;

    std::string _location;

    Repository<PackagePtr> _package_repo;

    int _max_size;

public:
    PackageLocker(const std::string &id, const std::string &location, int size);
    ~PackageLocker();

    std::string get_id() const;

    std::string get_info() const;

    std::string get_location() const;

    int get_max_size() const;

    int get_package_count() const;

    /**
     * @brief Calculate locker load value which is from 0 to
     */
    double get_locker_load() const;

    /**
     * Add package to locker
     * @param package
     */
    void add_package(const PackagePtr& package);

    /**
     * Check if package exists in this locker
     * @param package_id
     */
    bool has_package(const std::string& package_id);

    /**
     * Remove package from locker
     * @param package
     */
    bool remove_package(const PackagePtr& package);

    /**
     * @brief Returns info about all packages inside locker
     */
    std::string describe_content() const;

};



#endif //PACKAGELOCKER_H
