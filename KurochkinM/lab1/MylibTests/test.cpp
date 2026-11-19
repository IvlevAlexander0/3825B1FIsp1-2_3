#include "pch.h"
#include <sstream>
#include <stdexcept>
#include "rl_tbitfield.h"
#include "rl_tset.h"


//тесты для класса: TBitField


//Конструкторы

TEST(TBitFieldConstructor, ValidLength) {
    EXPECT_NO_THROW(TBitField bf(10));
    EXPECT_NO_THROW(TBitField bf(1));
    EXPECT_NO_THROW(TBitField bf(100));
}

TEST(TBitFieldConstructor, ZeroLengthThrows) {
    EXPECT_THROW(TBitField bf(0), std::invalid_argument);
}

TEST(TBitFieldConstructor, NegativeLengthThrows) {
    EXPECT_THROW(TBitField bf(-5), std::invalid_argument);
}

TEST(TBitFieldConstructor, AllBitsInitiallyZero) {
    TBitField bf(20);
    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(bf.GetBit(i), 0) << "Бит " << i << " должен быть 0";
    }
}

//GetLength

TEST(TBitFieldGetLength, ReturnsCorrectLength) {
    TBitField bf1(1);
    TBitField bf2(32);
    TBitField bf3(100);

    EXPECT_EQ(bf1.GetLength(), 1);
    EXPECT_EQ(bf2.GetLength(), 32);
    EXPECT_EQ(bf3.GetLength(), 100);
}

//SetBit / GetBit

TEST(TBitFieldSetGetBit, SetAndGetSingleBit) {
    TBitField bf(10);
    bf.SetBit(3);
    EXPECT_EQ(bf.GetBit(3), 1);
    EXPECT_EQ(bf.GetBit(0), 0);
    EXPECT_EQ(bf.GetBit(9), 0);
}

TEST(TBitFieldSetGetBit, SetAllBits) {
    TBitField bf(20);
    for (int i = 0; i < 20; i++) {
        bf.SetBit(i);
    }
    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(bf.GetBit(i), 1) << "Бит " << i << " должен быть 1";
    }
}

TEST(TBitFieldSetGetBit, SetBitTwiceDoesNotChange) {
    TBitField bf(5);
    bf.SetBit(2);
    bf.SetBit(2);
    EXPECT_EQ(bf.GetBit(2), 1);
}

TEST(TBitFieldSetGetBit, SetBitOutOfRangeThrows) {
    TBitField bf(10);
    EXPECT_THROW(bf.SetBit(-1), std::out_of_range);
    EXPECT_THROW(bf.SetBit(10), std::out_of_range);
    EXPECT_THROW(bf.SetBit(100), std::out_of_range);
}

TEST(TBitFieldSetGetBit, GetBitOutOfRangeThrows) {
    TBitField bf(10);
    EXPECT_THROW(bf.GetBit(-1), std::out_of_range);
    EXPECT_THROW(bf.GetBit(10), std::out_of_range);
    EXPECT_THROW(bf.GetBit(100), std::out_of_range);
}

TEST(TBitFieldSetGetBit, SetBitAcrossMultipleElements) {
    TBitField bf(100);
    bf.SetBit(0);
    bf.SetBit(31);
    bf.SetBit(32);
    bf.SetBit(63);
    bf.SetBit(99);

    EXPECT_EQ(bf.GetBit(0), 1);
    EXPECT_EQ(bf.GetBit(31), 1);
    EXPECT_EQ(bf.GetBit(32), 1);
    EXPECT_EQ(bf.GetBit(63), 1);
    EXPECT_EQ(bf.GetBit(99), 1);

    EXPECT_EQ(bf.GetBit(1), 0);
    EXPECT_EQ(bf.GetBit(33), 0);
}

// ClrBit

TEST(TBitFieldClrBit, ClearSingleBit) {
    TBitField bf(10);
    bf.SetBit(3);
    EXPECT_EQ(bf.GetBit(3), 1);
    bf.ClrBit(3);
    EXPECT_EQ(bf.GetBit(3), 0);
}

TEST(TBitFieldClrBit, ClearAlreadyClearBit) {
    TBitField bf(5);
    EXPECT_NO_THROW(bf.ClrBit(2));
    EXPECT_EQ(bf.GetBit(2), 0);
}

TEST(TBitFieldClrBit, ClearOnlyOneBitDoesNotAffectOthers) {
    TBitField bf(10);
    for (int i = 0; i < 10; i++) bf.SetBit(i);
    bf.ClrBit(5);
    EXPECT_EQ(bf.GetBit(5), 0);
    for (int i = 0; i < 10; i++) {
        if (i != 5) EXPECT_EQ(bf.GetBit(i), 1);
    }
}

TEST(TBitFieldClrBit, ClearBitOutOfRangeThrows) {
    TBitField bf(10);
    EXPECT_THROW(bf.ClrBit(-1), std::out_of_range);
    EXPECT_THROW(bf.ClrBit(10), std::out_of_range);
}

// Конструктор копирования

TEST(TBitFieldCopy, CopyConstructorCopiesAllBits) {
    TBitField bf1(20);
    bf1.SetBit(0);
    bf1.SetBit(7);
    bf1.SetBit(19);

    TBitField bf2(bf1);
    EXPECT_EQ(bf2.GetLength(), 20);
    EXPECT_EQ(bf2.GetBit(0), 1);
    EXPECT_EQ(bf2.GetBit(7), 1);
    EXPECT_EQ(bf2.GetBit(19), 1);
    EXPECT_EQ(bf2.GetBit(5), 0);
}

TEST(TBitFieldCopy, CopyIsIndependent) {
    TBitField bf1(10);
    bf1.SetBit(3);

    TBitField bf2(bf1);
    bf2.SetBit(5);

    EXPECT_EQ(bf1.GetBit(5), 0);
    EXPECT_EQ(bf2.GetBit(3), 1);
    EXPECT_EQ(bf2.GetBit(5), 1);
}

// Оператор присваивания

TEST(TBitFieldAssignment, AssignCopiesAllBits) {
    TBitField bf1(15);
    bf1.SetBit(0);
    bf1.SetBit(14);

    TBitField bf2(5);
    bf2 = bf1;

    EXPECT_EQ(bf2.GetLength(), 15);
    EXPECT_EQ(bf2.GetBit(0), 1);
    EXPECT_EQ(bf2.GetBit(14), 1);
}

TEST(TBitFieldAssignment, SelfAssignment) {
    TBitField bf(10);
    bf.SetBit(3);
    bf = bf;
    EXPECT_EQ(bf.GetBit(3), 1);
}

//   Операторы == и !=  

TEST(TBitFieldEquality, EqualFields) {
    TBitField bf1(10);
    TBitField bf2(10);
    bf1.SetBit(3);
    bf2.SetBit(3);
    EXPECT_TRUE(bf1 == bf2);
    EXPECT_FALSE(bf1 != bf2);
}

TEST(TBitFieldEquality, DifferentBits) {
    TBitField bf1(10);
    TBitField bf2(10);
    bf1.SetBit(3);
    bf2.SetBit(4);
    EXPECT_FALSE(bf1 == bf2);
    EXPECT_TRUE(bf1 != bf2);
}

TEST(TBitFieldEquality, DifferentLengths) {
    TBitField bf1(10);
    TBitField bf2(20);
    EXPECT_FALSE(bf1 == bf2);
    EXPECT_TRUE(bf1 != bf2);
}

//   Операция &  

TEST(TBitFieldAnd, BasicAnd) {
    TBitField bf1(10);
    TBitField bf2(10);
    bf1.SetBit(1); bf1.SetBit(3); bf1.SetBit(5);
    bf2.SetBit(3); bf2.SetBit(5); bf2.SetBit(7);

    TBitField res = bf1 & bf2;
    EXPECT_EQ(res.GetBit(1), 0);
    EXPECT_EQ(res.GetBit(3), 1);
    EXPECT_EQ(res.GetBit(5), 1);
    EXPECT_EQ(res.GetBit(7), 0);
}

TEST(TBitFieldAnd, AndWithEmpty) {
    TBitField bf1(10);
    TBitField bf2(10);
    bf1.SetBit(1);
    TBitField res = bf1 & bf2;
    for (int i = 0; i < 10; i++) EXPECT_EQ(res.GetBit(i), 0);
}

//   Операция |  

TEST(TBitFieldOr, BasicOr) {
    TBitField bf1(10);
    TBitField bf2(10);
    bf1.SetBit(1); bf1.SetBit(3);
    bf2.SetBit(3); bf2.SetBit(5);

    TBitField res = bf1 | bf2;
    EXPECT_EQ(res.GetBit(1), 1);
    EXPECT_EQ(res.GetBit(3), 1);
    EXPECT_EQ(res.GetBit(5), 1);
    EXPECT_EQ(res.GetBit(7), 0);
}

TEST(TBitFieldOr, OrWithEmpty) {
    TBitField bf1(10);
    TBitField bf2(10);
    bf1.SetBit(1); bf1.SetBit(5);
    TBitField res = bf1 | bf2;
    EXPECT_EQ(res.GetBit(1), 1);
    EXPECT_EQ(res.GetBit(5), 1);
}

//   Операция ~  

TEST(TBitFieldNot, BasicNot) {
    TBitField bf(8);
    bf.SetBit(0);
    bf.SetBit(2);

    TBitField res = ~bf;
    EXPECT_EQ(res.GetBit(0), 0);
    EXPECT_EQ(res.GetBit(1), 1);
    EXPECT_EQ(res.GetBit(2), 0);
    EXPECT_EQ(res.GetBit(3), 1);
}

TEST(TBitFieldNot, DoubleNotReturnsOriginal) {
    TBitField bf(20);
    bf.SetBit(3);
    bf.SetBit(10);
    bf.SetBit(19);

    TBitField res = ~(~bf);
    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(res.GetBit(i), bf.GetBit(i)) << "Бит " << i;
    }
}

//   Ввод / вывод  

TEST(TBitFieldIO, OutputFormat) {
    TBitField bf(5);
    bf.SetBit(0);
    bf.SetBit(2);
    bf.SetBit(4);

    std::ostringstream oss;
    oss << bf;
    EXPECT_EQ(oss.str(), "10101");
}

TEST(TBitFieldIO, InputOutputRoundTrip) {
    std::istringstream iss("10110");
    TBitField bf(5);
    iss >> bf;

    EXPECT_EQ(bf.GetBit(0), 1);
    EXPECT_EQ(bf.GetBit(1), 0);
    EXPECT_EQ(bf.GetBit(2), 1);
    EXPECT_EQ(bf.GetBit(3), 1);
    EXPECT_EQ(bf.GetBit(4), 0);
}

//   Краевые случаи  

TEST(TBitFieldEdgeCases, SingleBitField) {
    TBitField bf(1);
    EXPECT_EQ(bf.GetLength(), 1);
    bf.SetBit(0);
    EXPECT_EQ(bf.GetBit(0), 1);
    bf.ClrBit(0);
    EXPECT_EQ(bf.GetBit(0), 0);
}

TEST(TBitFieldEdgeCases, BoundaryBits) {
    TBitField bf(32);
    bf.SetBit(0);
    bf.SetBit(31);
    EXPECT_EQ(bf.GetBit(0), 1);
    EXPECT_EQ(bf.GetBit(31), 1);
    EXPECT_EQ(bf.GetBit(1), 0);
    EXPECT_EQ(bf.GetBit(30), 0);
}

TEST(TBitFieldEdgeCases, LastBitOfLastElement) {
    TBitField bf(33);
    bf.SetBit(32);
    EXPECT_EQ(bf.GetBit(32), 1);
    EXPECT_EQ(bf.GetBit(31), 0);
}



//тесты для класса: TSet

//   Конструкторы  

TEST(TSetConstructor, ValidPower) {
    EXPECT_NO_THROW(TSet s(10));
    EXPECT_NO_THROW(TSet s(1));
}

TEST(TSetConstructor, AllElementsInitiallyAbsent) {
    TSet s(20);
    for (int i = 0; i < 20; i++) {
        EXPECT_FALSE(s.IsMember(i)) << "Элемент " << i << " не должен быть в множестве";
    }
}

TEST(TSetConstructor, GetMaxPower) {
    TSet s1(10);
    TSet s2(100);
    EXPECT_EQ(s1.GetMaxPower(), 10);
    EXPECT_EQ(s2.GetMaxPower(), 100);
}

//   InsElem / DelElem / IsMember  

TEST(TSetInsDel, InsertSingleElement) {
    TSet s(10);
    s.InsElem(3);
    EXPECT_TRUE(s.IsMember(3));
    EXPECT_FALSE(s.IsMember(0));
    EXPECT_FALSE(s.IsMember(9));
}

TEST(TSetInsDel, DeleteElement) {
    TSet s(10);
    s.InsElem(5);
    EXPECT_TRUE(s.IsMember(5));
    s.DelElem(5);
    EXPECT_FALSE(s.IsMember(5));
}

TEST(TSetInsDel, InsertAllElements) {
    TSet s(20);
    for (int i = 0; i < 20; i++) {
        s.InsElem(i);
    }
    for (int i = 0; i < 20; i++) {
        EXPECT_TRUE(s.IsMember(i)) << "Элемент " << i;
    }
}

TEST(TSetInsDel, InsertDuplicateDoesNotChange) {
    TSet s(10);
    s.InsElem(3);
    s.InsElem(3);
    EXPECT_TRUE(s.IsMember(3));
}

//   Конструктор копирования  

TEST(TSetCopy, CopyConstructorCopiesElements) {
    TSet s1(10);
    s1.InsElem(1);
    s1.InsElem(5);
    s1.InsElem(9);

    TSet s2(s1);
    EXPECT_EQ(s2.GetMaxPower(), 10);
    EXPECT_TRUE(s2.IsMember(1));
    EXPECT_TRUE(s2.IsMember(5));
    EXPECT_TRUE(s2.IsMember(9));
    EXPECT_FALSE(s2.IsMember(0));
}

TEST(TSetCopy, CopyIsIndependent) {
    TSet s1(10);
    s1.InsElem(3);

    TSet s2(s1);
    s2.InsElem(5);

    EXPECT_FALSE(s1.IsMember(5));
    EXPECT_TRUE(s2.IsMember(5));
}

//   Оператор присваивания  

TEST(TSetAssignment, AssignCopiesAllElements) {
    TSet s1(10);
    s1.InsElem(2);
    s1.InsElem(7);

    TSet s2(5);
    s2 = s1;

    EXPECT_EQ(s2.GetMaxPower(), 10);
    EXPECT_TRUE(s2.IsMember(2));
    EXPECT_TRUE(s2.IsMember(7));
}

TEST(TSetAssignment, SelfAssignment) {
    TSet s(10);
    s.InsElem(3);
    s = s;
    EXPECT_TRUE(s.IsMember(3));
}

//   Операторы == и !=  

TEST(TSetEquality, EqualSets) {
    TSet s1(10);
    TSet s2(10);
    s1.InsElem(3);
    s2.InsElem(3);
    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 != s2);
}

TEST(TSetEquality, DifferentSets) {
    TSet s1(10);
    TSet s2(10);
    s1.InsElem(3);
    s2.InsElem(5);
    EXPECT_FALSE(s1 == s2);
    EXPECT_TRUE(s1 != s2);
}

TEST(TSetEquality, DifferentPower) {
    TSet s1(10);
    TSet s2(20);
    EXPECT_FALSE(s1 == s2);
}

//   Операторы + и - с элементом  

TEST(TSetInsertOperator, PlusElement) {
    TSet s(10);
    s.InsElem(3);
    TSet res = s + 5;
    EXPECT_TRUE(res.IsMember(3));
    EXPECT_TRUE(res.IsMember(5));
    EXPECT_FALSE(s.IsMember(5));
}

TEST(TSetInsertOperator, MinusElement) {
    TSet s(10);
    s.InsElem(3);
    s.InsElem(5);
    TSet res = s - 3;
    EXPECT_FALSE(res.IsMember(3));
    EXPECT_TRUE(res.IsMember(5));
    EXPECT_TRUE(s.IsMember(3));
}

//   Операции объединения и пересечения  

TEST(TSetSetOperations, Union) {
    TSet s1(10);
    TSet s2(10);
    s1.InsElem(1); s1.InsElem(3);
    s2.InsElem(3); s2.InsElem(5);

    TSet res = s1 + s2;
    EXPECT_TRUE(res.IsMember(1));
    EXPECT_TRUE(res.IsMember(3));
    EXPECT_TRUE(res.IsMember(5));
    EXPECT_FALSE(res.IsMember(0));
}

TEST(TSetSetOperations, Intersection) {
    TSet s1(10);
    TSet s2(10);
    s1.InsElem(1); s1.InsElem(3); s1.InsElem(5);
    s2.InsElem(3); s2.InsElem(5); s2.InsElem(7);

    TSet res = s1 * s2;
    EXPECT_FALSE(res.IsMember(1));
    EXPECT_TRUE(res.IsMember(3));
    EXPECT_TRUE(res.IsMember(5));
    EXPECT_FALSE(res.IsMember(7));
}

//   Дополнение (~)  

TEST(TSetComplement, BasicComplement) {
    TSet s(10);
    s.InsElem(1);
    s.InsElem(3);

    TSet res = ~s;
    EXPECT_FALSE(res.IsMember(1));
    EXPECT_FALSE(res.IsMember(3));
    EXPECT_TRUE(res.IsMember(0));
    EXPECT_TRUE(res.IsMember(2));
    EXPECT_TRUE(res.IsMember(9));
}

TEST(TSetComplement, DoubleComplementReturnsOriginal) {
    TSet s(10);
    s.InsElem(2);
    s.InsElem(7);

    TSet res = ~(~s);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(res.IsMember(i), s.IsMember(i)) << "Элемент " << i;
    }
}

//   Ввод / вывод  

TEST(TSetIO, OutputFormat) {
    TSet s(5);
    s.InsElem(1);
    s.InsElem(3);

    std::ostringstream oss;
    oss << s;
    EXPECT_EQ(oss.str(), "{1, 3}");
}

TEST(TSetIO, OutputEmptySet) {
    TSet s(5);
    std::ostringstream oss;
    oss << s;
    EXPECT_EQ(oss.str(), "{}");
}

TEST(TSetIO, InputOutputRoundTrip) {
    std::istringstream iss("10101");
    TSet s(5);
    iss >> s;

    EXPECT_TRUE(s.IsMember(0));
    EXPECT_FALSE(s.IsMember(1));
    EXPECT_TRUE(s.IsMember(2));
    EXPECT_FALSE(s.IsMember(3));
    EXPECT_TRUE(s.IsMember(4));
}

//   Преобразование типов  

TEST(TSetConversion, ToBitField) {
    TSet s(10);
    s.InsElem(2);
    s.InsElem(5);

    TBitField bf = s;
    EXPECT_EQ(bf.GetLength(), 10);
    EXPECT_EQ(bf.GetBit(2), 1);
    EXPECT_EQ(bf.GetBit(5), 1);
    EXPECT_EQ(bf.GetBit(0), 0);
}

TEST(TSetConversion, FromBitField) {
    TBitField bf(10);
    bf.SetBit(3);
    bf.SetBit(7);

    TSet s(bf);
    EXPECT_EQ(s.GetMaxPower(), 10);
    EXPECT_TRUE(s.IsMember(3));
    EXPECT_TRUE(s.IsMember(7));
    EXPECT_FALSE(s.IsMember(0));
}

//   Краевые случаи  

TEST(TSetEdgeCases, SingleElementSet) {
    TSet s(1);
    EXPECT_FALSE(s.IsMember(0));
    s.InsElem(0);
    EXPECT_TRUE(s.IsMember(0));
    s.DelElem(0);
    EXPECT_FALSE(s.IsMember(0));
}

TEST(TSetEdgeCases, OperationsWithEmptySets) {
    TSet s1(10);
    TSet s2(10);

    TSet unionRes = s1 + s2;
    for (int i = 0; i < 10; i++) EXPECT_FALSE(unionRes.IsMember(i));

    TSet interRes = s1 * s2;
    for (int i = 0; i < 10; i++) EXPECT_FALSE(interRes.IsMember(i));
}

TEST(TSetEdgeCases, UnionWithFullSet) {
    TSet s1(5);
    TSet s2(5);
    for (int i = 0; i < 5; i++) s1.InsElem(i);

    TSet res = s1 + s2;
    for (int i = 0; i < 5; i++) EXPECT_TRUE(res.IsMember(i));
}