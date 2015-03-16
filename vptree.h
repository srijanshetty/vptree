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

// Include the point library
#include "point.h"

// STL required by VPTRee
#include <string>
#include <vector>

// Stream output
#include <iostream>

// Math
#include <limits>

namespace VPTree {
    class DBObject {
        private:
            // Information about the object
            long long objectID = -1;
            std::string dataString = "";
            Point objectPoint = Point();

        public:
            // Default constructor
            DBObject() { };

            // Construct a DBObject
            DBObject(long long objectID, std::string dataString, Point objectPoint) :
                objectID(objectID), dataString(dataString), objectPoint(objectPoint) { };

            // Accessor methods
            std::string getDataString() const { return dataString; }
            long long getObjectID() const { return objectID; }
            Point getObjectPoint() const { return objectPoint; }

            // Compute the distance to either to a DBObject or to a Point
            double distance(const DBObject &targetObject) const { return objectPoint.distance(targetObject.getObjectPoint()); };
            double distance(const Point &targetPoint) const { return objectPoint.distance(targetPoint); };

            // Print the object
            void print() const { objectPoint.print(); std::cout << " :: " << objectID << " :: " << dataString; }
    };

    class Node {
        private:
            // Information about the Node
            double radius = std::numeric_limits<double>::max();
            DBObject object = DBObject();

        public:
            // A cache of elements
            std::vector<DBObject> objectCache;

            // Information about children
            Node *rightNode = nullptr;
            Node *leftNode = nullptr;

        public:
            // Default constructor
            Node() { };

            // Constructor which constructs an object
            Node(double radius, DBObject object) : radius(radius), object(object) { };

            // Accessor methods
            double getRadius() const { return radius; }
            double getCacheSize() const { return objectCache.size(); }

            // Ascertain if the node is a leaf
            bool isLeaf() const { return ((rightNode == nullptr) && (leftNode == nullptr)); }

            // Compute the distance of the root to a DBObject or to Point
            double distance(const DBObject &targetObject) const;
            double distance(const Point &point) const;

            // Print the node
            void print();

            // Print the tree recursive
            void printRecursive();

            // Split the node according to median
            void split();

            // Insert an object into the node
            void insert(DBObject targetObject);

            // Perform a rangeSearch on the tree
            void rangeSearch(Point point, double rangeRadius);
    };
}
