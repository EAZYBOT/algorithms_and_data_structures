#pragma once
#include<string>
#include<vector>
#include"Enrollee.h"
#include"MultiplyLinkedList.h"

enum EnrolleeCriteria
{
	WITHOUT_CRITERIA = 0,
	HAS_MAX_ENTRY_EXAM_SCORE,
	HAS_SCHOOL_CERTIFICATE_WITH_HONOURS,
	LIVES_FAR_FROM_UNIVERSITY,
	NEEDS_HOSTEL
};

class AdmissionsBoard
{
public:
	AdmissionsBoard();
	~AdmissionsBoard();

	void addEnrollee(Enrolle* enrollee);
	void deleteEnrollee(unsigned int id);
	std::vector<Enrolle*> getAllEnrollees();
	std::vector<Enrolle*> getAllEnrolleesByCriteria(EnrolleeCriteria criterion);
	void deleteAllEnrollees();

private:
	MultiplyLinkedList<Enrolle>* enrollees;
	std::string universityLocation = "Orel";
};

