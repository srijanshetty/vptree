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

// Configuration paramters
#define DIMENSIONS 2
#define DISTANCE_EUCLIDEAN
// #define DISTANCE_MAHALONOBIS

// Standard containers
#include <vector>

// Math functions
#include <math.h>

namespace VPTree {
    class Point {
        private:
            // Store the number of comparisons
            static long long comparisons;

            // Update the number of comparisons
            void incrementComparisons() { ++comparisons; }

        public:
            // Return the number of euclidean comparisons
            long long getComparisons() const { return comparisons; }

        private:
            std::vector <double> coordinates;

        public:
            Point(std::vector<double> _coordinates) : coordinates(_coordinates) {};

            // Compute the Euclidean distance to another point
            double Euclidean(std::vector<double> point) const;

            // Compute the Mahalonobis distance to a point
            double Mahalonobis(std::vector<double> point) const;

            // Compute the distance between this point and a provided point
            double distance(std::vector<double> point);
    };
}
