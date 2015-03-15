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

namespace VPTree {
    Node *VPRoot = nullptr;

    // Insert an object into the objectCache
    void Node::insertToCache(DBObject insertObject, double objectDistance) {
        /* obtain the insert index and then add the distance and object
           to the hashmaps */

        // Insert the index into the indexCache
        long long insertIndex = getCacheSize();
        indexCache[object.getObjectID()] = insertIndex;

        // Insert the distance into the distanceCache
        distanceCache[insertIndex] = objectDistance;

        // Insert the object into the hashmap
        objectCache.push_back(insertObject);
    }

    // Get the distance of an object
    double Node::getDistanceFromCache(DBObject searchObject) {
        /* Get the index of the object from the indexCache and then get
           the distance from the distance cache */
        long long objectIndex = indexCache[searchObject.getObjectID()];

        // Return the distance from the cache
        return distanceCache[objectIndex];
    }

    /* Split the node according to the media */
    void Node::split() {
    }

    /* Insert a point into the VPTree */
    void insert(Node *root, DBObject object, double objectDistance) {
        // Check if the root is a leaf
        if (root->isLeaf()) {
            /* Directly insert the object into the root's cache and then split if
               we've reached the sample size limit */
            root->insertToCache(object, objectDistance);

            if (root->getCacheSize() > SAMPLE_SIZE) {
                root->split();
            }
        } else {
            /* It will never be the case that one of the subtrees is empty, this is because we sample
               the objects and then split according to the median, this gurantees that half the nodes
               will go to one side and the rest on the other */
            /* Compute the distance of the object from the root and insert into the correct subtree */
            if (objectDistance < root->getRadius()) {
                insert(root->leftNode, object, root->leftNode->distance(object));
            } else {
                insert(root->rightNode, object, root->rightNode->distance(object));
            }
        }
    }
}
