#pragma once

#include "tbitfield.h"
#include <stdexcept> // ОБЯЗАТЕЛЬНО для std::out_of_range

// Вспомогательная константа: сколько бит в одном элементе (обычно 32)
constexpr int BITS_PER_ELEM = sizeof(TELEM) * 8;

inline int TBitField::GetMemIndex(const int n) const {
    return n / BITS_PER_ELEM;
}

inline TELEM TBitField::GetMemMask(const int n) const {
    return TELEM(1) << (n % BITS_PER_ELEM);
}

inline TBitField::TBitField(int len) {
    if (len < 0) throw std::invalid_argument("Length cannot be negative");
    BitLen = len;
    MemLen = (BitLen + BITS_PER_ELEM - 1) / BITS_PER_ELEM;
    pMem = new TELEM[MemLen](); // () в конце - заполняет нулями
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
    if (n < 0 || n >= BitLen) throw std::out_of_range("Index out of range");
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

inline void TBitField::ClrBit(const int n) {
    if (n < 0 || n >= BitLen) throw std::out_of_range("Index out of range");
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

inline int TBitField::GetBit(const int n) const {
    if (n < 0 || n >= BitLen) throw std::out_of_range("Index out of range");
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0 ? 1 : 0;
}

inline int TBitField::operator==(const TBitField& bf) const {
    if (BitLen != bf.BitLen) return 0;
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) return 0;
    }
    return 1;
}

inline int TBitField::operator!=(const TBitField& bf) const {
    return !(*this == bf);
}

inline TBitField& TBitField::operator=(const TBitField& bf) {
    if (this == &bf) return *this; // защита от самоприсваивания
    // Сначала выделяем новую память, чтобы не потерять старую, если new упадет
    TELEM* newMem = new TELEM[bf.MemLen];
    for (int i = 0; i < bf.MemLen; i++) {
        newMem[i] = bf.pMem[i];
    }
    delete[] pMem;
    pMem = newMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    return *this;
}

inline TBitField TBitField::operator|(const TBitField& bf) {
    int maxLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField res(maxLen);
    int minMem = (MemLen < bf.MemLen) ? MemLen : bf.MemLen;

    for (int i = 0; i < minMem; i++) {
        res.pMem[i] = pMem[i] | bf.pMem[i];
    }
    // Докидываем остатки от того, кто длиннее
    if (MemLen > bf.MemLen) {
        for (int i = minMem; i < MemLen; i++) res.pMem[i] = pMem[i];
    }
    else {
        for (int i = minMem; i < bf.MemLen; i++) res.pMem[i] = bf.pMem[i];
    }
    return res;
}

inline TBitField TBitField::operator&(const TBitField& bf) {
    int maxLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField res(maxLen);
    int minMem = (MemLen < bf.MemLen) ? MemLen : bf.MemLen;

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
    // Зачистка "хвоста": если BitLen не кратен 32, последние биты надо обнулить
    int tail = BitLen % BITS_PER_ELEM;
    if (tail != 0 && MemLen > 0) {
        TELEM mask = (TELEM(1) << tail) - 1;
        res.pMem[MemLen - 1] &= mask;
    }
    return res;
}

inline std::istream& operator>>(std::istream& istr, TBitField& bf) {
    for (int j = 0; j < bf.BitLen; j++) {
        bf.ClrBit(j);
    }
    if (bf.BitLen == 0) return istr; // Защита для нулевой длины

    int i = 0;
    char ch;
    while (i < bf.BitLen && (istr >> ch)) {
        if (ch == '0') bf.ClrBit(i++);
        else if (ch == '1') bf.SetBit(i++);
        else {
            istr.putback(ch);
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