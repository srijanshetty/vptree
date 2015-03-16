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

#include "point.h"

// Stream processing
#include <iostream>
#include <fstream>

namespace VPTree {
#ifdef DISTANCE_MAHALONOBIS
    // Initialize the mahalonobis matrix
    std::vector< std::vector<double> > Point::mat;

    // Initialize the Mahalonobis matrix
    void Point::initializeMatrix() {
        std::ifstream ifile(MATRIXFILE);

        // read the matrix from file
        double coordinate;
        for (long long i = 0; i < DIMENSIONS; ++i) {
            std::vector<double> coordinates;
            for (long long j = 0; j < DIMENSIONS; ++j) {
                ifile >> coordinate;
                coordinates.push_back(coordinate);
            }
            mat.push_back(coordinates);
        }
    }
#endif

    // Initialize the comparisons in Metrics
    long long Metrics::comparisons = 0;

    // Print the point
    void Point::print() const {
        std::cout << "(";
        for (long long i = 0; i < DIMENSIONS; ++i) {
            std::cout << coordinates[i] << ",";
        }
        std::cout << "\b)";
    }

    // Compute the distance between this point and a provided point
    double Point::distance(const Point &otherPoint) const {
        Metrics::incrementComparisons();

        double componentDistance = 0;
#ifdef DISTANCE_EUCLIDEAN
        for (long long i = 0; i < DIMENSIONS; ++i) {
            componentDistance += (otherPoint.coordinates[i] - coordinates[i]) * (otherPoint.coordinates[i] - coordinates[i]);
        }
#endif

#ifdef DISTANCE_MAHALONOBIS
        componentDistance =
            mat[0][0] * (coordinates[0] - otherPoint.coordinates[0]) * (coordinates[0] - otherPoint.coordinates[0])
            + mat[1][1] * (coordinates[1] - otherPoint.coordinates[1]) * (coordinates[1] - otherPoint.coordinates[1])
            + (mat[0][1] + mat[1][0]) * (coordinates[0] - otherPoint.coordinates[0]) * (coordinates[1] - otherPoint.coordinates[1]);
#endif
        return sqrt(componentDistance);
    }
}
