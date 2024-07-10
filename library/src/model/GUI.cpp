//
// Created by patryk on 6/11/24.
//

#include "GUI.h"

#include <BaseError.h>
#include <ncurses.h>
#include <NormalPackage.h>
#include <numeric>
#include <PackageLocker.h>

#define SEP "======================================================================================================"
#define endl "\n\r"

GUI::GUI(PackageSystemPtr system) : _system(system){
}

void GUI::print_all_packages() {
    for (const auto& package: _system->get_all_packages()) {
        std::cout << package->get_info() << "\n\r";
    }
}

void GUI::print_package_info(const std::string& id) {
    cout << _system->get_package(id)->get_info();
}


void GUI::print_all_package_lockers() {
    std::cout << SEP << endl;
    for (const auto& locker: _system->get_all_package_lockers()) {
        std::cout << locker->get_info() << endl;
        std::cout << locker->describe_content() << endl;
        std::cout << SEP << endl;
    }
}


void GUI::clear() {
    system("clear");
}

void GUI::print_search_for_package_by_id() {
    endwin();
    clear();
    string package_id;
    cout << " === Searching for package ===" << endl;
    cout << "(*) Enter package id: " << endl;
    cin >> package_id;
    clear();
    try {
        PackagePtr package = _system->get_package(package_id);
        cout <<  SEP << endl;
        cout << "Found: " << endl;
        cout << package->get_info() << endl;
        cout <<  SEP << endl;
    } catch (const BaseError& e) {
        cout << "Error: " << e.what() << endl;
    }
    cin.get();
    initscr();
    cbreak();
    noecho();
}

void GUI::receive_package_prompt() {
    endwin();
    clear();
    string package_id;
    cout << " === Receiving package ===" << endl;
    cout << "(*) Enter package id: " << endl;
    cin >> package_id;
    clear();
    try {
        _system->receive_package(package_id);
        cout <<  SEP << endl;
        cout << "Success! " << endl;
        cout << _system->get_package(package_id)->get_info() << endl;
        cout <<  SEP << endl;
    } catch (const BaseError& e) {
        cout << "Error: " << e.what() << endl;
    }
    cin.get();
    initscr();
    cbreak();
    noecho();
}

void GUI::cancel_package_prompt() {
    endwin();
    clear();
    string package_id;
    cout << " === Canceling package ===" << endl;
    cout << "(*) Enter package id: " << endl;
    cin >> package_id;
    clear();
    try {
        _system->cancel_package(package_id);
        cout <<  SEP << endl;
        cout << "Success! " << endl;
        cout << _system->get_package(package_id)->get_info() << endl;
        cout <<  SEP << endl;
    } catch (const BaseError& e) {
        cout << "Error: " << e.what() << endl;
    }
    cin.get();
    initscr();
    cbreak();
    noecho();
}

void GUI::create_package_prompt() {
    endwin();
    clear();
    string pkg_id;
    double weight;
    BoxSize size;
    string lck_destination_id;
    string lck_source_id;


    clear();
    try {
        cout << " === Creating package ===" << endl;
        cout << "(*) Enter package id: " << endl << "\t- ";
        cin >> pkg_id;
        cout << "(*) Enter weight: " << endl << "\t- ";
        cin >> weight;
        cout << "(*) Enter size (x, y, z), confrm each value by pressing enter: " << endl << "\t- ";
        cin >> std::get<0>(size);
        cout << "\t- ";
        cin >> std::get<1>(size);
        cout << "\t- ";
        cin >> std::get<2>(size);
        auto available_lockers = _system->get_all_package_lockers();
        string available_lockers_as_str;
        for (const auto& lck: available_lockers)
            available_lockers_as_str += lck->get_id()
            + " - " + lck->get_location()
            + " - free space: " + to_string(lck->get_max_size() - lck->get_package_count()) + endl;
        cout << "(*) Enter destination locker id: " << endl;
        cout << "Available lockers:  " << endl << available_lockers_as_str << endl << "\t- ";
        cin >> lck_destination_id;
        cout << "(*) Enter source locker id: " << endl;
        cout << "Available lockers:  " << endl << available_lockers_as_str << endl << "\t- ";
        cin >> lck_source_id;

        auto pkg = make_shared<NormalPackage>(pkg_id, weight, size, lck_source_id, lck_destination_id);
        _system->send_package(pkg);
        cout <<  SEP << endl;
        cout << "Success! " << endl;
        cout << _system->get_package(pkg_id)->get_info() << endl;
        cout <<  SEP << endl;
    } catch (const BaseError& e) {
        cout << "Error: " << e.what() << endl;
    }
    cin.get();
    initscr();
    cbreak();
    noecho();
}

GUI::~GUI() {
}


void GUI::show() {
    initscr();
    cbreak();
    noecho();
    while (true) {
        char c = getch();
        clear();
        switch (c) {
            case 'e':
                endwin();
                return;
            case 'p':
                print_all_packages();
                break;
            case 'l':
                print_all_package_lockers();
                break;
            case 'd':
                _system->delivery_iteration();
                print_all_package_lockers();
                break;
            case 'f':
                print_search_for_package_by_id();
                break;
            case 'c':
                cancel_package_prompt();
                break;
            case 'r':
                receive_package_prompt();
                break;
            case 'a':
                create_package_prompt();
                break;
            case 'h':
                cout <<
                   "* press p to view all packages" << endl
                   "* press l to view all lockers with its content" << endl
                   "* press d to execute delivery on all packages" << endl
                   "* press f to search for package" << endl
                   "* press r to receive package" << endl
                   "* press a to create package" << endl
                   "* press e to exit" << endl;
                cin.get();
                break;
            default:
                break;

        }
    }
}
