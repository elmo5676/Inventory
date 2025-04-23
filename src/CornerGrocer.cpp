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
 * @brief Loads item frequency data from a file.
 * 
 * Reads each item from the provided file and increments its count in the
 * frequencyMap. Also writes the frequency data out to a file named 
 * "frequency.dat".
 *
 * @param filename Name of the input file to load.
 */
void CornerGrocer::loadData(const string& filename) {
    ifstream inFile(filename);
    string item;
    if (!inFile) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
    while (inFile >> item) {
        frequencyMap[item]++;
    }
    inFile.close();
    
    // Write frequency map to frequency.dat
    ofstream outFile("items/frequency.dat");
    for (map<string, int>::const_iterator it = frequencyMap.begin(); it != frequencyMap.end(); ++it) {
        outFile << it->first << " " << it->second << endl;
    }
    outFile.close();
}

/**
 * @brief Prints the frequency for the specified item inside a decorative box.
 *
 * Searches for the item in frequencyMap and prints the frequency. If the item is not found,
 * an appropriate message is printed.
 *
 * @param item The item to search for.
 */
void CornerGrocer::itemFrequency(const string& item) const {
    // Initialize message string for output.
    string message; 
    // Create a copy of the input item to modify its case.
    string fixedItem = item;
    
    // Capitalize the first letter if the string is not empty.
    if (!fixedItem.empty()) {
        fixedItem[0] = toupper(fixedItem[0]);
    }

    // Search for the item in the frequency map.
    map<string, int>::const_iterator it = frequencyMap.find(fixedItem);
    if (it != frequencyMap.end()) {
        // If found, prepare the display message with the item's frequency.
        message = fixedItem + ": " + to_string(it->second);
    } else {
        // If not found, prepare an appropriate message.
        message = fixedItem + " not found.";
    }
    
    // Calculate the padding size based on the message length.
    int pad = message.size() + 4;
    
    // Create a border string for the decorative box.
    string border = "+" + string(pad, '-') + "+";
    
    // Output the formatted decorative box with the message.
    cout << border << endl;
    cout << "|  " << message << "  |" << endl;
    cout << border << endl;
}

/**
 * @brief Prints all item frequencies in a formatted table.
 *
 * The table is displayed with column headers "Item" and "Qty", including a top border,
 * internal separators, and a bottom border.
 */
void CornerGrocer::printAllFrequencies() const {
    // Set the width for the "Item" column.
    const int widthItem = 20;
    // Set the width for the "Qty" column.
    const int widthQty = 5;
    
    // Construct the top and bottom border using dashes.
    string topBottomBorder = "+" + string(widthItem, '-') + "+" + string(widthQty, '-') + "+";
    
    // Print the top border of the table.
    cout << topBottomBorder << endl;
    
    // Print the header row with column titles "Item" and "Qty".
    cout << "|" << setw(widthItem) << left << "Item"
         << "|" << setw(widthQty) << left << "Qty" << "|" << endl;
    
    // Print the separator border after the header.
    cout << topBottomBorder << endl;
    
    // Loop through the frequencyMap to print each item's frequency.
    for (map<string, int>::const_iterator it = frequencyMap.begin(); it != frequencyMap.end(); ++it) {
        // Print each row: the item name and its frequency.
        cout << "|" << setw(widthItem) << left << it->first
             << "|" << setw(widthQty) << left << it->second << "|" << endl;
    }
    
    // Print the bottom border of the table.
    cout << topBottomBorder << endl;
}

/**
 * @brief Prints a histogram of items with their frequencies.
 * 
 * Displays the histogram in a table format with column headers "Item" and "Frequency". 
 * The frequency is visualized as a series of asterisks with a border surrounding the table.
 */
void CornerGrocer::printHistogram() const {
    // Set the width for the "Item" column.
    const int widthItem = 20;
    // Set the width for the "Frequency" column.
    const int widthFreq = 20;
    
    // Create the top and bottom border using the widths for both columns.
    string topBottomBorder = "+" + string(widthItem, '-') + "+" + string(widthFreq, '-') + "+";
    
    // Print the top border of the histogram table.
    cout << topBottomBorder << endl;
    
    // Print the header row with column titles "Item" and "Frequency".
    cout << "|" << setw(widthItem) << left << "Item"
         << "|" << setw(widthFreq) << left << "Frequency" << "|" << endl;
    
    // Print the border below the header.
    cout << topBottomBorder << endl;
    
    // Iterate over each item frequency in the frequencyMap.
    for (map<string, int>::const_iterator it = frequencyMap.begin(); it != frequencyMap.end(); ++it) {
        string stars;
        
        // Build a string of asterisks representing the frequency of the item.
        for (int i = 0; i < it->second; ++i) {
            stars.push_back('*');
        }
        
        // Print a row with the item name and its corresponding frequency visualized as stars.
        cout << "|" << setw(widthItem) << left << it->first
             << "|" << setw(widthFreq) << left << stars << "|" << endl;
    }
    
    // Print the bottom border of the histogram table.
    cout << topBottomBorder << endl;
}

/**
 * @brief Runs the Corner Grocery Inventory System.
 *
 * This method manages the entire program flow. It handles command-line file input,
 * prompts the user for a file name if none is provided or if the provided file cannot be opened,
 * loads the inventory data, and initiates a menu-driven interface that allows the user to:
 * 
 * 1 - Search for an item’s frequency.
 * 
 * 2 - Print all item frequencies.
 * 
 * 3 - Print a histogram of item frequencies.
 * 
 * 4 - Exit the program.
 *
 * @param argc The number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void CornerGrocer::run(int argc, char* argv[]) {
    string filename;
    // Check if a filename was provided via command-line arguments.
    if (argc > 1) {
        filename = argv[1];
    } else {
        bool validFile = false;
        // Loop until a valid filename is provided or default is chosen.
        do {
            cout << "Place the file in the Project_3 main folder and" << endl;
            cout << "enter the input file name or leave blank to use" << endl;
            cout << "the default file (\"CS210_Project_Three_Input_File.txt\"): ";
            getline(cin, filename);
            ifstream testFile(filename);
            // If the file opens successfully, mark as valid.
            if (testFile.good()) {
                validFile = true;
                testFile.close();
            } else if (filename.empty()) {
                // If blank, use the default file.
                filename = "items/CS210_Project_Three_Input_File.txt";
                validFile = true;
            } else {
                // If file cannot be opened, prompt user for options.
                cout << "Error: cannot open file \"" << filename << "\"." << endl;
                cout << "Enter 1 to try again or 2 to use the default file (\"CS210_Project_Three_Input_File.txt\"): ";
                int option;
                cin >> option;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (option == 2) {
                    // Use the default file if user selects option 2.
                    filename = "items/CS210_Project_Three_Input_File.txt";
                    validFile = true;
                }
            }
        } while (!validFile);
    }

    // Load inventory data from the provided or default file.
    loadData(filename);

    int choice;
    string item;
    // Main menu loop: continue until user chooses to exit.
    do {
        const int boxWidth = 44;
        // Create a border line for the menu.
        string border = "+" + string(boxWidth - 2, '-') + "+";
        cout << "\n" << border << "\n";
        string menuStr = "MENU";
        int insideWidth = boxWidth - 2;
        // Calculate padding for centering the menu title.
        int leftPad = (insideWidth - menuStr.size()) / 2;
        int rightPad = insideWidth - menuStr.size() - leftPad;
        // Display Menu title in a decorative box.
        cout << "|" << string(leftPad, ' ') << menuStr << string(rightPad, ' ') << "|\n";
        cout << border << "\n";
        // Display menu options.
        cout << "| " << left << setw(boxWidth - 4) << "1. Search item frequency" << " |\n";
        cout << "| " << left << setw(boxWidth - 4) << "2. Print all item frequencies" << " |\n";
        cout << "| " << left << setw(boxWidth - 4) << "3. Print histogram" << " |\n";
        cout << "| " << left << setw(boxWidth - 4) << "4. Exit" << " |\n";
        cout << border << "\n";
        cout << "Enter choice: ";
        
        // Validate user input.
        if (!(cin >> choice)) {
            cin.clear(); // Clear error flag if non-numeric input was provided.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard input.
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
            continue;
        }
        
        // Process user's menu choice using a switch-case statement.
        switch (choice) {
            case 1:
                // Option 1: prompt the user for an item to search for.
                cout << "Enter item to search: ";
                cin >> item;
                itemFrequency(item); // Display frequency of the given item.
                break;
            case 2:
                // Option 2: print all item frequencies in a formatted table.
                printAllFrequencies();
                break;
            case 3:
                // Option 3: display a histogram of item frequencies.
                printHistogram();
                break;
            case 4:
                // Option 4: exit the application.
                cout << "Exiting..." << endl;
                break;
            default:
                // Default case: handle invalid menu selections.
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    } while (choice != 4); // Continue loop until user chooses to exit.
};


