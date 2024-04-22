#pragma once
#include <vector>
#include "Cluster.h"

class ClusterTree
{
public:
	struct Node {
		Cluster cluster;
		std::vector<Node*> childs;

		Node();

		Node(POI& poi);

		Node(Cluster& cluster);
		Node(Cluster& cluster1, Cluster& cluster2);
		void addChild(Node* node);
	};

private:
	int treeSize;

public:
	Node root;

	ClusterTree();
	int getSize();
	std::vector<Node*> getLeafs();

	void addNode(Node* parent, Node* child);
	void mergeNodes(Node* node1, Node* node2);
};

