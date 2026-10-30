#include "../Lab1/tbitfield.h"
#include <stdexcept>

// индекс в pМем для бита n
int TBitField::GetMemIndex(const int n) const
{
    return n / (sizeof(TELEM) * 8);
}
// битовая маска для бита n 
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
// получить длину (к-во битов)  
int TBitField::GetLength(void) const
{
    return BitLen;
}

// установить бит  
void TBitField::SetBit(const int n)
{
    if (n < 0 || n >= BitLen)
        throw std::out_of_range::out_of_range("");
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

// очистить бит 
void TBitField::ClrBit(const int n)
{
    if (n < 0 || n >= BitLen)
        throw std::out_of_range::out_of_range("");
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

// получить значение бита
int TBitField::GetBit(const int n) const
{
    if (n < 0 || n >= BitLen)
        throw std::out_of_range::out_of_range("");
    if (pMem[GetMemIndex(n)] & GetMemMask(n))
        return 1;
    return 0;
}
// сравнение 
int TBitField::operator==(const TBitField& bf) const
{
    if (BitLen != bf.BitLen)
        return 0;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 0;
    return 1;
}

// сравнение
int TBitField::operator!=(const TBitField& bf) const
{
    return !(*this == bf);
}
// присваивание 
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
// операция "или" 
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

// операция "и"
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


//отрицание 
TBitField TBitField::operator~(void)
{
    TBitField res(BitLen);
    for (int i = 0; i < BitLen; i++)
        if (GetBit(i) == 0)
            res.SetBit(i);
    return res;
}

std::istream& operator>>(std::istream &istr, TBitField &bf)
{
    char c;
    for (int i = 0; i < bf.BitLen; i++)
    {
        istr >> c;
        if (c == '1')
            bf.SetBit(i);
        else
            bf.ClrBit(i);
    }
    return istr;
}

std::ostream& operator<<(std::ostream &ostr, const TBitField &bf)
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i);
    return ostr;
}