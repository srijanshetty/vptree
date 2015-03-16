/*
 * Copyright (c) 2015 <name of copyright holder>
 * Author: Srijan R Shetty <srijan.shetty+code@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

// Include the VPTree library
#include "vptree.h"

// STL
#include <queue>

// Stream processing
#include <iostream>
#include <fstream>

// Limits of numbers
#include <limits>

using namespace std;
using namespace VPTree;

// Print the tree recursively
void printRecursive(const Node *root) {
    // Prettify
    std::cout << std::endl << std::endl;

    // To store the previous Level
    std::queue< std::pair<const Node*, char> > previousLevel;
    previousLevel.push(std::make_pair(root, 'N'));

    // To store the leaves
    std::queue< std::pair<DBObject, char> > leaves;

    while (!previousLevel.empty()) {
        std::queue< std::pair<const Node*, char> > nextLevel;

        while (!previousLevel.empty()) {
            // Get the front and pop
            const Node *iterator = previousLevel.front().first;
            char type = previousLevel.front().second;
            previousLevel.pop();

            // If it a seperator, print and move ahead
            if (type == '|') {
                std::cout << " || ";
                continue;
            }

            // Print the MBR
            iterator->getObjectPoint().print();

            if (!iterator->isLeaf()) {
                // Push the leftSubtree
                if (iterator->leftNode != nullptr) {
                    nextLevel.push(std::make_pair(iterator->leftNode, 'N'));

                    // Insert a marker to indicate end of child
                    nextLevel.push(std::make_pair(nullptr, '|'));
                }

                // Push the rightSubtree
                if (iterator->rightNode != nullptr) {
                    nextLevel.push(std::make_pair(iterator->rightNode, 'N'));

                    // Insert a marker to indicate end of child
                    nextLevel.push(std::make_pair(nullptr, '|'));
                }
            } else {
                // Add all child points to the leaf
                for (auto child: iterator->objectCache) {
                    // leaves.push(std::make_pair(child, 'L'));
                }

                // marker for end of leaf
                // leaves.push(std::make_pair(DBObject(), '|'));

            }

            // Delete allocated memory
            delete iterator;
        }

        // Seperate different levels
        std::cout << std::endl << std::endl;
        previousLevel = nextLevel;
    }

    // Print all the leaves
    while (!leaves.empty()) {
        // Get the front and pop
        DBObject obj = leaves.front().first;
        char type = leaves.front().second;
        leaves.pop();

        // If it a seperator, print and move ahead
        if (type == '|') {
            std::cout << " || ";
            continue;
        }

        // Print the MBR
        obj.print(); std::cout << " | ";
    }

    // Prettify
    std::cout << std::endl << std::endl;
}


// Build the tree from reading the DATAFILE
void buildTree(Node *root) {
    ifstream ifile;
    ifile.open(DATAFILE, ios::in);

    // Items to read from the file
    vector <double> point;
    double coordinate;
    string dataString;
    long long objectID;

    while (!ifile.eof()) {
        // Get the point
        point.clear();
        for (long i = 0; i < DIMENSIONS; ++i) {
            ifile >> coordinate;
            point.push_back(coordinate);
        }

        // Get the objectID and the dataString
        ifile >> objectID >> dataString;

        // Some quirk which needs to be handled
        if (ifile.eof()) {
            break;
        }

        if (objectID % 10000 == 0) {
            cout << endl << "Inserting " << objectID << " ";
        }

        // Insert the object into file
        root->insert(DBObject(objectID, dataString, point));
    }

    // Close the file
    ifile.close();
}

void processQuery(Node *root) {
    ifstream ifile;
    ifile.open(QUERYFILE, ios::in);

    long query;

    // Loop over the entire file
    while (ifile >> query) {
        // Get the point from the file
        vector <double> coordinates;
        double coordinate;
        for (long i = 0; i < DIMENSIONS; ++i) {
            ifile >> coordinate;
            coordinates.push_back(coordinate);
        }
        Point point(coordinates);

#ifdef OUTPUT
            cout << endl << query << " ";
            point.print();
#endif

        if (query == 1) {
            // Get the range
            double range;
            ifile >> range;

#ifdef OUTPUT
            cout << " " << range << endl;
#endif

#ifdef TIME
            cout << query << " ";
            auto start = std::chrono::high_resolution_clock::now();
#endif
            // rangeSearch
            root->rangeSearch(point, range * 1.0);
#ifdef TIME
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            cout << microseconds << endl;
#endif
        } else if (query == 2) {
            // Get the number of points
            long k;
            ifile >> k;

#ifdef OUTPUT
            cout << " " << k << endl;
#endif

#ifdef TIME
            cout << query << " ";
            auto start = std::chrono::high_resolution_clock::now();
#endif
            // kNNSearch
            // root->kNNSearch(point, k);
#ifdef TIME
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            cout << microseconds << endl;
#endif
        }
    }

    // Close the file
    ifile.close();
}

int main() {
    // Test the insertion routine
    vector<double> p1 = {0.0, 0.0};
    DBObject obj(0, "srijan", p1);
    Node *VPRoot = new Node(numeric_limits<double>::max(), obj);
    buildTree(VPRoot);

    // VPRoot->printRecursive();

    vector<double> p2 = {0.0, 0.0};
    VPRoot->rangeSearch(p1, 10);

    return 0;
}
