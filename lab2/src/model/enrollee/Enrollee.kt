package model.enrollee

import model.exam.EntrySubject
import model.exam.ExamMark

data class Enrollee(
    val secondName: String,
    val entrySubjectToMark: Map<EntrySubject, ExamMark>,
    val locality: String,
    val hasSchoolCertificateWithHonours: Boolean = false,
    val needsHostel: Boolean = false
)