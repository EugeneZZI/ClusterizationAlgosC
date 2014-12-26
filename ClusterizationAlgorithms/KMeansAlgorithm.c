#include "KMeansAlgorithm.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Internal definitions
//
//////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {
	int				ID;
	Point			tmpMean;
	unsigned int	pointsCount;
	long long int	tmpX;
	long long int	tmpY;
	ClusterPoint	tmpCentroid;
	float			centroidDistanceToMean;
} KMeansCluster;
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Functions declaration
//
//////////////////////////////////////////////////////////////////////////////////////////////////
void			dividePointsToRandomClusters(ClusterPoint *pointsList, unsigned int pointsCount, unsigned int clustersCount);
void			updateMeans(KMeansCluster *clustersList, unsigned int clustersCount, ClusterPoint *pointsList, unsigned int pointsCount);
void			updateCentroids(KMeansCluster *clustersList, ClusterPoint *pointsList, unsigned int pointsCount);
bool			assignPointsToClasters(KMeansCluster *clustersList, unsigned int clustersCount, ClusterPoint *pointsList, unsigned int pointsCount);
void			populateClustersList(Cluster *clustersList, KMeansCluster *tempClustersList, unsigned int clustersCount, ClusterPoint *pointsList, unsigned int pointsCount);
KMeansCluster*	createTempClustersFromClustersList(unsigned int clustersCount);
void			resetTempClustersList(KMeansCluster *tempClustersList, unsigned int clustersCount);
//////////////////////////////////////////////////////////////////////////////////////////////////

Cluster* kMeansClusterizationForPoints(ClusterPoint *originalPointsList, unsigned int pointsCount, unsigned int clustersCount)
{
	Cluster *retClusters = createEmptyClustersList(clustersCount);
	dividePointsToRandomClusters(originalPointsList, pointsCount, clustersCount);
	KMeansCluster *tmpClusters = createTempClustersFromClustersList(clustersCount);

	bool clustersChanged = true;
	while (clustersChanged)
	{
		resetTempClustersList(tmpClusters, clustersCount);
		updateMeans(tmpClusters, clustersCount, originalPointsList, pointsCount);
		updateCentroids(tmpClusters, originalPointsList, pointsCount);
		clustersChanged = assignPointsToClasters(tmpClusters, clustersCount, originalPointsList, pointsCount);
	}

	populateClustersList(retClusters, tmpClusters, clustersCount, originalPointsList, pointsCount);
	free(tmpClusters);

    return retClusters;
}

void dividePointsToRandomClusters(ClusterPoint *pointsList, unsigned int pointsCount, unsigned int clustersCount)
{
	for (unsigned int i = 0; i < pointsCount; i++)
	{
		pointsList[i].clusterID = rand() % clustersCount;
	}
}

void updateMeans(KMeansCluster *clustersList, unsigned int clustersCount, ClusterPoint *pointsList, unsigned int pointsCount)
{	
	// process each point from all clusters and populate temp array with clusters info
	for (unsigned int i = 0; i < pointsCount; i++)
	{
		ClusterPoint currentPoint = pointsList[i];
		KMeansCluster tmpCluster = clustersList[currentPoint.clusterID];
		tmpCluster.tmpX += currentPoint.coordinates.x;
		tmpCluster.tmpY += currentPoint.coordinates.y;
		tmpCluster.pointsCount++;
		clustersList[currentPoint.clusterID] = tmpCluster;
	}

	for (unsigned int i = 0; i < clustersCount; i++)
	{
		KMeansCluster tmpCluster = clustersList[i];
		clustersList[i].tmpMean.x = (int)(tmpCluster.tmpX / tmpCluster.pointsCount);
		clustersList[i].tmpMean.y = (int)(tmpCluster.tmpY / tmpCluster.pointsCount);
	}
}

void updateCentroids(KMeansCluster *clustersList, ClusterPoint *pointsList, unsigned int pointsCount)
{
	// check all points to calculate new clusters centroids
	for (unsigned int i = 0; i < pointsCount; i++)
	{
		ClusterPoint point = pointsList[i];
		KMeansCluster cluster = clustersList[point.clusterID];
		float newDistance = calculateDistanceBetweenCoordinates(point.coordinates, cluster.tmpMean);
		if ((cluster.centroidDistanceToMean == 0) || (newDistance < cluster.centroidDistanceToMean))
		{
			cluster.centroidDistanceToMean = newDistance;
			cluster.tmpCentroid = point;
			clustersList[point.clusterID] = cluster;
		}
	}
}

bool assignPointsToClasters(KMeansCluster *clustersList, unsigned int clustersCount, ClusterPoint *pointsList, unsigned int pointsCount)
{
	bool retFlag = false;
	for (unsigned int i = 0; i < pointsCount; i++)
	{
		ClusterPoint point = pointsList[i];
		float minDistance = 0.0;
		int newClusterID = -1;
		for (unsigned int j = 0; j < clustersCount; j++)
		{
			KMeansCluster cluster = clustersList[j];
			float currentDistance = calculateDistanceBetweenCoordinates(point.coordinates, cluster.tmpCentroid.coordinates);
			if ((j == 0) || (currentDistance < minDistance))
			{
				minDistance = currentDistance;
				newClusterID = j;
			}
		}

		if (newClusterID != point.clusterID)
		{
			retFlag = true;
			pointsList[i].clusterID = newClusterID;
		}
	}

	return retFlag;
}

void populateClustersList(Cluster *clustersList, KMeansCluster *tempClustersList, unsigned int clustersCount, ClusterPoint *pointsList, unsigned int pointsCount)
{
	ClusterPoint *sortedPoints = sortPointsListByClusters(pointsList, pointsCount);

	for (unsigned int i = 0; i < pointsCount; i++)
	{
		clustersList[pointsList[i].clusterID].pointsListCount++;
	}

	int pointsArrOffset = 0;
	for (unsigned int i = 0; i < clustersCount; i++)
	{
		clustersList[i].centroid = tempClustersList[i].tmpCentroid;
		clustersList[i].pointsList = sortedPoints + pointsArrOffset;
		pointsArrOffset += clustersList[i].pointsListCount;
	}
}

KMeansCluster* createTempClustersFromClustersList(unsigned int clustersCount)
{
	KMeansCluster *retClusters = malloc(sizeof(KMeansCluster) * clustersCount);
	for (unsigned int i = 0; i < clustersCount; i++)
	{
		KMeansCluster tmpCluster;
		tmpCluster.ID = i;
		tmpCluster.pointsCount = 0;
		tmpCluster.tmpX = 0;
		tmpCluster.tmpY = 0;
		tmpCluster.centroidDistanceToMean = 0;
		tmpCluster.tmpCentroid.coordinates.x = 0;
		tmpCluster.tmpCentroid.coordinates.y = 0;
		retClusters[i] = tmpCluster;
	}

	return retClusters;
}

void resetTempClustersList(KMeansCluster *tempClustersList, unsigned int clustersCount)
{
	for (unsigned int i = 0; i < clustersCount; i++)
	{
		tempClustersList[i].ID = i;
		tempClustersList[i].pointsCount = 0;
		tempClustersList[i].tmpX = 0;
		tempClustersList[i].tmpY = 0;
		tempClustersList[i].centroidDistanceToMean = 0;
		tempClustersList[i].tmpCentroid.coordinates.x = 0;
		tempClustersList[i].tmpCentroid.coordinates.y = 0;
	}
}