#pragma once
#include <stdlib.h>
#include "POI.h"
#include <vector>

class LogisticHandler
{
public:
	enum ClusterType {
		HIERARCHICAL,
		K_MEANS
	};

	//generate cluster
	void generateCluster(ClusterType clusterType, std::vector<POI> pointsOfInterests);

	//generate roads

	//generate logistic map layer
};

