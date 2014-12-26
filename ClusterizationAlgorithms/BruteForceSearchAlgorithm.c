#include "BruteForceSearchAlgorithm.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Internal definitions
//
//////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {
	int				ID;
	ClusterPoint	tmpCentroid;
	unsigned int	currentPosition;
	unsigned int	lastPosition;
} BFCluster;

//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Functions declaration
//
//////////////////////////////////////////////////////////////////////////////////////////////////
BFCluster* createEmptyBruteForceClustersList(unsigned int clustersCount);
void setupBFClustersInFirstPosition(ClusterPoint *pointsList, unsigned int pointsCount, BFCluster *clustersList, unsigned int clustersCount);
double processCurrentCentroidPosition(ClusterPoint *pointsList, unsigned int pointsCount, BFCluster *clustersList, unsigned int clustersCount);
void storeCurrentCentroidPostitionInClusters(ClusterPoint *pointsList, unsigned int pointsCount, BFCluster *tmpClustersList, Cluster *retClustersList, unsigned int clustersCount);
bool needMoveCentroidBFCluster(BFCluster *clustersList, unsigned int clustersCount);
void resetClustersList(Cluster *clustersList, unsigned int clustersCount);
//////////////////////////////////////////////////////////////////////////////////////////////////

Cluster* bruteForceSearchClusterizationForPoints(ClusterPoint *originalPointsList, unsigned int pointsCount, unsigned int clustersCount)
{
	long double totalLenght = 0;
	unsigned int moveCentroidClusterIndex = clustersCount - 1;

	Cluster *retClusters	= createEmptyClustersList(clustersCount);
	BFCluster *tempClusters = createEmptyBruteForceClustersList(clustersCount);

	// setup first position for centroids and process it
	setupBFClustersInFirstPosition(originalPointsList, pointsCount, tempClusters, clustersCount);
	totalLenght = processCurrentCentroidPosition(originalPointsList, pointsCount, tempClusters, clustersCount);
	storeCurrentCentroidPostitionInClusters(originalPointsList, pointsCount, tempClusters, retClusters, clustersCount);
	
	// move temp clusters centroids
	while (needMoveCentroidBFCluster(tempClusters, clustersCount))
	{
		// move last cluster centroid through all possible points
		while (tempClusters[moveCentroidClusterIndex].currentPosition < tempClusters[moveCentroidClusterIndex].lastPosition)
		{
			tempClusters[moveCentroidClusterIndex].currentPosition++;
			tempClusters[moveCentroidClusterIndex].tmpCentroid = originalPointsList[tempClusters[moveCentroidClusterIndex].currentPosition];

			long double newLength = processCurrentCentroidPosition(originalPointsList, pointsCount, tempClusters, clustersCount);
			if (newLength < totalLenght)
			{
				totalLenght = newLength;
				storeCurrentCentroidPostitionInClusters(originalPointsList, pointsCount, tempClusters, retClusters, clustersCount);
			}
		}

		bool stopFlag = false;
		while (!stopFlag)
		{
			if (moveCentroidClusterIndex > 0)
			{
				moveCentroidClusterIndex--;
			}
			else
			{
				stopFlag = true;
				continue;
			}

			if (tempClusters[moveCentroidClusterIndex].currentPosition < tempClusters[moveCentroidClusterIndex].lastPosition)
			{
				tempClusters[moveCentroidClusterIndex].currentPosition += 1;
				tempClusters[moveCentroidClusterIndex].tmpCentroid = originalPointsList[tempClusters[moveCentroidClusterIndex].currentPosition];

				for (unsigned int i = moveCentroidClusterIndex + 1; i < clustersCount; i++)
				{
					tempClusters[i].currentPosition = tempClusters[i - 1].currentPosition + 1;
					tempClusters[moveCentroidClusterIndex].tmpCentroid = originalPointsList[tempClusters[i].currentPosition];
				}

				long double newLength = processCurrentCentroidPosition(originalPointsList, pointsCount, tempClusters, clustersCount);
				if (newLength < totalLenght)
				{
					totalLenght = newLength;
					storeCurrentCentroidPostitionInClusters(originalPointsList, pointsCount, tempClusters, retClusters, clustersCount);
				}
				moveCentroidClusterIndex = clustersCount - 1;
				stopFlag = true;
			}
		}
	}
	
	free(tempClusters);

	return retClusters;
}

BFCluster* createEmptyBruteForceClustersList(unsigned int clustersCount)
{
	BFCluster *retClusters = malloc(sizeof(BFCluster) * clustersCount);

	for (unsigned int i = 0; i < clustersCount; i++)
	{
		BFCluster newCluster;
		newCluster.ID = i;
		newCluster.currentPosition = 0;
		newCluster.lastPosition = 0;
		retClusters[i] = newCluster;
	}

	return retClusters;
}

void setupBFClustersInFirstPosition(ClusterPoint *pointsList, unsigned int pointsCount, BFCluster *clustersList, unsigned int clustersCount)
{
	for (unsigned int i = 0; i < clustersCount; i++)
	{
		clustersList[i].tmpCentroid = pointsList[i];
		clustersList[i].currentPosition = i;
		clustersList[i].lastPosition = pointsCount - (clustersCount - i);
	}
}

double processCurrentCentroidPosition(ClusterPoint *pointsList, unsigned int pointsCount, BFCluster *clustersList, unsigned int clustersCount)
{
	double retLength = 0;

	for (unsigned int i = 0; i < pointsCount; i++)
	{
		ClusterPoint point = pointsList[i];
		float minDistance = 0.0;
		int newClusterID = -1;
		for (unsigned int j = 0; j < clustersCount; j++)
		{
			BFCluster cluster = clustersList[j];
			float currentDistance = calculateDistanceBetweenCoordinates(point.coordinates, cluster.tmpCentroid.coordinates);
			if ((j == 0) || (currentDistance < minDistance))
			{
				minDistance = currentDistance;
				newClusterID = j;
			}
		}

		if (newClusterID != point.clusterID)
		{
			pointsList[i].clusterID = newClusterID;
		}

		retLength += (double)minDistance;
	}

	return retLength;
}

void storeCurrentCentroidPostitionInClusters(ClusterPoint *pointsList, unsigned int pointsCount, BFCluster *tmpClustersList, Cluster *retClustersList, unsigned int clustersCount)
{
	ClusterPoint *sortedPoints = sortPointsListByClusters(pointsList, pointsCount);
	resetClustersList(retClustersList, clustersCount);
	for (unsigned int i = 0; i < pointsCount; i++)
	{
		retClustersList[pointsList[i].clusterID].pointsListCount++;
	}

	int pointsArrOffset = 0;
	for (unsigned int i = 0; i < clustersCount; i++)
	{
		retClustersList[i].centroid = tmpClustersList[i].tmpCentroid;
		retClustersList[i].pointsList = sortedPoints + pointsArrOffset;
		pointsArrOffset += retClustersList[i].pointsListCount;
	}
}

bool needMoveCentroidBFCluster(BFCluster *clustersList, unsigned int clustersCount)
{
	for (int i = (int)clustersCount - 1; i >= 0; i--)
	{
		if (i < 0) break;
		if (clustersList[i].currentPosition < clustersList[i].lastPosition)
			return true;
	}

	return false;
}

void resetClustersList(Cluster *clustersList, unsigned int clustersCount)
{
	for (unsigned int i = 0; i < clustersCount; i++)
	{
		if (clustersList[0].pointsListCount != 0 && i == 0)
		{
			free(clustersList[0].pointsList);
		}

		clustersList[i].pointsListCount = 0;
	}
}