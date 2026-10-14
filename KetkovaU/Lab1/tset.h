#pragma once

#include "tbitfield.h"

class TSet
{
private:
    int MaxPower;
    TBitField BitField;

public:
    TSet(int mp)
        : MaxPower(mp), BitField(mp)
    {
        if (mp < 0)
            throw std::invalid_argument("set power <0");
    }

    TSet(const TSet& s)
        : MaxPower(s.MaxPower), BitField(s.BitField)
    {
    }

    TSet(const TBitField& bf)
        : MaxPower(bf.GetLength()), BitField(bf)
    {
    }

    operator TBitField()
    {
        return BitField;
    }

    int GetMaxPower(void) const
    {
        return MaxPower;
    }

    void InsElem(const int Elem)
    {
        if (Elem < 0 || Elem >= MaxPower)
            throw std::out_of_range("set element out of range");

        BitField.SetBit(Elem);
    }

    void DelElem(const int Elem)
    {
        if (Elem < 0 || Elem >= MaxPower)
            throw std::out_of_range("set element out of range");

        BitField.ClrBit(Elem);
    }

    int IsMember(const int Elem) const
    {
        if (Elem < 0 || Elem >= MaxPower)
            throw std::out_of_range("set element out of range");

        return BitField.GetBit(Elem);
    }

    int operator==(const TSet& s) const
    {
        return MaxPower == s.MaxPower && BitField == s.BitField;
    }

    int operator!=(const TSet& s) const
    {
        return !(*this == s);
    }

    TSet& operator=(const TSet& s)
    {
        if (this != &s)
        {
            BitField = s.BitField;
            MaxPower = s.MaxPower;
        }

        return *this;
    }

    TSet operator+(const int Elem)
    {
        TSet result(*this);
        result.InsElem(Elem);
        return result;
    }

    TSet operator-(const int Elem)
    {
        TSet result(*this);
        result.DelElem(Elem);
        return result;
    }

    TSet operator+(const TSet& s)
    {
        if (MaxPower != s.MaxPower)
            throw std::invalid_argument("set powers different");

        TSet result(*this);
        result.BitField = BitField | s.BitField;

        return result;
    }

    TSet operator*(const TSet& s)
    {
        if (MaxPower != s.MaxPower)
            throw std::invalid_argument("set powers different");

        TSet result(*this);
        result.BitField = BitField & s.BitField;

        return result;
    }

    TSet operator~(void)
    {
        TSet result(*this);
        result.BitField = ~BitField;

        return result;
    }

    friend std::istream& operator>>(std::istream& istr, TSet& s)
    {
        return istr >> s.BitField;
    }

    friend std::ostream& operator<<(std::ostream& ostr, const TSet& s)
    {
        return ostr << s.BitField;
    }
};
