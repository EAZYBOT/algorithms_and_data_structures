package model.queue

interface QueueInterface<T> {
    /**
     * Adds element to queue
     *
     * @return 'true' if added successfully, 'false' - otherwise
     */
    fun add(element: T): Boolean

    /**
     * Retrieves and removes head
     */
    fun poll(): T?

    /**
     * Retrieves, but does not remove head
     */
    fun peek(): T?
    fun removeHead()
    fun isEmpty(): Boolean
    fun getAllElements(): List<T>
}