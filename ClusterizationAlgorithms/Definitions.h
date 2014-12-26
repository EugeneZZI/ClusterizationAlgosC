#ifndef CA_DEFINITIONS
#define CA_DEFINITIONS

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

	typedef struct {
		int x;
		int y;
	} Point;

	typedef struct {
		Point		coordinates;
		int			clusterID;
	} ClusterPoint;

	typedef struct {
		int				ID;
		ClusterPoint*   pointsList;
		int				pointsListCount;
		ClusterPoint	centroid;
	} Cluster;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // #define CA_DEFINITIONS