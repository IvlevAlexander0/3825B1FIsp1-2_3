#include "..\Lab1\tbitfield.h"
#include <stdexcept>


int TBitField::GetMemIndex(const int n) const
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const
{
    return 1 << (n % (sizeof(TELEM) * 8));
}

TBitField::TBitField(int len)
{
    if (len < 0)
        throw std::invalid_argument::invalid_argument("");
    BitLen = len;
    MemLen = (len + (sizeof(TELEM) * 8) - 1) / (sizeof(TELEM) * 8);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}


TBitField::TBitField(const TBitField& bf)
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
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
        throw std::out_of_range::out_of_range("");
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

 
void TBitField::ClrBit(const int n)
{
    if (n < 0 || n >= BitLen)
        throw std::out_of_range::out_of_range("");
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}


int TBitField::GetBit(const int n) const
{
    if (n < 0 || n >= BitLen)
        throw std::out_of_range::out_of_range("");
    if (pMem[GetMemIndex(n)] & GetMemMask(n))
        return 1;
    return 0;
}
 
int TBitField::operator==(const TBitField& bf) const
{
    if (BitLen != bf.BitLen)
        return 0;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 0;
    return 1;
}


int TBitField::operator!=(const TBitField& bf) const
{
    return !(*this == bf);
}

TBitField& TBitField::operator=(const TBitField& bf)
{
    if (this != &bf)
    {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

TBitField TBitField::operator|(const TBitField& bf)
{
    int len = BitLen;
    if (bf.BitLen > len)
        len = bf.BitLen;
    TBitField res(len);
    for (int i = 0; i < MemLen; i++)
        res.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++)
        res.pMem[i] |= bf.pMem[i];
    return res;
}

TBitField TBitField::operator&(const TBitField& bf)
{
    int len = BitLen;
    if (bf.BitLen > len)
        len = bf.BitLen;
    int minMemLen = MemLen;
    if (bf.MemLen < minMemLen)
        minMemLen = bf.MemLen;
    TBitField res(len);
    for (int i = 0; i < minMemLen; i++)
        res.pMem[i] = pMem[i] & bf.pMem[i];
    return res;
}

TBitField TBitField::operator~(void)
{
    TBitField res(BitLen);
    for (int i = 0; i < BitLen; i++)
        if (GetBit(i) == 0)
            res.SetBit(i);
    return res;
}

std::istream& operator>>(std::istream& istr, TBitField& bf) {
    const int len = bf.GetLength();

    for (int i = 0; i < len; i++) {
        bf.ClrBit(i);
    }

    char c;
    int i = 0;
    while (i < len && (istr >> c)) {
        if (c == '0') {
            bf.ClrBit(i++);
        }
        else if (c == '1') {
            bf.SetBit(i++);
        }

    }
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) {
    for (int i = 0; i < bf.BitLen; i++) {
        if (bf.GetBit(i))
            ostr << '1';
        else ostr << '0';
    }
    return ostr;
}