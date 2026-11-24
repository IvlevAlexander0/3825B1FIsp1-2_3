#pragma once
#include "C:\Users\максим\Desktop\3sem\3825B1FIsp1-2_3\includes\Lab1\tset.h"
#include "C:\Users\максим\Desktop\3sem\3825B1FIsp1-2_3\includes\Lab1\tbitfield.h"
#include <stdexcept>

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const
{
    return MaxPower;
}

void TSet::InsElem(const int Elem)
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem)
{
    BitField.ClrBit(Elem);
}

int TSet::IsMember(const int Elem) const
{
    return BitField.GetBit(Elem);
}

int TSet::operator==(const TSet& s) const
{
    return MaxPower == s.MaxPower && BitField == s.BitField;
}


int TSet::operator!=(const TSet& s) const
{
    return !(*this == s);
}

TSet& TSet::operator=(const TSet& s)
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

TSet TSet::operator+(const int Elem)
{
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}
TSet TSet::operator-(const int Elem)
{
    TSet res(*this);
    res.DelElem(Elem);
    return res;
}

TSet TSet::operator+(const TSet& s)
{
    if (MaxPower != s.MaxPower)
        throw std::invalid_argument::invalid_argument("");
    return TSet(BitField | s.BitField);
}

TSet TSet::operator*(const TSet& s)
{
    if (MaxPower != s.MaxPower)
        throw std::invalid_argument::invalid_argument("");
    return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void)
{
    return TSet(~BitField);
}

std::istream& operator>>(std::istream& istr, TSet& s) {
    int count, elem;
    istr >> count;
    for (int i = 0; i < count; i++)
    {
        istr >> elem;
        s.InsElem(elem);
    }
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& s) {
    ostr << "{ ";
    for (int i = 0; i < s.MaxPower; i++)
        if (s.IsMember(i))
            ostr << i << " ";
    ostr << "}";
    return ostr;
}
