#ifndef CA_KMEANS_ALGORITHM
#define CA_KMEANS_ALGORITHM

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "ClusterizationAlgorithms.h"

	Cluster* kMeansClusterizationForPoints(ClusterPoint *originalPointsList, unsigned int pointsCount, unsigned int clustersCount);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // #define CA_KMEANS_ALGORITHM