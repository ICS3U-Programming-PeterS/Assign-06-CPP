// Copyright (c) 2022 Peter Sobowale All rights reserved.
//
// Created by: Peter Sobowale
// Created on: December 25, 2022
// This program reads a list of elements from a text file
// or gets the input from user. Then splits it in the
// middle and stores the elements in two different lists
// using pass by reference
#include <cmath>     // for ceil
#include <fstream>   // for ifstream
#include <iostream>  // for cout, cin, and endl
#include <list>      // for list
#include <sstream>
#include <string>  // for string



// function to split the list in the middle
void SplitList(std::list<std::string> lst,
std::list<std::string> firstHalf, std::list<std::string> secondHalf) {
    // calculate the middle index of the list
    float middle = lst.size() / 2.0;  // keep as a float
    middle = ceil(middle);            // round up to the nearest integer

    // iterate over the first half of the list
    // aappend the elements to the firstHalf list
    for (int i = 0; i < middle; i++) {
        auto it = lst.begin();
        std::advance(it, i);
        firstHalf.push_back(*it);
    }

    // iterate over the second half of the list
    // append the elements to the secondHalf list
    for (int i = middle; i < lst.size(); i++) {
        auto it = lst.begin();
        std::advance(it, i);
        secondHalf.push_back(*it);
    }
}

int main() {
    // prompt the user
    std::cout << "This program reads a list of elements from a "
              << "text file or gets the input from user. Then splits"
              << " it in the middle and stores the elements in two "
              << "different lists using pass by reference\n"
              << std::endl;

    // ask the user whether they want to input the list or read it from a file
    std::string fileInput;
    std::cout << "Do you want to input or read from a file (Input, File): ";
    std::cin >> fileInput;

    // if the user wants to read from a file
    if (fileInput == "File" || fileInput == "file") {
        try {
            // open the file in read mode
            std::ifstream f("test.txt");
            // read the first line of the file
            std::string listString;
            std::getline(f, listString);
            // split the line into a list of numbers
            std::list<std::string> lst;
            std::string num;
            std::stringstream ss(listString);
            while (ss >> num) {
                lst.push_back(num);
            }

            // create empty lists to store the two halves of the list
            std::list<std::string> half1;
            std::list<std::string> half2;

            // call the SplitList function to split the list in the middle
            SplitList(lst, half1, half2);

            // calculate the middle index of the list
            float middle = lst.size() / 2.0;
            middle = ceil(middle);            // round up to the nearest integer

            // print the two halves of the list
            std::cout << "First half: [";
            for (int i = 1; i < middle; i++) {
                auto it = lst.begin();
                std::advance(it, i);
                std::cout << i << ", ";
            }
            std::cout << half1.back() << "]" << std::endl;

            std::cout << "Second half: [";
            for (int i = middle + 1; i < lst.size(); i++) {
                auto it = lst.begin();
                std::advance(it, i);
                std::cout << i << ", ";
            }
            std::cout << half2.back() << "]" << std::endl;


            // close the file
            f.close();
        } catch (...) {
            std::cout << "There was an error reading the file." << std::endl;
        }
    } else {  // if the user wants to input or they just input incorrectly
        // get list of numbers
        std::string listString, num, extra;
        std::list<std::string> lst;
        std::cout << "Enter a list of elements (separated by spaces): ";
        std::cin >> listString;
        // Read the entire line of input (including spaces)
        try {
            std::getline(std::cin, extra);

            listString += extra;

            // Use a stringstream to parse the input string
            std::stringstream stream(listString);

            // Extract integers from the stream until there are none left
            while (stream >> num) {
                // Add the extracted integer to the list
                lst.push_back(num);
            }

            // Check the status of the stream
            if (!stream.eof()) {
                // Message for invalid input
                std::cout << "Error parsing the list" << std::endl;
                return 1;
            }

            // create empty lists to store the two halves of the list
            std::list<std::string> half1;
            std::list<std::string> half2;

            // call the SplitList function to split the list in the middle
            SplitList(lst, half1, half2);


            // print the two halves of the list
            std::cout << "First half: [";
            std::string z = half1.back();
            half1.pop_back();

            for (std::string x : half1) {
                std::cout << "'" << x << "', ";
            }
            std::cout << "'" << z << "']" << std::endl;


            std::cout << "Second half: [";
            z = half2.back();
            half2.pop_back();

            for (std::string x : half2) {
                std::cout <<"'" << x << "', ";
            }
            std::cout << "'" << z << "']" << std::endl;
        } catch (...) {
            std::cout << "Error parsing the list" << std::endl;
        }
    }
}
