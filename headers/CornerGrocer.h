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

#ifndef CORNERGROCER_H_
#define CORNERGROCER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <limits>

/**
 * @class CornerGrocer
 * @brief Manages a collection of items with their frequencies and handles all
 *        user interactions including file input and menu-driven processing.
 */
class CornerGrocer {
private:
    /// Map storing item as key and its frequency as value.
    std::map<std::string, int> frequencyMap;

public:
    void loadData(const std::string& filename);
    void itemFrequency(const std::string& item) const;
    void printAllFrequencies() const;
    void printHistogram() const;
    void run(int argc, char* argv[]);
};

#endif