#include <iostream>
#include "Vector.h"


void print(Vector& vector) {
    for (size_t i = 0; i < vector.size(); i++) {
        std::cout << vector[i] << "\n";
    }
    std::cout << "---\n";
}

int main() {

    Value* array = new Value[3];
    array[0] = 0;
    array[1] = 1;
    array[2] = 2;

    Vector first(array, 3, 0.1);
    std::cout << first.capacity() << std::endl;
    first.pushBack(3);
    first.pushBack(4);
    first.pushBack(5);
    std::cout << first.capacity() << std::endl;
    print(first);
    first.popBack();
    first.popFront();
    print(first);
    Vector second;
    second.insert(first, 0);
    second.pushBack(11);
    second.pushFront(111);
    print(second);
    first.insert(3, 1);
    first.insert(2, 1);
    first.insert(1, 1);
    print(first);
    second.insert(first, 0);
    print(second);
    second.popBack();
    second.popFront();
    print(second);
    second.erase(0, 3);
    print(second);
    second.insert(second, 1);
    //second.insert(second, 2);
    print(second);
    second.eraseBetween(2, 5);
    print(second);

    return 0;
}

