#pragma once
#include <vector>
#include "POI.h"

class Cluster
{
public:
	int x, y;
	std::vector<POI*> points;

	//cluster position x,y is based on it's points
	Cluster(POI* poi);
	Cluster(Cluster* cluster1, Cluster* cluster2);
};

