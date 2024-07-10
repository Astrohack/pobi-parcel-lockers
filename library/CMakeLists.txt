cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
        include/repositories/Repository.h
        src/model/Package.cpp
        src/model/PackageLocker.cpp
        src/model/PackageSystem.cpp
        src/model/InsuredPackage.cpp
        src/model/NormalPackage.cpp
        src/model/HazardousPackage.cpp
        src/managers/PackageManager.cpp
        src/managers/PackageLockerManager.cpp
        src/model/InsuranceClass.cpp
        include/model/InsuranceClass.h
        src/model/GUI.cpp
        include/model/GUI.h
)

add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
target_include_directories(Library PUBLIC include/model)
target_include_directories(Library PUBLIC include/repositories)
target_include_directories(Library PUBLIC include/managers)
target_include_directories(Library PUBLIC include/exceptions)

enable_testing()
find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIRS} )
target_link_libraries( Library ${CURSES_LIBRARIES} )

find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

find_package (Boost 1.60.0 COMPONENTS "date_time" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        test/master.cpp
        src/model/Package.cpp
        src/model/PackageLocker.cpp
        src/model/PackageSystem.cpp
        src/model/InsuredPackage.cpp
        src/model/NormalPackage.cpp
        src/model/HazardousPackage.cpp
        src/managers/PackageManager.cpp
        src/managers/PackageLockerManager.cpp
        include/repositories/Repository.h
        src/repositories/Repository.cpp

        test/PackageTest.cpp
        test/PackageLockerTest.cpp
        test/PackageSystemTest.cpp
        src/model/InsuranceClass.cpp
        test/RepositoryTest.cpp
        test/PackageLockerManagerTest.cpp
        test/PackageManagerTest.cpp
        test/InsuredPackageTest.cpp

)

add_executable (LibraryTester ${SOURCE_TEST_FILES})

target_link_libraries (
        LibraryTester
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_test(LibraryTest LibraryTester
        --report_level=detailed
        --log_level=all
        --color_output=yes
)
