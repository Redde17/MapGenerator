#include "Cluster.h"

Cluster::Cluster(POI* poi) {
	this->points.push_back(poi);
	x = poi->x;
	y = poi->y;
}

Cluster::Cluster(Cluster* cluster1, Cluster* cluster2) {
	//merge vectors
	points.insert(points.end(), cluster1->points.begin(), cluster1->points.end());
	points.insert(points.end(), cluster2->points.begin(), cluster2->points.end());
	
	//get new centroid from merged clusters
	x = (cluster1->x + cluster2->x) * 0.5;
	y = (cluster1->y + cluster2->y) * 0.5;
}