#pragma once
#include "../Lab1/tbitfield.h"
#include <algorithm>

int TBitField::GetMemIndex(const int n) const {
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const {
	return TELEM(1) << (n % (sizeof(TELEM) * 8));
}

TBitField::TBitField(int len) {
	if (len <= 0) {
		throw std::invalid_argument("Error, lenght < 0");
	}
	BitLen = len;
	MemLen = (BitLen + (sizeof(TELEM) * 8) - 1) / (sizeof(TELEM) * 8);
	pMem = new TELEM[MemLen]();
}

TBitField::TBitField(const TBitField& bf) {
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];  
	for (size_t i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField() {
	delete[] pMem;
	pMem = nullptr;
}

int TBitField::GetLength(void) const { return BitLen;}

void TBitField::SetBit(const int n) {
	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Бит выходит за рамки длины");
	}
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) {
	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Бит выходит за рамки длины");
	}
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const {
	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Бит выходит за рамки длины");
	}
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

int TBitField::operator==(const TBitField& bf) const {
	if (BitLen != bf.BitLen) {
		return 0;
	}
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i]) {
			return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const { return !(*this == bf); }

TBitField& TBitField::operator=(const TBitField& bf) {
	if (*this == bf) { return *this; }
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;
	pMem = new TELEM[MemLen];
	for (size_t i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

TBitField TBitField::operator&(const TBitField& bf) {
	int mxlen = std::max(BitLen, bf.BitLen); 
	TBitField res(mxlen);
	int mnlen = std::min(MemLen, bf.MemLen);   
	for (size_t i = 0; i < mnlen; i++) {
		res.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return res;
}
TBitField TBitField::operator|(const TBitField& bf) {
	int mxBitLen = std::max(BitLen, bf.BitLen);   
	int mxMemLen = (mxBitLen + (sizeof(TELEM) * 8) - 1) / (sizeof(TELEM) * 8);  
	TBitField res(mxBitLen);                            
	int mnMemLen = std::min(MemLen, bf.MemLen);           

	for (int i = 0; i < mnMemLen; i++) {
		res.pMem[i] = pMem[i] | bf.pMem[i];
	}

	if (MemLen > bf.MemLen) {
		for (int i = mnMemLen; i < MemLen; i++) {
			res.pMem[i] = pMem[i];
		}
	}
	else {
		for (int i = mnMemLen; i < bf.MemLen; i++) {
			res.pMem[i] = bf.pMem[i];
		}
	}

	return res;
}
	
TBitField TBitField::operator~(void) {
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++) {
		res.pMem[i] = ~pMem[i];
	}
	return res;
}

std::istream& operator>>(std::istream& istr, TBitField& bf) {
	char el;
	int i = 0;
	while (i < bf.BitLen && istr >> el) {
		if (el == '0') {
			bf.ClrBit(i++);
		}
		else {
			bf.SetBit(i++);
		}
	}
	return istr;
}
std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) {
	for (size_t i = 0; i < bf.BitLen; i++) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}