#pragma once
#include<iostream>
#include<cstdlib>
#include"AdmissionsBoard.h"

class DialogHandler
{
public:
	void printMenu();
	void printSubMenu();

	void addEnrollee();
	void printAllEnrollees();
	void printEnrolleesByCriteria();
	void deleteEnrollee();
	void deleteAllEnrollees();

	void start();

	void printEnrollee(Enrolle* enrollee);

private:
	AdmissionsBoard board;

	unsigned int checkMark(unsigned int mark);
	bool transformChoice(char choice);
};

