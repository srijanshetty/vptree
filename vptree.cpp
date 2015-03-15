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

// Include the header file
#include "vptree.h"

// Stream processing
#include <fstream>

// STL Algorithm
#include <algorithm>

// Math
#include <limits>

namespace VPTree {
    // Compute distance from root
    double Node::distance(const DBObject &targetObject) const {
        if (!isLeaf()) {
            return object.distance(targetObject);
        } else {
            return std::numeric_limits<double>::max();
        }
    }

    // Print the node
    void Node::print()  {
        // Print the object
        std::cout << std::endl << "Object: ";
        object.print();

        // Print the cache
        std::cout << std::endl << "Cache: ";
        for (auto object : objectCache) {
            std::cout << "\t";
            object.print();
            std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;

        // Print the leftNode
        if (leftNode != nullptr) {
            std::cout << std::endl << "\tLeftNode: ";
            leftNode->object.print();
        }

        // Print the rightNode
        if (rightNode != nullptr) {
            std::cout << std::endl << "\tRightNode: ";
            rightNode->object.print();
        }
    }

    /* Split the node according to the media */
    void Node::split() {
        /* We have to split the current node into three nodes, a parent and two children
           the nodes in cache as the sample */
    }

    /* Insert a point into the VPTree */
    void Node::insert(DBObject object) {
        // Check if the root is a leaf
        if (isLeaf()) {
            /* Directly insert the object into the root's cache and then split if
               we've reached the sample size limit */
            objectCache.push_back(object);

            if (getCacheSize() > SAMPLE_SIZE) {
                split();
            }
        } else {
            /* Compute the distance of the object from the root and insert into the correct subtree */
            double objectDistance = distance(object);

            /* It will never be the case that one of the subtrees is empty, this is because we sample
               the objects and then split according to the median, this gurantees that half the nodes
               will go to one side and the rest on the other */
            if (objectDistance < radius) {
                leftNode->insert(object);
            } else {
                rightNode->insert(object);
            }
        }
    }
}
