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

namespace VPTree {
    // Compute the Euclidean distance to a point
    double Point::Euclidean(std::vector<double> point) const {
        double distance = 0;
        for (long long i = 0; i < DIMENSIONS; ++i) {
            distance += (point[i] - coordinates[i]) * (point[i] - coordinates[i]);
        }
        return sqrt(distance);
    }

    // Compute the Mahalonobis distance to a point
    double Point::Mahalonobis(std::vector<double> point) const {
        return Euclidean(point);
    }

    // Compute the distance between this point and a provided point
    double Point::distance(std::vector<double> point) {
        // Update the distance counter
        Point::incrementComparisons();

#ifdef DISTANCE_EUCLIDEAN
        // Call the distance function
        return Euclidean(point);
#endif

#ifdef DISTANCE_MAHALONOBIS
        // Call the distance function
        return Mahalonobis(point);
#endif
    }

    // Setup the static variables
    long long Point::comparisons = 0;
}
