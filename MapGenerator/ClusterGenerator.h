#pragma once
#include "POI.h"
#include <vector>
#include "ClusterTree.h"

static class ClusterGenerator{
public:
	//K-means cluster generation
	static void getK_MeansCluster(std::vector<POI> &pointsOfInterests);
};