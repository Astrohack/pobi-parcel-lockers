#include <memory>
#include <boost/test/unit_test.hpp>
#include "InsuredPackage.h"

struct InsuredPackageTestFixture {
    InsuredPackageTestFixture() {}
    ~InsuredPackageTestFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(InsuredPackageTestSuite, InsuredPackageTestFixture)

// Test get_price
BOOST_AUTO_TEST_CASE(InsuredPackageTest_GetPrice) {
    BoxSize size = std::make_tuple(2, 3, 4);
    InsuranceClassPtr insurance = std::make_shared<Default>();
    InsuredPackage package("PKG123", 5.0, size, "SRC123", "DEST123", insurance);

    BOOST_TEST(package.get_price() == 13.86, boost::test_tools::tolerance(0.0001));
}

// Test set_insurance_class
BOOST_AUTO_TEST_CASE(InsuredPackageTest_SetInsuranceClass) {
    BoxSize size = std::make_tuple(2, 3, 4);
    InsuranceClassPtr default_insurance = std::make_shared<Default>();
    InsuranceClassPtr premium_insurance = std::make_shared<Premium>();
    InsuredPackage package("PKG123", 5.0, size, "SRC123", "DEST123", default_insurance);

    package.set_insurance_class(premium_insurance);
    BOOST_TEST(package.get_price() == 117.64, boost::test_tools::tolerance(0.0001));

    package.set_insurance_class(default_insurance);
    BOOST_TEST(package.get_price() == 13.86, boost::test_tools::tolerance(0.0001));
}

// Test get_info
BOOST_AUTO_TEST_CASE(InsuredPackageTest_GetInfo) {
    BoxSize size = std::make_tuple(2, 3, 4);
    InsuranceClassPtr insurance = std::make_shared<Premium>();
    InsuredPackage package("PKG123", 5.0, size, "SRC123", "DEST123", insurance);

    std::string expected_info = "Package: id: PKG123 weight: 5.000000 size: (2, 3, 4) status: none to: DEST123 from: SRC123 currently at: --- price: " + std::to_string(package.get_price()) + " packet class: Extended insurance";
    BOOST_TEST(package.get_info() == expected_info);
}

BOOST_AUTO_TEST_SUITE_END()
