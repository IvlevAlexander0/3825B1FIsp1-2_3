#include "tset.h"
#include <stdexcept>

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField() {
    return BitField;
}

// доступ к битам
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

// теоретико-множественные операции
int TSet::operator==(const TSet& s) const {
    return (MaxPower == s.MaxPower) && (BitField == s.BitField);
}

int TSet::operator!=(const TSet& s) const {
    return !(*this == s);
}

TSet& TSet::operator=(const TSet& s) {
    if (this != &s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
}

TSet TSet::operator+(const int Elem) {
    TSet temp(*this);
    temp.InsElem(Elem);
    return temp;
}

TSet TSet::operator-(const int Elem) {
    TSet temp(*this);
    temp.DelElem(Elem);
    return temp;
}
//ƒобавлена проверка на мощность множеств
TSet TSet::operator+(const TSet& s) {
    if (MaxPower != s.MaxPower) {
        throw std::invalid_argument("Sets of unequal power");
    }
    return TSet(BitField | s.BitField);
}

TSet TSet::operator*(const TSet& s) {
    if (MaxPower != s.MaxPower) {
        throw std::invalid_argument("Sets of unequal power");
    }
    return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) {
    return TSet(~BitField);
}

std::istream& operator>>(std::istream& istr, TSet& s) {
    for (int i = 0; i < s.GetMaxPower(); i++) {
        s.DelElem(i);
    }

    int elem;
    while (istr >> elem) {
        if (elem >= 0 && elem < s.GetMaxPower()) {
            s.InsElem(elem);
        }
    }
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& s) {
    ostr << "{ ";
    bool first = true;
    for (int i = 0; i < s.GetMaxPower(); i++) {
        if (s.IsMember(i)) {
            if (!first) {
                ostr << ", ";
            }
            ostr << i;
            first = false;
        }
    }
    ostr << " }";
    return ostr;
}