#include "pch.h"
#include "../MainLab/tset.h"
#include "../MainLab/tblitfield.cpp"
#include "../MainLab/tset.cpp"

TEST(TBitFieldTest, create_and_get) {
    TBitField bf(100);
    bf.SetBit(10);
    EXPECT_EQ(bf.GetBit(10), 1);
    EXPECT_EQ(bf.GetBit(5), 0);
}

TEST(TBitFieldTest, copy_and_equality) {
    TBitField bf1(30);
    bf1.SetBit(5);
    TBitField bf2(bf1);
    TBitField bf3(30);
    bf3.SetBit(5);

    EXPECT_EQ(bf2.GetBit(5), 1);
    EXPECT_TRUE(bf1 == bf3);
}

TEST(TBitFieldTest, negative_size_exception) {
    bool flag = false;
    try {
        TBitField bf(-10);
    }
    catch (...) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TBitFieldTest, clear_bit) {
    TBitField bf(50);
    bf.SetBit(15);
    bf.ClrBit(15);
    EXPECT_EQ(bf.GetBit(15), 0);
}

TEST(TBitFieldTest, out_of_range_exception) {
    TBitField bf(20);
    bool flag = false;
    try {
        bf.GetBit(100);
    }
    catch (...) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TBitFieldTest, bitfield_or_and) {
    TBitField bf1(50);
    TBitField bf2(50);
    bf1.SetBit(5);
    bf2.SetBit(10);

    TBitField res = bf1 | bf2;
    EXPECT_EQ(res.GetBit(5), 1);
    EXPECT_EQ(res.GetBit(10), 1);
}

TEST(TBitFieldTest, bitfield_not) {
    TBitField bf(10);
    bf.SetBit(0);
    TBitField res = ~bf;
    EXPECT_EQ(res.GetBit(0), 0);
    EXPECT_EQ(res.GetBit(1), 1);
}

TEST(TBitFieldTest, random_bits) {
    int size = 200;
    TBitField bf(size);
    for (int i = 0; i < 100; ++i) {
        int idx = rand() % size;
        bf.SetBit(idx);
        EXPECT_EQ(bf.GetBit(idx), 1);
    }
}

TEST(TSetTest, create_and_insert) {
    TSet set(100);
    set.InsElem(15);
    EXPECT_TRUE(set.IsMember(15));
    EXPECT_FALSE(set.IsMember(10));
}

TEST(TSetTest, copy_and_equality) {
    TSet s1(50);
    s1.InsElem(10);
    TSet s2(s1);
    TSet s3(50);
    s3.InsElem(10);

    EXPECT_TRUE(s2.IsMember(10));
    EXPECT_TRUE(s1 == s3);
}

TEST(TSetTest, negative_set_exception) {
    bool flag = false;
    try {
        TSet set(-50);
    }
    catch (...) {
        flag = true;
    }
    EXPECT_TRUE(flag);
}

TEST(TSetTest, delete_element) {
    TSet set(50);
    set.InsElem(20);
    set.DelElem(20);
    EXPECT_FALSE(set.IsMember(20));
}

TEST(TSetTest, set_operations_union) {
    TSet s1(50);
    TSet s2(50);
    s1.InsElem(1);
    s2.InsElem(2);

    TSet s3 = s1 + s2;
    EXPECT_TRUE(s3.IsMember(1));
    EXPECT_TRUE(s3.IsMember(2));
}

TEST(TSetTest, set_operations_intersection) {
    TSet s1(50);
    TSet s2(50);
    s1.InsElem(5);
    s1.InsElem(10);
    s2.InsElem(10);

    TSet s3 = s1 * s2;
    EXPECT_FALSE(s3.IsMember(5));
    EXPECT_TRUE(s3.IsMember(10));
}

TEST(TSetTest, set_difference_and_not) {
    TSet s1(50);
    s1.InsElem(5);
    s1.InsElem(10);

    TSet s_diff = s1 - 5;
    EXPECT_FALSE(s_diff.IsMember(5));
    EXPECT_TRUE(s_diff.IsMember(10));

    TSet s_not = ~s1;
    EXPECT_FALSE(s_not.IsMember(5));
    EXPECT_TRUE(s_not.IsMember(0));
}

TEST(TSetTest, random_elements) {
    int max_val = 100;
    TSet set(max_val);
    for (int i = 0; i < 50; ++i) {
        int val = rand() % max_val;
        set.InsElem(val);
        EXPECT_TRUE(set.IsMember(val));
    }
}