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

void ClusterTree::getLeafsRecursiveFunc(std::vector<Node*>* leafs, Node* currentNode) {
	if (currentNode->childs.size() == 0) {
		leafs->push_back(currentNode);
		return;
	}

	for (auto child : currentNode->childs)
		getLeafsRecursiveFunc(leafs, child);
}

std::vector<ClusterTree::Node*> ClusterTree::getLeafs() {
	std::vector<Node*> leafs;

	getLeafsRecursiveFunc(&leafs, root);
	
	return leafs;
}



//merges two leafs into a new one, the new leaf parents are it's composing leafs
void ClusterTree::mergeLeafs(Node* leaf1, Node* leaf2) {
	std::vector<Node*> parents;
	parents.push_back(leaf1);
	parents.push_back(leaf2);
	Cluster newLeafCluster(leaf1->cluster, leaf2->cluster);
	Node newLeaf(&newLeafCluster, parents);


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
}

int ClusterTree::getTreeSize() {
	return size;
}