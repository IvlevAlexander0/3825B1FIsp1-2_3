
#include "pch.h"
#include "../Lab1/tbitfield.cpp"
#include "../Lab1/tset.cpp"
#include <sstream>

TEST(TBitFieldTest, GetLength)
{
    TBitField bf(5);
    EXPECT_EQ(bf.GetLength(), 5);
}

TEST(TBitFieldTest, SetAndGetBit)
{
    TBitField bf(5);

    bf.SetBit(2);

    EXPECT_EQ(bf.GetBit(2), 1);
    EXPECT_EQ(bf.GetBit(1), 0);
}

TEST(TBitFieldTest, ClearBit)
{
    TBitField bf(5);

    bf.SetBit(2);
    bf.ClrBit(2);

    EXPECT_EQ(bf.GetBit(2), 0);
}

TEST(TBitFieldTest, InvalidIndexes)
{
    TBitField bf(5);

    EXPECT_EQ(bf.GetBit(-1), 0);
    EXPECT_EQ(bf.GetBit(5), 0);

    bf.SetBit(-1);
    bf.SetBit(5);
    bf.ClrBit(-1);
    bf.ClrBit(5);

    EXPECT_EQ(bf.GetLength(), 5);
    EXPECT_EQ(bf.GetBit(0), 0);
    EXPECT_EQ(bf.GetBit(4), 0);
}

TEST(TBitFieldTest, BoundaryIndexes)
{
    TBitField bf(5);

    bf.SetBit(0);
    bf.SetBit(4);

    EXPECT_EQ(bf.GetBit(0), 1);
    EXPECT_EQ(bf.GetBit(4), 1);
}

TEST(TBitFieldTest, EmptyBitField)
{
    TBitField bf(0);

    EXPECT_EQ(bf.GetLength(), 0);
    EXPECT_EQ(bf.GetBit(0), 0);

    bf.SetBit(0);
    bf.ClrBit(0);

    EXPECT_EQ(bf.GetLength(), 0);
}

TEST(TBitFieldTest, CopyConstructor)
{
    TBitField a(5);

    a.SetBit(1);
    a.SetBit(4);

    TBitField b(a);

    EXPECT_EQ(b.GetLength(), 5);
    EXPECT_EQ(b.GetBit(1), 1);
    EXPECT_EQ(b.GetBit(4), 1);
    EXPECT_EQ(b.GetBit(0), 0);

    b.ClrBit(1);

    EXPECT_EQ(a.GetBit(1), 1);
    EXPECT_EQ(b.GetBit(1), 0);
}

TEST(TBitFieldTest, AssignmentOperator)
{
    TBitField a(5);
    a.SetBit(2);

    TBitField b(3);
    b.SetBit(0);

    b = a;

    EXPECT_EQ(b.GetLength(), 5);
    EXPECT_EQ(b.GetBit(2), 1);
    EXPECT_EQ(b.GetBit(0), 0);

    b.ClrBit(2);

    EXPECT_EQ(a.GetBit(2), 1);
}

TEST(TBitFieldTest, SelfAssignment)
{
    TBitField a(5);
    a.SetBit(2);

    a = a;

    EXPECT_EQ(a.GetLength(), 5);
    EXPECT_EQ(a.GetBit(2), 1);
}

TEST(TBitFieldTest, BitwiseOr)
{
    TBitField a(5);
    TBitField b(5);

    a.SetBit(0);
    a.SetBit(2);

    b.SetBit(1);
    b.SetBit(2);

    TBitField result = a | b;

    EXPECT_EQ(result.GetBit(0), 1);
    EXPECT_EQ(result.GetBit(1), 1);
    EXPECT_EQ(result.GetBit(2), 1);
    EXPECT_EQ(result.GetBit(3), 0);
    EXPECT_EQ(result.GetBit(4), 0);
}

TEST(TBitFieldTest, BitwiseAnd)
{
    TBitField a(5);
    TBitField b(5);

    a.SetBit(0);
    a.SetBit(2);

    b.SetBit(1);
    b.SetBit(2);

    TBitField result = a & b;

    EXPECT_EQ(result.GetBit(0), 0);
    EXPECT_EQ(result.GetBit(1), 0);
    EXPECT_EQ(result.GetBit(2), 1);
    EXPECT_EQ(result.GetBit(3), 0);
    EXPECT_EQ(result.GetBit(4), 0);
}

TEST(TBitFieldTest, BitwiseNot)
{
    TBitField a(5);

    a.SetBit(1);
    a.SetBit(3);

    TBitField result = ~a;

    EXPECT_EQ(result.GetBit(0), 1);
    EXPECT_EQ(result.GetBit(1), 0);
    EXPECT_EQ(result.GetBit(2), 1);
    EXPECT_EQ(result.GetBit(3), 0);
    EXPECT_EQ(result.GetBit(4), 1);
}

TEST(TBitFieldTest, Compare)
{
    TBitField a(4);
    TBitField b(4);

    a.SetBit(1);
    b.SetBit(1);

    EXPECT_EQ(a == b, 1);
    EXPECT_EQ(a != b, 0);

    b.SetBit(2);

    EXPECT_EQ(a == b, 0);
    EXPECT_EQ(a != b, 1);
}

TEST(TBitFieldTest, CompareDifferentLengths)
{
    TBitField a(4);
    TBitField b(5);

    EXPECT_EQ(a == b, 0);
    EXPECT_EQ(a != b, 1);
}

TEST(TBitFieldTest, OutputOperator)
{
    TBitField bf(5);

    bf.SetBit(0);
    bf.SetBit(2);
    bf.SetBit(4);

    std::stringstream stream;
    stream << bf;

    EXPECT_EQ(stream.str(), "10101");
}

TEST(TBitFieldTest, InputOperator)
{
    TBitField bf(5);
    std::stringstream stream("1 0 1 0 1");

    stream >> bf;

    EXPECT_EQ(bf.GetBit(0), 1);
    EXPECT_EQ(bf.GetBit(1), 0);
    EXPECT_EQ(bf.GetBit(2), 1);
    EXPECT_EQ(bf.GetBit(3), 0);
    EXPECT_EQ(bf.GetBit(4), 1);
    EXPECT_FALSE(stream.fail());
}

TEST(TBitFieldTest, InputIncompleteData)
{
    TBitField bf(5);
    std::stringstream stream("1 0");

    stream >> bf;

    EXPECT_EQ(bf.GetBit(0), 1);
    EXPECT_EQ(bf.GetBit(1), 0);
    EXPECT_TRUE(stream.fail());
}

TEST(TSetTest, GetMaxPower)
{
    TSet s(5);

    EXPECT_EQ(s.GetMaxPower(), 5);
}

TEST(TSetTest, InsertAndCheck)
{
    TSet s(5);

    s.InsElem(2);

    EXPECT_EQ(s.IsMember(2), 1);
    EXPECT_EQ(s.IsMember(1), 0);
}

TEST(TSetTest, DeleteElement)
{
    TSet s(5);

    s.InsElem(2);
    s.DelElem(2);

    EXPECT_EQ(s.IsMember(2), 0);
}

TEST(TSetTest, InvalidElements)
{
    TSet s(5);

    s.InsElem(-1);
    s.InsElem(5);
    s.DelElem(-1);
    s.DelElem(5);

    EXPECT_EQ(s.IsMember(-1), 0);
    EXPECT_EQ(s.IsMember(5), 0);
}

TEST(TSetTest, BoundaryElements)
{
    TSet s(5);

    s.InsElem(0);
    s.InsElem(4);

    EXPECT_EQ(s.IsMember(0), 1);
    EXPECT_EQ(s.IsMember(4), 1);
}

TEST(TSetTest, EmptySet)
{
    TSet s(0);

    EXPECT_EQ(s.GetMaxPower(), 0);
    EXPECT_EQ(s.IsMember(0), 0);

    s.InsElem(0);
    s.DelElem(0);

    EXPECT_EQ(s.GetMaxPower(), 0);
}

TEST(TSetTest, CopyConstructor)
{
    TSet a(5);
    a.InsElem(2);

    TSet b(a);

    EXPECT_EQ(b.GetMaxPower(), 5);
    EXPECT_EQ(b.IsMember(2), 1);

    a.DelElem(2);

    EXPECT_EQ(b.IsMember(2), 1);
}

TEST(TSetTest, AssignmentOperator)
{
    TSet a(3);
    a.InsElem(1);

    TSet b(5);
    b.InsElem(4);

    b = a;

    EXPECT_EQ(b.GetMaxPower(), 3);
    EXPECT_EQ(b.IsMember(1), 1);
    EXPECT_EQ(b.IsMember(4), 0);

    a.DelElem(1);

    EXPECT_EQ(b.IsMember(1), 1);
}

TEST(TSetTest, SelfAssignment)
{
    TSet a(5);
    a.InsElem(2);

    a = a;

    EXPECT_EQ(a.GetMaxPower(), 5);
    EXPECT_EQ(a.IsMember(2), 1);
}

TEST(TSetTest, AddElementOperator)
{
    TSet a(5);

    TSet b = a + 2;

    EXPECT_EQ(a.IsMember(2), 0);
    EXPECT_EQ(b.IsMember(2), 1);
}

TEST(TSetTest, RemoveElementOperator)
{
    TSet a(5);
    a.InsElem(2);

    TSet b = a - 2;

    EXPECT_EQ(a.IsMember(2), 1);
    EXPECT_EQ(b.IsMember(2), 0);
}

TEST(TSetTest, Union)
{
    TSet a(5);
    TSet b(5);

    a.InsElem(0);
    a.InsElem(2);

    b.InsElem(1);
    b.InsElem(2);

    TSet result = a + b;

    EXPECT_EQ(result.GetMaxPower(), 5);
    EXPECT_EQ(result.IsMember(0), 1);
    EXPECT_EQ(result.IsMember(1), 1);
    EXPECT_EQ(result.IsMember(2), 1);
    EXPECT_EQ(result.IsMember(3), 0);
    EXPECT_EQ(result.IsMember(4), 0);
}

TEST(TSetTest, Intersection)
{
    TSet a(5);
    TSet b(5);

    a.InsElem(0);
    a.InsElem(2);

    b.InsElem(1);
    b.InsElem(2);

    TSet result = a * b;

    EXPECT_EQ(result.GetMaxPower(), 5);
    EXPECT_EQ(result.IsMember(0), 0);
    EXPECT_EQ(result.IsMember(1), 0);
    EXPECT_EQ(result.IsMember(2), 1);
    EXPECT_EQ(result.IsMember(3), 0);
    EXPECT_EQ(result.IsMember(4), 0);
}

TEST(TSetTest, Complement)
{
    TSet a(5);

    a.InsElem(1);
    a.InsElem(3);

    TSet result = ~a;

    EXPECT_EQ(result.GetMaxPower(), 5);
    EXPECT_EQ(result.IsMember(0), 1);
    EXPECT_EQ(result.IsMember(1), 0);
    EXPECT_EQ(result.IsMember(2), 1);
    EXPECT_EQ(result.IsMember(3), 0);
    EXPECT_EQ(result.IsMember(4), 1);
}

TEST(TSetTest, Compare)
{
    TSet a(5);
    TSet b(5);

    a.InsElem(1);
    b.InsElem(1);

    EXPECT_EQ(a == b, 1);
    EXPECT_EQ(a != b, 0);

    b.InsElem(2);

    EXPECT_EQ(a == b, 0);
    EXPECT_EQ(a != b, 1);
}

TEST(TSetTest, CompareDifferentPowers)
{
    TSet a(4);
    TSet b(5);

    EXPECT_EQ(a == b, 0);
    EXPECT_EQ(a != b, 1);
}

TEST(TSetTest, UnionDifferentPowers)
{
    TSet a(4);
    TSet b(5);

    TSet result = a + b;

    EXPECT_EQ(result.GetMaxPower(), 0);
}

TEST(TSetTest, IntersectionDifferentPowers)
{
    TSet a(4);
    TSet b(5);

    TSet result = a * b;

    EXPECT_EQ(result.GetMaxPower(), 0);
}

TEST(TSetTest, ConstructorFromBitField)
{
    TBitField bf(5);

    bf.SetBit(1);
    bf.SetBit(3);

    TSet s(bf);

    EXPECT_EQ(s.GetMaxPower(), 5);
    EXPECT_EQ(s.IsMember(1), 1);
    EXPECT_EQ(s.IsMember(3), 1);
    EXPECT_EQ(s.IsMember(0), 0);
}

TEST(TSetTest, ConvertToBitField)
{
    TSet s(5);

    s.InsElem(1);
    s.InsElem(3);

    TBitField bf = s;

    EXPECT_EQ(bf.GetLength(), 5);
    EXPECT_EQ(bf.GetBit(1), 1);
    EXPECT_EQ(bf.GetBit(3), 1);
    EXPECT_EQ(bf.GetBit(0), 0);
}

TEST(TSetTest, OutputOperator)
{
    TSet s(5);

    s.InsElem(1);
    s.InsElem(3);

    std::stringstream stream;
    stream << s;

    EXPECT_EQ(stream.str(), "{1,3}");
}

TEST(TSetTest, OutputEmptySet)
{
    TSet s(5);

    std::stringstream stream;
    stream << s;

    EXPECT_EQ(stream.str(), "{}");
}

TEST(TSetTest, InputOperator)
{
    TSet s(5);
    std::stringstream stream("1 0 1 0 1");

    stream >> s;

    EXPECT_EQ(s.IsMember(0), 1);
    EXPECT_EQ(s.IsMember(1), 0);
    EXPECT_EQ(s.IsMember(2), 1);
    EXPECT_EQ(s.IsMember(3), 0);
    EXPECT_EQ(s.IsMember(4), 1);
    EXPECT_FALSE(stream.fail());
}

TEST(TSetTest, InputIncompleteData)
{
    TSet s(5);
    std::stringstream stream("1 0");

    stream >> s;

    EXPECT_EQ(s.IsMember(0), 1);
    EXPECT_EQ(s.IsMember(1), 0);
    EXPECT_TRUE(stream.fail());
}

TEST(TSetTest, NegativePower)
{
    TSet set(-5);

    EXPECT_EQ(set.GetMaxPower(), 0);
} //проверка на отрицательныый ввод

TEST(TBitFieldTest, InputInvalidBit)
{
    TBitField bf(3);
    std::stringstream input("1 5 0");

    input >> bf;

    EXPECT_TRUE(input.fail());
    EXPECT_EQ(bf.GetBit(0), 1);
    EXPECT_EQ(bf.GetBit(1), 0);
}

TEST(TSetTest, InputInvalidBit)
{
    TSet set(3);
    std::stringstream input("1 5 0");

    input >> set;

    EXPECT_TRUE(input.fail());
    EXPECT_EQ(set.IsMember(0), 1);
    EXPECT_EQ(set.IsMember(1), 0);
}

TEST(TBitFieldTest, OrDifferentLengths)
{
    TBitField a(5);
    TBitField b(10);

    TBitField result = a | b;

    EXPECT_EQ(result.GetLength(), 0);
}

TEST(TBitFieldTest, AndDifferentLengths)
{
    TBitField a(5);
    TBitField b(10);

    TBitField result = a & b;

    EXPECT_EQ(result.GetLength(), 0);
}

TEST(TBitFieldTest, AssignmentDifferentLengths)
{
    TBitField a(5);
    a.SetBit(2);

    TBitField b(10);
    b.SetBit(8);

    a = b;

    EXPECT_EQ(a.GetLength(), 10);
    EXPECT_EQ(a.GetBit(8), 1);
    EXPECT_EQ(a.GetBit(2), 0);
}

TEST(TSetTest, AssignmentDifferentPowers)
{
    TSet a(5);
    a.InsElem(2);

    TSet b(10);
    b.InsElem(8);

    a = b;

    EXPECT_EQ(a.GetMaxPower(), 10);
    EXPECT_EQ(a.IsMember(8), 1);
    EXPECT_EQ(a.IsMember(2), 0);
}

TEST(TBitFieldTest, OrLongerFirstField)
{
    TBitField a(100);
    TBitField b(10);

    TBitField result = a | b;

    EXPECT_EQ(result.GetLength(), 0);
}

TEST(TBitFieldTest, AndLongerFirstField)
{
    TBitField a(100);
    TBitField b(10);

    TBitField result = a & b;

    EXPECT_EQ(result.GetLength(), 0);
}