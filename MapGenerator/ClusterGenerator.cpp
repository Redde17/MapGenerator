#include "ClusterGenerator.h"
#include "GlobalInclude.h"




//Hierarchical cluster generation
void ClusterGenerator::getHierarchicalCluster(std::vector<POI> pointsOfInterests) {
	std::cout << "HierarchicalCluster generation start with ["<< pointsOfInterests.size() <<"] points" << std::endl;

	//bottom up cluster genertion
	//generate initial clusters 
	ClusterTree H_Cluster;

	for (POI poi : pointsOfInterests) {
		H_Cluster.addNode(H_Cluster.getRoot(), new Cluster(&poi));
		std::cout << "Node added" << std::endl;
	}

	std::cout << "Tree size ["<< H_Cluster.getTreeSize() <<"] " << std::endl;

	//while there is more then 1 leaf in the tree
	//calculate distances between clusters on the leafs of the tree
	//find the two clusters with the minimum distance
	//merge them and put the new cluster as the leaf of both it's source clusters

	std::cout << "HierarchicalCluster generation end" << std::endl;
}

//K-means cluster generation
void ClusterGenerator::getK_MeansCluster(std::vector<POI> pointsOfInterests) {
	return;
}