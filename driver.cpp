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

// Stream processing
#include <iostream>
#include <fstream>

// Limits of numbers
#include <limits>

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

        if (objectID % 100 == 0) {
            cout << endl << "Inserting " << objectID << " ";
        }

        // Insert the object into file
        root->insert(DBObject(objectID, dataString, point), 0.0);
    }

    // Close the file
    ifile.close();
}

int main() {
    // Test points
    vector<double> p1 = {1.0, 0.0};
    vector<double> p2 = {4.0, 0.0};

    Point alpha(p1);
    Point beta(p2);

    // cout << alpha.distance(beta);

    // test objects
    DBObject obj(0, "srijan", p1);

    // Test the insertion routine
    Node *VPRoot = new Node(numeric_limits<double>::max(), obj);
    buildTree(VPRoot);

    // Print tree
    VPRoot->print();

    return 0;
}
