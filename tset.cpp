#include "tset.h"
#include "tbitfield.h"
#include <stdexcept>

using std::invalid_argument;
using std::out_of_range;
using std::min;

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}
TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField() {
    return BitField;
}

int TSet::GetMaxPower() const {
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
    if (MaxPower != s.MaxPower) return 0;
    return (BitField == s.BitField);
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
    TSet result(*this); // копия текущего множествва
    result.InsElem(Elem);
    return result;
}
TSet TSet::operator-(const int Elem) {
    TSet result(*this);
    result.DelElem(Elem);
    return result;
}

TSet TSet::operator+(const TSet& s) {
    if (MaxPower != s.MaxPower) {
        throw invalid_argument("Разная мощность");
    }
    return TSet(BitField | s.BitField);
}
TSet TSet::operator*(const TSet& s) {
    if (MaxPower != s.MaxPower) {
        throw invalid_argument("Разная мощность");
    }
    return TSet(BitField & s.BitField);
}
TSet TSet::operator~() {
    return TSet(~BitField);
}

std::istream& operator>>(std::istream& istr, TSet& s) {
    for (int i = 0; i < s.MaxPower; ++i) {
        s.DelElem(i);
    }
    int elem;
    while (istr >> elem) {
        if (elem < 0) break;
        if (elem >= s.MaxPower) {
            throw out_of_range("Введенный элемент превышает max мощность множества");
        }
        s.InsElem(elem);
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