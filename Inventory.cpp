/******************************************************************************
* SNHU Computer Science
* Class: CS-210 Programming Languages
* Author: Matthew Elmore
* Date: 2025-04-22
* 
* Assignment: Project 3
* Description: Corner grocery store inventory system.
* It reads item names from a file, counts their occurrences, and allows the user
* to search for specific items, print all item frequencies, and display a histogram
* of item frequencies. The data is stored in a map for efficient access and
* manipulation. All functionality is encapsulated within the CornerGrocer class.
*
* Language: C++
******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <limits>
#include "CornerGrocer.h"

using namespace std;

/**
 * @brief Program entry point.
 *
 * Creates a CornerGrocer object and calls its Run() method to
 * handle the complete application flow.
 *
 * @param argc The number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return int Exit status code (0 indicates success).
 */
int main(int argc, char* argv[]) {
    CornerGrocer grocer;
    grocer.run(argc, argv);
    return 0;
}
