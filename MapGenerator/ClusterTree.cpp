#include "ClusterTree.h"

ClusterTree::ClusterTree() {
	size = 0;
	root = new Node(NULL, NULL);
}

ClusterTree::Node::Node(Cluster* cluster, Node* parent) {
	this->cluster = cluster;
	parents.push_back(parent);
}

ClusterTree::Node::Node(Cluster* cluster, std::vector<Node*> parents) {
	this->cluster = cluster;
	this->parents = parents;
}

void ClusterTree::Node::addChild(Node* node) {
	childs.push_back(node);
}


ClusterTree::Node* ClusterTree::getRoot() {
	return root;
}

std::vector<ClusterTree::Node*> ClusterTree::getLeafs() {
	return leafs;
}

//merges two leafs into a new one, the new leaf parents are it's composing leafs
void ClusterTree::mergeLeafs(Node* leaf1, Node* leaf2) {
	Node newLeaf(new Cluster(leaf1->cluster, leaf2->cluster), std::vector<Node*>(leaf1, leaf2));

	leaf1->addChild(&newLeaf);
	leaf2->addChild(&newLeaf);

	size++;
}

void ClusterTree::addNode(Node* parentNode, Cluster* nodeCluster) {
	Node node(nodeCluster, parentNode);

	parentNode->addChild(&node);

	size++;
}

void ClusterTree::addNode(std::vector<Node*> parentNodes, Cluster* nodeCluster) {
	Node node(nodeCluster, parentNodes);
	
	for (Node* parentNode : parentNodes)
		parentNode->addChild(&node);

	size++;
	//node->parents.insert(node->parents.end(), parentNodes.begin(), parentNodes.end());
}

int ClusterTree::getTreeSize() {
	return size;
}