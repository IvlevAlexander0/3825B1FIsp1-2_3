#include "pch.h"
#include "\Users\lapte\Desktop\Blok1\3825B1FIsp1-2_3\includes\Lab2\utmatrix.h"
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
// TVector 
TEST(TVectorTest, Getters) {
    TVector<int> v(5, 2);
    EXPECT_EQ(v.GetSize(), 5);
    EXPECT_EQ(v.GetStartIndex(), 2);
}


TEST(TVectorTest, AccessOperator) {
    TVector<int> v(3, 0);
    v[0] = 10;
    v[1] = 20;
    v[2] = 30;
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
}

TEST(TVectorTest, Access) {
    TVector<int> v(3, 1);
    EXPECT_THROW(v[0], std::out_of_range);
    EXPECT_THROW(v[3], std::out_of_range);
}

TEST(TVectorTest, CopyConstructor) {
    TVector<int> v1(3, 0);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    TVector<int> v2(v1);
    EXPECT_EQ(v1, v2);
}

TEST(TVectorTest, AssignmentOperator) {
    TVector<int> v1(3, 0);
    v1[0] = 5; v1[1] = 6; v1[2] = 7;
    TVector<int> v2(4, 0); // Изначально другого размера
    v2 = v1;
    EXPECT_EQ(v2.GetSize(), 3);
    EXPECT_EQ(v1, v2);
}

TEST(TVectorTest, ComparisonOperators) {
    TVector<int> v1(3, 0);
    TVector<int> v2(3, 0);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);

    v1[0] = 99;
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST(TVectorTest, Addition) {
    TVector<int> v1(3, 0); v1[0] = 1; v1[1] = 2; v1[2] = 3;
    TVector<int> v2(3, 0); v2[0] = 4; v2[1] = 5; v2[2] = 6;
    TVector<int> res = v1 + v2;
    EXPECT_EQ(res[0], 5); EXPECT_EQ(res[1], 7); EXPECT_EQ(res[2], 9);
}

TEST(TVectorTest, Subtraction) {
    TVector<int> v1(3, 0); v1[0] = 1; v1[1] = 2; v1[2] = 3;
    TVector<int> v2(3, 0); v2[0] = 4; v2[1] = 5; v2[2] = 6;
    TVector<int> res = v2 - v1;
    EXPECT_EQ(res[0], 3); EXPECT_EQ(res[1], 3); EXPECT_EQ(res[2], 3);
}

TEST(TVectorTest, DotProduct) {
    TVector<int> v1(3, 0); v1[0] = 1; v1[1] = 2; v1[2] = 3;
    TVector<int> v2(3, 0); v2[0] = 4; v2[1] = 5; v2[2] = 6;
    EXPECT_EQ(v1 * v2, 32); // 1*4 + 2*5 + 3*6 = 32
}

TEST(TVectorTest, ScalarOperations) {
    TVector<int> v(3, 0); v[0] = 1; v[1] = 2; v[2] = 3;

    TVector<int> v_add = v + 10;
    EXPECT_EQ(v_add[0], 11); EXPECT_EQ(v_add[2], 13);

    TVector<int> v_sub = v - 1;
    EXPECT_EQ(v_sub[0], 0); EXPECT_EQ(v_sub[2], 2);

    TVector<int> v_mul = v * 2;
    EXPECT_EQ(v_mul[0], 2); EXPECT_EQ(v_mul[2], 6);
}
// TMatrix 
TEST(TMatrixTest, ConstructorAndStorage) {
    TMatrix<int> m(3);
    EXPECT_EQ(m.GetSize(), 3);

    EXPECT_EQ(m[0].GetStartIndex(), 0);
    EXPECT_EQ(m[1].GetStartIndex(), 1);
    EXPECT_EQ(m[2].GetStartIndex(), 2);
}


TEST(TMatrixTest, Access) {
    TMatrix<int> m(3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][1] = 4; m[1][2] = 5;
    m[2][2] = 6;

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][2], 5);
    EXPECT_EQ(m[2][2], 6);
}

TEST(TMatrixTest, CopyAndAssign) {
    TMatrix<int> m1(2);
    m1[0][1] = 77;

    TMatrix<int> m2(m1); 
    EXPECT_TRUE(m1 == m2);

    TMatrix<int> m3(3);
    m3 = m1;
    EXPECT_TRUE(m1 == m3);
    EXPECT_EQ(m3.GetSize(), 2);
}

TEST(TMatrixTest, Arithmetic) {
    TMatrix<int> m1(2);
    TMatrix<int> m2(2);
    m1[0][0] = 1; m2[0][0] = 10;

    TMatrix<int> sum = m1 + m2;
    EXPECT_EQ(sum[0][0], 11);

    TMatrix<int> diff = m2 - m1;
    EXPECT_EQ(diff[0][0], 9);
}

TEST(TMatrixTest, Comparison) {
    TMatrix<int> m1(2);
    TMatrix<int> m2(2);

    EXPECT_TRUE(m1 == m2); 
    m1[0][1] = 5;
    EXPECT_FALSE(m1 == m2);
    EXPECT_TRUE(m1 != m2);
}
