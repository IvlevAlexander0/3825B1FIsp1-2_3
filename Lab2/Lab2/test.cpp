#include "pch.h"
#include "C:\users\yuket\source\repos\Lab1\3825B1FIsp1-2_3\includes\utmatrix.h"
#include "umatrix1.h"

#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>

// TVector construction, indexing and memory semantics
TEST(TVectorTests, ConstructionAndValidation)
{
    EXPECT_NO_THROW((TVector<int>(10, 3)));
    EXPECT_THROW((TVector<int>(-1, 0)), std::invalid_argument);
    EXPECT_THROW((TVector<int>(10, -1)), std::invalid_argument);
    EXPECT_THROW((TVector<int>(10, 11)), std::invalid_argument);
    EXPECT_THROW((TVector<int>(MAX_VECTOR_SIZE + 1, 0)), std::invalid_argument);

    TVector<int> empty(0, 0);
    EXPECT_EQ(empty.GetSize(), 0);
    EXPECT_EQ(empty.GetStartIndex(), 0);
}

TEST(TVectorTests, IndexingUsesLogicalIndices)
{
    TVector<int> v(8, 3);
    EXPECT_EQ(v.GetSize(), 8);
    EXPECT_EQ(v.GetStartIndex(), 3);

    v[3] = 10;
    v[7] = 20;
    EXPECT_EQ(v[3], 10);
    EXPECT_EQ(v[7], 20);
    EXPECT_THROW(v[2], std::out_of_range);
    EXPECT_THROW(v[8], std::out_of_range);
}

TEST(TVectorTests, CopyIsDeep)
{
    TVector<int> a(5, 2);
    a[2] = 12;
    a[4] = 99;

    TVector<int> b(a);
    EXPECT_TRUE(a == b);
    b[2] = -1;
    EXPECT_EQ(a[2], 12);
    EXPECT_EQ(b[2], -1);
}

TEST(TVectorTests, AssignmentAndSelfAssignment)
{
    TVector<int> a(3, 0);
    TVector<int> b(8, 4);
    b[4] = 41;
    b[7] = 77;

    a = b;
    EXPECT_EQ(a.GetSize(), 8);
    EXPECT_EQ(a.GetStartIndex(), 4);
    EXPECT_EQ(a[4], 41);
    EXPECT_EQ(a[7], 77);

    a = a;
    EXPECT_EQ(a[4], 41);
    EXPECT_EQ(a[7], 77);
}

TEST(TVectorTests, ScalarOperations)
{
    TVector<int> v(5, 2);
    v[2] = 1;
    v[3] = 2;
    v[4] = 3;

    auto plus = v + 4;
    auto minus = v - 1;
    auto multiply = v * 3;

    EXPECT_EQ(plus[2], 5);
    EXPECT_EQ(plus[4], 7);
    EXPECT_EQ(minus[3], 1);
    EXPECT_EQ(multiply[4], 9);
    EXPECT_EQ(plus.GetSize(), 5);
    EXPECT_EQ(plus.GetStartIndex(), 2);
}

TEST(TVectorTests, VectorOperationsAndDimensionChecks)
{
    TMatrix<int> m(4);
    TVector<int> a(5, 2), b(5, 2);
    a[2] = 1; a[3] = 2; a[4] = 3;
    b[2] = 10; b[3] = 20; b[4] = 30;

    auto sum = a + b;
    auto difference = b - a;
    EXPECT_EQ(sum[2], 11);
    EXPECT_EQ(sum[4], 33);
EXPECT_EQ(m.GetSize(), 4);
EXPECT_EQ(m.GetStartIndex(), 0);

for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(m[i].GetSize(), 4);
    EXPECT_EQ(m[i].GetStartIndex(), i);
    for (int j = i; j < 4; ++j) {
        EXPECT_EQ(m[i][j], 0);
    }
    if (i > 0) {
        EXPECT_THROW(m[i][i - 1], std::out_of_range);
    }
}

EXPECT_NO_THROW((TMatrix<int>(0)));
EXPECT_THROW((TMatrix<int>(-1)), std::invalid_argument);
EXPECT_THROW((TMatrix<int>(MAX_MATRIX_SIZE + 1)), std::invalid_argument);
}

TEST(TMatrixTests, CopyConstructorMakesIndependentMatrix)
{
    TMatrix<int> a(3);
    a[0][0] = 1;
    a[0][2] = 3;
    a[1][2] = 5;

    TMatrix<int> b(a);
    EXPECT_TRUE(a == b);
    b[0][0] = 100;
    EXPECT_EQ(a[0][0], 1);
    EXPECT_EQ(b[0][0], 100);
}

TEST(TVectorTests, IncompatibleVectorsThrowExceptions)
{
    TVector<int> a(5, 0);
    TVector<int> b(3, 0);
    TVector<int> c(5, 2);

    // Different sizes
    EXPECT_THROW(a + b, std::invalid_argument);
    EXPECT_THROW(a - b, std::invalid_argument);

    // Same size, but different start indices
    EXPECT_THROW(a + c, std::invalid_argument);
    EXPECT_THROW(a - c, std::invalid_argument);
}

TEST(TMatrixTests, SelfAssignment)
{
    TMatrix<int> m(3);

    m[0][0] = 10;
    m[0][1] = 20;
    m[0][2] = 30;
    m[1][1] = 40;
    m[1][2] = 50;
    m[2][2] = 60;

    m = m;

    EXPECT_EQ(m.GetSize(), 3);
    EXPECT_EQ(m.GetStartIndex(), 0);

    EXPECT_EQ(m[0][0], 10);
    EXPECT_EQ(m[0][1], 20);
    EXPECT_EQ(m[0][2], 30);
    EXPECT_EQ(m[1][1], 40);
    EXPECT_EQ(m[1][2], 50);
    EXPECT_EQ(m[2][2], 60);
}

TEST(TMatrixTests, AddingMatricesOfDifferentSizesThrows)
{
    TMatrix<int> a(3);
    TMatrix<int> b(4);

    EXPECT_THROW(a + b, std::invalid_argument);
}
