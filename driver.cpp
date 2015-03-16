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

// For timing
#include <chrono>

using namespace std;
using namespace VPTree;

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

        if (query == 2) {
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
#ifdef DISTANCE
            cout << query << " ";
            Metrics::resetComparisons();
#endif

            // rangeSearch
            root->rangeSearch(point, range * 1.0);
#ifdef TIME
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            cout << microseconds << endl;
#endif

#ifdef DISTANCE
            cout << Metrics::getComparisons() << endl;
#endif
        } else if (query == 3) {
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
#ifdef DISTANCE
            cout << query << " ";
            Metrics::resetComparisons();
#endif
            // kNNSearch
            root->kNNSearch(point, k);
#ifdef TIME
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            cout << microseconds << endl;
#endif

#ifdef DISTANCE
            cout << Metrics::getComparisons() << endl;
#endif
        }
    }

    // Close the file
    ifile.close();
}

int main() {
#ifdef DISTANCE_MAHALONOBIS
    // Intialize the Mahalonobis matrix
    Point::initializeMatrix();
#endif

    // Build the tree using the points
    Node *VPRoot = new Node();
    buildTree(VPRoot);

    // Process the queries
    processQuery(VPRoot);

    return 0;
}
