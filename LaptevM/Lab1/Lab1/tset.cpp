#include "../Lab1/tset.h"
#include <stdexcept>
// cоздаём множество с максимальной мощностью mp
TSet::TSet(int mp) : MaxPower(mp), BitField(mp){}
// конструктор копирования
TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField){}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf){}

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
    return MaxPower == s.MaxPower && BitField == s.BitField;
}

// сравнение множеств на неравенство
int TSet::operator!=(const TSet& s) const
{
    return !(*this == s);
}

// присваивание
TSet& TSet::operator=(const TSet& s)
{
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
    if (MaxPower != s.MaxPower)
        throw std::invalid_argument::invalid_argument("");
    return TSet(BitField | s.BitField);
}

// пересечение
TSet TSet::operator*(const TSet& s)
{
    if (MaxPower != s.MaxPower)
        throw std::invalid_argument::invalid_argument("");
    return TSet(BitField & s.BitField);
}

// дополнение 
TSet TSet::operator~(void)
{
    return TSet(~BitField);
}

// ввод множества 
std::istream& operator>>(std::istream& istr, TSet &s){
    int count, elem;
    istr >> count;
    for (int i = 0; i < count; i++)
    {
        istr >> elem;
        s.InsElem(elem);
    }
    return istr;
}

// вывод множества
std::ostream& operator<<(std::ostream &ostr, const TSet &s){
    ostr << "{ ";
    for (int i = 0; i < s.MaxPower; i++)
        if (s.IsMember(i))
            ostr << i << " ";
    ostr << "}";
    return ostr;
}

