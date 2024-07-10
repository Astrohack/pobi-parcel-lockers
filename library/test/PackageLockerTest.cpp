
#include <NormalPackage.h>
#include <PackageLocker.h>
#include <boost/test/unit_test.hpp>


using namespace std;

struct PackageLockerTestFixture {

    PackageLockerTestFixture() = default;
    ~PackageLockerTestFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(PackageLockerTestSuite, PackageLockerTestFixture)

// Test constructor
BOOST_AUTO_TEST_CASE(PackageLockerTest_Constructor) {
    PackageLocker locker("LCK123", "Location123", 10);

    BOOST_TEST(locker.get_id() == "LCK123");
    BOOST_TEST(locker.get_location() == "Location123");
    BOOST_TEST(locker.get_max_size() == 10);
}

// Test get_package_count
BOOST_AUTO_TEST_CASE(PackageLockerTest_GetPackageCount) {
    PackageLocker locker("LCK123", "Location123", 10);

    BOOST_TEST(locker.get_package_count() == 0);
}

// Test get_info
BOOST_AUTO_TEST_CASE(PackageLockerTest_GetInfo) {
    PackageLocker locker("LCK123", "Location123", 10);

    string info = "PackageLocker: id: LCK123 location: Location123 max size: 10 package count: 0 load: 0.000000";
    BOOST_TEST(locker.get_info() == info);
}

// Test get_locker_load
BOOST_AUTO_TEST_CASE(PackageLockerTest_GetLockerLoad) {
    PackageLocker locker("LCK123", "Location123", 10);

    BOOST_TEST(locker.get_locker_load() == 0.0);
}

// Test add_package and get_package_count
BOOST_AUTO_TEST_CASE(PackageLockerTest_AddPackage) {
    PackageLocker locker("LCK123", "Location123", 10);
    BoxSize size = std::make_tuple(2, 3, 4);
    auto package = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");

    locker.add_package(package);
    BOOST_TEST(locker.get_package_count() == 1);
}

// Test remove_package and get_package_count
BOOST_AUTO_TEST_CASE(PackageLockerTest_RemovePackage) {
    PackageLocker locker("LCK123", "Location123", 10);
    BoxSize size = std::make_tuple(2, 3, 4);
    auto package = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");

    locker.add_package(package);
    BOOST_TEST(locker.get_package_count() == 1);

    locker.remove_package(package);
    BOOST_TEST(locker.get_package_count() == 0);
}

// Test has_package
BOOST_AUTO_TEST_CASE(PackageLockerTest_HasPackage) {
    PackageLocker locker("LCK123", "Location123", 10);
    BoxSize size = std::make_tuple(2, 3, 4);
    auto package = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");

    locker.add_package(package);
    BOOST_TEST(locker.has_package("PKG123") == true);

    locker.remove_package(package);
    BOOST_TEST(locker.has_package("PKG123") == false);
}

// Test describe_content
BOOST_AUTO_TEST_CASE(PackageLockerTest_DescribeContent) {
    PackageLocker locker("LCK123", "Location123", 10);
    BoxSize size = std::make_tuple(2, 3, 4);
    auto package1 = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");
    auto package2 = make_shared<NormalPackage>("PKG456", 2.0, size, "SRC456", "DEST456");

    locker.add_package(package1);
    locker.add_package(package2);

    string content = package1->get_info() + "\n\r" + package2->get_info() + "\n\r";
    BOOST_TEST(locker.describe_content() == content);
}

BOOST_AUTO_TEST_SUITE_END()