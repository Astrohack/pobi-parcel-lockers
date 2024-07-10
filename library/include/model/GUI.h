//
// Created by patryk on 6/11/24.
//

#ifndef GUI_H
#define GUI_H
#include <iostream>
#include <PackageSystem.h>

using namespace std;

/**
 * @brief Allows printing application state to console
 */
class GUI {
    PackageSystemPtr _system;
public:
    GUI(PackageSystemPtr system);

    /**
     * @brief Print to console all packages in system
     */
    void print_all_packages();

    /**
     * Print to console info about package for given id
     * @param id
     */
    void print_package_info(const std::string& id);

    /**
     * Print to console all package lockers in system
     */
    void print_all_package_lockers();

    /**
     * Clear console screen
     */
    void clear();
      /**
      * Search and print to console package by id
      */
    void print_search_for_package_by_id();

     /**
      * Receive package prompt
      */
    void receive_package_prompt();

     /**
     * Cancel package prompt
     */
    void cancel_package_prompt();

    /**
     * Ask user for data, create and send package
     */
    void create_package_prompt();

    ~GUI();

    /**
     * Render menu,
     * press "p" to view all packages
     * press "l" to view all lockers with its content
     * press "d" to execute delivery on all packages
     * press "f" to search for package
     * press "r" to receive package
     * press "a" to create package
     * press "e" to exit
     */
    void show();
};



#endif //GUI_H
