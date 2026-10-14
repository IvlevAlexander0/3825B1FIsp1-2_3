#include <iostream>
#include "tbitfield.h"
#include <stdexcept>

int TBitField::GetMemIndex(const int n) const
{
	return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const
{
	return (TELEM)1 << n % 32;
}

TBitField::TBitField(int len)                  //                                   (#О1)
{
	if (len <= 0) { throw std::invalid_argument("Количество битов должно быть больше 0"); }
	BitLen = len;
	if (len % 32 == 0) { MemLen = len / 32; }
	else { MemLen = len / 32 + 1; }
	pMem = new TELEM[MemLen]();
}

TBitField::TBitField(const TBitField& bf)		//                                   (#П1)
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (size_t i = 0; i < MemLen; ++i) { pMem[i] = bf.pMem[i]; }
}

TBitField::~TBitField() { delete[] pMem; }		//                                    (#С)

int TBitField::GetLength(void) const
{
	return BitLen;
}

void TBitField::SetBit(const int n)
{
	if (n < 0 || n >= BitLen) { throw std::invalid_argument("Бит не должен выходить за границы битового поля"); }
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n)
{
	if (n < 0 || n >= BitLen) { throw std::invalid_argument("Бит не должен выходить за границы битового поля"); }
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const
{
	if (n < 0 || n >= BitLen) { throw std::invalid_argument("Бит не должен выходить за границы битового поля"); }
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

int TBitField::operator==(const TBitField& bf) const
{
	if (BitLen != bf.BitLen) { return 0; }
	for (size_t i = 0; i < MemLen; ++i) {
		if (pMem[i] != bf.pMem[i]) {
			return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const
{
	return !(*this == bf);
}

TBitField& TBitField::operator=(const TBitField& bf)
{
	if (*this != bf)
	{
		delete[] pMem;
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;
		pMem = new TELEM[MemLen];
		for (size_t i = 0; i < MemLen; ++i) { pMem[i] = bf.pMem[i]; }
	}
	return *this;
}

TBitField  TBitField::operator|(const TBitField& bf)
{
	TBitField res(*this);
	if (BitLen != bf.BitLen) { throw std::invalid_argument("Не равны длинны битового поля"); }
	for (size_t i = 0; i < MemLen; ++i) {
		res.pMem[i] |= bf.pMem[i];
	}
	return res;
}

TBitField  TBitField::operator&(const TBitField& bf)
{
	TBitField res(*this);
	if (BitLen != bf.BitLen) { throw std::invalid_argument("Не равны длинны битового поля"); }
	for (size_t i = 0; i < MemLen; ++i) {
		res.pMem[i] &= bf.pMem[i];
	}
	return res;
}

TBitField  TBitField::operator~(void)
{
	TBitField res(*this);
	for (size_t i = 0; i < MemLen; ++i) {
		res.pMem[i] = ~pMem[i];
	}
	return res;
}

std::istream& operator>>(std::istream& istr, TBitField& bf)
{
	char is;
	int len = bf.GetLength();
	for (size_t i = 0; i < len; ++i) {
		istr >> is;
		if (is == '0') {
			bf.ClrBit(i);
		}
		else if (is == '1') {
			bf.SetBit(i);
		}
		else {
			throw std::invalid_argument("Введено неверное значение");
		}
	}
	return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf)
{
	int len = bf.GetLength();
	for (size_t i = 0; i < len; ++i) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}