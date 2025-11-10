#pragma once
#include "POI.h"
#include <vector>
#include "Cluster.h"


class ClusterGenerator{
private:
	void generateKmeanClusters(std::list<Cluster*>* clusters, int clustersAmount);
	std::vector<POI*> getRandomPoints(Cluster* cluster, int amount);

	float getPointsDistance(const POI& a, const POI& b);

public:
	enum ClusteringType
	{
		K_MEANS
	};

	void generateClusters(ClusteringType clusteringType, std::list<Cluster*>* clusters, int clustersAmount = 1);
};
