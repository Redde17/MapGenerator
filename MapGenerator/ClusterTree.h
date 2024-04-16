#pragma once
#include <vector>
#include "Cluster.h"

class ClusterTree
{
	struct Node {
		Cluster* cluster;
		std::vector<Node*> parents;
		std::vector<Node*> childs;

		Node(Cluster* cluster, Node* parent);
		Node(Cluster* cluster, std::vector<Node*> parents);
		void addChild(Node* node);
	};


	int size;
	Node* root;
	//leafs list for faster access as the operation on the tree will mostly use it's leafs
	std::vector<Node*> leafs;

public:
	ClusterTree();

	//remember to add leaf tracking support to adding and merging functions
	Node* getRoot();
	std::vector<Node*> getLeafs();
	void mergeLeafs(Node* leaf1, Node* leaf2);
	void addNode(Node* parentNode, Cluster* nodeCluster);
	void addNode(std::vector<Node*> parentNode, Cluster* nodeCluster);
	int getTreeSize();
};

