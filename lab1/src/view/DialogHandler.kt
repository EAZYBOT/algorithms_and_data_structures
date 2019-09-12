package view

import controller.Producer
import model.production.ElType
import model.queue.LinkedMemoryQueue
import java.util.*
import kotlin.system.exitProcess

class DialogHandler {
    private val productsQueue = LinkedMemoryQueue<ElType>()
    private val producer = Producer(productsQueue)
    private var shouldRun = true
    private val scanner = Scanner(System.`in`)

    init {
        listOf(
            ElType("Car1", 1),
            ElType("Car2", 2),
            ElType("Car3", 3),
            ElType("Car4", 2),
            ElType("Car5", 4),
            ElType("Car6", 1)
        ).forEach { producer.addProduct(it) }
    }

    fun start() {
        while (shouldRun) {
            printMenu()

            when (scanner.next()) {
                "1" -> requestNewProduct()
                "2" -> makeTick()
                "3" -> cancelProduct()
                "4" -> printProductsQueue()
                "5" -> reset()
                "0" -> exitProcess(0)

                else -> println("Некорректный ввод")
            }
        }
    }

    private fun printMenu() {
        println("""
            
            ===============================
            1) Добавить деталь
            2) Сделать тик
            3) Отменить производство детали
            4) Вывести все детали в очереди
            5) Сбросить производство
            0) Выйти
            ===============================
        
        """.trimIndent())
    }

    private fun requestNewProduct() {
        print("Введите код детали: ")
        val code = scanner.next()

        var productionTime = -1
        while (productionTime <= 0) {
            print("Введите время производства: ")
            val userInput = scanner.next()
            productionTime = try {
                userInput.toInt()
            } catch (ex: NumberFormatException) {
                -1
            }
        }

        val newElement = ElType(code, productionTime)
        val isAddedSuccessfully = producer.addProduct(newElement)

        if (!isAddedSuccessfully) {
            println("Элемент не добавлен т.к. чередь переполнена!")
        }
    }

    private fun makeTick() {
        if (producer.currentProduct == null) {
            println("\nОчередь пуста!")
            return
        }

        val isProduced = producer.makeTick()
        println("""
                Продукт произведен: $isProduced
                Текущий продукт: ${producer.currentProduct}
                Осталось тиков до производства: ${producer.currentProductRemainingTime}
            """.trimIndent())
    }

    private fun printProductsQueue() {
        println("-------Элементы в очереди-------")
        producer.getAllProducts().forEach { println(it) }
        println("--------------------------------")
    }

    private fun cancelProduct() {
        println("\nОтмена производства продукта ${producer.currentProduct}")
        producer.cancelCurrentProduct()
    }

    private fun reset() = producer.reset()
}