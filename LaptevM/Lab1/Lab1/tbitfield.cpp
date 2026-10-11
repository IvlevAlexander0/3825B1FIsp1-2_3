#include "tbitfield.h"

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
    BitLen = len;
    MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
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
    int i = GetMemIndex(n);
    TELEM m = GetMemMask(n);
    pMem[i] = pMem[i] | m;
}

// очистить бит 
void TBitField::ClrBit(const int n)
{
    int i = GetMemIndex(n);
    TELEM m = GetMemMask(n);
    pMem[i] = pMem[i] & ~m;
}

// получить значение бита
int TBitField::GetBit(const int n) const
{
    int i = GetMemIndex(n);
    TELEM m = GetMemMask(n);
    if (pMem[i] & m)
        return 1;
    else
        return 0;
}
// сравнение 
int TBitField::operator==(const TBitField& bf) const
{
    if (BitLen != bf.BitLen)
        return 0;
    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i])
            return 0;
    }
    return 1;
}

// сравнение
int TBitField::operator!=(const TBitField& bf) const
{
    if (*this == bf)
        return 0;
    else
        return 1;
}
// присваивание 
TBitField& TBitField::operator=(const TBitField& bf)
{
    if (this == &bf)
        return *this;

    delete[] pMem;

    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];

    return *this;
}
// операция "или" 
TBitField TBitField::operator|(const TBitField& bf)
{
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; i++)
        res.pMem[i] = pMem[i] | bf.pMem[i];
    return res;
}

// операция "и"
TBitField TBitField::operator&(const TBitField& bf)
{
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; i++)
        res.pMem[i] = pMem[i] & bf.pMem[i];
    return res;
}

//отрицание 
TBitField TBitField::operator~(void)
{
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; i++)
        res.pMem[i] = ~pMem[i];

    //обнуляем "лишние" биты в последнем элементе
    int ostatok = BitLen % (sizeof(TELEM) * 8);
    if (ostatok != 0)
    {
        TELEM m = (1 << ostatok) - 1;
        res.pMem[MemLen - 1] = res.pMem[MemLen - 1] & m;
    }

    return res;
}

std::istream& operator>>(std::istream& istr, TBitField& bf)
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        int b;
        istr >> b;
        if (b == 1)
            bf.SetBit(i);
        else
            bf.ClrBit(i);
    }
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf)
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        ostr << bf.GetBit(i);
    }
    return ostr;
}