package model.queue

class LinkedMemoryQueue<T> : QueueInterface<T> {
    private var firstElement: LinkedListElement<T>? = null
    private var lastElement: LinkedListElement<T>? = null

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
            lastElement = firstElement
        } else {
            lastElement?.next = LinkedListElement(element)
            lastElement = lastElement!!.next
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