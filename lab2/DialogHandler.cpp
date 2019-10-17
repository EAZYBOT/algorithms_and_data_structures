#include "DialogHandler.h"
#include "Test.h"

using namespace std;

void DialogHandler::printMenu()
{
	cout << "Menu" << endl << endl;
	cout << "1) Add Enrollee" << endl;
	cout << "2) Print Enrollees By Criteria" << endl;
	cout << "3) Print All Enrollees" << endl;
	cout << "4) Delete Enrollee" << endl;
	cout << "5) Delete All Enrollees" << endl << endl;
	cout << "0) Exit" << endl << endl;
}

void DialogHandler::printSubMenu()
{
	cout << "Print By Criteria" << endl << endl;
	cout << "1) Max Entry Exam Score" << endl;
	cout << "2) School Certificate With Honors" << endl;
	cout << "3) Lives Far From University" << endl;
	cout << "4) Needs Hostel" << endl << endl;
	cout << "0) Back" << endl << endl;
}

void DialogHandler::addEnrollee()
{
	Enrolle* enrollee = new Enrolle();

	system("cls");

	cout << "Enter ID: ";
	cin >> enrollee->id;

	system("cls");

	cout << "Enter Second Name: ";
	cin >> enrollee->secondName;

	system("cls");

	cout << "Enter Score Russian Language: ";
	cin >> enrollee->markRussian;
	enrollee->markRussian = checkMark(enrollee->markRussian);

	system("cls");

	cout << "Enter Score Math: ";
	cin >> enrollee->markMath;
	enrollee->markMath = checkMark(enrollee->markMath);

	system("cls");

	cout << "Enter Score IT: ";
	cin >> enrollee->markRussian;
	enrollee->markIT = checkMark(enrollee->markIT);

	system("cls");

	cout << "Enter Locality: ";
	cin >> enrollee->locality;

	system("cls");

	char answer;
	cout << "Has School Certificate With Honours(y/n): ";
	cin >> answer;
	enrollee->hasSchoolCertificateWithHonours = transformChoice(answer);

	system("cls");

	cout << "Needs Hostel(y/n): ";
	cin >> answer;
	enrollee->needsHostel = transformChoice(answer);

	system("cls");

	board.addEnrollee(enrollee);
	cout << "Success" << endl;

	system("pause");
}

void DialogHandler::printAllEnrollees()
{
	vector<Enrolle*> enrollees = board.getAllEnrollees();

	system("cls");

	for (Enrolle* enrollee : enrollees) {
		printEnrollee(enrollee);
	}

	system("pause");
}

void DialogHandler::printEnrolleesByCriteria()
{
	int choice;

	system("cls");
	printSubMenu();

	cout << "Your choice: ";
	cin >> choice;
	system("cls");

	vector<Enrolle*> enrollees;

	switch (choice)
	{
	case 1:
		enrollees = board.getAllEnrolleesByCriteria(EnrolleeCriteria::HAS_MAX_ENTRY_EXAM_SCORE);
		break;

	case 2:
		enrollees = board.getAllEnrolleesByCriteria(EnrolleeCriteria::HAS_SCHOOL_CERTIFICATE_WITH_HONOURS);
		break;

	case 3:
		enrollees = board.getAllEnrolleesByCriteria(EnrolleeCriteria::LIVES_FAR_FROM_UNIVERSITY);
		break;

	case 4:
		enrollees = board.getAllEnrolleesByCriteria(EnrolleeCriteria::NEEDS_HOSTEL);
		break;

	default:
		return;
		break;
	}

	for (Enrolle* enrollee : enrollees) {
		printEnrollee(enrollee);
	}

	system("pause");
}

void DialogHandler::deleteEnrollee()
{
	system("cls");

	int id;
	cout << "Enter ID for deleting: ";
	cin >> id;

	system("cls");

	board.deleteEnrollee(id);
}

void DialogHandler::deleteAllEnrollees()
{
	board.deleteAllEnrollees();
}

void DialogHandler::start()
{
	test(board);

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
			addEnrollee();
			break;

		case 2:
			printEnrolleesByCriteria();
			break;

		case 3:
			printAllEnrollees();
			break;

		case 4:
			deleteEnrollee();
			break;

		case 5:
			deleteAllEnrollees();
			break;

		case 0:
			isRunning = false;
			break;

		default:
			break;
		}
	}
}

void DialogHandler::printEnrollee(Enrolle* enrollee)
{
	cout << "ID: " << enrollee->id << endl;
	cout << "Second Name: " << enrollee->secondName << endl;
	cout << "Score Russian Language: " << enrollee->markRussian << endl;
	cout << "Score Math: " << enrollee->markMath << endl;
	cout << "Score IT: " << enrollee->markIT << endl;
	cout << "Locality: " << enrollee->locality << endl;
	cout << "Has School Certificate With Honours: " << enrollee->hasSchoolCertificateWithHonours << endl;
	cout << "Needs Hostel: " << enrollee->needsHostel << endl << endl;
}

unsigned int DialogHandler::checkMark(unsigned int mark)
{
	return (mark > 5) ? 5 : mark;
}

bool DialogHandler::transformChoice(char choice)
{
	return tolower(choice) == 'y';
}
