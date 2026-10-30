#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0)
    {
        len = 0;
    }

    BitLen = len;

    const int bitsElement = sizeof(TELEM) * 8;
    MemLen = (BitLen + bitsElement - 1) / bitsElement; //берем больше на вес одного элемента для корректного целочисленного деления, иначе бюдет округление в низ

    if (MemLen > 0)
    {
        pMem = new TELEM[MemLen]();
    }
    else
    {
        pMem = nullptr;
    }
} //create pMem с числом элементов подходящим по введенной длине 

int TBitField::GetLength(void) const {    
    
    return BitLen;
}

int TBitField::GetMemIndex(const int n) const {

    const int bitsElement = sizeof(TELEM) * 8;
    return n / bitsElement; // возвращаем номер элемента полученный простым целочисл делением 
}

TELEM TBitField::GetMemMask(const int n) const {

    const int bitsElement = sizeof(TELEM) * 8;
    return TELEM(1) << (n % bitsElement);

}

void TBitField::SetBit(const int n) {

    if (n < 0 || n >= BitLen) { return; }

    pMem[GetMemIndex(n)] |= GetMemMask(n);

}

void TBitField::ClrBit(const int n) {

    if (n < 0 || n >= BitLen) { return; }

    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const {

    if (n < 0 || n >= BitLen) { return 0; }

    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;

}


TBitField::TBitField(const TBitField& bf)
    : BitLen(bf.BitLen), pMem(nullptr), MemLen(bf.MemLen)
{
    if (MemLen > 0)
    {
        pMem = new TELEM[MemLen];

        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
}
//копироввание

TBitField& TBitField::operator=(const TBitField& bf)
{
    if (this == &bf)
        return *this;

    TELEM* newMem = nullptr;

    if (bf.MemLen > 0)
    {
        newMem = new TELEM[bf.MemLen];

        for (int i = 0; i < bf.MemLen; i++)
            newMem[i] = bf.pMem[i];
    }

    delete[] pMem;

    pMem = newMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;

    return *this;
}
//присваивание с проверкой на самоприсваивание + сначала проверим потом удалим, чтобы не терять данные

int TBitField::operator==(const TBitField& bf) const {

    if (BitLen != bf.BitLen){return 0;}
    
    for (int i = 0; i < MemLen;i++) {

        if (pMem[i] != bf.pMem[i])
            return 0;
    }

    return 1;
}


int TBitField::operator!=(const TBitField& bf) const
{
    return !(*this == bf);
}


TBitField TBitField::operator|(const TBitField& bf)
{
    if (BitLen != bf.BitLen)
        return TBitField(0);

    TBitField result(BitLen);

    for (int i = 0; i < MemLen; i++)
        result.pMem[i] = pMem[i] | bf.pMem[i];

    return result;
}

TBitField TBitField::operator&(const TBitField& bf)
{
    if (BitLen != bf.BitLen)
        return TBitField(0);

    TBitField result(BitLen);

    for (int i = 0; i < MemLen; i++)
        result.pMem[i] = pMem[i] & bf.pMem[i];

    return result;
}

TBitField TBitField::operator~(void){
    TBitField result(BitLen);

    for (int i = 0; i < BitLen; i++)
    {
        if (GetBit(i) == 0)
        {
            result.SetBit(i);
        }
    }

    return result;
}

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf){
    for (int i = 0; i < bf.GetLength(); i++)
    {
        ostr << bf.GetBit(i);
    }

    return ostr;
}

std::istream& operator>>(std::istream& istr, TBitField& bf){
    for (int i = 0; i < bf.BitLen; i++)
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
            bf.SetBit(i);
        else
            bf.ClrBit(i);
    }

    return istr;
}



TBitField::~TBitField(){

    delete[] pMem;
}

