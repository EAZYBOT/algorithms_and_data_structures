#include <iostream>
#include <vector>
#include "BinaryTree.h"

using namespace std;

NodeTree::NodeTree(int key)
{
	this->key = key;
	left = nullptr;
	right = nullptr;
}

BinaryTree::BinaryTree()
{
	this->root = nullptr;
}

NodeTree* BinaryTree::search(NodeTree* &node, int key)
{
	if (node == nullptr) {
		return nullptr;
	}

	if (node->key > key) {
		return search(node->left, key);
	}
	else if (node->key < key) {
		return search(node->right, key);
	}
	else {
		return node;
	}
}

bool BinaryTree::insertNode(NodeTree* &node, int key)
{
	if (node == nullptr) {
		node = new NodeTree(key);
		return true;
	}

	if (node->key == key) {
		return false;
	}
	else if (node->key > key) {
		return insertNode(node->left, key);
	}
	else {
		return insertNode(node->right, key);
	}
	
}

bool BinaryTree::deleteNode(NodeTree*& node, int key)
{
	if (node == nullptr) {
		return false;
	}

	if (node->key > key) {
		return deleteNode(node->left, key);
	}
	else if (node->key < key) {
		return deleteNode(node->right, key);
	}
	else {
		NodeTree* tmpPtr = node;

		if (node->left != nullptr && node->right == nullptr) {
			node = node->left;
		}
		else if (node->left == nullptr && node->right != nullptr) {
			node = node->right;
		}
		else if (node->left != nullptr && node->right != nullptr) {
			NodeTree* preMostLeft = node->right;
			NodeTree* mostLeft = preMostLeft->left;
			

			while (mostLeft->left != nullptr)
			{
				preMostLeft = mostLeft;
				mostLeft = mostLeft->left;
			}

			preMostLeft->left = nullptr;

			node = mostLeft;
			node->left = tmpPtr->left;
			node->right = tmpPtr->right;
		}
		else {
			node = nullptr;
		}

		delete tmpPtr;

		return true;
	}
}

int BinaryTree::upwardTraversal(NodeTree* node, vector<NodeTree*> &result)
{
	if (node == nullptr) {
		return 0;
	}

	int numResult = 1;

	int numLeft = upwardTraversal(node->left, result);
	int numRight = upwardTraversal(node->right, result);

	if (abs(numLeft - numRight) == 1) {
		result.push_back(node);
	}

	numResult += numLeft + numRight;

	return numResult;
}

int BinaryTree::downwardTraversal(NodeTree* node)
{
	int currentHight = 0;
	int maxHight = currentHight;

	while (true) {
		currentHight++;

		if (currentHight > maxHight) {
			maxHight = currentHight;
		}

		if (node->left != nullptr && node->right != nullptr) {
			stack.push(node->right);
			hightStack.push(currentHight);

			node = node->left;
		}
		else if (node->left == nullptr && node->right == nullptr) {
			if (!stack.empty()) {
				node = stack.top();
				stack.pop();

				currentHight = hightStack.top();
				hightStack.pop();
			}
			else {
				break;
			}
		}
		else if (node->left != nullptr) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}

	return maxHight;
}

void BinaryTree::mixedTraversal(NodeTree* node, int &k, NodeTree* &result)
{
	if (node == nullptr) {
		return;
	}

	mixedTraversal(node->left, k, result);

	if (node->left == nullptr && node->right == nullptr) {
		k--;
		if (k == 0) {
			result = node;
		}
		return;
	}
	
	mixedTraversal(node->right, k, result);
}
