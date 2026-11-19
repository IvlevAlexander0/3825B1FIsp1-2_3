#include <iostream>
#include "../../../includes/Lab1/tbitfield.h"
#include "../../../includes/Lab1/tset.h"
#include <stdexcept> //исключения

int main() {
    TSet s1(8);
    s1.InsElem(2);
    s1.InsElem(5);
    s1.InsElem(7);

    std::cout << "1. Set s1: " << s1 << std::endl;
    //ожидаем: {2, 5, 7} (а не 00100101 как раньше)

    std::cout << "\n2. Enter elements for set s2 (for example: '1 3 5'): ";
    TSet s2(45);
    try {
        std::cin >> s2;
        std::cout << "   You entered: " << s2 << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "   [ERROR CAUGHT] " << e.what() << std::endl;
    }

    std::cout << "\n3. Trying to add element 100 to set of size 8..." << std::endl;
    try {
        s1.InsElem(100); //это вызовет ошибку
    }
    catch (const std::out_of_range& e) {
        std::cout << "   [ERROR CAUGHT] " << e.what() << std::endl;
    }

    std::cout << "\n4. Trying to compare sets of different sizes..." << std::endl;
    TSet s3(16);
    try {
        if (s1 == s3) { //это вызовет ошибку (универс из 8 пытаемся сравнить с универсом из 16)
            std::cout << "Equal" << std::endl;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cout << "   [ERROR CAUGHT] " << e.what() << std::endl;
    }

    return 0;
}