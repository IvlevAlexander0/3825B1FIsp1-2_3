#include "tbitfield.h"
#include <stdexcept>
#include <algorithm>

const int bits_in_telem = sizeof(TELEM) * 8;

int TBitField::GetMemIndex(const int n) const {
    return n / bits_in_telem;
}

TELEM TBitField::GetMemMask(const int n) const {
    return TELEM(1) << (n % bits_in_telem);
}

TBitField::TBitField(int len) {
    if (len < 0) {
        throw std::invalid_argument("Bitfield length cannot be negative");
    }
    BitLen = len;
    MemLen = (BitLen + bits_in_telem - 1) / bits_in_telem;
    pMem = new TELEM[MemLen]();
}

TBitField::TBitField(const TBitField& bf) : BitLen(bf.BitLen), MemLen(bf.MemLen) {
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField() {
    delete[] pMem;
    pMem = nullptr;
}

int TBitField::GetLength(void) const {
    return BitLen;
}

void TBitField::SetBit(const int n) {
    if (n < 0 || n >= BitLen) {
        throw std::out_of_range("Bit index is out of range");
    }
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) {
    if (n < 0 || n >= BitLen) {
        throw std::out_of_range("Bit index is out of range");
    }
    pMem[GetMemIndex(n)] &= ~GetMemMask(n); // используем отрицание маски ~
}

int TBitField::GetBit(const int n) const {
    if (n < 0 || n >= BitLen) {
        throw std::out_of_range("Bit index is out of range");
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

int TBitField::operator!=(const TBitField& bf) const {
    return !(*this == bf);
}

TBitField& TBitField::operator=(const TBitField& bf) {
    if (this != &bf) {
        if (MemLen != bf.MemLen) {
            delete[] pMem;
            MemLen = bf.MemLen;
            pMem = new TELEM[MemLen];
        }
        BitLen = bf.BitLen;
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

TBitField TBitField::operator|(const TBitField& bf) {
    int maxLen = std::max(BitLen, bf.BitLen);
    TBitField res(maxLen);

    int minMemLen = std::min(MemLen, bf.MemLen);
    for (int i = 0; i < minMemLen; i++) {
        res.pMem[i] = pMem[i] | bf.pMem[i];
    }

    if (BitLen > bf.BitLen) {
        for (int i = minMemLen; i < MemLen; i++) {
            res.pMem[i] = pMem[i];
        }
    }
    else {
        for (int i = minMemLen; i < bf.MemLen; i++) {
            res.pMem[i] = bf.pMem[i];
        }
    }

    return res;
}

TBitField TBitField::operator&(const TBitField& bf) {
    int maxLen = std::max(BitLen, bf.BitLen);
    TBitField res(maxLen);

    int minMemLen = std::min(MemLen, bf.MemLen);
    for (int i = 0; i < minMemLen; i++) {
        res.pMem[i] = pMem[i] & bf.pMem[i];
    }

    return res;
}

TBitField TBitField::operator~(void) {
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = ~pMem[i];
    }
    // Обнуляем неиспользуемые биты в последнем слове
    if (MemLen > 0 && BitLen % bits_in_telem != 0) {
        int used = BitLen % bits_in_telem;
        TELEM mask = (TELEM(1) << used) - 1; 
        res.pMem[MemLen - 1] &= mask;
    }
    return res;
}

std::istream& operator>>(std::istream& istr, TBitField& bf) {
    const int len = bf.GetLength();

    for (int i = 0; i < len; i++) {
        bf.ClrBit(i);
    }

    char c;
    int i = 0;
    while (i < len && (istr >> c)) {
        if (c == '0') {
            bf.ClrBit(i++);      
        }
        else if (c == '1') {
            bf.SetBit(i++);     
        }
        
    }
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) {
    for (int i = 0; i < bf.BitLen; i++) {
        if (bf.GetBit(i))
            ostr << '1';
        else ostr << '0';
    }
    return ostr;
}