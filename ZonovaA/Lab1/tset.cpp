#include "../../includes/Lab1/tset.h"
#include <stdexcept>
#include <string> 

//конструктор инициализации
TSet::TSet(int mp) :MaxPower(mp), BitField(mp) {}
//конструктор копировани€
TSet::TSet(const TSet& s) :MaxPower(s.MaxPower), BitField(s.BitField) {}
//конструктор преобразовани€ типа
TSet::TSet(const TBitField& bf) :MaxPower(bf.GetLength()), BitField(bf) {}
//преобразование типа к битовому полю
TSet::operator TBitField() {
    return BitField;
}
// доступ к битам
// максимальна€ мощность множества
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
        return *this; //если адреса совпадают Ч это самоприсваивание
    MaxPower = s.MaxPower;
    BitField = s.BitField;//копируем битовое поле, тк у TBitField есть свой оператор присваивани€
    return *this;
}
// объединение с элементом
// элемент должен быть из того же универса
TSet TSet::operator+ (const int Elem) {
    TSet result(*this);//создаЄм копию текущего множества
    result.InsElem(Elem);//добавление элемента
    return result;
}
// разность с элементом
// элемент должен быть из того же универса
TSet TSet::operator- (const int Elem) {
    TSet result(*this);//создаЄм копию текущего множества
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
    // return TSet(~BitField) - инвертирует все биты, поэтому по€вл€ютс€ лишние
    TBitField bf(MaxPower);//создаЄм пустое битовое поле нужной длины
    TBitField inv = ~BitField;//создаем инвертированное исходному полю
    for (int i = 0; i < MaxPower; i++) { //тк копируютс€ только биты в пределах MaxPower нет лишних битов
        if (inv.GetBit(i))
            bf.SetBit(i);
    }
    return TSet(bf);
}
std::istream& operator>>(std::istream& istr, TSet& bf) {
    int n;
    while (istr >> n) { //пока ввод успешный
        if (n < 0) {
            break; //сигнал конца ввода
        }
        if (n >= bf.MaxPower) { //если элемент больше или равен мощности, это ошибка логики, тк n €вл€етс€ еще и индексом
            throw std::out_of_range("Error input: element goes out of range this set");
        }
        bf.InsElem(n);
    }

    if (istr.fail() && !istr.eof()) { //недоступный символ
        throw std::invalid_argument("Element not right");
    }
    return istr;
}
std::ostream& operator<<(std::ostream& ostr, const TSet& bf) {
    ostr << "{";
    int first = 1; //чтобы красиво расставить зап€тые
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