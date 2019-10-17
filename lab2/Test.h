#pragma once
#include<vector>
#include<string>
#include"AdmissionsBoard.h"

void test(AdmissionsBoard &board) {


	Enrolle* enrolle = new Enrolle();
	enrolle->id = 1;
	enrolle->secondName = "Test";
	enrolle->markRussian = 5;
	enrolle->markMath = 5;
	enrolle->markIT = 5;
	enrolle->locality = "Orel";
	enrolle->hasSchoolCertificateWithHonours = true;
	enrolle->needsHostel = false;
	board.addEnrollee(enrolle);

	enrolle = new Enrolle();
	enrolle->id = 2;
	enrolle->secondName = "Test2";
	enrolle->markRussian = 5;
	enrolle->markMath = 4;
	enrolle->markIT = 5;
	enrolle->locality = "Texas";
	enrolle->hasSchoolCertificateWithHonours = false;
	enrolle->needsHostel = true;
	board.addEnrollee(enrolle);

	enrolle = new Enrolle();
	enrolle->id = 3;
	enrolle->secondName = "Test3";
	enrolle->markRussian = 5;
	enrolle->markMath = 5;
	enrolle->markIT = 5;
	enrolle->locality = "Moscow";
	enrolle->hasSchoolCertificateWithHonours = true;
	enrolle->needsHostel = true;
	board.addEnrollee(enrolle);

	enrolle = new Enrolle();
	enrolle->id = 4;
	enrolle->secondName = "Test4";
	enrolle->markRussian = 3;
	enrolle->markMath = 5;
	enrolle->markIT = 3;
	enrolle->locality = "Orel";
	enrolle->hasSchoolCertificateWithHonours = false;
	enrolle->needsHostel = false;
	board.addEnrollee(enrolle);

	enrolle = new Enrolle();
	enrolle->id = 5;
	enrolle->secondName = "Test5";
	enrolle->markRussian = 5;
	enrolle->markMath = 5;
	enrolle->markIT = 4;
	enrolle->locality = "Moscow";
	enrolle->hasSchoolCertificateWithHonours = true;
	enrolle->needsHostel = false;
	board.addEnrollee(enrolle);
}