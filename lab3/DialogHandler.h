#pragma once
#include<fstream>
#include<cstdlib>
#include"BinaryTree.h"

class DialogHandler
{
public:
	DialogHandler();

	void printMenu();

	void start();

	void findNodesDifferByOne();
	void treeHight();
	void findLeafByNumber();
	void deleteNode();

private:
	BinaryTree tree;
};

