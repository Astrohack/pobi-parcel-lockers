This project is a C++ application developed using CMake, created for the Object-Oriented Programming course. The application simulates the operation of parcel lockers, providing a text-based menu for various parcel locker operations.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [Testing](#documentation)
- [License](#license)

## Overview
The Parcel Locker Simulation application allows users to simulate basic operations of a parcel locker system. Users can add or remove parcel lockers, add or remove parcels, send parcels to a locker, and collect parcels from lockers. Additionally, the application includes a delivery simulation feature, which updates parcel statuses and transfers them to the appropriate lockers based on their current status.

## Features
- Add a new parcel locker
- Remove an existing parcel locker
- Add a new parcel to the system
- Remove a parcel from the system
- Send a parcel to a designated locker
- Collect a parcel from a locker
- Simulate parcel delivery, updating statuses and locations
- Unit tests for each class

## Requirements
- CMake 3.10 or higher
- C++17 compatible compiler
- Curses library (ncurses-devel)
- Boost 1.60 unit_test_framework

## Installation
1. Clone the repository:
    ```sh
    git clone https://github.com/Astrohack/pobi-parcel-lockers.git
    cd pobi-parcel-lockers
    ```

2. Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3. Generate the build files using CMake:
    ```sh
    cmake ..
    ```

4. Build the project:
    ```sh
    make
    ```

## Usage
After building the project, you can run the application from the build directory:
```sh
./program/Program
```

## The application provides a text-based menu with the following options:
- Add a new parcel locker
- Remove an existing parcel locker
- Add a new parcel
- Remove an existing parcel
- Send a parcel to a locker
- Collect a parcel from a locker
- Simulate delivery

Follow the on-screen instructions to perform each operation.
## Testing

Unit tests are provided for each class in the project. There is dedicated test target in cmake conf:

```sh
make check
```
Then run the tests from the build directory.

## Documentation

Documentation can be generated with doxygen cmake target.
Build docs from the build directory using:

```sh
make doc
```
## License

This project is licensed under the [MIT License](LICENSE) .