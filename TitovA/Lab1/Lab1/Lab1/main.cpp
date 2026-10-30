#include "tbitfield.h"
#include "tset.h"

#include <iostream>


int main()
{
    //TBitField a(4);
    //TBitField b(4);

    //a.SetBit(0);
   // a.SetBit(2);

   // b.SetBit(1);
    //b.SetBit(2);

    //std::cout << "a = " << a << '\n';
   // std::cout << "b = " << b << '\n';

   // TBitField c = a | b;
   // TBitField d = a & b;
   // TBitField e = ~a;

    //std::cout << "a | b = " << c << '\n';
   // std::cout << "a & b = " << d << '\n';
    //std::cout << "~a = " << e << '\n';

    //std::cout << "a == b: " << (a == b) << '\n';
    //std::cout << "a != b: " << (a != b) << '\n';


    TSet a(5);
    TSet b(5);

    a.InsElem(1);
    a.InsElem(2);

    b.InsElem(2);
    b.InsElem(3);

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';

    std::cout << "a + b = " << (a + b) << '\n';
    std::cout << "a * b = " << (a * b) << '\n';

    std::cout << "a + 4 = " << (a + 4) << '\n';
    std::cout << "a - 1 = " << (a - 1) << '\n';

    TSet c = ~a;
    std::cout << "~a = " << c << '\n';

    std::cout << "2 in a: " << a.IsMember(2) << '\n';
    std::cout << "a == b: " << (a == b) << '\n'; 

    return 0;
}
