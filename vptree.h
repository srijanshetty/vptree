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
#include <map>

// Stream output
#include <iostream>

namespace VPTree {
    class DBObject {
        private:
            // Information about the object
            long long objectID;
            std::string dataString;
            Point objectPoint;

        public:
            // Construct a DBObject
            DBObject(long long objectID, std::string dataString, Point objectPoint) :
                objectID(objectID), dataString(dataString), objectPoint(objectPoint) { };

            // Accessor methods
            std::string getDataString() const { return dataString; }
            long long getObjectID() const { return objectID; }
            Point getObjectPoint() const { return objectPoint; }

            // Compute the distance between objects
            double distance(const DBObject &targetObject) const { return objectPoint.distance(targetObject.getObjectPoint()); };

            // Print the object
            void print() const { objectPoint.print(); std::cout << " :: " << objectID << " :: " << dataString; }
    };

    class Node {
        private:
            // Information about the Node
            double radius;
            DBObject object;

        public:
            // A cache of elements
            std::map<long long, long long> indexCache;
            std::vector<DBObject> objectCache;
            std::map<long long, double> distanceCache;

            // Information about children
            Node *rightNode = nullptr;
            Node *leftNode = nullptr;

        public:
            // Constructor which constructs an object
            Node(double radius, DBObject object) : radius(radius), object(object) { };

            // Accessor methods
            double getRadius() const { return radius; }
            double getCacheSize() const { return objectCache.size(); }

            // Ascertain if the node is a leaf
            bool isLeaf() const { return ((rightNode == nullptr) && (leftNode == nullptr)); }

            // Compute the distance of the root to a object
            double distance(const DBObject &targetObject) const;

            // Print the node
            void print();

            // Insert an object into the objectCache
            void insertToCache(DBObject insertObject, double objectDistance);

            // get the distance from the cache
            double getDistanceFromCache(DBObject searchObject);

            // Split the node according to median
            void split();

            // Insert an object into the node
            void insert(DBObject targetObject, double objectDistance);
    };
}
