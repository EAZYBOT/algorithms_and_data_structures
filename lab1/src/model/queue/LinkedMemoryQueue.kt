package model.queue

class LinkedMemoryQueue<T> : QueueInterface<T> {
    private var firstElement: LinkedListElement<T>? = null

    override fun peek(): T? {
        return firstElement?.data
    }

    override fun poll(): T? {
        if (isEmpty()) {
            return null
        }

        val returnElement = firstElement
        firstElement = firstElement?.next

        return returnElement?.data
    }

    override fun removeHead() {
        if (isEmpty()) { return }

        firstElement = firstElement?.next
    }

    override fun add(element: T): Boolean {
        if (isEmpty()) {
            firstElement = LinkedListElement(element)
        } else {
            var lastElement = firstElement
            while (lastElement?.next != null) {
                lastElement = lastElement.next
            }

            lastElement?.next = LinkedListElement(element)
        }

        return true
    }

    override fun isEmpty() = firstElement == null

    override fun getAllElements(): List<T> {
        return if (isEmpty()) {
            emptyList()
        } else {
            val elements = mutableListOf(firstElement!!.data)

            var currentElement = firstElement?.next
            while (currentElement != null) {
                elements.add(currentElement.data)
                currentElement = currentElement.next
            }

            elements
        }
    }
}

data class LinkedListElement<T> (
    val data: T,
    var next: LinkedListElement<T>? = null
)