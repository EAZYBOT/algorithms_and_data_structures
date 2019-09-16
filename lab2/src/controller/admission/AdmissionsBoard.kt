package controller.admission

import model.enrollee.Enrollee
import model.enrollee.EnrolleeCriteria
import model.exam.ExamMark
import model.list.MultiplyLinkedList

class AdmissionsBoard {
    private val universityLocation = "орел"
    private val enrollees = MultiplyLinkedList<EnrolleeCriteria, Enrollee>()

    fun addEnrollee(enrollee: Enrollee) {
        val criteria = HashSet<EnrolleeCriteria>()
        with(enrollee) {
            if (hasSchoolCertificateWithHonours) {
                criteria.add(EnrolleeCriteria.HAS_SCHOOL_CERTIFICATE_WITH_HONOURS)
            }

            if (needsHostel) {
                criteria.add(EnrolleeCriteria.NEEDS_HOSTEL)
            }

            run {
                val locality = locality.toLowerCase().replace('ё', 'е')
                if (locality != universityLocation) {
                    criteria.add(EnrolleeCriteria.LIVES_FAR_FROM_UNIVERSITY)
                }
            }

            if (entrySubjectToMark.values.all { it == ExamMark.A }) {
                criteria.add(EnrolleeCriteria.HAS_MAX_ENTRY_EXAM_SCORE)
            }
        }

        enrollees.add(enrollee, criteria)
    }

    fun deleteEnrollee(index: Int) {
        enrollees.deleteByIndex(index)
    }

    fun getAllEnrollees(): List<Enrollee> {
        return enrollees.getAllItems()
    }

    fun getAllEnrolleesByCriteria(
        criteria: EnrolleeCriteria
    ): List<Enrollee> {
        return enrollees.getAllItemsByCriteria(criteria)
    }

    fun deleteAllEnrollees() {
        while (!enrollees.isEmpty()) {
            enrollees.deleteByIndex(0)
        }
    }
}