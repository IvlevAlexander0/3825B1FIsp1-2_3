#include "pch.h"
#include <gtest/gtest.h>
#include "tbitfield.h"
#include "tset.h"

//ТЕСТЫ TBitField

// Проверка: конструктор задаёт правильную длину поля
TEST(TBitField, Length){
	TBitField bf(10);
	EXPECT_EQ(bf.GetLength(), 10);
}

// Проверка: установка и считывание бита
TEST(TBitField, SetAndGet){
	TBitField bf(8);

	bf.SetBit(3);
	EXPECT_EQ(bf.GetBit(3), 1);
	EXPECT_EQ(bf.GetBit(2), 0);

	bf.ClrBit(3);
	EXPECT_EQ(bf.GetBit(3), 0);
}

// Проверка: сравнение двух полей
TEST(TBitField, Equality){
	TBitField a(6);
	TBitField b(6);

	a.SetBit(1);
	b.SetBit(1);

	EXPECT_TRUE(a == b);

	b.SetBit(2);
	EXPECT_TRUE(a != b);
}

// Проверка: операции или и не
TEST(TBitField, BitOperations){
	TBitField a(4);
	TBitField b(4);

	a.SetBit(0);
	a.SetBit(2);
	b.SetBit(1);
	b.SetBit(2);

	TBitField c = a | b;
	EXPECT_EQ(c.GetBit(0), 1);
	EXPECT_EQ(c.GetBit(1), 1);
	EXPECT_EQ(c.GetBit(2), 1);

	TBitField d = a & b;
	EXPECT_EQ(d.GetBit(0), 0);
	EXPECT_EQ(d.GetBit(2), 1);

	TBitField e = ~a;
	EXPECT_EQ(e.GetBit(0), 0);
	EXPECT_EQ(e.GetBit(1), 1);
}

// Проверка: ввод и вывод 
TEST(TBitField, InputOutput){
	TBitField a(4);
	a.SetBit(0);
	a.SetBit(2);

	std::stringstream ss;
	ss << a;
	EXPECT_EQ(ss.str(), "1010");

	TBitField b(4);
	std::stringstream ss2("1 0 1 0");
	ss2 >> b;
	EXPECT_EQ(b.GetBit(0), 1);
	EXPECT_EQ(b.GetBit(1), 0);
	EXPECT_EQ(b.GetBit(2), 1);
	EXPECT_EQ(b.GetBit(3), 0);
}


//ТЕСТЫ TSet


// Проверка: добавление и удаление
TEST(TSet, InsertAndDelete){
	TSet s(8);

	s.InsElem(3);
	EXPECT_EQ(s.IsMember(3), 1);

	s.DelElem(3);
	EXPECT_EQ(s.IsMember(3), 0);
}

// Проверка: сравнение 
TEST(TSet, Equality){
	TSet a(6);
	TSet b(6);

	a.InsElem(1);
	b.InsElem(1);

	EXPECT_TRUE(a == b);

	b.InsElem(2);
	EXPECT_TRUE(a != b);
}

// Проверка: объединение и пересечение 
TEST(TSet, UnionAndIntersection){
	TSet a(8);
	TSet b(8);

	a.InsElem(0);
	a.InsElem(2);
	b.InsElem(1);
	b.InsElem(2);

	TSet c = a + b;
	EXPECT_EQ(c.IsMember(0), 1);
	EXPECT_EQ(c.IsMember(1), 1);
	EXPECT_EQ(c.IsMember(2), 1);

	TSet d = a * b;
	EXPECT_EQ(d.IsMember(0), 0);
	EXPECT_EQ(d.IsMember(2), 1);
}

// Проверка: дополнение множества
TEST(TSet, Complement){
	TSet a(4);
	a.InsElem(0);

	TSet b = ~a;

	EXPECT_EQ(b.IsMember(0), 0);
	EXPECT_EQ(b.IsMember(1), 1);
	EXPECT_EQ(b.IsMember(2), 1);
	EXPECT_EQ(b.IsMember(3), 1);
}

// Проверка: объединение и разность с элементом
TEST(TSet, ElementOperations){
	TSet a(5);
	a.InsElem(1);

	TSet b = a + 3;
	EXPECT_EQ(b.IsMember(1), 1);
	EXPECT_EQ(b.IsMember(3), 1);

	TSet c = b - 1;
	EXPECT_EQ(c.IsMember(1), 0);
	EXPECT_EQ(c.IsMember(3), 1);
}

TEST(TSet, InputOutput){
	TSet a(8);
	a.InsElem(1);
	a.InsElem(3);
	a.InsElem(4);

	std::stringstream ss;
	ss << a;

	EXPECT_EQ(ss.str(), "1 3 4");
	TSet b(8);
	std::stringstream ss2("3 1 3 4");
	ss2 >> b;
	EXPECT_EQ(b.IsMember(1), 1);
	EXPECT_EQ(b.IsMember(2), 0);
	EXPECT_EQ(b.IsMember(3), 1);
	EXPECT_EQ(b.IsMember(4), 1);
}