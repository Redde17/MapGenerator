#include "ClusterGenerator.h"
#include "GlobalInclude.h"



void ClusterGenerator::generateKmeanClusters(std::list<Cluster*>* clusters, int clustersAmount){
	if(clustersAmount == 1)
		return;

	std::vector<POI*> centroids;
}

std::vector<POI*> ClusterGenerator::getRandomPoints(Cluster* cluster, int amount){
	std::vector<POI*> points;
	std::vector<POI*>* availablePoints = cluster->getPoints();
	POI* point;

	for (int i = 0; i < amount; i++){
		//get random point
		point = availablePoints->at(0);

		//check if point is already taken
	}

	return std::vector<POI*>();
}

float ClusterGenerator::getPointsDistance(const POI& a, const POI& b){
	return 0.0f;
}

void ClusterGenerator::generateClusters(ClusteringType clusteringType, std::list<Cluster*>* clusters, int clustersAmount){
	switch (clusteringType){
		case K_MEANS:
			generateKmeanClusters(clusters, clustersAmount);
			break;

		default:
			break;
	}	
}