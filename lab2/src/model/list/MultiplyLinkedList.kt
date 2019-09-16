package model.list

import java.lang.IndexOutOfBoundsException

class MultiplyLinkedList<C: Enum<C>, T> {
    inner class ListItem<T>(
        val id: Int,
        val data: T,
        val criteriaToNextItem: HashMap<Enum<C>, ListItem<T>?> = HashMap(),
        var next: ListItem<T>? = null
    )

    inner class Descriptor {
        var root: ListItem<T>? = null
        var last: ListItem<T>? = null
    }

    private val criteriaToDescriptors = HashMap<C, Descriptor>()
    private val mainDescriptor = Descriptor() // contains all items
    private var idCounter = 0

    fun isEmpty(): Boolean = mainDescriptor.root == null

    fun add(data: T, criteriaSet: Set<C>) {
        val listItem = ListItem(idCounter, data)

        // list is empty
        if (mainDescriptor.root == null) {
            mainDescriptor.root = listItem
            mainDescriptor.last = listItem
            criteriaSet.forEach { initNewDescriptor(listItem, it) }

            return
        }

        mainDescriptor.last?.next = listItem
        mainDescriptor.last = listItem

        criteriaSet.forEach { criteria ->
            val descriptor = criteriaToDescriptors[criteria]
            if (descriptor == null) {
                initNewDescriptor(listItem, criteria)
            } else {
                descriptor.last?.next = listItem
                descriptor.last = listItem
            }
        }

        idCounter++
    }

    private fun initNewDescriptor(data: ListItem<T>, criteria: C) {
        criteriaToDescriptors[criteria] = Descriptor()
        criteriaToDescriptors[criteria]!!.root = data
        criteriaToDescriptors[criteria]!!.last = data
    }

    fun getByIndex(index: Int): ListItem<T> {
        var counter = 0
        var resultItem = mainDescriptor.root
        while (counter != index && resultItem != null) {
            resultItem = resultItem.next
            counter++
        }

        if (resultItem == null || counter != index) {
            throw IndexOutOfBoundsException()
        }

        return resultItem
    }

    fun getByIndexAndCriteria(index: Int, criteria: C): T {
        var counter = 0
        var resultItem = criteriaToDescriptors[criteria]?.root
        while (counter != index && resultItem != null) {
            resultItem = resultItem.criteriaToNextItem[criteria]
            counter++
        }

        if (resultItem == null || counter != index) {
            throw IndexOutOfBoundsException()
        }

        return resultItem.data
    }

    fun deleteByIndex(index: Int) {
        val neededItem = getByIndex(index)
        val neededId = neededItem.id

        var currentItem = mainDescriptor.root
        while (currentItem != null) {
            for (key in currentItem.criteriaToNextItem.keys) {
                if (currentItem.criteriaToNextItem[key]?.id == neededId) {
                    currentItem.criteriaToNextItem[key] = currentItem.criteriaToNextItem[key]?.next
                }
            }

            currentItem = currentItem.next
        }
    }

    fun getLastItem(): T? = mainDescriptor.last?.data

    fun getLastByCriteria(criteria: C): T? {
        return criteriaToDescriptors[criteria]?.last?.data
    }

    fun getAllItems(): List<T> {
        val resultList = mutableListOf<T>()

        var item = mainDescriptor.root
        while (item != null) {
            resultList.add(item.data)
            item = item.next
        }

        return resultList
    }

    fun getAllItemsByCriteria(criteria: C): List<T> {
        val resultList = mutableListOf<T>()

        var item = criteriaToDescriptors[criteria]?.root
        while (item != null) {
            resultList.add(item.data)
            item = item.criteriaToNextItem[criteria]
        }

        return resultList
    }
}