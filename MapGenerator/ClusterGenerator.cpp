#include "ClusterGenerator.h"
#include "GlobalInclude.h"
#include "ClusterTree.h"

float getDistance(ClusterTree::Node& cl1, ClusterTree::Node& cl2) {
	return sqrt(pow(cl1.cluster.x - cl2.cluster.x, 2) + pow(cl1.cluster.y - cl2.cluster.y, 2));
}

//K-means cluster generation
void ClusterGenerator::getK_MeansCluster(std::vector<POI>& pointsOfInterests) {
	return;
}