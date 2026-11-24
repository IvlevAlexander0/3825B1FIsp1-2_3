#include "pch.h" 
#include <stdexcept>
#include "../Lab2/utmatrix_reliz.h" 

// TVector 

TEST(TVectorTest, ConstructorAndProperties) {
    TVector<int> v(10, 3); 
    EXPECT_EQ(v.GetSize(), 10);
    EXPECT_EQ(v.GetStartIndex(), 3);

    EXPECT_THROW(v[2], std::out_of_range);
    EXPECT_THROW(v[10], std::out_of_range);
    EXPECT_NO_THROW(v[3]);
}

TEST(TVectorTest, ElementAccessAndEquality) {
    TVector<int> v1(5, 0);
    TVector<int> v2(5, 0);

    for (int i = 0; i < 5; ++i) {
        v1[i] = i * 10;
        v2[i] = i * 10;
    }

    EXPECT_TRUE(v1 == v2);
    v2[4] = 99;
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST(TVectorTest, ScalarOperations) {
    TVector<int> v(4, 1);
    v[1] = 1; v[2] = 2; v[3] = 3;

    TVector<int> res = v + 10;
    EXPECT_EQ(res[1], 11);
    EXPECT_EQ(res[2], 12);
    EXPECT_EQ(res[3], 13);

    TVector<int> res2 = v * 2;
    EXPECT_EQ(res2[1], 2);
    EXPECT_EQ(res2[2], 4);
    EXPECT_EQ(res2[3], 6);
}

TEST(TVectorTest, VectorOperations) {
    TVector<int> v1(3, 0);
    TVector<int> v2(3, 0);

    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    TVector<int> sum = v1 + v2;
    EXPECT_EQ(sum[0], 5);
    EXPECT_EQ(sum[1], 7);
    EXPECT_EQ(sum[2], 9);

    int dot = v1 * v2; 
    EXPECT_EQ(dot, 32);
}

// TMatrix

TEST(TMatrixTest, ConstructorAndStructure) {
    TMatrix<int> m(3);
    EXPECT_EQ(m.GetSize(), 3);

    EXPECT_EQ(m[0].GetStartIndex(), 0);
    EXPECT_EQ(m[0].GetSize(), 3);

    EXPECT_EQ(m[1].GetStartIndex(), 1);
    EXPECT_EQ(m[1].GetSize(), 3);

    EXPECT_THROW(m[1][0], std::out_of_range);
    EXPECT_NO_THROW(m[1][1]);
}

TEST(TMatrixTest, MatrixAdditionAndSubtraction) {
    TMatrix<int> m1(2);
    TMatrix<int> m2(2);

    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][1] = 3;

    m2[0][0] = 10; m2[0][1] = 20;
    m2[1][1] = 30;

    TMatrix<int> sum = m1 + m2;
    EXPECT_EQ(sum[0][0], 11);
    EXPECT_EQ(sum[0][1], 22);
    EXPECT_EQ(sum[1][1], 33);

    TMatrix<int> diff = m2 - m1;
    EXPECT_EQ(diff[0][0], 9);
    EXPECT_EQ(diff[0][1], 18);
    EXPECT_EQ(diff[1][1], 27);
}
