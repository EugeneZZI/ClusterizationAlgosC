# ClusterizationAlgosC

Several clusterization algorithms implemented in C.

##Included algorithms
- Brute force algorithms (check all possible positions of centroids for current number of clusters)
- K-Means (implementation of the [K-Means] algorithm)

## Adding algorithms to your project
Directly add the ClusterizationAlgorithms folder to your project and include header
```C
#include "ClusterizationAlgorithms.h" 
```

## Usage
Generate random array of ClusterPoints (points which will be processed in clusters)
```C
unsigned int pointsCount = 100
ClusterPoint *randomPoints = generateRandomPointsList(pointsCount, 0, 500);
```
Also you can get hardcoded array of ClusterPoints
```C
ClusterPoint *hardCodedPoints = getExamplePointsList();
```
You can print generated array in console
```C
printPointsList(randomPoints, pointsCount); 
```
Set count of cluster and use algorithm which you want
```C
unsigned int clustersCount = 3;
Cluster *clusters = kMeansClusterizationForPoints(randomPoints, pointsCount, clustersCount);
```
And then you can print clusters in console
```C
printClustersList(clusters, clustersCount);
```

## License

This code is distributed under the terms and conditions of the [MIT license](LICENSE). 

[K-Means]:https://ru.wikipedia.org/wiki/K-means

