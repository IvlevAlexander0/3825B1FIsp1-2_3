#include "pch.h"
#include "../../includes/Lab1/tbitfield.h"
#include "../../includes/Lab1/tset.h"
#include <sstream> //для тестов input/out

//Тесты для tbitfield

//создание пустого поля (т.е. вся длина забивается нулями)
TEST(TBitFieldConstructor, empty_field) {
	TBitField bf(8);
	EXPECT_EQ(bf.GetLength(), 8);
	for (int i = 0; i < 8; i++) {
		EXPECT_EQ(bf.GetBit(i), 0);
	}
}

//округление вверх если длина >32 битов 
TEST(TBitFieldConstructor, round_up_if_more_than_32) {
	TBitField bf(36);
	EXPECT_EQ(bf.GetLength(), 36);
	for (int i = 0; i < 36; i++) {
		EXPECT_EQ(bf.GetBit(i), 0);
	}
}

//установка одного конкретного бита не изменяет соседние
TEST(TBitFieldBits, set_single_bit) {
	TBitField bf(8);
	bf.SetBit(3);
	EXPECT_EQ(bf.GetBit(2), 0);
	EXPECT_EQ(bf.GetBit(3), 1);
	EXPECT_EQ(bf.GetBit(4), 0);
}

//установка нескольких битов
TEST(TBitFieldBits, set_multiple_bits) {
	TBitField bf(16);
	bf.SetBit(0);
	bf.SetBit(7);
	bf.SetBit(15);
	EXPECT_EQ(bf.GetBit(0), 1);
	EXPECT_EQ(bf.GetBit(7), 1);
	EXPECT_EQ(bf.GetBit(15), 1);
	EXPECT_EQ(bf.GetBit(8), 0);
}

//сброс бита, остальные неизменны
TEST(TBitFieldBits, clear_bit_keeps_others) {
	TBitField bf(8);
	bf.SetBit(2);
	bf.SetBit(5);
	bf.ClrBit(2);
	EXPECT_EQ(bf.GetBit(2), 0);
	EXPECT_EQ(bf.GetBit(5), 1);
}

//копия реально является копией
TEST(TBitFieldCopy, copy_really_is_copy) {
	TBitField a(8);
	a.SetBit(0);
	a.SetBit(3);

	TBitField b(a);

	EXPECT_EQ(b.GetBit(0), 1);
	EXPECT_EQ(b.GetBit(3), 1);
	EXPECT_EQ(b.GetBit(1), 0);
	EXPECT_EQ(b.GetBit(2), 0);
	for (int i = 4; i < 8; i++) {
		EXPECT_EQ(b.GetBit(i), 0);
	}
}

//изменение копии не влияет на оригинал (deep copy)
TEST(TBitFieldCopy, changing_copy_doesnt_change_original) {
	TBitField a(8);
	a.SetBit(2);

	TBitField b(a);
	b.SetBit(5);

	EXPECT_EQ(a.GetBit(5), 0);
	EXPECT_EQ(a.GetBit(2), 1);
	EXPECT_EQ(b.GetBit(2), 1);
	EXPECT_EQ(b.GetBit(5), 1);
}

//проверка работы сравнений битовых полей
TEST(TBitFieldCompare, compare_equal_and_different) {
	TBitField a(8), b(8);
	a.SetBit(1);
	b.SetBit(1);
	EXPECT_EQ(a == b, 1);
	EXPECT_EQ(a != b, 0);

	b.SetBit(2);
	EXPECT_EQ(a == b, 0);
	EXPECT_EQ(a != b, 1);
}

//поля разной длины не должны быть равны, даже если выглядят одинаково 
TEST(TBitFieldCompare, different_length_not_equal) {
	TBitField a(8), b(16);
	EXPECT_EQ(a == b, 0);
	EXPECT_EQ(a != b, 1);
}

//присваивание + самоприсваивание (не должно ломать битовое поле)
TEST(TBitFieldAssign, assign_and_selfassign) {
	TBitField a(8), b(8);
	a.SetBit(1);
	a.SetBit(4);

	b = a;
	EXPECT_EQ(a, b);

	a = a;
	EXPECT_EQ(a.GetBit(1), 1);
	EXPECT_EQ(a.GetBit(4), 1);
	EXPECT_EQ(a.GetLength(), 8);
}

//присваивание поля другой длины (короткое должно стать длинным, иначе не влезет)
TEST(TBitFieldAssign, assign_different_lengths) {
	TBitField a(8);
	TBitField b(16);
	b.SetBit(10);

	a = b;

	EXPECT_EQ(a.GetLength(), 16);
	EXPECT_EQ(a.GetBit(10), 1);
	EXPECT_EQ(a, b);
}

//операция или
TEST(TBitFieldOperations, bit_or) {
	TBitField a(8);
	TBitField b(8);
	a.SetBit(0);
	a.SetBit(2);
	b.SetBit(2);
	b.SetBit(4);

	TBitField c = a | b;

	EXPECT_EQ(c.GetBit(0), 1);
	EXPECT_EQ(c.GetBit(2), 1);
	EXPECT_EQ(c.GetBit(4), 1);
	EXPECT_EQ(c.GetBit(1), 0);
	EXPECT_EQ(c.GetBit(3), 0);
	EXPECT_EQ(c.GetBit(5), 0);
}

//операция и
TEST(TBitFieldOperations, bit_and) {
	TBitField a(8);
	TBitField b(8);
	a.SetBit(0);
	a.SetBit(2);
	b.SetBit(2);
	b.SetBit(4);

	TBitField c = a & b;

	EXPECT_EQ(c.GetBit(2), 1);
	EXPECT_EQ(c.GetBit(0), 0);
	EXPECT_EQ(c.GetBit(4), 0);
}

//операция отрицания
TEST(TBitFieldOperations, bit_not) {
	TBitField a(8);
	a.SetBit(0);
	a.SetBit(2);

	TBitField c = ~a;

	EXPECT_EQ(c.GetBit(0), 0);
	EXPECT_EQ(c.GetBit(2), 0);
	EXPECT_EQ(c.GetBit(1), 1);
	for (int i = 3; i < 7; i++) {
		EXPECT_EQ(c.GetBit(i), 1);
	}
	EXPECT_EQ(c.GetBit(7), 1);
}

//двойная инверсия возвращает исходное поле
TEST(TBitFieldOperations, double_not_returns_original) {
	TBitField a(100);
	a.SetBit(0);
	a.SetBit(99);

	TBitField c = ~a;
	TBitField d = ~c;

	EXPECT_EQ(a, d);
}

//на выводе: строка из 0 и 1, старший бит слева
TEST(TBitFieldInputOut, out_string) {
	TBitField a(8);
	a.SetBit(0);
	a.SetBit(3);

	std::ostringstream out;
	out << a;

	EXPECT_EQ(out.str(), "00001001");
}

//из строки считалось правильно
TEST(TBitFieldInputOut, in_string) {
	TBitField a(8);
	std::istringstream in("00001001");
	in >> a;

	EXPECT_EQ(a.GetBit(0), 1);
	EXPECT_EQ(a.GetBit(3), 1);
	EXPECT_EQ(a.GetBit(1), 0);
}

//что ввелось - то и вывелось
TEST(TBitFieldInputOut, in_out_equal) {
	TBitField original(8);
	original.SetBit(0);
	original.SetBit(5);
	original.SetBit(7);

	std::ostringstream out;
	out << original;

	TBitField restored(8);
	std::istringstream in(out.str());
	in >> restored;

	EXPECT_EQ(original, restored);
}


//тесты для Tset


//пустое множество
TEST(TSetConstructor, empty_set) {
	TSet s(8);
	EXPECT_EQ(s.GetMaxPower(), 8);
	for (int i = 0; i < 8; i++) {
		EXPECT_EQ(s.IsMember(i), 0);
	}
}

//добавление, удаление, проверка элемента
TEST(TSetElements, insert_delete_check) {
	TSet s(8);
	s.InsElem(2);
	s.InsElem(5);

	EXPECT_EQ(s.IsMember(2), 1);
	EXPECT_EQ(s.IsMember(5), 1);
	EXPECT_EQ(s.IsMember(3), 0);

	s.DelElem(2);

	EXPECT_EQ(s.IsMember(2), 0);
	EXPECT_EQ(s.IsMember(5), 1);
}

//добавление/удаление через оператор не меняет оригинал
TEST(TSetElements, elem_operators_dont_change_original) {
	TSet a(8);
	a.InsElem(2);

	TSet b = a + 5;
	TSet c = b - 2;

	EXPECT_EQ(a.IsMember(5), 0);
	EXPECT_EQ(a.IsMember(2), 1);

	EXPECT_EQ(b.IsMember(2), 1);
	EXPECT_EQ(b.IsMember(5), 1);

	EXPECT_EQ(c.IsMember(2), 0);
	EXPECT_EQ(c.IsMember(5), 1);
}

//копия содержит те же элементы, что и оригинал
TEST(TSetCopy, copies_content) {
	TSet a(8);
	a.InsElem(1);
	a.InsElem(4);

	TSet b(a);

	EXPECT_EQ(a, b);
	EXPECT_EQ(b.IsMember(1), 1);
	EXPECT_EQ(b.IsMember(4), 1);
	EXPECT_EQ(b.IsMember(0), 0);
}

//изменение копии не влияет на оригинал (deep copy)
TEST(TSetCopy, changing_copy_doesnt_change_original) {
	TSet a(8);
	a.InsElem(2);

	TSet b(a);
	b.InsElem(5);

	EXPECT_EQ(a.IsMember(5), 0);
	EXPECT_EQ(a.IsMember(2), 1);
	EXPECT_EQ(b.IsMember(2), 1);
	EXPECT_EQ(b.IsMember(5), 1);
}

//сравнение равных и разных множеств
TEST(TSetCompare, equal_and_different) {
	TSet a(8), b(8);
	a.InsElem(1);
	b.InsElem(1);
	EXPECT_EQ(a == b, 1);
	EXPECT_EQ(a != b, 0);

	b.InsElem(2);
	EXPECT_EQ(a == b, 0);
	EXPECT_EQ(a != b, 1);
}

//присваивание + самоприсваивание (не должно ломать множество)
TEST(TSetAssign, assign_and_selfassign) {
	TSet a(8), b(8);
	a.InsElem(1);
	a.InsElem(4);

	b = a;
	EXPECT_EQ(a, b);

	a = a;
	EXPECT_EQ(a.IsMember(1), 1);
	EXPECT_EQ(a.IsMember(4), 1);
	EXPECT_EQ(a.GetMaxPower(), 8);
}

//объединение двух множеств
TEST(TSetOperations, union_sets) {
	TSet a(8), b(8);
	a.InsElem(0);
	a.InsElem(2);
	b.InsElem(2);
	b.InsElem(4);

	TSet c = a + b;

	EXPECT_EQ(c.IsMember(0), 1);
	EXPECT_EQ(c.IsMember(2), 1);
	EXPECT_EQ(c.IsMember(4), 1);
	EXPECT_EQ(c.IsMember(1), 0);
	EXPECT_EQ(c.IsMember(3), 0);
}

//пересечение двух множеств
TEST(TSetOperations, intersection_sets) {
	TSet a(8), b(8);
	a.InsElem(0);
	a.InsElem(2);
	b.InsElem(2);
	b.InsElem(4);

	TSet c = a * b;

	EXPECT_EQ(c.IsMember(2), 1);
	EXPECT_EQ(c.IsMember(0), 0);
	EXPECT_EQ(c.IsMember(4), 0);
}

//дополнение множества
TEST(TSetOperations, complement) {
	TSet a(8);
	a.InsElem(0);
	a.InsElem(2);

	TSet c = ~a;

	EXPECT_EQ(c.IsMember(0), 0);
	EXPECT_EQ(c.IsMember(2), 0);
	EXPECT_EQ(c.IsMember(1), 1);
	EXPECT_EQ(c.IsMember(3), 1);
	EXPECT_EQ(c.IsMember(7), 1);
}