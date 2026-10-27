#include "pch.h"
#include "../../includes/Lab1/tbitfield.h"
#include <stdexcept>

int TBitField::GetMemIndex(const int n) const
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const
{
    return static_cast<TELEM>(1) << (n % (sizeof(TELEM) * 8));
}

TBitField::TBitField(int len)
    : BitLen(len), pMem(nullptr), MemLen(0)
{
    if (len < 0)
        throw std::invalid_argument("bit field length < 0");

    const int bitsPerElement = sizeof(TELEM) * 8;
    MemLen = len / bitsPerElement
        + (len % bitsPerElement != 0 ? 1 : 0);

    if (MemLen > 0)
        pMem = new TELEM[MemLen]();
}

TBitField::TBitField(const TBitField& bf)
    : BitLen(bf.BitLen), pMem(nullptr), MemLen(bf.MemLen)
{
    if (MemLen > 0)
    {
        pMem = new TELEM[MemLen];

        for (int i = 0; i < MemLen; ++i)
            pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetLength(void) const
{
    return BitLen;
}

void TBitField::SetBit(const int n)
{
    if (n < 0 || n >= BitLen)
        throw std::out_of_range("bit index out of range");

    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n)
{
    if (n < 0 || n >= BitLen)
        throw std::out_of_range("bit index out of range");

    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const
{
    if (n < 0 || n >= BitLen)
        throw std::out_of_range("bit index out of range");

    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

int TBitField::operator==(const TBitField& bf) const
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

int TBitField::operator!=(const TBitField& bf) const
{
    return !(*this == bf);
}

TBitField& TBitField::operator=(const TBitField& bf)
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

TBitField TBitField::operator|(const TBitField& bf)
{
    if (BitLen != bf.BitLen)
        throw std::invalid_argument("bit field lengths different");

    TBitField result(BitLen);

    for (int i = 0; i < MemLen; ++i)
        result.pMem[i] = pMem[i] | bf.pMem[i];

    return result;
}

TBitField TBitField::operator&(const TBitField& bf)
{
    if (BitLen != bf.BitLen)
        throw std::invalid_argument("bit field lengths different");

    TBitField result(BitLen);

    for (int i = 0; i < MemLen; ++i)
        result.pMem[i] = pMem[i] & bf.pMem[i];

    return result;
}

TBitField TBitField::operator~(void)
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

std::istream& operator>>(std::istream& istr, TBitField& bf)
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

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf)
{
    for (int i = bf.BitLen - 1; i >= 0; --i)
        ostr << bf.GetBit(i);

    return ostr;
}
