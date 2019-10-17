#pragma once
#include<vector>
#include<stack>

struct NodeTree {
	int key;

	NodeTree* left;
	NodeTree* right;

	NodeTree(int key);
};

class BinaryTree
{
public:
	NodeTree* root;

	BinaryTree();

	NodeTree* search(NodeTree* &node, int key);
	bool insertNode(NodeTree* &node, int key);
	bool deleteNode(NodeTree*& node, int key);

	int upwardTraversal(NodeTree* node, std::vector<NodeTree*> &result);
	int downwardTraversal(NodeTree* node);
	void mixedTraversal(NodeTree* node, int &k, NodeTree* &result);

private:
	std::stack<NodeTree*> stack;
	std::stack<int> hightStack;

};

