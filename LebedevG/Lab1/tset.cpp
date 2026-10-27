#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

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
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const {
    return !(*this == s);
}

TSet& TSet::operator=(const TSet& s) {
    if (this == &s) return *this;
    MaxPower = s.MaxPower;
    BitField = s.BitField;
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
    TSet res(*this);
    res.BitField = BitField | s.BitField;
    return res;
}

TSet TSet::operator*(const TSet& s) {
    TSet res(*this);
    res.BitField = BitField & s.BitField;
    return res;
}

TSet TSet::operator~(void) {
    TSet res(*this);
    res.BitField = ~BitField;
    return res;
}

std::istream& operator>>(std::istream& istr, TSet& s) {
    istr >> s.BitField;
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& s) {
    ostr << "{ ";
    bool first = true;
    for (int i = 0; i < s.MaxPower; ++i) {
        if (s.IsMember(i)) {
            if (!first) ostr << ", ";
            ostr << i;
            first = false;
        }
    }
    ostr << " }";
    return ostr;
}