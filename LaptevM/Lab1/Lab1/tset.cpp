#include "../Lab1/tset.h"

// cоздаём множество с максимальной мощностью mp
TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

// преобразование типа к битовому полю
TSet::operator TBitField()
{
    return BitField;
}

// максимальная мощность множества
int TSet::GetMaxPower(void) const
{
    return MaxPower;
}

// включить элемент в множество
void TSet::InsElem(const int Elem)
{
    BitField.SetBit(Elem);
}

// удалить элемент из множества
void TSet::DelElem(const int Elem)
{
    BitField.ClrBit(Elem);
}

// проверить наличие элемента в множестве
int TSet::IsMember(const int Elem) const
{
    return BitField.GetBit(Elem);
}

// сравнение множеств на равенство
int TSet::operator==(const TSet& s) const
{
    if (BitField == s.BitField)
        return 1;
    else
        return 0;
}

// сравнение множеств на неравенство
int TSet::operator!=(const TSet& s) const
{
    if (BitField != s.BitField)
        return 1;
    else
        return 0;
}

// присваивание
TSet& TSet::operator=(const TSet& s)
{
    if (this == &s)
        return *this;

    MaxPower = s.MaxPower;
    BitField = s.BitField;

    return *this;
}

// объединение с элементом
TSet TSet::operator+(const int Elem)
{
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}

// разность с элементом
TSet TSet::operator-(const int Elem)
{
    TSet res(*this);
    res.DelElem(Elem);
    return res;
}

// объединение 
TSet TSet::operator+(const TSet& s)
{
    TBitField bf = BitField | s.BitField;
    TSet res(bf);
    return res;
}

// пересечение
TSet TSet::operator*(const TSet& s)
{
    TBitField bf = BitField & s.BitField;
    TSet res(bf);
    return res;
}

// дополнение 
TSet TSet::operator~(void)
{
    TBitField bf = ~BitField;
    TSet res(bf);
    return res;
}

// ввод множества 
std::istream& operator>>(std::istream& istr, TSet& s)
{
    int count;
    istr >> count; 
    for (int i = 0; i < s.MaxPower; i++){
        s.DelElem(i);
    }
    for (int i = 0; i < count; i++){
        int elem;
        istr >> elem;
        if (elem >= 0 && elem < s.MaxPower)
            s.InsElem(elem);
    }
    return istr;
}

// вывод множества
std::ostream& operator<<(std::ostream& ostr, const TSet& s){
    bool first = true;
    for (int i = 0; i < s.MaxPower; i++) {
        if (s.IsMember(i)) {
            if (!first) ostr << " ";
            ostr << i;
            first = false;
        }
    }
    return ostr;
}

