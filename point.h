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

// Configuration parameters
#include "config.h"

// Standard containers
#include <vector>

// Math functions
#include <math.h>

namespace VPTree {
    class Metrics {
        private:
            static long long comparisons;

        public:
            // Increment the number of comparisons
            static void incrementComparisons() { ++comparisons; }

            // Reset the counter
            static void resetComparisons() { comparisons = 0; }

            // Print the comparisons
            static long long getComparisons() { return comparisons; }
    };

    class Point {
        public:
            // The coordiantes of the point
            std::vector <double> coordinates = std::vector<double>(DIMENSIONS, 0.0);

        public:
            // The default constructor
            Point() { };

            // The standard constructor
            Point(std::vector<double> _coordinates) : coordinates(_coordinates) { };

            // Compute the distance between this point and a provided point
            double distance(const Point &otherPoint) const;

            // Print the point
            void print() const;
    };
}
