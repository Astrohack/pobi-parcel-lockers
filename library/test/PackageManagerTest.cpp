#include <NormalPackage.h>
#include <boost/test/unit_test.hpp>
#include "PackageManager.h"
#include "Package.h"
#include "BaseError.h"

using namespace std;

struct PackageManagerTestFixture {
    PackageManager manager;
    PackageManagerTestFixture() {}
    ~PackageManagerTestFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(PackageManagerTestSuite, PackageManagerTestFixture)

// Test constructor and destructor
BOOST_AUTO_TEST_CASE(PackageManagerTest_Constructor) {
    PackageManager manager;
    BOOST_TEST(manager.get_all_packages().size() == 0);
}

// Test register_package
BOOST_AUTO_TEST_CASE(PackageManagerTest_RegisterPackage) {
    BoxSize size = make_tuple(2, 3, 4);
    auto package = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");

    manager.register_package(package);
    BOOST_TEST(manager.get_package("PKG123") == package);
    BOOST_CHECK_THROW(manager.register_package(nullptr), BadRequestException);
    BOOST_CHECK_THROW(manager.register_package(package), DuplicateException);
}

// Test unregister_package
BOOST_AUTO_TEST_CASE(PackageManagerTest_UnregisterPackage) {
    BoxSize size = make_tuple(2, 3, 4);
    auto package = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");

    manager.register_package(package);
    BOOST_TEST(manager.get_package("PKG123") == package);
    manager.unregister_package("PKG123");
    BOOST_TEST(package->is_archive() == true);
    BOOST_CHECK_THROW(manager.unregister_package("NON_EXISTENT"), ObjectNotFoundException);
}

// Test get_package
BOOST_AUTO_TEST_CASE(PackageManagerTest_GetPackage) {
    BoxSize size = make_tuple(2, 3, 4);
    auto package = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");

    manager.register_package(package);
    BOOST_TEST(manager.get_package("PKG123") == package);

    BOOST_CHECK_THROW(manager.get_package("NON_EXISTENT"), ObjectNotFoundException);
}

// Test get_packages_for_delivery
BOOST_AUTO_TEST_CASE(PackageManagerTest_GetPackagesForDelivery) {
    BoxSize size = make_tuple(2, 3, 4);
    auto package1 = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");
    auto package2 = make_shared<NormalPackage>("PKG456", 2.0, size, "SRC456", "DEST456");

    package1->update_status(waiting_for_delivery);
    package2->update_status(returning);

    manager.register_package(package1);
    manager.register_package(package2);

    auto packages = manager.get_packages_for_delivery();
    BOOST_TEST(packages.size() == 2);
    BOOST_TEST(packages[0] == package1);
    BOOST_TEST(packages[1] == package2);
}

// Test get_all_packages
BOOST_AUTO_TEST_CASE(PackageManagerTest_GetAllPackages) {
    BoxSize size = make_tuple(2, 3, 4);
    auto package1 = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");
    auto package2 = make_shared<NormalPackage>("PKG456", 2.0, size, "SRC456", "DEST456");

    manager.register_package(package1);
    manager.register_package(package2);

    auto packages = manager.get_all_packages();
    BOOST_TEST(packages.size() == 2);
    BOOST_TEST(packages[0] == package1);
    BOOST_TEST(packages[1] == package2);
}

BOOST_AUTO_TEST_SUITE_END()
