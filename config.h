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

/* ------------- STATS -------------- */
// #define OUTPUT
#define TIME
// #define DISTANCE

/* ------------- POINT -------------- */
#define DIMENSIONS 2
#define DISTANCE_EUCLIDEAN
// #define DISTANCE_MAHALONOBIS

#ifdef DISTANCE_MAHALONOBIS
#define MATRIXFILE "./assgn5_matrix.txt"
#endif

/* ------------- VPTREE ------------- */
#define POINTS 1000000
#define SAMPLE_SIZE 100

/* ------------- DATAFILE------------ */
#define DATAFILE "./assgn5_data.txt"
#define QUERYFILE "./assgn5_querysample.txt"

/* ------------- DEBUG -------------- */
// #define DEBUG_SPLIT
