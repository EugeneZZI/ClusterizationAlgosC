// Clusterization.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
#include "ClusterizationAlgorithms.h"

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int pointsCount = 100;
	unsigned int clustersCount = 3;

	ClusterPoint *randomPoints = generateRandomPointsList(pointsCount, 0, 500);
	printPointsList(randomPoints, pointsCount);

	/*ClusterPoint *randomPoints = getExamplePointsList();
	printPointsList(randomPoints, pointsCount);*/

	char m;
	Cluster* clusters = kMeansClusterizationForPoints(randomPoints, pointsCount, clustersCount);
	printClustersList(clusters, clustersCount);
	printf("\r\nTotal Length of clusters %f\r\n", calculateTotalLengthOfClusterList(clusters, clustersCount));
	for (unsigned int i = 0; i < clustersCount; i++)
	{
		printf("\r\nTotal Length of cluster %i -  %f\r\n", i, calculateTotalLengthOfCluster(clusters[i]));
	}
	std::cin >> m;

	Cluster* bfClusters = bruteForceSearchClusterizationForPoints(randomPoints, pointsCount, clustersCount);
	printClustersList(bfClusters, clustersCount);
	printf("\r\nTotal Length of clusters %f\r\n", calculateTotalLengthOfClusterList(bfClusters, clustersCount));
	for (unsigned int i = 0; i < clustersCount; i++)
	{
		printf("\r\nTotal Length of cluster %i -  %f\r\n", i, calculateTotalLengthOfCluster(bfClusters[i]));
	}
	std::cin >> m;

	return 0;
}

