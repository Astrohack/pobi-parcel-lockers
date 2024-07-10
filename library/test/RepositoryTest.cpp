#include <boost/test/unit_test.hpp>
#include "Repository.h"
#include "Package.h"
#include <memory>
#include <NormalPackage.h>

using namespace std;

struct RepositoryTestFixture {
    RepositoryTestFixture() {}
    ~RepositoryTestFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(RepositoryTestSuite, RepositoryTestFixture)

// Test constructor
BOOST_AUTO_TEST_CASE(RepositoryTest_Constructor) {
    Repository<PackagePtr> repo;
    BOOST_TEST(repo.size() == 0);
}

// Test add and size
BOOST_AUTO_TEST_CASE(RepositoryTest_Add) {
    Repository<PackagePtr> repo;
    BoxSize size = std::make_tuple(2, 3, 4);
    auto package = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");

    BOOST_TEST(repo.add(package) == true);
    BOOST_TEST(repo.size() == 1);

    // Test adding the same package again
    BOOST_TEST(repo.add(package) == false);
    BOOST_TEST(repo.size() == 1);
}

// Test get
BOOST_AUTO_TEST_CASE(RepositoryTest_Get) {
    Repository<PackagePtr> repo;
    BoxSize size = std::make_tuple(2, 3, 4);
    auto package = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");

    repo.add(package);
    BOOST_TEST(repo.get("PKG123") == package);
    BOOST_TEST(repo.get("NON_EXISTENT") == nullptr);
}

// Test remove
BOOST_AUTO_TEST_CASE(RepositoryTest_Remove) {
    Repository<PackagePtr> repo;
    BoxSize size = std::make_tuple(2, 3, 4);
    auto package = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");

    repo.add(package);
    BOOST_TEST(repo.size() == 1);
    BOOST_TEST(repo.remove(package) == true);
    BOOST_TEST(repo.size() == 0);

    // Test removing a non-existent package
    BOOST_TEST(repo.remove(package) == false);
}

// Test report
BOOST_AUTO_TEST_CASE(RepositoryTest_Report) {
    Repository<PackagePtr> repo;
    BoxSize size = std::make_tuple(2, 3, 4);
    auto package1 = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");
    auto package2 = make_shared<NormalPackage>("PKG456", 2.0, size, "SRC456", "DEST456");

    repo.add(package1);
    repo.add(package2);

    string expected_report = package1->get_info() + "\n" + package2->get_info() + "\n";
    BOOST_TEST(repo.report() == expected_report);
}

// Test findBy
BOOST_AUTO_TEST_CASE(RepositoryTest_FindBy) {
    Repository<PackagePtr> repo;
    BoxSize size = std::make_tuple(2, 3, 4);
    auto package1 = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");
    auto package2 = make_shared<NormalPackage>("PKG456", 2.0, size, "SRC456", "DEST456");

    repo.add(package1);
    repo.add(package2);

    auto found_packages = repo.findBy([](const PackagePtr& p) {
        return p->get_weight() > 3.0;
    });

    BOOST_TEST(found_packages.size() == 1);
    BOOST_TEST(found_packages[0] == package1);
}

// Test foreach
BOOST_AUTO_TEST_CASE(RepositoryTest_Foreach) {
    Repository<PackagePtr> repo;
    BoxSize size = std::make_tuple(2, 3, 4);
    auto package1 = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");
    auto package2 = make_shared<NormalPackage>("PKG456", 2.0, size, "SRC456", "DEST456");

    repo.add(package1);
    repo.add(package2);

    vector<string> ids;
    repo.foreach([&ids](const PackagePtr& p) {
        ids.push_back(p->get_id());
    });

    BOOST_TEST(ids.size() == 2);
    BOOST_TEST(ids[0] == "PKG123");
    BOOST_TEST(ids[1] == "PKG456");
}

// Test findOneBy
BOOST_AUTO_TEST_CASE(RepositoryTest_FindOneBy) {
    Repository<PackagePtr> repo;
    BoxSize size = std::make_tuple(2, 3, 4);
    auto package1 = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");
    auto package2 = make_shared<NormalPackage>("PKG456", 2.0, size, "SRC456", "DEST456");

    repo.add(package1);
    repo.add(package2);

    auto found_package = repo.findOneBy([](const PackagePtr& p) {
        return p->get_weight() > 3.0;
    });

    BOOST_TEST(found_package == package1);
}

// Test findAll
BOOST_AUTO_TEST_CASE(RepositoryTest_FindAll) {
    Repository<PackagePtr> repo;
    BoxSize size = std::make_tuple(2, 3, 4);
    auto package1 = make_shared<NormalPackage>("PKG123", 5.0, size, "SRC123", "DEST123");
    auto package2 = make_shared<NormalPackage>("PKG456", 2.0, size, "SRC456", "DEST456");

    repo.add(package1);
    repo.add(package2);

    auto all_packages = repo.findAll();
    BOOST_TEST(all_packages.size() == 2);
    BOOST_TEST(all_packages[0] == package1);
    BOOST_TEST(all_packages[1] == package2);
}

BOOST_AUTO_TEST_SUITE_END()
