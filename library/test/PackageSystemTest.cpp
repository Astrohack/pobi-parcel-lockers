
#include <BaseError.h>
#include <NormalPackage.h>
#include <Package.h>
#include <PackageSystem.h>
#include <PackageLocker.h>
#include <boost/test/unit_test.hpp>


using namespace std;

struct PackageSystemTestFixtureBasic {

    PackageSystemPtr system = make_shared<PackageSystem>();
    PackagePtr p1 = make_shared<NormalPackage>("p1", 12, BoxSize(10, 10, 10), "A", "B");
    PackagePtr p2 = make_shared<NormalPackage>("p2", 12, BoxSize(10, 10, 10), "A", "B");
    PackageLockerPtr l1 = make_shared<PackageLocker>("A", "Łódź", 1);
    PackageLockerPtr l2 = make_shared<PackageLocker>("B", "Pabianice", 1);

    PackageSystemTestFixtureBasic() {
        system->register_locker(l1);
        system->register_locker(l2);
        system->send_package(p1);
        system->send_package(p2);
    }
    ~PackageSystemTestFixtureBasic() {}
};

struct PackageSystemTestFixtureExtended {

    PackageSystemPtr system = make_shared<PackageSystem>();
    PackageLockerPtr l1 = make_shared<PackageLocker>("A", "Łódź", 5);
    PackageLockerPtr l2 = make_shared<PackageLocker>("B", "Pabianice", 5);
    PackageLockerPtr l3 = make_shared<PackageLocker>("C", "Warszawa", 6);
    PackagePtr p1 = make_shared<NormalPackage>("p1", 12, BoxSize(10, 10, 10), "A", "B");
    PackagePtr p2 = make_shared<NormalPackage>("p2", 12, BoxSize(10, 10, 10), "A", "C");
    PackagePtr p3 = make_shared<NormalPackage>("p3", 12, BoxSize(10, 10, 10), "C", "B");
    PackagePtr p4_same_dest_src = make_shared<NormalPackage>("p4", 12, BoxSize(10, 10, 10), "B", "B");
    PackagePtr p5 = make_shared<NormalPackage>("p5", 12, BoxSize(10, 10, 10), "A", "B");
    PackagePtr p6 = make_shared<NormalPackage>("p6", 12, BoxSize(10, 10, 10), "A", "B");
    PackagePtr p7 = make_shared<NormalPackage>("p7", 12, BoxSize(10, 10, 10), "A", "B");
    PackagePtr p8 = make_shared<NormalPackage>("p8", 12, BoxSize(10, 10, 10), "A", "B");
    PackagePtr p9 = make_shared<NormalPackage>("p9", 12, BoxSize(21, 10, 10), "B", "A");


    PackageSystemTestFixtureExtended() {
        system->register_locker(l1);
        system->register_locker(l2);
        system->register_locker(l3);
    }
    ~PackageSystemTestFixtureExtended() {}
};

/**
 * @brief Test cases are summary tests of all app features
 */
BOOST_FIXTURE_TEST_SUITE(PackageSystemTestSuiteBasic, PackageSystemTestFixtureBasic)

BOOST_AUTO_TEST_CASE(PackageSystemTest_PackageRegister) {
    BOOST_TEST(l1->get_package_count() == 1);
    BOOST_TEST(l2->get_package_count() == 0);
    BOOST_TEST(p1->get_status() == PackageStatus::waiting_for_delivery);
    BOOST_TEST(p2->get_status() == PackageStatus::none);
}

BOOST_AUTO_TEST_CASE(PackageSystemTest_PackageUnregister) {
    BOOST_CHECK_NO_THROW(system->cancel_package(p1->get_id()));
    BOOST_CHECK_THROW(system->cancel_package(p2->get_id()), ObjectNotFoundException);
    BOOST_TEST(p1->has_status(returned_to_sender));
    BOOST_TEST(p2->has_status(none));
    BOOST_CHECK_NO_THROW(system->receive_package(p1->get_id()));
    BOOST_TEST(l1->get_package_count() == 0);
    BOOST_TEST(l2->get_package_count() == 0);
    BOOST_CHECK_NO_THROW(system->send_package(p2));
    BOOST_TEST(p2->get_status() == waiting_for_delivery);
    BOOST_CHECK_NO_THROW(system->deliver_package(p2->get_id()));
    BOOST_CHECK_NO_THROW(system->cancel_package(p2->get_id()));
    BOOST_TEST(p2->get_status() == PackageStatus::returning);
    system->deliver_package(p2->get_id());
    BOOST_TEST(p2->get_status() == PackageStatus::returned_to_sender);
}

BOOST_AUTO_TEST_CASE(PackageSystemTest_PackageCancel) {
    BOOST_CHECK_NO_THROW(system->cancel_package(p1->get_id()));
    BOOST_CHECK_THROW(system->cancel_package(p1->get_id()), BadRequestException);
    BOOST_CHECK_THROW(system->cancel_package(p2->get_id()), ObjectNotFoundException);
    BOOST_TEST(p1->has_status(returned_to_sender));
    BOOST_CHECK_NO_THROW(system->receive_package(p1->get_id()));
    BOOST_TEST(l1->get_package_count() == 0);
    BOOST_TEST(l2->get_package_count() == 0);
    BOOST_CHECK_NO_THROW(system->send_package(p2));
    BOOST_TEST(p2->get_status() == waiting_for_delivery);
    BOOST_CHECK_NO_THROW(system->deliver_package(p2->get_id()));
    BOOST_CHECK_NO_THROW(system->cancel_package(p2->get_id()));
    BOOST_TEST(p2->get_status() == PackageStatus::returning);
    system->deliver_package(p2->get_id());
    BOOST_TEST(p2->get_status() == PackageStatus::returned_to_sender);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(PackageSystemTestSuiteExtended, PackageSystemTestFixtureExtended)

BOOST_AUTO_TEST_CASE(PackageSystemTest_SUMMARY) {
    BOOST_CHECK_NO_THROW(system->send_package(p1));
    BOOST_CHECK_NO_THROW(system->send_package(p2));
    BOOST_CHECK_NO_THROW(system->send_package(p3));
    BOOST_CHECK_THROW(system->send_package(p4_same_dest_src), BadRequestException);
    BOOST_CHECK_NO_THROW(system->send_package(p5));
    BOOST_CHECK_NO_THROW(system->send_package(p6));
    BOOST_CHECK_NO_THROW(system->send_package(p7));
    BOOST_CHECK_NO_THROW(system->send_package(p8));
    BOOST_CHECK_THROW(system->send_package(p9), BadRequestException);

    BOOST_TEST(system->get_all_packages().size() == 6);
    BOOST_TEST(system->get_package_locker("A")->get_package_count() == 5);
    BOOST_TEST(system->get_package_locker("B")->get_package_count() == 0);
    BOOST_TEST(system->get_package_locker("C")->get_package_count() == 1);

    BOOST_CHECK_THROW(system->receive_package("p1"), BadRequestException);
    BOOST_CHECK_THROW(system->receive_package("p2"), BadRequestException);
    BOOST_CHECK_THROW(system->receive_package("p3"), BadRequestException);
    BOOST_CHECK_THROW(system->receive_package("p4"), ObjectNotFoundException);

    BOOST_CHECK_NO_THROW(system->delivery_iteration());

    BOOST_CHECK_NO_THROW(system->receive_package("p1"));
    BOOST_CHECK_NO_THROW(system->receive_package("p2"));
    BOOST_CHECK_NO_THROW(system->receive_package("p3"));

    BOOST_CHECK_THROW(system->receive_package("p3"), BadRequestException);

    BOOST_TEST(p1->get_status() == received);
    BOOST_TEST(p2->get_status() == received);
    BOOST_TEST(p3->get_status() == received);

    BOOST_TEST(p1->is_archive());
    BOOST_TEST(p2->is_archive());
    BOOST_TEST(p3->is_archive());

    BOOST_CHECK_NO_THROW(system->cancel_package("p5"));
    BOOST_CHECK_NO_THROW(system->cancel_package("p6"));
    BOOST_CHECK_NO_THROW(system->cancel_package("p7"));

    BOOST_TEST(p5->get_status() == returning);
    BOOST_TEST(p6->get_status() == returning);
    BOOST_TEST(p7->get_status() == returning);

    BOOST_CHECK_NO_THROW(system->delivery_iteration());

    BOOST_TEST(p5->get_status() == returned_to_sender);
    BOOST_TEST(p6->get_status() == returned_to_sender);
    BOOST_TEST(p7->get_status() == returned_to_sender);

    BOOST_CHECK_NO_THROW(system->receive_package("p5"));
    BOOST_CHECK_NO_THROW(system->receive_package("p6"));
    BOOST_CHECK_NO_THROW(system->receive_package("p7"));

    BOOST_TEST(p5->is_archive());
    BOOST_TEST(p6->is_archive());
    BOOST_TEST(p7->is_archive());
}

BOOST_AUTO_TEST_SUITE_END()

