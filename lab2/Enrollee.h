#pragma once
#include<string>

struct Enrolle {
	unsigned int id = 0;
	std::string secondName;

	unsigned int markRussian = 2;
	unsigned int markMath = 2;
	unsigned int markIT = 2;

	std::string locality;
	bool hasSchoolCertificateWithHonours = false;
	bool needsHostel = false;
};