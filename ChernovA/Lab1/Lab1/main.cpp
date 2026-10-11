#include <iostream>
#include "tbitfield.h"
#include "tset.h"

int main() {
	TBitField a(8);
	a.SetBit(0);
	a.SetBit(3);
	std::cout << "a = " << a << std::endl;

	TBitField b = ~a;
	std::cout << "~a = " << b << std::endl;

	TSet s(8);
	s.InsElem(2);
	s.InsElem(5);
	std::cout << "s = " << s << std::endl;
	std::cout << "s + 7 = " << (s + 7) << std::endl;

	return 0;
}