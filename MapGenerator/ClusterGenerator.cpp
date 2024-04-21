#include "ClusterGenerator.h"
#include "GlobalInclude.h"
#include "ClusterTree.h"

struct NodeCouple {
	float distance;
	ClusterTree::Node* node1;
	ClusterTree::Node* node2;
};

float getDistance(ClusterTree::Node* cl1, ClusterTree::Node* cl2) {
	return sqrt(pow(cl1->cluster->x - cl2->cluster->x, 2) + pow(cl1->cluster->y - cl2->cluster->y, 2));
}

//Hierarchical cluster generation
ClusterTree ClusterGenerator::getHierarchicalCluster(std::vector<POI> pointsOfInterests) {
	std::cout << "HierarchicalCluster generation start with ["<< pointsOfInterests.size() <<"] points" << std::endl;

	//bottom up cluster genertion
	//generate initial clusters 
	ClusterTree H_Cluster;

	for (POI poi : pointsOfInterests) {
		H_Cluster.addNode(H_Cluster.getRoot(), new Cluster(&poi));
		std::cout << "Node added with poi.x["<< poi.x <<"] and poi.y[" << poi.y << "]" << std::endl;
	}

	std::vector<ClusterTree::Node*> leafs = H_Cluster.getLeafs();

	std::cout << "Tree size ["<< leafs.size() <<"] " << std::endl;

	NodeCouple minDistanceNodes;
	//while there is more then 1 leaf in the tree
	while (leafs.size() > 1) {
		minDistanceNodes.node1 = leafs[0];
		minDistanceNodes.node2 = leafs[1];
		minDistanceNodes.distance = getDistance(minDistanceNodes.node1, minDistanceNodes.node2);

		//calculate distances between clusters on the leafs of the tree
		//find the two clusters with the minimum distance
		for (size_t i = 0; i < leafs.size() - 2; i++)
		{
			for (size_t j = i + 1; j < leafs.size(); j++)
			{
				float newDistance = getDistance(leafs[i], leafs[j]);
				if (newDistance < minDistanceNodes.distance) {
					minDistanceNodes.node1 = leafs[i];
					minDistanceNodes.node2 = leafs[j];
					minDistanceNodes.distance = newDistance;
				}
			}
		}

		//merge them and put the new cluster as the leaf of both it's source clusters
		H_Cluster.mergeLeafs(minDistanceNodes.node1, minDistanceNodes.node2);
		leafs = H_Cluster.getLeafs();
		std::cout << "Tree size [" << leafs.size() << "] " << std::endl;
	}


	std::cout << "HierarchicalCluster generation end" << std::endl;

	return H_Cluster;
}

//K-means cluster generation
void ClusterGenerator::getK_MeansCluster(std::vector<POI> pointsOfInterests) {
	return;
}