#include "../../includes/Lab1/tset.h"
#include <iostream>

TSet::TSet(int mp) : BitField(mp) {
    MaxPower = mp;
}

TSet::TSet(const TSet& s) : BitField(s.BitField) {
    MaxPower = s.MaxPower;
}      // конструктор копирования

TSet::TSet(const TBitField& bf) : BitField(bf) {
    MaxPower = bf.GetLength();
} // конструктор преобразования типа

TSet::operator TBitField() {
    return BitField;
}      // преобразование типа к битовому полю

// доступ к битам
int TSet::GetMaxPower(void) const {
    return MaxPower;
}     // максимальная мощность множества

void TSet::InsElem(const int Elem) {
    BitField.SetBit(Elem);
}       // включить элемент в множество

void TSet::DelElem(const int Elem) {
    BitField.ClrBit(Elem);
}       // удалить элемент из множества

int TSet::IsMember(const int Elem) const {
    return BitField.GetBit(Elem);
} // проверить наличие элемента в множестве

    // теоретико-множественные операции
int TSet::operator== (const TSet& s) const {
    return BitField == s.BitField;
} // сравнение

int TSet::operator!= (const TSet& s) const {
    if (*this == s) {
        return 0;
    }
    return 1;
} // несравнение

TSet& TSet::operator=(const TSet& s) {
    if (&s == this) {
        return *this;
    }
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}  // присваивание

TSet TSet::operator+ (const int Elem) {
    TSet result(*this);
    result.InsElem(Elem);
    return result;
} // объединение с элементом
  // элемент должен быть из того же универса

TSet TSet::operator- (const int Elem) {
    TSet result(*this);
    result.DelElem(Elem);
    return result;
} // разность с элементом
  // элемент должен быть из того же универса

TSet TSet::operator+ (const TSet& s) {
    TBitField result_bf = BitField | s.BitField;
    return TSet(result_bf);
}  // объединение

TSet TSet::operator* (const TSet& s) {
    TBitField result_bf = BitField & s.BitField;
    return TSet(result_bf);
}  // пересечение

TSet TSet::operator~ (void) {
    TBitField result_bf = ~BitField;
    return TSet(result_bf);
}           // дополнение

std::istream& operator>>(std::istream& istr, TSet& bf) {
    istr >> bf.BitField;
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& bf) {
    ostr << bf.BitField;
    return ostr;
}