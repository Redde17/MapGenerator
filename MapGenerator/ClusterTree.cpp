#include "ClusterTree.h"
#include <algorithm>

ClusterTree::Node::Node() {
}

ClusterTree::Node::Node(POI& poi) {
	cluster = Cluster(&poi);
}

ClusterTree::Node::Node(Cluster& cluster) {
	this->cluster = cluster;
}

ClusterTree::Node::Node(Cluster& cluster1, Cluster& cluster2) {
	this->cluster = Cluster(cluster1, cluster2);
}

void ClusterTree::Node::addChild(Node* node) {
	childs.push_back(node);
}

ClusterTree::ClusterTree() {
	treeSize = 0;
}

void getLeafsRecursive(std::vector<ClusterTree::Node*>& leafs, ClusterTree::Node* currentNode) {
	if (currentNode->childs.size() == 0) {
		//checks if the leaf has already been added to the vector
		//this is because a leaf can have more then one parent, usually 2.
		if (std::find(leafs.begin(), leafs.end(), currentNode) == leafs.end())
			leafs.push_back(currentNode);

		return;
	}

	for (auto nextNode : currentNode->childs)
		getLeafsRecursive(leafs, nextNode);
}

int ClusterTree::getSize() {
	return treeSize;
}

std::vector<ClusterTree::Node*> ClusterTree::getLeafs() {
	std::vector<Node*> leafs;

	getLeafsRecursive(leafs, &root);

	return leafs;
}

void ClusterTree::addNode(Node* parent, Node* child) {
	parent->childs.push_back(child);

	treeSize++;
}

void ClusterTree::mergeNodes(Node* node1, Node* node2) {
	Node* newNode = new Node(node1->cluster, node2->cluster);
	node1->addChild(newNode);
	node2->addChild(newNode);

	treeSize++;
}