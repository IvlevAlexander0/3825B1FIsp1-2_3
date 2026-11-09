#include <iostream>
#include "tbitfield.h"
#include <stdexcept>

int TBitField::GetMemIndex(const int n) const
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const
{
	return (TELEM)1 << n % (sizeof(TELEM) * 8);
}

TBitField::TBitField(int len)                  //                                   (#О1)
{
	if (len < 0) { throw std::invalid_argument("Количество бит не может быть отрицательным"); }
	BitLen = len;
	if (len % (sizeof(TELEM) * 8) == 0) { MemLen = len / (sizeof(TELEM) * 8); }
	else { MemLen = len / (sizeof(TELEM) * 8) + 1; }
	if (MemLen > 0) {
		pMem = new TELEM[MemLen]();
	}
	else
		pMem = nullptr;
}

TBitField::TBitField(const TBitField& bf)		//                                   (#П1)
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	if (MemLen > 0) {
		pMem = new TELEM[MemLen];
	}
	else {
		pMem = nullptr;
	}
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
	size_t maxMem = (size_t)MemLen;
	if (bf.MemLen > MemLen) {
		maxMem = (size_t)bf.MemLen;
	}
	for (size_t i = 0; i < maxMem; ++i) {
		TELEM a = 0;
		if (i < (size_t)MemLen) {
			a = pMem[i];
		}
		TELEM b = 0;
		if (i < (size_t)bf.MemLen) {
			b = bf.pMem[i];
		}
		if (a != b) { return 0; }
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const
{
	return !(*this == bf);
}

TBitField& TBitField::operator=(const TBitField& bf)
{
	if (this != &bf)
	{
		TELEM* newMem = nullptr;
		if (bf.MemLen > 0) {
			newMem = new TELEM[bf.MemLen];
		}
		for (size_t i = 0; i < (size_t)bf.MemLen; ++i) {
			newMem[i] = bf.pMem[i];
		}
		delete[] pMem;
		pMem = newMem;
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;
	}
	return *this;
}

TBitField  TBitField::operator|(const TBitField& bf)
{
	int newLen = BitLen;
	if (bf.BitLen > BitLen) {
		newLen = bf.BitLen;
	}
	TBitField res(newLen);
	for (size_t i = 0; i < (size_t)res.MemLen; ++i) {
		TELEM a = 0;
		if (i < (size_t)MemLen) {
			a = pMem[i];
		}
		TELEM b = 0;
		if (i < (size_t)bf.MemLen) {
			b = bf.pMem[i];
		}
		res.pMem[i] = a | b;
	}
	return res;
}

TBitField  TBitField::operator&(const TBitField& bf)
{
	int newLen = BitLen;
	if (bf.BitLen > BitLen) {
		newLen = bf.BitLen;
	}
	TBitField res(newLen);
	for (size_t i = 0; i < (size_t)res.MemLen; ++i) {
		TELEM a = 0;
		if (i < (size_t)MemLen) {
			a = pMem[i];
		}
		TELEM b = 0;
		if (i < (size_t)bf.MemLen) {
			b = bf.pMem[i];
		}
		res.pMem[i] = a & b;
	}
	return res;
}

TBitField  TBitField::operator~(void)
{
	TBitField res(*this);
	for (size_t i = 0; i < MemLen; ++i) {
		res.pMem[i] = ~pMem[i];
	}
	if (BitLen % (sizeof(TELEM) * 8) != 0) {
		TELEM mask = ((TELEM)1 << BitLen % (sizeof(TELEM) * 8)) - 1;
		res.pMem[MemLen - 1] &= mask;
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