#pragma once

#include <iostream>
#include <stdexcept>

typedef unsigned int TELEM;

class TBitField
{
private:
    int BitLen;
    TELEM* pMem;
    int MemLen;

    int GetMemIndex(const int n) const
    {
        return n / (sizeof(TELEM) * 8);
    }

    TELEM GetMemMask(const int n) const
    {
        return static_cast<TELEM>(1) << (n % (sizeof(TELEM) * 8));
    }

public:
    TBitField(int len)
        : BitLen(len), pMem(nullptr), MemLen(0)
    {
        if (len < 0)
            throw std::invalid_argument("bit field length <0");

        const int bitsPerElement = sizeof(TELEM) * 8;
        MemLen = len / bitsPerElement
            + (len % bitsPerElement != 0 ? 1 : 0);

        if (MemLen > 0)
            pMem = new TELEM[MemLen]();
    }

    TBitField(const TBitField& bf)
        : BitLen(bf.BitLen), pMem(nullptr), MemLen(bf.MemLen)
    {
        if (MemLen > 0)
        {
            pMem = new TELEM[MemLen];
            for (int i = 0; i < MemLen; ++i)
                pMem[i] = bf.pMem[i];
        }
    }

    ~TBitField()
    {
        delete[] pMem;
    }

    int GetLength(void) const
    {
        return BitLen;
    }

    void SetBit(const int n)
    {
        if (n < 0 || n >= BitLen)
            throw std::out_of_range("bit index out of range");

        pMem[GetMemIndex(n)] |= GetMemMask(n);
    }

    void ClrBit(const int n)
    {
        if (n < 0 || n >= BitLen)
            throw std::out_of_range("bit index out of range");

        pMem[GetMemIndex(n)] &= ~GetMemMask(n);
    }

    int GetBit(const int n) const
    {
        if (n < 0 || n >= BitLen)
            throw std::out_of_range("bit index out of range");

        return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
    }

    int operator==(const TBitField& bf) const
    {
        if (BitLen != bf.BitLen)
            return 0;

        for (int i = 0; i < MemLen; ++i)
        {
            if (pMem[i] != bf.pMem[i])
                return 0;
        }

        return 1;
    }

    int operator!=(const TBitField& bf) const
    {
        return !(*this == bf);
    }

    TBitField& operator=(const TBitField& bf)
    {
        if (this == &bf)
            return *this;

        TBitField temp(bf);

        TELEM* oldMem = pMem;
        pMem = temp.pMem;
        temp.pMem = oldMem;

        int oldLen = BitLen;
        BitLen = temp.BitLen;
        temp.BitLen = oldLen;

        int oldMemLen = MemLen;
        MemLen = temp.MemLen;
        temp.MemLen = oldMemLen;

        return *this;
    }

    TBitField operator|(const TBitField& bf)
    {
        if (BitLen != bf.BitLen)
            throw std::invalid_argument("bit field lengths different");

        TBitField result(BitLen);

        for (int i = 0; i < MemLen; ++i)
            result.pMem[i] = pMem[i] | bf.pMem[i];

        return result;
    }

    TBitField operator&(const TBitField& bf)
    {
        if (BitLen != bf.BitLen)
            throw std::invalid_argument("bit field lengths different");

        TBitField result(BitLen);

        for (int i = 0; i < MemLen; ++i)
            result.pMem[i] = pMem[i] & bf.pMem[i];

        return result;
    }

    TBitField operator~(void)
    {
        TBitField result(BitLen);

        for (int i = 0; i < MemLen; ++i)
            result.pMem[i] = ~pMem[i];

        const int bitsPerElement = sizeof(TELEM) * 8;
        const int usedBits = BitLen % bitsPerElement;

        if (MemLen > 0 && usedBits != 0)
        {
            TELEM mask = (static_cast<TELEM>(1) << usedBits) - 1;
            result.pMem[MemLen - 1] &= mask;
        }

        return result;
    }

    friend std::istream& operator>>(std::istream& istr, TBitField& bf)
    {
        for (int i = bf.BitLen - 1; i >= 0; --i)
        {
            char ch;

            if (!(istr >> ch))
                return istr;

            if (ch != '0' && ch != '1')
            {
                istr.setstate(std::ios::failbit);
                return istr;
            }

            if (ch == '1')
                bf.SetBit(i);
            else
                bf.ClrBit(i);
        }

        return istr;
    }

    friend std::ostream& operator<<(std::ostream& ostr,
        const TBitField& bf)
    {
        for (int i = bf.BitLen - 1; i >= 0; --i)
            ostr << bf.GetBit(i);

        return ostr;
    }
};
