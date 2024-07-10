#include <HazardousPackage.h>
#include <InsuredPackage.h>
#include <memory>
#include <NormalPackage.h>
#include <PackageLocker.h>
#include <PackageSystem.h>

#include "GUI.h"

namespace pt = boost::posix_time;

int main() {
    PackageSystemPtr system = make_shared<PackageSystem>();
    PackageLockerPtr locker_pab = std::make_shared<PackageLocker>("A", "Pabianice", 6);
    system->register_locker(locker_pab);

    PackageLockerPtr locker_lodz = std::make_shared<PackageLocker>("B", "Łódź", 6);
    system->register_locker(locker_lodz);

    PackagePtr package0 = std::make_shared<NormalPackage>("p0", 10.1, BoxSize(10,10,11), "A", "B");
    PackagePtr package1 = std::make_shared<HazardousPackage>("p1", 10.1, BoxSize(10,10,11), "A", "B", "radioactive waste");
    PackagePtr package2 = std::make_shared<InsuredPackage>("p2", 10.1, BoxSize(19,10,11), "A", "B", std::make_shared<Premium>());
    PackagePtr package3 = std::make_shared<NormalPackage>("p3", 30.1, BoxSize(10,10,11), "B", "A");

    system->send_package(package0);
    system->send_package(package1);
    system->send_package(package2);
    system->send_package(package3);

    GUI gui(system);

    gui.show();

    return 0;
}
