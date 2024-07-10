#ifndef PACKAGE_H
#define PACKAGE_H
#include <string>
#include <boost/date_time/posix_time/ptime.hpp>
#include "typedefs.h"
namespace pt = boost::posix_time;

typedef enum {
    received = 0,
    ready_to_receive = 1,
    returning = 2,
    waiting_for_delivery = 3,
    none = 4,
    returned_to_sender = 5
} PackageStatus;

/**
 * @brief Class representing one package
 */
class Package : public std::enable_shared_from_this<Package> {
private:
    std::string _id;
    std::string _destination_locker_id;
    std::string _source_locker_id;
    double _weight;
    bool _is_archive;
    BoxSize _size;
    PackageStatus _status = none;

public:
    /**
     * @brief Get id of package locker from where package is send to
     */
    std::string get_destination_locker_id() const;

    /**
    * @brief Get id of package locker from where package was send;
    */
    std::string get_source_locker_id() const;


    Package(const std::string &id, double weight, const BoxSize &size, std::string source_id, std::string destination_id);

    virtual ~Package() = 0;

    /**
     * Get id of package
     */
    std::string get_id() const;

    /**
     * Check if this package is archive
     */
    bool is_archive() const;

    /**
     * Get package weight
     */
    double get_weight() const;

    /**
     * Get package size
     * @return BoxSize
     */
    BoxSize get_size() const;

    /**
     * Get package volume
     */
    int get_volume() const;

    /**
     * Get current package status as number
     * @return PackageStatus
     */
    PackageStatus get_status() const;

    /**
     * Check if package has given status
     * @param status
     */
    bool has_status(PackageStatus status) const;

    /**
     * Update package status
     * @param status
     */
    void update_status(PackageStatus status);

    /**
     * Calculate package price;
     */
    virtual double get_price() const;

    /**
     * Get id of package locker where package is currently hold
     */
    std::string get_current_location_id();

    /**
     * Get package status as string
     */
    std::string get_status_string();

    /**
     * Describe package content
     */
    virtual std::string get_info();

    /**
     * Make this package archive
     */
    void set_archive();

};

#endif //PACKAGE_H
