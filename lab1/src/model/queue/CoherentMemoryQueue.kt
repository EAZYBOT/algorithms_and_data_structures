package model.queue

class CoherentMemoryQueue<T>(private val maxLength: Int = 5) : QueueInterface<T> {

    private val queue: Array<T?> = Array<Any?>(maxLength) { null } as Array<T?>
    private var head = 0
    private var tail = 0
    private var elementCount = 0

    override fun add(element: T): Boolean {
        if (elementCount >= maxLength) {
            return false
        }

        queue[tail % maxLength] = element
        tail = (tail + 1) % maxLength
        elementCount++

        return true
    }

    override fun poll(): T? {
        if (elementCount <= 0) {
            return null
        }

        elementCount--
        val returnElement = queue[head]
        head = (head + 1) % maxLength

        return returnElement
    }

    override fun peek(): T? {
        if (elementCount <= 0) {
            return null
        }

        return queue[head]
    }

    override fun removeHead() {
        if (elementCount <= 0) { return }

        elementCount--
        head = (head + 1) % maxLength
    }

    override fun isEmpty() = elementCount <= 0

    override fun getAllElements(): List<T> {
        val returnList = mutableListOf<T>()
        for (i in 0 until elementCount) {
            returnList.add(queue[(i + head) % maxLength]!!)
        }

        return returnList
    }
}