#include "pch.h"
#include "..\Lab2\utmatrix_realiz.h"

TEST(TVector, test1) {
    ASSERT_NO_THROW(TVector<int> v(5));
    ASSERT_NO_THROW(TVector<int> v0(0));
}

TEST(TVector, test2) {
    ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
    ASSERT_ANY_THROW(TVector<int> v(-5));
    ASSERT_ANY_THROW(TVector<int> v(5, -2));
    ASSERT_ANY_THROW(TVector<int> v(5, 5));
    ASSERT_ANY_THROW(TVector<int> v(5, MAX_VECTOR_SIZE + 1));
}

TEST(TVector, test3) {
    TVector<int> v(5, 2); // допустимые индексы: 2, 3, 4
    v[2] = 10;
    v[3] = 20;
    v[4] = 30;

    TVector<int> v1(v);
    EXPECT_EQ(v, v1);
    EXPECT_EQ(10, v1[2]);
    EXPECT_EQ(20, v1[3]);
    EXPECT_EQ(30, v1[4]);

    v1[2] = 100;
    EXPECT_NE(v, v1);
    EXPECT_EQ(10, v[2]);
}

TEST(TVector, test4) {
    TVector<int> v(4, 2); // допустимые индексы: 2, 3
    EXPECT_EQ(4, v.GetSize());
    EXPECT_EQ(2, v.GetStartIndex());
    v[2] = 10;
    v[3] = 20;
    EXPECT_EQ(10, v[2]);
    EXPECT_EQ(20, v[3]);
}

TEST(TVector, test5) {
    TVector<int> v(4, 2); // допустимые индексы: 2, 3
    ASSERT_ANY_THROW(v[-1] = 5);
    ASSERT_ANY_THROW(v[1] = 5);
    ASSERT_ANY_THROW(v[4] = 5);
}

TEST(TVector, test6) {
    TVector<int> v1(4), v2(6);
    for (int i = 0; i < 4; i++) {
        v1[i] = i + 1;
    }

    ASSERT_NO_THROW(v1 = v1);
    EXPECT_EQ(4, v1.GetSize());
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(i + 1, v1[i]);
    }

    v2 = v1;
    EXPECT_EQ(4, v2.GetSize());
    EXPECT_EQ(v1, v2);
}

TEST(TVector, test7) {
    TVector<int> v1(4), v2(4), v3(5), v4(4, 1);
    EXPECT_TRUE(v1 == v2);
    EXPECT_TRUE(v1 != v3);
    EXPECT_TRUE(v1 != v4);
}

TEST(TVector, test8) {
    TVector<int> v(3), res(3);
    for (int i = 0; i < 3; i++) {
        v[i] = i + 1; // 1, 2, 3
    }

    res = v + 5;
    EXPECT_EQ(6, res[0]);
    EXPECT_EQ(7, res[1]);
    EXPECT_EQ(8, res[2]);

    res = v - 1;
    EXPECT_EQ(0, res[0]);
    EXPECT_EQ(1, res[1]);
    EXPECT_EQ(2, res[2]);

    res = v * 3;
    EXPECT_EQ(3, res[0]);
    EXPECT_EQ(6, res[1]);
    EXPECT_EQ(9, res[2]);
}

TEST(TVector, test9) {
    TVector<int> v1(3), v2(3), v3(4);
    for (int i = 0; i < 3; i++) {
        v1[i] = i + 1; // 1, 2, 3
        v2[i] = 10;    // 10, 10, 10
    }

    TVector<int> sum = v1 + v2;
    EXPECT_EQ(11, sum[0]);
    EXPECT_EQ(12, sum[1]);
    EXPECT_EQ(13, sum[2]);

    TVector<int> diff = v1 - v2;
    EXPECT_EQ(-9, diff[0]);
    EXPECT_EQ(-8, diff[1]);
    EXPECT_EQ(-7, diff[2]);

    EXPECT_EQ(60, v1 * v2);

    ASSERT_ANY_THROW(v1 + v3);
    ASSERT_ANY_THROW(v1 - v3);
    ASSERT_ANY_THROW(v1 * v3);
}

TEST(TMatrix, test1) {
    ASSERT_NO_THROW(TMatrix<int> m(5));
    ASSERT_NO_THROW(TMatrix<int> m0(0));
}

TEST(TMatrix, test2) {
    ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
    ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, test3) {
    TMatrix<int> m(3);
    m[0][0] = 1;
    m[1][2] = 5;
    TMatrix<int> m1(m);
    EXPECT_EQ(m, m1);

    m1[0][0] = 99;
    EXPECT_NE(m, m1);
    EXPECT_EQ(1, m[0][0]);
}

TEST(TMatrix, test4) {
    TMatrix<int> m(4);
    EXPECT_EQ(4, m.GetSize());
    m[1][2] = 42;
    EXPECT_EQ(42, m[1][2]);
}

TEST(TMatrix, test5) {
    TMatrix<int> m(4);
    ASSERT_ANY_THROW(m[-1][0] = 5);
    ASSERT_ANY_THROW(m[4][4] = 5);
    ASSERT_ANY_THROW(m[2][0] = 5);
}

TEST(TMatrix, test6) {
    TMatrix<int> m1(3), m2(5);
    m1[0][0] = 5;
    m1[1][2] = 8;

    ASSERT_NO_THROW(m1 = m1);
    EXPECT_EQ(3, m1.GetSize());
    EXPECT_EQ(5, m1[0][0]);
    EXPECT_EQ(8, m1[1][2]);

    m2 = m1;
    EXPECT_EQ(3, m2.GetSize());
    EXPECT_EQ(m1, m2);
}

TEST(TMatrix, test7) {
    TMatrix<int> m1(3), m2(3), m3(4);
    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m1 != m3);
}

TEST(TMatrix, test8) {
    TMatrix<int> m1(3), m2(3), m3(4);
    m1[0][0] = 1;
    m1[0][1] = 10;
    m1[2][2] = 7;

    m2[0][0] = 2;
    m2[0][1] = 4;
    m2[2][2] = 3;

    TMatrix<int> sum = m1 + m2;
    EXPECT_EQ(3, sum[0][0]);
    EXPECT_EQ(14, sum[0][1]);
    EXPECT_EQ(10, sum[2][2]);

    TMatrix<int> diff = m1 - m2;
    EXPECT_EQ(-1, diff[0][0]);
    EXPECT_EQ(6, diff[0][1]);
    EXPECT_EQ(4, diff[2][2]);

    ASSERT_ANY_THROW(m1 + m3);
    ASSERT_ANY_THROW(m1 - m3);
}
