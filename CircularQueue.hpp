#ifndef CIRCULAR_QUEUE_HPP
#define CIRCULAR_QUEUE_HPP

#include <array>
#include <stdexcept>
#include <cstddef>
#include <iterator>

template<typename T, std::size_t Capacity>
class CircularQueue {
    static_assert(Capacity > 0, "Capacity must be greater than 0");

private:
    std::array<T, Capacity> buffer;  // внутренний массив для хранения элементов
    std::size_t head = 0;            // индекс на самый старый (первый) элемент очереди
    std::size_t tail = 0;            // индекс для вставки следующего элемента
    bool full = false;               // флаг, указывающий, что очередь заполнена

public:
    CircularQueue() = default;
    ~CircularQueue() = default;

    // Проверка на пустоту очереди
    bool isEmpty() const {
        return (!full && (head == tail));
    }

    // Проверка на заполненность очереди
    bool isFull() const {
        return full;
    }

    // Получение текущего числа элементов в очереди
    std::size_t size() const {
        if (full)
            return Capacity;
        if (tail >= head)
            return tail - head;
        return Capacity - head + tail;
    }

    // Возвращает максимально допустимое количество элементов
    std::size_t capacity() const {
        return Capacity;
    }

    // Метод push добавляет элемент в очередь.
    // Если очередь заполнена, то самый старый элемент перезаписывается.
    void push(const T &item) {
        buffer[tail] = item;
        tail = (tail + 1) % Capacity;  // переход к следующей позиции с учетом цикличности

        // Если очередь уже была полной, смещаем head, чтобы "удалить" самый старый элемент
        if (full) {
            head = (head + 1) % Capacity;
        } else if (tail == head) {
            // Если после вставки tail совпал с head, значит, очередь стала полной
            full = true;
        }
    }

    // Метод pop удаляет (выбирает) самый старый элемент очереди.
    // Если очередь пуста, генерируется исключение.
    void pop() {
        if (isEmpty())
            throw std::runtime_error("Queue is empty");
        head = (head + 1) % Capacity;
        full = false;  // после удаления очередь не может быть полной
    }

    // Возвращает константную ссылку на первый (самый старый) элемент очереди.
    const T &front() const {
        if (isEmpty())
            throw std::runtime_error("Queue is empty");
        return buffer[head];
    }

    // Возвращает ссылку на первый (самый старый) элемент очереди.
    T &front() {
        if (isEmpty())
            throw std::runtime_error("Queue is empty");
        return buffer[head];
    }

    // --- Реализация итераторов для поддержки STL алгоритмов ---

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using reference = T &;
        using pointer = T *;
        using difference_type = std::ptrdiff_t;

        // Конструктор итератора.
        // queue_ptr - указатель на объект очереди,
        // pos - текущая позиция в буфере,
        // count - число уже пройденных элементов (нужно для определения конца итерации)

        iterator(CircularQueue* queue_ptr, std::size_t pos, std::size_t count)
            : queue_ptr(queue_ptr), pos(pos), count(count) {}

        reference operator*() {
            return queue_ptr->buffer[pos];
        }

        pointer operator->() {
            return &queue_ptr->buffer[pos];
        }

        // Префиксный инкремент
        iterator &operator++() {
            pos = (pos + 1) % Capacity;
            ++count;
            return *this;
        }

        // Постфиксный инкремент
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        // Сравнение итераторов: считаем, что итераторы равны, если пройденное количество элементов совпадает
        bool operator==(const iterator &other) const {
            return count == other.count;
        }

        bool operator!=(const iterator &other) const {
            return !(*this == other);
        }

    private:
        CircularQueue* queue_ptr;  // указатель на очередь
        std::size_t pos;           // текущая позиция в циклическом буфере
        std::size_t count;         // число пройденных элементов
    };

    // Возвращает итератор на первый элемент очереди
    iterator begin() {
        return iterator(this, head, 0);
    }

    // Возвращает итератор, указывающий на конец последовательности элементов очереди
    iterator end() {
        return iterator(this, tail, size());
    }
};

#endif // CIRCULAR_QUEUE_HPP