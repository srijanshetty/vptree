# VPTree

## Results
- The computed time is in microseconds.

**Euclidean Time**

QUERY | MAX  | MIN | AVG     | STD
------|------|-----|---------|--------
2     | 1685 | 79  | 4430.26 | 382.426
3     | 2497 | 3   | 8408.12 | 828.912

**Euclidean Distance Computations**

QUERY  | MAX    | MIN   | AVG       | STD
------ | ------ | ----- | --------- | --------
2      | 1865   | 273   | 9114.19   | 838.119
3      | 229    | 1     | 1192.72   | 116.272


**Mahalonobis Time**

QUERY  | MAX    | MIN   | AVG       | STD
------ | ------ | ----- | --------- | --------
2      | 1036   | 129   | 4215.2    | 388.42
3      | 1772   | 2     | 8026.14   | 789.314

**Mahalonobis Distance Computations**

QUERY  | MAX    | MIN   | AVG       | STD
------ | ------ | ----- | --------- | --------
2      | 1865   | 273   | 9114.19   | 838.119
3      | 229    | 1     | 1192.72   | 116.272

## Observations

**Distance Computations**
- The distance computations for both Mahalonobis distance and Euclidean distance turn out to be the same, which is the expected behaviour in a deterministic program.

**Mahalonobis Distance vs Euclidean Distance**
- While one would expect a difference in the time taken for Mahalonobis distance and Euclidean Distance, the data concludes otherwise. In fact, one would expect Mahalonobis distance to be worse off which isn't the case here with Euclidean distance taking marginally more time.
- This reversal of trend is attributed to the dimensionality of data. As the data is two dimensional, we cannot observe the difference in both these distance metrics. (Additionally, my implementation optimizes Mahalonobis distance for the case of two dimensions, hence it outperforms Euclidean distance)

**kNNSearch vs rangeSearch**
- Unlike the previous assignment on **B+ Tree** and **R Tree**, kNNSearches take more time here than rangeSearch.
- One possible explanation is small range that we are searching for in the given query_sample file.
- Another reason is the optimized **Best Fit Serach** algorithm which is used for computing kNNSearch.

**Time taken vs Distance Computation**
- kNNSearch takes more time than rangeSearch but it performs lesser distance computations.
- In this assignment, the effect of distance computations is not much pronounced as the time taken to compute the distance is very small.
- If the number of dimensions would have been larger, the effect would have manifested in a disparity in the time taken by rangeSearch and kNNSearch with the former taking a huge amount of time.

## INSTALL

- Tree parameters are defined in *[config.h]*(config.h).

- To build a new tree one can run:

        $ make

- To chose **Mahalonobis Distance** uncomment the line:

        // #define DISTANCE_MAHALONOBIS

- The configuration for computing time values are:

        // #define OUTPUT
        #define TIME
        // #define DISTANCE

- To just get the output, the configuration is as follows:

        #define OUTPUT
        // #define TIME
        // #define DISTANCE

- The configuration for computing distance values are:

        #define OUTPUT
        // #define TIME
        // #define DISTANCE

- There are many DEBUG levels available in *[config.h]*(config.h).
