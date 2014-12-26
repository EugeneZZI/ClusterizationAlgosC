#ifndef CA_COMMON_FUNCTIONS
#define CA_COMMON_FUNCTIONS

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "Definitions.h"

	Cluster* createEmptyClustersList(unsigned int clustersCount);
	float calculateDistanceBetweenCoordinates(Point from, Point to);
	ClusterPoint*	sortPointsListByClusters(ClusterPoint *pointsList, unsigned int pointsCount);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // #define CA_COMMON_FUNCTIONS