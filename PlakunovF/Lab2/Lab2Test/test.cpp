#include "pch.h"

#include "../Lab2/utmatrix.h"

						// Тесты для TVector

TEST(TVectorTest, DefaultConstructor) {
    TVector<int> v;
    EXPECT_EQ(v.GetSize(), 10);
    EXPECT_EQ(v.GetStartIndex(), 0);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(v[i], 0);
    }
}

TEST(TVectorTest, CustomConstructorAndAccess) {
    TVector<int> v(5, 2); 
    EXPECT_EQ(v.GetSize(), 5);
    EXPECT_EQ(v.GetStartIndex(), 2);

    v[2] = 10;
    v[4] = 60;

    EXPECT_EQ(v[2], 10);
    EXPECT_EQ(v[4], 60);
    EXPECT_EQ(v[3], 0);
}

TEST(TVectorTest, CopyConstructorAndAssignment) {
    TVector<int> v1(3, 0);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    TVector<int> v2(v1);
    EXPECT_EQ(v2.GetSize(), 3);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[2], 3);

    TVector<int> v3;
    v3 = v1;
    EXPECT_EQ(v3.GetSize(), 3);
    EXPECT_EQ(v3[1], 2);
}

TEST(TVectorTest, AdditionAndSubtraction) {
    TVector<int> v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    TVector<int> v2(3);
    v2[0] = 10; v2[1] = 20; v2[2] = 30;

    TVector<int> sum = v1 + v2;
    EXPECT_EQ(sum[0], 11);
    EXPECT_EQ(sum[1], 22);
    EXPECT_EQ(sum[2], 33);

    TVector<int> diff = v2 - v1;
    EXPECT_EQ(diff[0], 9);
    EXPECT_EQ(diff[1], 18);
    EXPECT_EQ(diff[2], 27);
}

TEST(TVectorTest, ScalarOperations) {
    TVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    TVector<int> vPlus = v + 10;
    EXPECT_EQ(vPlus[0], 11);

    TVector<int> vMinus = v - 1;
    EXPECT_EQ(vMinus[0], 0);

    TVector<int> vMult = v * 2;
    EXPECT_EQ(vMult[2], 6);
}

TEST(TVectorTest, DotProduct) {
    TVector<int> v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    TVector<int> v2(3);
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    EXPECT_EQ(v1 * v2, 32);
}

TEST(TVectorTest, IndexOutOfBounds) {
    TVector<int> v(5, 0); 

    EXPECT_THROW(v[-1], std::out_of_range);
    EXPECT_THROW(v[0 - 1], std::out_of_range);

    EXPECT_THROW(v[5], std::out_of_range);
}

TEST(TVectorTest, DifferentSizesAdditionThrows) {
    TVector<int> v1(3);
    TVector<int> v2(4);

    EXPECT_THROW(v1 + v2, std::invalid_argument);
    EXPECT_THROW(v1 - v2, std::invalid_argument);
    EXPECT_THROW(v1 * v2, std::invalid_argument);
}

TEST(TVectorTest, DifferentStartIndicesThrows) {
    TVector<int> v1(3, 0);
    TVector<int> v2(3, 2);

    EXPECT_THROW(v1 + v2, std::invalid_argument);
}

                        // Тесты для TMatrix

TEST(TMatrixTest, ConstructorAndStructure) {
    TMatrix<int> m(3); 
    EXPECT_EQ(m.GetSize(), 3);

    EXPECT_EQ(m[0].GetSize(), 3);
    EXPECT_EQ(m[0].GetStartIndex(), 0);

    EXPECT_EQ(m[1].GetSize(), 3);
    EXPECT_EQ(m[1].GetStartIndex(), 1);

    EXPECT_EQ(m[2].GetSize(), 3);
    EXPECT_EQ(m[2].GetStartIndex(), 2);
}

TEST(TMatrixTest, SetAndGetElements) {
    TMatrix<int> m(3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][1] = 5; m[1][2] = 6;
    m[2][2] = 9;

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][2], 6);
    EXPECT_EQ(m[2][2], 9);

    EXPECT_EQ(m[1][0], 0);
    EXPECT_EQ(m[2][1], 0);
}

TEST(TMatrixTest, AdditionAndSubtraction) {
    TMatrix<int> m1(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][1] = 3;

    TMatrix<int> m2(2);
    m2[0][0] = 10; m2[0][1] = 20;
    m2[1][1] = 30;

    TMatrix<int> sum = m1 + m2;
    EXPECT_EQ(sum[0][0], 11);
    EXPECT_EQ(sum[0][1], 22);
    EXPECT_EQ(sum[1][1], 33);

    TMatrix<int> diff = m2 - m1;
    EXPECT_EQ(diff[0][0], 9);
    EXPECT_EQ(diff[0][1], 18);
}

TEST(TMatrixTest, CopyAndAssign) {
    TMatrix<int> m1(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][1] = 3;

    TMatrix<int> m2(m1);
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[1][1], 3);

    TMatrix<int> m3;
    m3 = m1; 
    EXPECT_EQ(m3.GetSize(), 2);
}

TEST(TMatrixTest, DifferentSizesAdditionThrows) {
    TMatrix<int> m1(2);
    TMatrix<int> m2(3);

    EXPECT_THROW(m1 + m2, std::invalid_argument);
}

TEST(TMatrixTest, ZeroSizeMatrix) {
    EXPECT_THROW(TMatrix<int> m(0), std::invalid_argument);
}
