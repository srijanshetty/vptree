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
#include <queue>

// Math
#include <limits>
#include "statistics.cpp"

namespace VPTree {
    // Compute distance of an DBObject from root
    double Node::distance(const DBObject &targetObject) const {
        if (!isLeaf()) {
            return nodeObject.distance(targetObject);
        } else {
            return std::numeric_limits<double>::max();
        }
    }

    // Compute the distance of a Point from the root
    double Node::distance(const Point &point) const {
        if (!isLeaf()) {
            return nodeObject.distance(point);
        } else {
            return std::numeric_limits<double>::max();
        }
    }

    // Print the node
    void Node::print()  {
        // Print the object
        std::cout << std::endl << "Object: ";
        nodeObject.print();

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
            std::cout << std::endl << "LeftSubtree: ";
            leftNode->nodeObject.print();
        }

        // Print the rightNode
        if (rightNode != nullptr) {
            std::cout << std::endl << "RightSubtree: ";
            rightNode->nodeObject.print();
        }
    }

    // Print the tree recursively
    void Node::printRecursive() {
        // Prettify
        std::cout << std::endl << std::endl;

        // To store the previous Level
        std::queue< std::pair<Node*, char> > previousLevel;
        previousLevel.push(std::make_pair(this, 'N'));

        // To store the leaves
        std::queue< std::pair<DBObject, char> > leaves;

        Node *iterator;
        char type;
        while (!previousLevel.empty()) {
            std::queue< std::pair<Node*, char> > nextLevel;

            while (!previousLevel.empty()) {
                // Get the front and pop
                iterator = previousLevel.front().first;
                type = previousLevel.front().second;
                previousLevel.pop();

                // If it a seperator, print and move ahead
                if (type == '|') {
                    std::cout << " || ";
                    continue;
                }

                // Print the MBR
                iterator->nodeObject.print();

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
                        leaves.push(std::make_pair(child, 'L'));
                    }

                    // marker for end of leaf
                    leaves.push(std::make_pair(DBObject(), '|'));

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
            type = leaves.front().second;
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

    /* Split the node according to the media */
    void Node::split() {
        /* We have to split the current node into three nodes, a parent and two children
           the nodes in cache as the sample */

        /* Compute the point with the largest vairance in distance */
        long long objectPosition = -1;
        double maxVariance = std::numeric_limits<double>::min();
        std::vector<double> maxVarianceDistances;
        std::vector<double> allDistances;

        long long size = objectCache.size();
        for (long long i = 0; i < size; ++i) {
            // Store the distances at the current level to compute variance
            std::vector<double> currentDistances;

            // Compute all distances
            for (long long j = 0; j < size; ++j) {
                double currentDistance = objectCache[i].distance(objectCache[j]);

                // Push into vectors
                currentDistances.push_back(currentDistance);
                allDistances.push_back(currentDistance);
            }

            // Compute the variance of the array
            double currentVariance = Statistics::getVariance(currentDistances);
            if (currentVariance > maxVariance) {
                maxVariance = currentVariance;
                objectPosition = i;
                maxVarianceDistances = currentDistances;
            }
        }

        // The object with max variance is the object this node will contain
        nodeObject = objectCache[objectPosition];

        // Compute the median of the distances to other objects to find radius
        std::vector<double> tempDistances = allDistances;
        sort(tempDistances.begin(), tempDistances.end());
        radius = tempDistances[(tempDistances.size() / 2)];

        /* Now divide the object cache into two sets depending on the object we
           found and the value of radius */
        leftNode = new Node();
        rightNode = new Node();

        // Divide the objects between the two nodes
        for (long long i = 0; i < size; ++i) {
            if (maxVarianceDistances[i] < radius) {
                leftNode->objectCache.push_back(objectCache[i]);
            } else {
                rightNode->objectCache.push_back(objectCache[i]);
            }
        }

        // Clean up the cache
        objectCache.clear();

#ifdef DEBUG_SPLIT
        std::cout << std::endl << std::endl << "Parent: "; print();
        std::cout << std::endl << std::endl << "LeftNode: "; leftNode->print();
        std::cout << std::endl << std::endl << "RightNode: "; rightNode->print();
#endif
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

