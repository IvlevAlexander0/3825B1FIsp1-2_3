#include "pch.h"
#include "../../includes/Lab1/tset.h"
#include <stdexcept>

TSet::TSet(int mp)
    : MaxPower(mp), BitField(mp)
{
    if (mp < 0)
        throw std::invalid_argument("set power < 0");
}

TSet::TSet(const TSet& s)
    : MaxPower(s.MaxPower), BitField(s.BitField)
{
}

TSet::TSet(const TBitField& bf)
    : MaxPower(bf.GetLength()), BitField(bf)
{
}

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
    if (this != &s)
    {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }

    return *this;
}

TSet TSet::operator+(const int Elem)
{
    TSet result(*this);
    result.InsElem(Elem);
    return result;
}

TSet TSet::operator-(const int Elem)
{
    TSet result(*this);
    result.DelElem(Elem);
    return result;
}

TSet TSet::operator+(const TSet& s)
{
    if (MaxPower != s.MaxPower)
        throw std::invalid_argument("set powers different");

    TSet result(*this);

    for (int i = 0; i < MaxPower; ++i)
    {
        if (s.IsMember(i))
            result.InsElem(i);
    }

    return result;
}

TSet TSet::operator*(const TSet& s)
{
    if (MaxPower != s.MaxPower)
        throw std::invalid_argument("set powers different");

    TSet result(MaxPower);

    for (int i = 0; i < MaxPower; ++i)
    {
        if (IsMember(i) && s.IsMember(i))
            result.InsElem(i);
    }

    return result;
}

TSet TSet::operator~(void)
{
    TBitField result = ~BitField;
    return TSet(result);
}

std::istream& operator>>(std::istream& istr, TSet& s)
{
    istr >> s.BitField;
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& s)
{
    ostr << s.BitField;
    return ostr;
}
