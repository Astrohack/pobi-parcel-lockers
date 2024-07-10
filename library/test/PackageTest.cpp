
#include <InsuredPackage.h>
#include <NormalPackage.h>
#include <Package.h>
#include <typedefs.h>
#include <boost/test/unit_test.hpp>


using namespace std;

struct PackageTestFixture {

    PackageTestFixture() {}
    ~PackageTestFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(PackageTestSuite, PackageTestFixture)

// Test constructor
BOOST_AUTO_TEST_CASE(PackageTest_Constructor) {
    BoxSize size = BoxSize(2, 3, 4);
    NormalPackage pkg("123", 5.0, size, "SRC123", "DEST123");

    BOOST_TEST(pkg.get_id() == "123");
    BOOST_TEST(pkg.get_weight() == 5.0);
    BOOST_TEST(pkg.get_source_locker_id() == "SRC123");
    BOOST_TEST(pkg.get_destination_locker_id() == "DEST123");
    BOOST_TEST(pkg.is_archive() == false);
}

// Test get_volume
BOOST_AUTO_TEST_CASE(PackageTest_GetVolume) {
    BoxSize size = std::make_tuple(2, 3, 4);
    NormalPackage pkg("123", 5.0, size, "SRC123", "DEST123");

    BOOST_TEST(pkg.get_volume() == 24);
}

// Test get_price
BOOST_AUTO_TEST_CASE(PackageTest_GetPrice) {
    BoxSize size = std::make_tuple(2, 3, 4);
    NormalPackage pkg("123", 5.0, size, "SRC123", "DEST123");

    double expected_price = pkg.get_volume() * 0.4 + pkg.get_weight() * 0.6;
    BOOST_TEST(pkg.get_price() == expected_price);
}

// Test update_status and get_status
BOOST_AUTO_TEST_CASE(PackageTest_UpdateStatus) {
    BoxSize size = std::make_tuple(2, 3, 4);
    NormalPackage pkg("123", 5.0, size, "SRC123", "DEST123");

    pkg.update_status(received);
    BOOST_TEST(pkg.get_status() == received);
    BOOST_TEST(pkg.has_status(received) == true);
}

// Test get_current_location_id
BOOST_AUTO_TEST_CASE(PackageTest_GetCurrentLocationId) {
    BoxSize size = std::make_tuple(2, 3, 4);
    NormalPackage pkg("123", 5.0, size, "SRC123", "DEST123");

    pkg.update_status(ready_to_receive);
    BOOST_TEST(pkg.get_current_location_id() == "DEST123");

    pkg.update_status(received);
    BOOST_TEST(pkg.get_current_location_id() == "RECEIVED");

    pkg.update_status(returned_to_sender);
    BOOST_TEST(pkg.get_current_location_id() == "SRC123");

    pkg.update_status(waiting_for_delivery);
    BOOST_TEST(pkg.get_current_location_id() == "SRC123");

    pkg.update_status(returning);
    BOOST_TEST(pkg.get_current_location_id() == "DEST123");
}

// Test set_archive
BOOST_AUTO_TEST_CASE(PackageTest_SetArchive) {
    BoxSize size = std::make_tuple(2, 3, 4);
    NormalPackage pkg("123", 5.0, size, "SRC123", "DEST123");

    pkg.set_archive();
    BOOST_TEST(pkg.is_archive() == true);
}

// Test get_info
BOOST_AUTO_TEST_CASE(PackageTest_GetInfo) {
    BoxSize size = std::make_tuple(2, 3, 4);
    NormalPackage pkg("123", 5.0, size, "SRC123", "DEST123");

    string info = "Package: id: 123 weight: 5.000000 size: (2, 3, 4) status: none to: DEST123 from: SRC123 currently at: --- price: " + to_string(pkg.get_price());
    BOOST_TEST(pkg.get_info() == info);
}

BOOST_AUTO_TEST_SUITE_END()