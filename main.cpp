// File: main.cpp

#include <iostream>
#include "CircularQueue.hpp"

int main() {
    CircularQueue<int, 5> queue;

    for (int i = 1; i <= 5; ++i) {
        queue.push(i);
    }

    std::cout << "Содержимое очереди после добавления 5 элементов:\n";
    for (const auto &elem : queue) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    queue.push(6);
    queue.push(7);

    std::cout << "Содержимое очереди после перезаписи старых элементов (добавление 6 и 7):\n";
    for (const auto &elem : queue) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    std::cout << "Первый элемент очереди: " << queue.front() << "\n";

    queue.pop();
    std::cout << "После удаления первого элемента, новый первый элемент: " << queue.front() << "\n";
    
    return 0;
}
