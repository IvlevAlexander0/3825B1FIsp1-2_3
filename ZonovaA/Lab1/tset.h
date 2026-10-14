#pragma once
#include "tbitfield.h"
#include <stdexcept>
#include <string> 

class TSet
{
private:
    int MaxPower;       // максимальная мощность множества
    TBitField BitField; // битовое поле для хранения характеристического вектора
public:
    TSet(int mp);
    TSet(const TSet& s);       // конструктор копирования
    TSet(const TBitField& bf); // конструктор преобразования типа
    operator TBitField();      // преобразование типа к битовому полю
    // доступ к битам
    int GetMaxPower(void) const;     // максимальная мощность множества
    void InsElem(const int Elem);       // добавить элемент в множество
    void DelElem(const int Elem);       // удалить элемент из множества
    int IsMember(const int Elem) const; // проверить наличие элемента в множестве
    // теоретико-множественные операции
    int operator== (const TSet& s) const; // сравнение
    int operator!= (const TSet& s) const; // сравнение
    TSet& operator=(const TSet& s);  // присваивание
    TSet operator+ (const int Elem); // объединение с элементом
    // элемент должен быть из того же универса
    TSet operator- (const int Elem); // разность с элементом
    // элемент должен быть из того же универса
    TSet operator+ (const TSet& s);  // объединение
    TSet operator* (const TSet& s);  // пересечение
    TSet operator~ (void);           // дополнение

    friend std::istream& operator>>(std::istream& istr, TSet& bf) {
        int n;
        while (istr >> n) { //пока ввод успешный
            if (n < 0) {
                break; //сигнал конца ввода
            }
            if (n >= bf.MaxPower) { //если элемент больше или равен мощности, это ошибка логики, тк n является еще и индексом
                throw std::out_of_range("Error input: element goes out of range this set");
            }
            bf.InsElem(n);
        }
       
        if (istr.fail() && !istr.eof()) { //недоступный символ
            throw std::invalid_argument("Element not right");
        }
        return istr;
    }
    friend std::ostream& operator<<(std::ostream& ostr, const TSet& bf) {
        ostr << "{";
        int first = 1; //чтобы красиво расставить запятые
        for (int i = 0; i < bf.MaxPower; i++) {
            if (bf.IsMember(i)) {
                if (!first) ostr << ", ";
                ostr << i;
                first = 0;
            }
        }
        ostr << "}";
        return ostr;
    }
};
//конструктор инициализации
TSet::TSet(int mp):MaxPower(mp),BitField(mp) {}     
//конструктор копирования
TSet::TSet(const TSet& s):MaxPower(s.MaxPower), BitField(s.BitField) {}
//конструктор преобразования типа
TSet::TSet(const TBitField& bf):MaxPower(bf.GetLength()), BitField(bf) {}
//преобразование типа к битовому полю
TSet::operator TBitField() {
    return BitField;
}
// доступ к битам
// максимальная мощность множества
int TSet::GetMaxPower(void) const {
    return MaxPower;
}
// включить элемент в множество
void TSet::InsElem(const int Elem) {
    BitField.SetBit(Elem); //устанавливаем бит номера Elem
}
// удалить элемент из множества
void TSet::DelElem(const int Elem) {
    BitField.ClrBit(Elem);
}
// проверить наличие элемента в множестве
int TSet::IsMember(const int Elem) const {
    if (BitField.GetBit(Elem))
        return 1;
    else
        return 0;
}
// теоретико-множественные операции
// сравнение
int TSet::operator== (const TSet& s) const {
    if (BitField == s.BitField)
        return 1;
    else
        return 0;
}
// сравнение
int TSet::operator!= (const TSet& s) const {
    if (BitField != s.BitField)
        return 1;
    else
        return 0;
}
// присваивание
TSet& TSet::operator=(const TSet& s) {
    if (this == &s)
        return *this; //если адреса совпадают — это самоприсваивание
    MaxPower = s.MaxPower;
    BitField = s.BitField;//копируем битовое поле, тк у TBitField есть свой оператор присваивания
    return *this;
}
// объединение с элементом
// элемент должен быть из того же универса
TSet TSet::operator+ (const int Elem) {
    TSet result(*this);//создаём копию текущего множества
    result.InsElem(Elem);//добавление элемента
    return result;
}
// разность с элементом
// элемент должен быть из того же универса
TSet TSet::operator- (const int Elem) {
    TSet result(*this);//создаём копию текущего множества
    result.DelElem(Elem);//удаление элемента
    return result;
}
// объединение
TSet TSet::operator+ (const TSet& s) {
    return TSet(BitField | s.BitField);
}
// пересечение
TSet TSet::operator* (const TSet& s) {
    return TSet(BitField & s.BitField);
}
// дополнение
TSet TSet::operator~ (void) {
    // return TSet(~BitField) - инвертирует все биты, поэтому появляются лишние
    TBitField bf(MaxPower);//создаём пустое битовое поле нужной длины
    TBitField inv = ~BitField;//создаем инвертированное исходному полю
    for (int i = 0; i < MaxPower; i++) { //тк копируются только биты в пределах MaxPower нет лишних битов
        if (inv.GetBit(i))
            bf.SetBit(i);
    }
    return TSet(bf);
}
