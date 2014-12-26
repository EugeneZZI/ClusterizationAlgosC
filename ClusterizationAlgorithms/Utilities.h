#ifndef CA_UTILITIES
#define CA_UTILITIES

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "Definitions.h"
#include "CommonFunctions.h"

	// Print data functions
	void printPointsList(ClusterPoint* pointsList, unsigned int pointsCount);
	void printClustersList(Cluster* clustersList, unsigned int clustersCount);

	// Generate random data functions
	ClusterPoint* generateRandomPointsList(unsigned int pointsCount, unsigned int rangeFrom, unsigned int rangeTo);
	ClusterPoint* getExamplePointsList();

	// Utilities functions
	double calculateTotalLengthOfCluster(Cluster cluster);
	double calculateTotalLengthOfClusterList(Cluster *clusterList, unsigned int clustersCount);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // #define CA_UTILITIES