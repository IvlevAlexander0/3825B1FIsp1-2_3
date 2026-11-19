#include <gtest/gtest.h>
#include <iostream>
#include "..\..\..\includes\Lab1\tset.h"
#include "..\..\..\includes\Lab1\tbitfield.h"

int main() {
    TBitField f(10), g(10);
    f.SetBit(1); f.SetBit(4); f.SetBit(9);
    g.SetBit(4); g.SetBit(5);

    std::cout << "f = " << f << '\n';
    std::cout << "g = " << g << '\n';
    std::cout << "f | g = " << (f | g) << '\n';
    std::cout << "f & g = " << (f & g) << '\n';
    std::cout << "~f = " << ~f << '\n';

    TSet a(12), b(12);
    a.InsElem(1); a.InsElem(5); a.InsElem(11);
    b.InsElem(5); b.InsElem(6);

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "a + b = " << (a + b) << '\n';
    std::cout << "a * b = " << (a * b) << '\n';
    std::cout << "~a = " << ~a << '\n';
    std::cout << "a - 5 = " << (a - 5) << '\n';
    std::cout << "a + 0 = " << (a + 0) << '\n';
}