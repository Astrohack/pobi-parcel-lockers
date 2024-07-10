
#include <functional>

#include "memory"

class InsuranceClass;
class PackageLocker;
class Package;
class PackageSystem;


typedef std::shared_ptr<PackageLocker> PackageLockerPtr;

typedef std::shared_ptr<Package> PackagePtr;

typedef std::shared_ptr<PackageSystem> PackageSystemPtr;

typedef std::shared_ptr<InsuranceClass> InsuranceClassPtr;

typedef std::weak_ptr<PackageLocker> PackageLockerWeakPtr;

typedef std::weak_ptr<Package> PackageWeakPtr;

typedef std::weak_ptr<PackageSystem> PackageSystemWeakPtr;


template<class T>
using Predicate = std::function<bool(const T&)> ;

template<class T>
using PredicateVoid = std::function<void(const T&)>;

typedef std::tuple<int, int, int> BoxSize;
