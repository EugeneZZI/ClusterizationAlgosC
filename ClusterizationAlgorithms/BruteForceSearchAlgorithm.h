#ifndef CA_BRUTE_FORCE_SEARCH_ALGORITHM
#define CA_BRUTE_FORCE_SEARCH_ALGORITHM

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "ClusterizationAlgorithms.h"

	Cluster* bruteForceSearchClusterizationForPoints(ClusterPoint *originalPointsList, unsigned int pointsCount, unsigned int clustersCount);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // #define CA_BRUTE_FORCE_SEARCH_ALGORITHM