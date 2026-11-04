#pragma once
#include "../Lab1/tset.h"
#include "../Lab1/tbitfield.h"

TSet::TSet(int mp): MaxPower(mp), BitField(mp){}
TSet::TSet(const TSet& s): MaxPower(s.MaxPower), BitField(s.BitField) {}
TSet::TSet(const TBitField& bf): MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField() {
	return BitField;
}

int TSet::GetMaxPower(void) const {
	return MaxPower;
}

void TSet::InsElem(const int Elem) {
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) {
	BitField.ClrBit(Elem);
}

int TSet::IsMember(const int Elem) const {
	return BitField.GetBit(Elem);
}

int TSet::operator==(const TSet& s) const {
	return (BitField == s.BitField);
}

int TSet::operator!=(const TSet& s) const {
	return (BitField != s.BitField);
}

TSet& TSet::operator=(const TSet& s) {
	if (this != &s) {
		MaxPower = s.MaxPower;
		BitField = s.BitField;
		
	}
	return *this;
}
TSet TSet::operator+(const int Elem) {
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) {
    TSet res(*this);
    res.DelElem(Elem);
    return res;
}

TSet TSet::operator+(const TSet& s) {
    return TSet(BitField | s.BitField);
}

TSet TSet::operator*(const TSet& s) {
    return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) {
    return TSet(~BitField);
}

std::istream& operator>>(std::istream& istr, TSet& s) {
    istr >> s.BitField;
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& s) {
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

