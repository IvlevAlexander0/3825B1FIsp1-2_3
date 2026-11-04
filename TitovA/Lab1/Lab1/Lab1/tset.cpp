
#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp < 0 ? 0 : mp), BitField(mp < 0 ? 0 : mp) {}

TSet::TSet(const TSet& s)
    : MaxPower(s.MaxPower), BitField(s.BitField)
{}

TSet::TSet(const TBitField& bf)
    : MaxPower(bf.GetLength()), BitField(bf)
{}

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
    if (Elem >= 0 && Elem < MaxPower)
        BitField.SetBit(Elem);}

void TSet::DelElem(const int Elem)
{
    if (Elem >= 0 && Elem < MaxPower)
        BitField.ClrBit(Elem);}

int TSet::IsMember(const int Elem) const
{
    if (Elem < 0 || Elem >= MaxPower)

        return 0;

    return BitField.GetBit(Elem);}

int TSet::operator==(const TSet& s) const
{
    if (MaxPower != s.MaxPower)
        return 0;

    return BitField == s.BitField;}

int TSet::operator!=(const TSet& s) const
{

    return !(*this == s);
}

TSet& TSet::operator=(const TSet& s)
{
    if (this == &s)
        return *this;

    BitField = s.BitField;
    MaxPower = s.MaxPower;

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

        return TSet(0);

    TSet res(MaxPower);
    res.BitField = BitField | s.BitField;

    return res;
}

TSet TSet::operator*(const TSet& s)
{
    if (MaxPower != s.MaxPower)
        return TSet(0);

    TSet res(MaxPower);
    res.BitField = BitField & s.BitField;
    return res;
}

TSet TSet::operator~(void)
{
    TSet res(MaxPower);
    res.BitField = ~BitField;
    return res;
}

std::istream& operator>>(std::istream& istr, TSet& s)
{
    for (int i = 0; i < s.MaxPower; i++)
    {
        int bit;

        if (!(istr >> bit))
            return istr;

        if (bit != 0 && bit != 1)
        {
            istr.setstate(std::ios::failbit);
            return istr;
        }

        if (bit == 1)
            s.InsElem(i);
        else
            s.DelElem(i);
    }

    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& s)
{
    ostr << "{";

    int first = 1;

    for (int i = 0; i < s.MaxPower; i++)
    {
        if (s.IsMember(i))
        {
            if (!first)
            {
                ostr << ",";
            }

            ostr << i;
            first = 0;
        }
    }

    ostr << "}";
    return ostr;

}
