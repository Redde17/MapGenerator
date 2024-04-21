#include "Cluster.h"
#include <stdlib.h>
#include <iostream>

Cluster::Cluster(POI* poi) {
	this->points.push_back(poi);
	this->x = poi->x;
	this->y = poi->y;
	std::cout << "POI generated with x["<< this->x <<"] and y["<< this->y <<"]" << std::endl;
}

Cluster::Cluster(Cluster* cluster1, Cluster* cluster2) {
	//merge vectors
	points.insert(points.end(), cluster1->points.begin(), cluster1->points.end());
	points.insert(points.end(), cluster2->points.begin(), cluster2->points.end());



	//get new centroid from merged clusters
	x = (cluster1->x + cluster2->x) * 0.5;
	y = (cluster1->y + cluster2->y) * 0.5;
}