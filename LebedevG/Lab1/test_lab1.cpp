#include <gtest/gtest.h>
#include <sstream>
#include "tbitfield.h"
#include "tset.h"

// ==================== TBitField ====================

TEST(TBitFieldTest, CreateAndLength) {
    TBitField bf(10);
    EXPECT_EQ(bf.GetLength(), 10);
}

TEST(TBitFieldTest, SetAndGetBit) {
    TBitField bf(10);
    bf.SetBit(3);
    EXPECT_EQ(bf.GetBit(3), 1);
    EXPECT_EQ(bf.GetBit(0), 0);
    EXPECT_EQ(bf.GetBit(9), 0);
}

TEST(TBitFieldTest, ClearBit) {
    TBitField bf(10);
    bf.SetBit(5);
    bf.ClrBit(5);
    EXPECT_EQ(bf.GetBit(5), 0);
}

TEST(TBitFieldTest, OutOfRangeDoesNotCrash) {
    TBitField bf(5);
    bf.SetBit(-1);
    bf.SetBit(100);
    EXPECT_EQ(bf.GetBit(-1), 0);
    EXPECT_EQ(bf.GetBit(100), 0);
}

TEST(TBitFieldTest, Equality) {
    TBitField a(8), b(8);
    a.SetBit(1); a.SetBit(3);
    b.SetBit(1); b.SetBit(3);
    EXPECT_TRUE(a == b);

    b.SetBit(5);
    EXPECT_TRUE(a != b);
}

TEST(TBitFieldTest, CopyConstructor) {
    TBitField a(8);
    a.SetBit(2);
    TBitField b(a);
    EXPECT_TRUE(a == b);
    b.ClrBit(2);
    EXPECT_TRUE(a != b);  // изменение копии не влияет на оригинал
}

TEST(TBitFieldTest, AssignmentOperator) {
    TBitField a(8), b(4);
    a.SetBit(5);
    b = a;
    EXPECT_EQ(b.GetLength(), 8);
    EXPECT_TRUE(a == b);
}

TEST(TBitFieldTest, Union) {
    TBitField a(8), b(8);
    a.SetBit(0);
    b.SetBit(7);
    TBitField c = a | b;
    EXPECT_EQ(c.GetBit(0), 1);
    EXPECT_EQ(c.GetBit(7), 1);
}

TEST(TBitFieldTest, Intersection) {
    TBitField a(8), b(8);
    a.SetBit(0); a.SetBit(1);
    b.SetBit(1); b.SetBit(2);
    TBitField c = a & b;
    EXPECT_EQ(c.GetBit(0), 0);
    EXPECT_EQ(c.GetBit(1), 1);
    EXPECT_EQ(c.GetBit(2), 0);
}

TEST(TBitFieldTest, Inversion) {
    TBitField a(5);
    a.SetBit(1);
    TBitField b = ~a;
    EXPECT_EQ(b.GetBit(0), 1);
    EXPECT_EQ(b.GetBit(1), 0);
    EXPECT_EQ(b.GetBit(4), 1);
}

TEST(TBitFieldTest, StreamOutput) {
    TBitField a(4);
    a.SetBit(0);
    a.SetBit(3);
    std::ostringstream oss;
    oss << a;
    EXPECT_EQ(oss.str(), "1001");
}

// ==================== TSet ====================

TEST(TSetTest, CreateAndMaxPower) {
    TSet s(10);
    EXPECT_EQ(s.GetMaxPower(), 10);
}

TEST(TSetTest, InsertAndCheck) {
    TSet s(10);
    s.InsElem(3);
    EXPECT_EQ(s.IsMember(3), 1);
    EXPECT_EQ(s.IsMember(4), 0);
}

TEST(TSetTest, DeleteElement) {
    TSet s(10);
    s.InsElem(3);
    s.DelElem(3);
    EXPECT_EQ(s.IsMember(3), 0);
}

TEST(TSetTest, CopyAndEquality) {
    TSet s1(10);
    s1.InsElem(1);
    s1.InsElem(5);
    TSet s2(s1);
    EXPECT_TRUE(s1 == s2);

    s2.DelElem(1);
    EXPECT_TRUE(s1 != s2);
}

TEST(TSetTest, AddElementOperator) {
    TSet s(10);
    TSet s2 = s + 4;
    EXPECT_EQ(s2.IsMember(4), 1);
    EXPECT_EQ(s.IsMember(4), 0);  // s не изменился
}

TEST(TSetTest, RemoveElementOperator) {
    TSet s(10);
    s.InsElem(4);
    TSet s2 = s - 4;
    EXPECT_EQ(s2.IsMember(4), 0);
    EXPECT_EQ(s.IsMember(4), 1);
}

TEST(TSetTest, UnionSets) {
    TSet a(10), b(10);
    a.InsElem(1);
    b.InsElem(5);
    TSet c = a + b;
    EXPECT_EQ(c.IsMember(1), 1);
    EXPECT_EQ(c.IsMember(5), 1);
}

TEST(TSetTest, IntersectionSets) {
    TSet a(10), b(10);
    a.InsElem(1); a.InsElem(2);
    b.InsElem(2); b.InsElem(3);
    TSet c = a * b;
    EXPECT_EQ(c.IsMember(1), 0);
    EXPECT_EQ(c.IsMember(2), 1);
    EXPECT_EQ(c.IsMember(3), 0);
}

TEST(TSetTest, Complement) {
    TSet a(3);
    a.InsElem(0);
    TSet b = ~a;
    EXPECT_EQ(b.IsMember(0), 0);
    EXPECT_EQ(b.IsMember(1), 1);
    EXPECT_EQ(b.IsMember(2), 1);
}

TEST(TSetTest, StreamOutput) {
    TSet s(5);
    s.InsElem(0);
    s.InsElem(3);
    std::ostringstream oss;
    oss << s;
    EXPECT_EQ(oss.str(), "{ 0, 3 }");
}