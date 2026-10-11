#include "tbitfield.h"
#include <stdexcept>
#include <string>

const int bits_in_el = sizeof(TELEM) * 8;

int TBitField::GetMemIndex(const int n) const {
	return n / bits_in_el;
}
TELEM TBitField::GetMemMask(const int n) const {
	return TELEM(1) << (n % bits_in_el);
}

TBitField::TBitField(int len) {
	if (len < 0) {
		throw std::invalid_argument("Отрицательная длина");
	}
	BitLen = len;
	MemLen = (BitLen / bits_in_el) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i) {
		pMem[i] = 0;
	}
}
TBitField::TBitField(const TBitField& bf) {
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i) {
		pMem[i] = bf.pMem[i];
	}
}
TBitField::~TBitField() {
	delete[] pMem;
	pMem = nullptr;
}

int TBitField::GetLength() const {
	return BitLen;
}
void TBitField::SetBit(const int n) {
	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Индекс бита выходит за границы поля");
	}
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}
void TBitField::ClrBit(const int n) {
	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Индекс бита выходит за границы поля");
	}
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}
int TBitField::GetBit(const int n) const {
	if (n < 0 || n >= BitLen) {
		throw std::out_of_range("Индекс бита выходит за границы поля");
	}
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0 ? 1 : 0;
}

int TBitField::operator==(const TBitField &bf) const {
	if (BitLen != bf.BitLen) return 0;
	for (int i = 0; i < MemLen; ++i) {
		if (pMem[i] != bf.pMem[i]) return 0;
	}
	return 1;
}
int TBitField::operator!=(const TBitField &bf) const {
	return !(*this == bf);
}
TBitField& TBitField::operator=(const TBitField &bf) {
	if (this == &bf) return *this;
	if (BitLen != bf.BitLen) {
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen]();
	}
		for (int i = 0; i < MemLen; ++i) {
			pMem[i] = bf.pMem[i];
		}
		return *this;
	}
TBitField TBitField::operator|(const TBitField &bf)
{
	if (BitLen != bf.BitLen) {
		throw std::invalid_argument("Операция | невозможна для полей разной длины");
	}
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; ++i) {
		res.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return res;
}
TBitField TBitField::operator&(const TBitField &bf)
{
	if (BitLen != bf.BitLen) {
		throw std::invalid_argument("Операция & невозможна для полей разной длины");
	}
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; ++i) {
		res.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return res;
}
TBitField TBitField::operator~(void)
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++) {
		res.pMem[i] = ~pMem[i];
	}
	int tail = BitLen % bits_in_el;
	if (tail != 0) {
		res.pMem[MemLen - 1] &= (TELEM(1) << tail) - 1;
	}
	return res;
}
std::istream& operator>>(std::istream& istr, TBitField& bf) {
	std::string s;
	istr >> s; // читаем слово до пробела
	for (int i = 0; i < bf.BitLen; ++i) {
		bf.ClrBit(i);
	}
	int len = std::min((int)s.length(), bf.BitLen);
	for (int i = 0; i < len; ++i) {
		if (s[i] == '1') {
			bf.SetBit(i);
		}
	}
	return istr;
}
std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) {
	for (int i = bf.BitLen - 1; i >= 0; --i) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}