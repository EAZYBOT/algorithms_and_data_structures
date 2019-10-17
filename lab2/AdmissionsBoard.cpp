#include "AdmissionsBoard.h"

AdmissionsBoard::AdmissionsBoard()
{
	enrollees = new MultiplyLinkedList<Enrolle>(5);
}

AdmissionsBoard::~AdmissionsBoard()
{
	delete enrollees;
}

void AdmissionsBoard::addEnrollee(Enrolle* enrollee)
{
	enrollees->insertItem(enrollee);
	enrollees->setLastListItem(0);

	if (enrollee->markIT == 5 && enrollee->markMath == 5 && enrollee->markRussian == 5) {
		enrollees->insertCurrentItemToDescriptor((unsigned int)EnrolleeCriteria::HAS_MAX_ENTRY_EXAM_SCORE);
	}

	if (enrollee->hasSchoolCertificateWithHonours) {
		enrollees->insertCurrentItemToDescriptor((unsigned int)EnrolleeCriteria::HAS_SCHOOL_CERTIFICATE_WITH_HONOURS);
	}

	if (enrollee->locality != universityLocation) {
		enrollees->insertCurrentItemToDescriptor((unsigned int)EnrolleeCriteria::LIVES_FAR_FROM_UNIVERSITY);
	}

	if (enrollee->needsHostel) {
		enrollees->insertCurrentItemToDescriptor((unsigned int)EnrolleeCriteria::NEEDS_HOSTEL);
	}
}

void AdmissionsBoard::deleteEnrollee(unsigned int id)
{
	enrollees->setFirstListItem((unsigned int)EnrolleeCriteria::WITHOUT_CRITERIA);

	for (unsigned int i = 0; i < enrollees->sizeList(); i++) {
		if (enrollees->getCurrentItemData()->id == id) {
			enrollees->deleteCurrentItem();
			break;
		}

		enrollees->toNextItem((unsigned int)EnrolleeCriteria::WITHOUT_CRITERIA);
	}
}

std::vector<Enrolle*> AdmissionsBoard::getAllEnrollees()
{
	return getAllEnrolleesByCriteria(EnrolleeCriteria::WITHOUT_CRITERIA);
}

std::vector<Enrolle*> AdmissionsBoard::getAllEnrolleesByCriteria(EnrolleeCriteria criterion)
{
	std::vector<Enrolle*> result;

	enrollees->setFirstListItem((unsigned int)criterion);

	while (enrollees->checkExistCurrentListItem()) {
		result.push_back(enrollees->getCurrentItemData());
		enrollees->toNextItem((unsigned int)criterion);
	}

	return result;
}

void AdmissionsBoard::deleteAllEnrollees()
{
	delete enrollees;
	enrollees = new MultiplyLinkedList<Enrolle>(5);
}
