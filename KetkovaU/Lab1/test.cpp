#include "pch.h"

#include "../Lab1/tbitfield.h"
#include "../Lab1/tset.h"

TEST(TBitField, Constructor)
{
    TBitField bf(10);
    EXPECT_EQ(bf.GetLength(), 10);
}

TEST(TBitField, SetBit)
{
    TBitField bf(5);
    bf.SetBit(2);
    EXPECT_EQ(bf.GetBit(2), 1);
}

TEST(TBitField, ClearBit)
{
    TBitField bf(5);
    bf.SetBit(2);
    bf.ClrBit(2);
    EXPECT_EQ(bf.GetBit(2), 0);
}

TEST(TBitField, GetBit)
{
    TBitField bf(5);
    bf.SetBit(3);
    EXPECT_EQ(bf.GetBit(3), 1);
    EXPECT_EQ(bf.GetBit(1), 0);
}

TEST(TBitField, CopyConstructor)
{
    TBitField bf(5);
    bf.SetBit(1);
    TBitField copy(bf);
    EXPECT_EQ(copy, bf);
}

TEST(TBitField, Assignment)
{
    TBitField bf1(5);
    bf1.SetBit(2);
    TBitField bf2(5);
    bf2 = bf1;
    EXPECT_EQ(bf2, bf1);
}

TEST(TBitField, Equality)
{
    TBitField bf1(5);
    TBitField bf2(5);
    EXPECT_EQ(bf1, bf2);
}

TEST(TBitField, Inequality)
{
    TBitField bf1(5);
    TBitField bf2(5);
    bf1.SetBit(1);
    EXPECT_NE(bf1, bf2);
}

TEST(TBitField, BitwiseOr)
{
    TBitField bf1(4);
    TBitField bf2(4);
    bf1.SetBit(0);
    bf2.SetBit(2);

    TBitField result = bf1 | bf2;

    EXPECT_EQ(result.GetBit(0), 1);
    EXPECT_EQ(result.GetBit(2), 1);
}

TEST(TBitField, BitwiseAnd)
{
    TBitField bf1(4);
    TBitField bf2(4);
    bf1.SetBit(1);
    bf1.SetBit(2);
    bf2.SetBit(2);

    TBitField result = bf1 & bf2;

    EXPECT_EQ(result.GetBit(1), 0);
    EXPECT_EQ(result.GetBit(2), 1);
}

TEST(TSet, Constructor)
{
    TSet s(10);
    EXPECT_EQ(s.GetMaxPower(), 10);
}

TEST(TSet, InsertElement)
{
    TSet s(10);
    s.InsElem(3);
    EXPECT_EQ(s.IsMember(3), 1);
}

TEST(TSet, DeleteElement)
{
    TSet s(10);
    s.InsElem(3);
    s.DelElem(3);
    EXPECT_EQ(s.IsMember(3), 0);
}

TEST(TSet, IsMember)
{
    TSet s(10);
    s.InsElem(4);
    EXPECT_EQ(s.IsMember(4), 1);
    EXPECT_EQ(s.IsMember(5), 0);
}

TEST(TSet, CopyConstructor)
{
    TSet s(10);
    s.InsElem(2);
    TSet copy(s);
    EXPECT_EQ(copy, s);
}

TEST(TSet, Assignment)
{
    TSet s1(10);
    s1.InsElem(2);
    TSet s2(10);
    s2 = s1;
    EXPECT_EQ(s2, s1);
}

TEST(TSet, Equality)
{
    TSet s1(10);
    TSet s2(10);
    EXPECT_EQ(s1, s2);
}

TEST(TSet, Inequality)
{
    TSet s1(10);
    TSet s2(10);
    s1.InsElem(1);
    EXPECT_NE(s1, s2);
}

TEST(TSet, Union)
{
    TSet s1(10);
    TSet s2(10);
    s1.InsElem(1);
    s2.InsElem(2);

    TSet result = s1 + s2;

    EXPECT_EQ(result.IsMember(1), 1);
    EXPECT_EQ(result.IsMember(2), 1);
}

TEST(TSet, Intersection)
{
    TSet s1(10);
    TSet s2(10);
    s1.InsElem(1);
    s1.InsElem(2);
    s2.InsElem(2);

    TSet result = s1 * s2;

    EXPECT_EQ(result.IsMember(1), 0);
    EXPECT_EQ(result.IsMember(2), 1);
}
