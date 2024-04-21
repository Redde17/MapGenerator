#pragma once
#include <vector>
#include "Cluster.h"

class ClusterTree
{
public:
	struct Node {
		Cluster* cluster;
		std::vector<Node*> parents;
		std::vector<Node*> childs;

		Node(Cluster* cluster, Node* parent);
		Node(Cluster* cluster, std::vector<Node*> parents);
		void addChild(Node* node);
	};

private:
	int size;
	Node* root;

	void getLeafsRecursiveFunc(std::vector<Node*>* leafs, Node* currentNode);

public:
	ClusterTree();

	Node* getRoot();
	std::vector<Node*> getLeafs();
	void mergeLeafs(Node* leaf1, Node* leaf2);
	void addNode(Node* parentNode, Cluster* nodeCluster);
	void addNode(std::vector<Node*> parentNode, Cluster* nodeCluster);
	int getTreeSize();
};

