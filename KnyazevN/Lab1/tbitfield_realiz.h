#pragma once

#include "tbitfield.h"

inline int TBitField::GetMemIndex(const int n) const {
	return n / (sizeof(TELEM) * 8);
}

inline TELEM TBitField::GetMemMask(const int n) const {
	int bitPos = n % (sizeof(TELEM) * 8);
	return 1u << bitPos;
}

inline TBitField::TBitField(int len) {
	if (len < 0) throw "Error length";
	BitLen = len;
	MemLen = (BitLen + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
}

inline TBitField::TBitField(const TBitField& bf) {
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

inline TBitField::~TBitField() {
	delete[] pMem;
}

inline int TBitField::GetLength(void) const {
	return BitLen;
}

inline void TBitField::SetBit(const int n) {
	if (n < 0 || n >= BitLen) throw "Error length";
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

inline void TBitField::ClrBit(const int n) {
	if (n < 0 || n >= BitLen) throw "Error length";
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

inline int TBitField::GetBit(const int n) const {
	if (n < 0 || n >= BitLen) throw "Error length";
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

inline int TBitField::operator==(const TBitField& bf) const {
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

inline int TBitField::operator!=(const TBitField& bf) const {
	return !(*this == bf);
}

inline TBitField& TBitField::operator=(const TBitField& bf) {
	if (this == &bf) {
		return *this;
	}
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

inline TBitField TBitField::operator|(const TBitField& bf) {
	int maxLen = BitLen;
	if (bf.BitLen > maxLen) {
		maxLen = bf.BitLen;
	}
	TBitField res(maxLen);

	int minMem = MemLen;
	if (bf.MemLen < minMem) {
		minMem = bf.MemLen;
	}

	for (int i = 0; i < minMem; i++) {
		res.pMem[i] = pMem[i] | bf.pMem[i];
	}

	if (MemLen > bf.MemLen) {
		for (int i = minMem; i < MemLen; i++) {
			res.pMem[i] = pMem[i];
		}
	}
	else {
		for (int i = minMem; i < bf.MemLen; i++) {
			res.pMem[i] = bf.pMem[i];
		}
	}

	return res;
}

inline TBitField TBitField::operator&(const TBitField& bf) {
	int maxLen = BitLen;
	if (bf.BitLen > maxLen) {
		maxLen = bf.BitLen;
	}
	TBitField res(maxLen);

	int minMem = MemLen;
	if (bf.MemLen < minMem) {
		minMem = bf.MemLen;
	}

	for (int i = 0; i < minMem; i++) {
		res.pMem[i] = pMem[i] & bf.pMem[i];
	}

	return res;
}

inline TBitField TBitField::operator~(void) {
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++) {
		res.pMem[i] = ~pMem[i];
	}

	int lishnie = BitLen % (sizeof(TELEM) * 8);
	if (lishnie != 0) {
		TELEM mask = (1u << lishnie) - 1;
		res.pMem[MemLen - 1] &= mask;
	}
	return res;
}

inline std::istream& operator>>(std::istream& istr, TBitField& bf) {
	int i = 0;
	char elem;
	for (int j = 0; j < bf.BitLen; j++) {
		bf.ClrBit(j);
	}
	while (istr >> elem) {
		if (elem == '0') {
			bf.ClrBit(i++);
		}
		else if (elem == '1') {
			bf.SetBit(i++);
		}
		else {
			break;
		}
		if (i >= bf.BitLen) {
			break;
		}
	}
	return istr;
}

inline std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) {
	for (int i = 0; i < bf.BitLen; i++) {
		ostr << bf.GetBit(i);
	}
	return ostr;
}