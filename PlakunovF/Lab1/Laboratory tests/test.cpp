#include "pch.h"
#include "../MainLab/tset.h"

//Тесты TBitField
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

    TBitField bf3(50);
    bf3.SetBit(5);
    bf3.SetBit(15);

    TBitField res_and = bf1 & bf3;
    EXPECT_EQ(res_and.GetBit(5), 1);
    EXPECT_EQ(res_and.GetBit(15), 0);
    EXPECT_EQ(res_and.GetBit(10), 0);
}

TEST(TBitFieldTest, bitfield_not) {
    TBitField bf(10);
    bf.SetBit(0);
    TBitField res = ~bf;
    EXPECT_EQ(res.GetBit(0), 0);
    EXPECT_EQ(res.GetBit(1), 1);

    TBitField double_not = ~res;
    EXPECT_TRUE(bf == double_not);
}

TEST(TBitFieldTest, inequality_operator) {
    TBitField bf1(30);
    TBitField bf2(30);
    EXPECT_FALSE(bf1 != bf2);

    bf2.SetBit(5);
    EXPECT_TRUE(bf1 != bf2);
}

TEST(TBitFieldTest, assignment_operator) {
    TBitField bf1(50);
    bf1.SetBit(10);
    bf1.SetBit(20);

    TBitField bf2(10);
    bf2 = bf1;         

    EXPECT_EQ(bf2.GetLength(), 50); 
    EXPECT_EQ(bf2.GetBit(10), 1);
    EXPECT_EQ(bf2.GetBit(20), 1);
}

TEST(TBitFieldTest, bitfield_io) {
    TBitField bf(5);
    bf.SetBit(0);
    bf.SetBit(2);
    bf.SetBit(4);

    std::stringstream ss;
    ss << bf;
    EXPECT_EQ(ss.str(), "10101");
    TBitField bf2(5);
    std::stringstream ss_in("01010");
    ss_in >> bf2;

    EXPECT_EQ(bf2.GetBit(0), 0);
    EXPECT_EQ(bf2.GetBit(1), 1);
    EXPECT_EQ(bf2.GetBit(2), 0);
    EXPECT_EQ(bf2.GetBit(3), 1);
    EXPECT_EQ(bf2.GetBit(4), 0);
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

//Тесты Tset
TEST(TSetTest, create_and_insert) {
    TSet set(100);
    set.InsElem(15);
    EXPECT_TRUE(set.IsMember(15));
    EXPECT_FALSE(set.IsMember(10));
}

TEST(TSetTest, out_of_bounds_elements) {
    TSet set(50);
    EXPECT_FALSE(set.IsMember(-10));
    EXPECT_FALSE(set.IsMember(100));
    EXPECT_THROW(set.InsElem(50), std::invalid_argument);
    EXPECT_THROW(set.DelElem(-1), std::invalid_argument);
}
TEST(TSetTest, copy_and_equality) {
    TSet s1(50);
    s1.InsElem(10);
    TSet s2(s1);
    TSet s3(50);
    s3.InsElem(10);
    EXPECT_TRUE(s2.IsMember(10));
    EXPECT_TRUE(s1 == s3);
    s3.InsElem(20);
    EXPECT_TRUE(s1 != s3);
}

TEST(TSetTest, assignment_operator) {
    TSet s1(50);
    s1.InsElem(10);
    TSet s2(30);
    s2 = s1;
    EXPECT_EQ(s2.GetMaxPower(), 50);
    EXPECT_TRUE(s2.IsMember(10));
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

TEST(TSetTest, set_operations_add_remove_element) {
    TSet s1(50);
    s1.InsElem(10);

    TSet s2 = s1 + 20; 
    EXPECT_TRUE(s2.IsMember(10));
    EXPECT_TRUE(s2.IsMember(20));
    EXPECT_FALSE(s1.IsMember(20)); 

    TSet s3 = s2 - 10; 
    EXPECT_FALSE(s3.IsMember(10));
    EXPECT_TRUE(s3.IsMember(20));

    EXPECT_THROW(s1 + 100, std::invalid_argument);
    EXPECT_THROW(s1 - (-5), std::invalid_argument);
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

TEST(TSetTest, set_complement) {
    TSet s1(10);
    s1.InsElem(5);
    TSet s_not = ~s1;
    EXPECT_FALSE(s_not.IsMember(5)); 
    EXPECT_TRUE(s_not.IsMember(0));  
    EXPECT_TRUE(s_not.IsMember(9));
}

TEST(TSetTest, set_io) {
    TSet set(20);
    set.InsElem(2);
    set.InsElem(5);
    set.InsElem(9);

    std::stringstream ss;
    ss << set;
    EXPECT_EQ(ss.str(), "2 5 9");
    TSet set_in(20);
    std::stringstream ss_in("1 4 7");
    ss_in >> set_in;

    EXPECT_TRUE(set_in.IsMember(1));
    EXPECT_TRUE(set_in.IsMember(4));
    EXPECT_TRUE(set_in.IsMember(7));
    EXPECT_FALSE(set_in.IsMember(2)); 
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