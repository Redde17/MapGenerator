#include "Cluster.h"
#include <stdlib.h>
#include <iostream>

Cluster::Cluster() {
	x, y = 0;
}

Cluster::Cluster(POI* poi) {
	x = poi->x;
	y = poi->y;
	points.push_back(poi);
}

Cluster::Cluster(Cluster& cluster1, Cluster& cluster2) {
	//merge vectors
	//if (points.empty())
	//	std::cout << "DEBUG: points vector is empty" << std::endl;

	if(cluster1.points.empty() && cluster2.points.empty())
		std::cout << "DEBUG: input clusters points vector are empty" << std::endl;

	points.insert(points.begin(), cluster1.points.begin(), cluster1.points.end());
	points.insert(points.end(), cluster2.points.begin(), cluster2.points.end());

	//get new centroid from merged clusters
	x = (cluster1.x + cluster2.x) * 0.5;
	y = (cluster1.y + cluster2.y) * 0.5;
}

