package controller

import model.production.ElType
import model.queue.LinkedMemoryQueue
import model.queue.QueueInterface

class Producer(queue: QueueInterface<ElType>? = null) {
    private val queue: QueueInterface<ElType> = queue ?: LinkedMemoryQueue()
    var currentProduct: ElType? = null
        get() = queue.peek()
        private set

    var currentProductRemainingTime = currentProduct?.productionTime ?: 0
        private set

    /**
     * Makes one production tick
     *
     * @returns 'true' if element got produced after this tick 'false' - otherwise
     */
    fun makeTick(): Boolean {
        if (currentProduct == null) {
            return false
        }

        currentProductRemainingTime--
        return if (currentProductRemainingTime <= 0) {
            getNextProduct()
            true
        } else {
            false
        }
    }

    fun addProducts(products: List<ElType>) {
        if (products.isEmpty()) { return }

        // if there were no products in queue, set production time according to new product
        val shouldUpdateTime = queue.isEmpty()
        products.forEach { queue.add(it) }

        if (shouldUpdateTime) {
            currentProductRemainingTime = queue.peek()!!.productionTime
        }
    }

    /**
     * Cancel current product and gets next out of production queue
     */
    fun cancelCurrentProduct() {
        getNextProduct()
    }

    fun reset() {
        currentProductRemainingTime = 0
        while (!queue.isEmpty()) {
            queue.removeHead()
        }
    }

    private fun getNextProduct() {
        queue.removeHead()
        currentProduct = queue.peek()
        currentProductRemainingTime = currentProduct?.productionTime ?: 0
    }

    fun getAllProducts() = queue.getAllElements()
}