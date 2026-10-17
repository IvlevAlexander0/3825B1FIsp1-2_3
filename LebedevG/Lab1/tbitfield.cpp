#include "tbitfield.h"

static const int BITS_PER_ELEM = sizeof(TELEM) * 8;

TBitField::TBitField(int len) {
    if (len < 0) len = 0;
    BitLen = len;
    MemLen = (len + BITS_PER_ELEM - 1) / BITS_PER_ELEM;
    if (MemLen == 0) MemLen = 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; ++i) pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) {
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; ++i) pMem[i] = bf.pMem[i];
}

TBitField::~TBitField() {
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const {
    return n / BITS_PER_ELEM;
}

TELEM TBitField::GetMemMask(const int n) const {
    return 1u << (n % BITS_PER_ELEM);
}

int TBitField::GetLength(void) const {
    return BitLen;
}

void TBitField::SetBit(const int n) {
    if (n < 0 || n >= BitLen) return;
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) {
    if (n < 0 || n >= BitLen) return;
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const {
    if (n < 0 || n >= BitLen) return 0;
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) ? 1 : 0;
}

int TBitField::operator==(const TBitField& bf) const {
    if (BitLen != bf.BitLen) return 0;
    for (int i = 0; i < MemLen; ++i)
        if (pMem[i] != bf.pMem[i]) return 0;
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const {
    return !(*this == bf);
}

TBitField& TBitField::operator=(const TBitField& bf) {
    if (this == &bf) return *this;
    delete[] pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; ++i) pMem[i] = bf.pMem[i];
    return *this;
}

TBitField TBitField::operator|(const TBitField& bf) {
    int maxLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField res(maxLen);
    for (int i = 0; i < res.MemLen; ++i) {
        TELEM a = (i < MemLen) ? pMem[i] : 0;
        TELEM b = (i < bf.MemLen) ? bf.pMem[i] : 0;
        res.pMem[i] = a | b;
    }
    return res;
}

TBitField TBitField::operator&(const TBitField& bf) {
    int maxLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField res(maxLen);
    for (int i = 0; i < res.MemLen; ++i) {
        TELEM a = (i < MemLen) ? pMem[i] : 0;
        TELEM b = (i < bf.MemLen) ? bf.pMem[i] : 0;
        res.pMem[i] = a & b;
    }
    return res;
}

TBitField TBitField::operator~(void) {
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; ++i)
        res.pMem[i] = ~pMem[i];
    int extra = MemLen * BITS_PER_ELEM - BitLen;
    if (extra > 0)
        res.pMem[MemLen - 1] &= (~0u >> extra);
    return res;
}

std::istream& operator>>(std::istream& istr, TBitField& bf) {
    for (int i = 0; i < bf.BitLen; ++i) {
        int bit;
        istr >> bit;
        if (bit) bf.SetBit(i);
        else     bf.ClrBit(i);
    }
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) {
    for (int i = 0; i < bf.BitLen; ++i)
        ostr << bf.GetBit(i);
    return ostr;
}