#pragma once
#include "tset.h"
#include "tbitfield.h"

inline TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

inline TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

inline TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

inline TSet::operator TBitField() {
    return BitField;
}

inline int TSet::GetMaxPower(void) const {
    return MaxPower;
}

inline int TSet::IsMember(const int Elem) const {
    return BitField.GetBit(Elem);
}

inline void TSet::InsElem(const int Elem) {
    BitField.SetBit(Elem);
}

inline void TSet::DelElem(const int Elem) {
    BitField.ClrBit(Elem);
}

inline int TSet::operator==(const TSet& s) const {
    return BitField == s.BitField;
}

inline int TSet::operator!=(const TSet& s) const {
    return BitField != s.BitField;
}

inline TSet& TSet::operator=(const TSet& s) {
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

inline TSet TSet::operator+(const int Elem) {
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}

inline TSet TSet::operator-(const int Elem) {
    TSet res(*this);
    res.DelElem(Elem);
    return res;
}

inline TSet TSet::operator+(const TSet& s) {
    TSet res(MaxPower > s.MaxPower ? MaxPower : s.MaxPower);
    res.BitField = BitField | s.BitField;
    return res;
}

inline TSet TSet::operator*(const TSet& s) {
    TSet res(MaxPower > s.MaxPower ? MaxPower : s.MaxPower);
    res.BitField = BitField & s.BitField;
    return res;
}

inline TSet TSet::operator~(void) {
    TSet res(~BitField);
    return res;
}

inline std::istream& operator>>(std::istream& istr, TSet& s) {
    istr >> s.BitField;
    return istr;
}

inline std::ostream& operator<<(std::ostream& ostr, const TSet& s) {
    ostr << "{";
    int first = 1;
    for (int i = 0; i < s.MaxPower; i++) {
        if (s.IsMember(i)) {
            if (!first) {
                ostr << ", ";
            }
            ostr << i;
            first = 0;
        }
    }
    ostr << "}";
    return ostr;
}