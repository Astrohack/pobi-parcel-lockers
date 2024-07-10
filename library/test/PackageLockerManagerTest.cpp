#include <boost/test/unit_test.hpp>
#include "PackageLockerManager.h"
#include "PackageLocker.h"
#include "BaseError.h"
#include <memory>
#include <NormalPackage.h>

using namespace std;

struct PackageLockerManagerTestFixture {
    PackageLockerManager manager;
    PackageLockerManagerTestFixture() {}
    ~PackageLockerManagerTestFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(PackageLockerManagerTestSuite, PackageLockerManagerTestFixture)

// Test register_package_locker
BOOST_AUTO_TEST_CASE(PackageLockerManagerTest_RegisterPackageLocker) {
    auto locker = make_shared<PackageLocker>("LCK123", "Location123", 10);

    manager.register_package_locker(locker);
    BOOST_TEST(manager.get_package_locker("LCK123") == locker);

    BOOST_CHECK_THROW(manager.register_package_locker(locker), DuplicateException);
}

// Test unregister_package_locker
BOOST_AUTO_TEST_CASE(PackageLockerManagerTest_UnregisterPackageLocker) {
    auto locker = make_shared<PackageLocker>("LCK123", "Location123", 10);

    manager.register_package_locker(locker);
    BOOST_TEST(manager.get_package_locker("LCK123") == locker);

    manager.unregister_package_locker("LCK123");
    BOOST_CHECK_THROW(manager.get_package_locker("LCK123"), ObjectNotFoundException);

    BOOST_CHECK_THROW(manager.unregister_package_locker("LCK123"), ObjectNotFoundException);
}

// Test get_package_locker
BOOST_AUTO_TEST_CASE(PackageLockerManagerTest_GetPackageLocker) {
    auto locker = make_shared<PackageLocker>("LCK123", "Location123", 10);

    manager.register_package_locker(locker);
    BOOST_TEST(manager.get_package_locker("LCK123") == locker);

    BOOST_CHECK_THROW(manager.get_package_locker("NON_EXISTENT"), ObjectNotFoundException);
}

// Test get_all_package_lockers
BOOST_AUTO_TEST_CASE(PackageLockerManagerTest_GetAllPackageLockers) {
    auto locker1 = make_shared<PackageLocker>("LCK123", "Location123", 10);
    auto locker2 = make_shared<PackageLocker>("LCK456", "Location456", 20);

    manager.register_package_locker(locker1);
    manager.register_package_locker(locker2);

    auto lockers = manager.get_all_package_lockers();
    BOOST_TEST(lockers.size() == 2);
    BOOST_TEST(lockers[0] == locker1);
    BOOST_TEST(lockers[1] == locker2);
}

BOOST_AUTO_TEST_SUITE_END()
