import model.enrollee.Enrollee
import model.enrollee.EnrolleeCriteria
import model.list.MultiplyLinkedList
import java.lang.reflect.TypeVariable

fun main() {
    for (i in EnrolleeCriteria.values()) {
        println(i)
    }
    val map = mutableMapOf<Int, String>(
        1 to "1",
        2 to "2",
        3 to "3",
        4 to "4"
    )
    val i = map[2]!!
    map.set(2, i)
}