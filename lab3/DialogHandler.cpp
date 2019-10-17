#include "DialogHandler.h"
#include <iostream>

using namespace std;

DialogHandler::DialogHandler()
{
	ifstream f;
	f.open("data.txt");

	while (!f.eof()) {
		int num;
		f >> num;
		tree.insertNode(tree.root, num);
	}
}

void DialogHandler::printMenu()
{
	cout << "Menu" << endl << endl;
	cout << "1) Find Nodes Which Hight Differs By 1" << endl;
	cout << "2) Tree Hight" << endl;
	cout << "3) Find k-th Leaf From Left To Right" << endl;
	cout << "4) Delete Node" << endl << endl;
	cout << "0) Exit" << endl << endl;
}

void DialogHandler::start()
{
	int choice;
	bool isRunning = true;

	while (isRunning) {
		system("cls");
		printMenu();

		cout << "Your choice: ";
		cin >> choice;
		system("cls");

		switch (choice)
		{
		case 1:
			findNodesDifferByOne();
			break;

		case 2:
			treeHight();
			break;

		case 3:
			findLeafByNumber();
			break;

		case 4:
			deleteNode();
			break;

		case 0:
			isRunning = false;
			break;

		default:
			break;
		}
	}
}

void DialogHandler::findNodesDifferByOne()
{
	system("cls");

	vector<NodeTree*> nodes;
	tree.upwardTraversal(tree.root, nodes);

	for (NodeTree* node : nodes) {
		cout << node->key << ' ';
	}

	system("pause");
}

void DialogHandler::treeHight()
{
	system("cls");

	cout << tree.downwardTraversal(tree.root) << endl;

	system("pause");
}

void DialogHandler::findLeafByNumber()
{
	system("cls");

	int k;
	cout << "Enter k: ";
	cin >> k;

	system("cls");

	NodeTree* result = nullptr;
	tree.mixedTraversal(tree.root, k, result);

	if (result == nullptr) {
		cout << "None" << endl;
	}
	else {
		cout << result->key << endl;
	}

	system("pause");
}

void DialogHandler::deleteNode()
{
	system("cls");

	int k;
	cout << "Enter key: ";
	cin >> k;

	system("cls");

	if (tree.deleteNode(tree.root, k)) {
		cout << "Success" << endl;
	}
	else {
		cout << "Fail" << endl;
	}
	

	system("pause");
}
