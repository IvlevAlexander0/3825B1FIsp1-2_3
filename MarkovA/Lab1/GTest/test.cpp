#include "pch.h"

#include "tbitfield.h"
#include "tset.h"

//TBitField
TEST(TestTBitField, Create_BitField) {
    ASSERT_NO_THROW(TBitField bf(10));
    EXPECT_THROW(TBitField bf(-10), std::invalid_argument);
}

TEST(TestTBitField, Constructor_Copy) {
    TBitField bf1(60);
    bf1.SetBit(44);
    TBitField bf2(bf1);
    EXPECT_EQ(bf1.GetBit(44), bf2.GetBit(44));
}

TEST(TestTBitField, SetBit_GetBit_ClrBit) {
    TBitField bf(60);
    bf.SetBit(5);
    EXPECT_EQ(1, bf.GetBit(5));
    EXPECT_EQ(0, bf.GetBit(4));
    EXPECT_EQ(0, bf.GetBit(3));
    bf.ClrBit(5);
    EXPECT_EQ(0, bf.GetBit(5));

    //Border cases
    bf.SetBit(0);
    EXPECT_EQ(1, bf.GetBit(0));
    bf.ClrBit(0);
    EXPECT_EQ(0, bf.GetBit(0));
    bf.SetBit(59);
    EXPECT_EQ(1, bf.GetBit(59));
    bf.ClrBit(59);
    EXPECT_EQ(0, bf.GetBit(59));
}

TEST(TestTBitField, GetLength) {
    for (int i = 2; i <= 128; i*=2) {
        TBitField bf(i);
        EXPECT_EQ(bf.GetLength(), i);
        for (int j = 0; j < i; j++) {
            EXPECT_EQ(0, bf.GetBit(j));
        }
    }
}

TEST(TestTBitField, Operation_ASSINGMENT) {
    TBitField bf1(1000), bf2(231);
    bf2.SetBit(21);
    bf1 = bf2;
    EXPECT_EQ(bf1.GetLength(), bf2.GetLength());
    EXPECT_EQ(1, bf1.GetBit(21));
}

TEST(TestTBitField, Check_Self_ASSINGMENT) {
    TBitField bf(60);
    bf.SetBit(5);
    bf.SetBit(44);
    bf = bf;
    EXPECT_EQ(60, bf.GetLength());
    EXPECT_EQ(1, bf.GetBit(5));
    EXPECT_EQ(1, bf.GetBit(44));
    EXPECT_EQ(0, bf.GetBit(0));
}

TEST(TestTBitField, Operation_COMPARISON) {
    TBitField bf1(75), bf2(75), bf3(9);
    EXPECT_TRUE(bf1 == bf2); 
    EXPECT_TRUE(bf1 != bf3);

    bf2.SetBit(3);
    EXPECT_FALSE(bf1 == bf2);
}

TEST(TestTBitField, Operation_OR) {
    TBitField bf1(10), bf2(10);
    bf1.SetBit(2);
    bf2.SetBit(5);
    TBitField res = bf1 | bf2;
    EXPECT_EQ(1, res.GetBit(2));
    EXPECT_EQ(1, res.GetBit(5));
    EXPECT_EQ(0, res.GetBit(0));
}

TEST(TestTBitField, Operation_AND) {
    TBitField bf1(10), bf2(10);
    bf1.SetBit(2);
    bf1.SetBit(5);
    bf2.SetBit(5);
    TBitField res = bf1 & bf2;
    EXPECT_EQ(0, res.GetBit(2));
    EXPECT_EQ(1, res.GetBit(5));
}

TEST(TestTBitField, Operation_NOT) {
    TBitField bf(5);
    bf.SetBit(0);
    bf.SetBit(2);
    TBitField res = ~bf;
    EXPECT_EQ(0, res.GetBit(0));
    EXPECT_EQ(1, res.GetBit(1));
    EXPECT_EQ(0, res.GetBit(2));
    EXPECT_EQ(1, res.GetBit(3));
    EXPECT_EQ(1, res.GetBit(4));
}

TEST(TestTBitField, Edge_Cases) {
    TBitField empty1(0), empty2(0);
    EXPECT_EQ(0, empty1.GetLength());
    EXPECT_TRUE(empty1 == empty2);
    EXPECT_TRUE((empty1 | empty2) == empty1);
    EXPECT_TRUE((empty1 & empty2) == empty1);
    EXPECT_TRUE((~empty1) == empty1);
    EXPECT_THROW(empty1.SetBit(0), std::out_of_range);
    EXPECT_THROW(empty1.GetBit(0), std::out_of_range);
    EXPECT_THROW(empty1.ClrBit(0), std::out_of_range);

    TBitField bf(64);
    EXPECT_THROW(bf.SetBit(-1), std::out_of_range);
    EXPECT_THROW(bf.SetBit(64), std::out_of_range);
    EXPECT_THROW(bf.ClrBit(-1), std::out_of_range);
    EXPECT_THROW(bf.ClrBit(64), std::out_of_range);
    EXPECT_THROW(bf.GetBit(-1), std::out_of_range);
    EXPECT_THROW(bf.GetBit(64), std::out_of_range);

    bf.SetBit(31);
    bf.SetBit(32);
    EXPECT_EQ(1, bf.GetBit(31));
    EXPECT_EQ(1, bf.GetBit(32));
    EXPECT_EQ(0, bf.GetBit(30));
    EXPECT_EQ(0, bf.GetBit(33));

    TBitField bf1(10), bf2(50);
    bf1.SetBit(3);
    bf2.SetBit(3);
    bf2.SetBit(45);
    TBitField resOr = bf1 | bf2;
    TBitField resAnd = bf1 & bf2;
    EXPECT_EQ(50, resOr.GetLength());
    EXPECT_EQ(1, resOr.GetBit(3));
    EXPECT_EQ(1, resOr.GetBit(45));
    EXPECT_EQ(50, resAnd.GetLength());
    EXPECT_EQ(1, resAnd.GetBit(3));
    EXPECT_EQ(0, resAnd.GetBit(45));
}

// TSet
TEST(TestTSet, Create_Set) {
    ASSERT_NO_THROW(TSet s(50));
    EXPECT_THROW(TSet s(-50), std::invalid_argument);
}

TEST(TestTSet, Constructor_Copy) {
    TSet s1(20);
    s1.InsElem(15);
    TSet s2(s1);
    EXPECT_EQ(s1.GetMaxPower(), s2.GetMaxPower());
    EXPECT_TRUE(s1 == s2);

    TBitField bf(20);
    bf.SetBit(19);
    bf.SetBit(1);
    TSet s3(bf);
    TSet s4(s3);
    EXPECT_EQ(s3.GetMaxPower(), s4.GetMaxPower());
    EXPECT_TRUE(s3 == s4);
}

TEST(TestTSet, InsElem_IsMember_DelElem) {
    TSet s(20);
    s.InsElem(7);
    EXPECT_TRUE(s.IsMember(7));
    EXPECT_FALSE(s.IsMember(6));
    s.DelElem(7);

    for (int i = 0; i < 20; i++) {
        s.InsElem(i);
        EXPECT_EQ(1, s.IsMember(i));
        s.DelElem(i);
        EXPECT_EQ(0, s.IsMember(i));
    }
}

TEST(TestTSet, Operation_COMPARISON) {
    TSet s1(355), s2(355), s3(434);
    EXPECT_TRUE(s1 == s2);
    EXPECT_TRUE(s1 != s3);

    s2.InsElem(24);
    EXPECT_FALSE(s1 == s2);
}

TEST(TestTSet, Operation_ASSINGMENT) {
    TSet s1(355), s2(234);
    s1.InsElem(24);

    s2 = s1;
    EXPECT_EQ(355, s2.GetMaxPower());
    EXPECT_EQ(1, s2.IsMember(24));
}

TEST(TestTSet, Operation_With_Int) {
    TSet s(60);
    EXPECT_EQ(0, s.IsMember(7));
    s = s + 7;
    EXPECT_EQ(1, s.IsMember(7));
    s = s - 7;
    EXPECT_EQ(0, s.IsMember(7));
}

TEST(TestTSet, Operation_Union) {
    TSet s1(10), s2(10), s3(20);
    s1.InsElem(1);
    s2.InsElem(3);
    TSet res = s1 + s2;
    EXPECT_THROW(s1 + s3, std::invalid_argument);
    EXPECT_TRUE(res.IsMember(1));
    EXPECT_TRUE(res.IsMember(3));
    EXPECT_FALSE(res.IsMember(2));
}

TEST(TestTSet, Operation_Intersection) {
    TSet s1(10), s2(10), s3(20);
    s1.InsElem(1);
    s1.InsElem(3);
    s2.InsElem(3);
    TSet res = s1 * s2;
    EXPECT_THROW(s1 * s3, std::invalid_argument);
    EXPECT_FALSE(res.IsMember(1));
    EXPECT_TRUE(res.IsMember(3));
}

TEST(TestTSet, Operation_Complement) {
    TSet s(5);
    s.InsElem(0);
    s.InsElem(2);
    TSet res = ~s;
    EXPECT_FALSE(res.IsMember(0));
    EXPECT_TRUE(res.IsMember(1));
    EXPECT_FALSE(res.IsMember(2));
    EXPECT_TRUE(res.IsMember(3));
    EXPECT_TRUE(res.IsMember(4));
}

TEST(TestTSet, Empty_Set_Operations) {
    TSet empty(20), s(20);
    for (int i = 0; i < 20; i++) {
        EXPECT_FALSE(empty.IsMember(i));
    }

    s.InsElem(3);
    s.InsElem(15);

    EXPECT_TRUE((s + empty) == s);
    EXPECT_TRUE((empty + empty) == empty);
    EXPECT_TRUE((s * empty) == empty);
    EXPECT_TRUE((empty * empty) == empty);

    EXPECT_TRUE((empty - 5) == empty);

    TSet universal = ~empty;
    for (int i = 0; i < 20; i++) {
        EXPECT_TRUE(universal.IsMember(i));
    }
    EXPECT_TRUE((~universal) == empty);

    TSet zeroSet(0);
    EXPECT_EQ(0, zeroSet.GetMaxPower());
    EXPECT_TRUE((zeroSet + zeroSet) == zeroSet);
    EXPECT_TRUE((zeroSet * zeroSet) == zeroSet);
    EXPECT_TRUE((~zeroSet) == zeroSet);
    EXPECT_THROW(zeroSet.InsElem(0), std::out_of_range);
    EXPECT_THROW(zeroSet.DelElem(0), std::out_of_range);
    EXPECT_THROW(zeroSet.IsMember(0), std::out_of_range);
}

TEST(TestTSet, Edge_Cases) {
    TSet s(20);

    s = s + 0;
    s = s + 19;
    EXPECT_TRUE(s.IsMember(0));
    EXPECT_TRUE(s.IsMember(19));

    TSet copy = s;
    s = s;
    EXPECT_TRUE(s == copy);

    TSet s1(10), s2(10), empty10(10);
    s1.InsElem(0);
    s2.InsElem(9);
    EXPECT_TRUE((s1 * s2) == empty10);

    EXPECT_THROW(s.InsElem(-1), std::out_of_range);
    EXPECT_THROW(s.InsElem(20), std::out_of_range);
    EXPECT_THROW(s.DelElem(-1), std::out_of_range);
    EXPECT_THROW(s.DelElem(20), std::out_of_range);
    EXPECT_THROW(s.IsMember(-1), std::out_of_range);
    EXPECT_THROW(s.IsMember(20), std::out_of_range);
    EXPECT_THROW(s + (-1), std::out_of_range);
    EXPECT_THROW(s + 20, std::out_of_range);
    EXPECT_THROW(s - (-1), std::out_of_range);
    EXPECT_THROW(s - 20, std::out_of_range);
}