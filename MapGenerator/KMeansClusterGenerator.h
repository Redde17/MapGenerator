#pragma once
#include "ClusterGenerator.h"

class KMeansClusterGenerator : ClusterGenerator
{
private:
	int clustersAmount;
	std::vector<POI>& points;
public:
	KMeansClusterGenerator(int clustersAmount, std::vector<POI>& points);

	void generateCluster();
};

