#include "CommonFunctions.h"

Cluster* createEmptyClustersList(unsigned int clustersCount)
{
	Cluster *retClusters = malloc(sizeof(Cluster) * clustersCount);

	for (unsigned int i = 0; i < clustersCount; i++)
	{
		Cluster newCluster;
		newCluster.ID = i;
		newCluster.pointsListCount = 0;
		retClusters[i] = newCluster;
	}

	return retClusters;
}

float calculateDistanceBetweenCoordinates(Point from, Point to)
{
	return sqrtf(powf((float)(to.x - from.x), 2) + powf((float)(to.y - from.y), 2));
}

ClusterPoint *sortPointsListByClusters(ClusterPoint *pointsList, unsigned int pointsCount) {
	ClusterPoint *retArr = malloc(sizeof(ClusterPoint) * pointsCount);
	memcpy(retArr, pointsList, (sizeof(ClusterPoint) * pointsCount));

	unsigned int i, j;
	ClusterPoint temp;
	for (i = 0; i < (pointsCount - 1); i++)
	{
		for (j = 0; j < (pointsCount - 1 - i); j++)
		{
			if (retArr[j].clusterID > retArr[j + 1].clusterID)
			{
				temp = retArr[j + 1];
				retArr[j + 1] = retArr[j];
				retArr[j] = temp;
			}
		}
	}

	return retArr;
}