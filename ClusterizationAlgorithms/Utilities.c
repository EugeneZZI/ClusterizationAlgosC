#include "Utilities.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Functions declaration
//
//////////////////////////////////////////////////////////////////////////////////////////////////
int iRandomFromRange(unsigned int from, unsigned int to);
//////////////////////////////////////////////////////////////////////////////////////////////////

void printPointsList(ClusterPoint* pointsList, unsigned int pointsCount)
{
	printf("\r\n====> Points List <==== \r\n");
	for (unsigned int i = 0; i < pointsCount; i++) {
		ClusterPoint point = pointsList[i];
		printf("Point: %d cluster: %d x: %d y: %d \r\n", i, point.clusterID, point.coordinates.x, point.coordinates.y);
	}
	printf("\r\n====> ----------- <==== \r\n");
}

void printClustersList(Cluster* clustersList, unsigned int clustersCount)
{
	printf("\r\n====> Clusters List <====\r\n");
	for (unsigned int i = 0; i < clustersCount; i++) {
		Cluster cluster = clustersList[i];
		printf("Cluster: %d points count: %d  \r\n", cluster.ID, cluster.pointsListCount);
		printf("   Centroid X: %d Y: %d\r\n", cluster.centroid.coordinates.x, cluster.centroid.coordinates.y);
		printPointsList(cluster.pointsList, cluster.pointsListCount);
	}
	printf("\r\n====> ----------- <====\r\n");
}

ClusterPoint* generateRandomPointsList(unsigned int pointsCount, unsigned int rangeFrom, unsigned int rangeTo)
{
	time_t t;
	time(&t);
	int seed = (int)t;
	srand(seed);

	ClusterPoint* pointsList = (ClusterPoint*)malloc(sizeof(ClusterPoint) * pointsCount);
	for (unsigned int i = 0; i < pointsCount; i++)
	{
		ClusterPoint point;
		point.clusterID = -1;
		point.coordinates.x = iRandomFromRange(rangeFrom, rangeTo);
		point.coordinates.y = iRandomFromRange(rangeFrom, rangeTo);
		pointsList[i] = point;
	}

	return pointsList;
}

ClusterPoint* getExamplePointsList()
{
	ClusterPoint point1;
	point1.coordinates.x = 30;
	point1.coordinates.y = 25;
	point1.clusterID = -1;

	ClusterPoint point2;
	point2.coordinates.x = 30;
	point2.coordinates.y = 15;
	point2.clusterID = -1;

	ClusterPoint point3;
	point3.coordinates.x = 20;
	point3.coordinates.y = 30;
	point3.clusterID = -1;

	ClusterPoint point4;
	point4.coordinates.x = 55;
	point4.coordinates.y = 50;
	point4.clusterID = -1;

	ClusterPoint point5;
	point5.coordinates.x = 65;
	point5.coordinates.y = 55;
	point5.clusterID = -1;

	ClusterPoint point6;
	point6.coordinates.x = 45;
	point6.coordinates.y = 60;
	point6.clusterID = -1;

	ClusterPoint point7;
	point7.coordinates.x = 80;
	point7.coordinates.y = 15;
	point7.clusterID = -1;

	ClusterPoint point8;
	point8.coordinates.x = 90;
	point8.coordinates.y = 25;
	point8.clusterID = -1;

	ClusterPoint point9;
	point9.coordinates.x = 80;
	point9.coordinates.y = 25;
	point9.clusterID = -1;

	ClusterPoint points[9] = {point1, point2, point3, point4, point5, point6, point7, point8, point9};
	ClusterPoint *retPoints = malloc(sizeof(ClusterPoint) * 9);
	memcpy(retPoints, points, (sizeof(ClusterPoint) * 9));
	return retPoints;
}

double calculateTotalLengthOfCluster(Cluster cluster)
{
	double retLength = 0.0;
	for (int i = 0; i < cluster.pointsListCount; i++)
		retLength += calculateDistanceBetweenCoordinates(cluster.pointsList[i].coordinates, cluster.centroid.coordinates);

	return retLength;
}

double calculateTotalLengthOfClusterList(Cluster *clusterList, unsigned int clustersCount)
{
	double retLength = 0.0;
	for (int i = 0; i < clustersCount; i++)
		retLength += calculateTotalLengthOfCluster(clusterList[i]);

	return retLength;
}

int iRandomFromRange(unsigned int from, unsigned int to)
{
	int retNum = rand() % (to - from) + from;
	return  retNum;
}