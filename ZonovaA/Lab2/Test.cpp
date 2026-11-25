#include <gtest/gtest.h>
#include <stdexcept>
#include "utmatrix.cpp"


using namespace std;

TEST(TVec, DIni) {
    ASSERT_NO_THROW(TVector<int> vDe);
    TVector<int> vDef;
    EXPECT_EQ(10, vDef.GetSize());
    EXPECT_EQ(0, vDef.GetStartIndex());

    ASSERT_NO_THROW(TVector<double> vC(7, 3));
    TVector<double> vCu(7, 3);
    EXPECT_EQ(7, vCu.GetSize());
    EXPECT_EQ(3, vCu.GetStartIndex());
}

TEST(TVec, InDim) {
    ASSERT_THROW(TVector<int>(-10), std::out_of_range);
    ASSERT_THROW(TVector<int>(MAX_VECTOR_SIZE + 50), std::out_of_range);

    ASSERT_THROW(TVector<int>(5, 10), std::out_of_range);
    ASSERT_THROW(TVector<int>(5, -1), std::out_of_range);

    ASSERT_NO_THROW(TVector<int>(0, 0)); //нулевой размер допустим
    TVector<int> vZ(0, 0);
    EXPECT_EQ(0, vZ.GetSize());
}

TEST(TVec, ShIn) {
    //данные начинаются с индекса 10
    TVector<int> vS(15, 10);
    //допустимые индексы: 10, 11, ..., 14
    ASSERT_NO_THROW(vS[10] = 100);
    ASSERT_NO_THROW(vS[14] = 140);

    EXPECT_EQ(100, vS[10]);
    EXPECT_EQ(140, vS[14]);

    ASSERT_THROW(vS[9], std::out_of_range);
    ASSERT_THROW(vS[0], std::out_of_range);
    ASSERT_THROW(vS[15], std::out_of_range);
    ASSERT_THROW(vS[99], std::out_of_range);
}

TEST(TVec, SaCop) {
    TVector<int> vO(4, 1);
    vO[1] = 55;
    vO[3] = 77;

    TVector<int> vCop(vO);
    EXPECT_EQ(55, vCop[1]);
    vCop[1] = 99; 
    EXPECT_EQ(55, vO[1]); 

    TVector<int> vT(2, 0);
    vT = vO;
    EXPECT_EQ(4, vT.GetSize());
    EXPECT_EQ(1, vT.GetStartIndex());
    EXPECT_EQ(77, vT[3]);

    vO = vO;
    EXPECT_EQ(55, vO[1]);
}

TEST(TVec, Scal) {
    TVector<int> v(3, 0);
    v[0] = 1; v[1] = 20; v[2] = 3;

    EXPECT_EQ(11, (v + 10)[0]);
    EXPECT_EQ(15, (v - 5)[1]);
    EXPECT_EQ(6, (v * 2)[2]);  // 3 * 2 = 6

    EXPECT_EQ(1, v[0]);
}

TEST(TVec, Vec) {
    TVector<int> v1(4, 1);
    v1[1] = 2; v1[2] = 3; v1[3] = 4;

    TVector<int> v2(4, 1);
    v2[1] = 10; v2[2] = 20; v2[3] = 30;

    EXPECT_EQ(12, (v1 + v2)[1]);
    EXPECT_EQ(26, (v2 - v1)[3]);

    //2*10 + 3*20 + 4*30 = 200
    EXPECT_EQ(200, v1 * v2);
}

TEST(TVec, Oper) {
    TVector<int> vDif1(5, 0);
    TVector<int> vDif2(3, 0);
    TVector<int> vIndDif(5, 2);

    ASSERT_THROW(vDif1 + vDif2, std::invalid_argument);
    ASSERT_THROW(vDif1 - vIndDif, std::invalid_argument);
    ASSERT_THROW(vDif1 * vIndDif, std::invalid_argument);
}

TEST(TMat, Ini) {
    ASSERT_NO_THROW(TMatrix<int> mDe);
    TMatrix<int> mDef;
    EXPECT_EQ(10, mDef.GetSize());

    ASSERT_NO_THROW(TMatrix<double> mCus(7));
    TMatrix<double> mCust(7);
    EXPECT_EQ(7, mCust.GetSize());
}

TEST(TMat, Inv) {
    ASSERT_THROW(TMatrix<int>(-5), std::out_of_range);
    ASSERT_THROW(TMatrix<int>(MAX_MATRIX_SIZE + 10), std::out_of_range);
    ASSERT_NO_THROW(TMatrix<int>(0));     //нулевой размер допустим
}

TEST(TMat, Min) {
    //1x1
    TMatrix<int> m1(1);
    EXPECT_EQ(1, m1.GetSize());
    EXPECT_EQ(1, m1[0].GetSize());
    EXPECT_EQ(0, m1[0].GetStartIndex()); //индекс начинается с 0
    ASSERT_NO_THROW(m1[0][0] = 42);
    EXPECT_EQ(42, m1[0][0]);

    //2x2 (проверка сдвига StartIndex)
    TMatrix<int> m2(2);
    EXPECT_EQ(0, m2[0].GetStartIndex()); // 0 строка - данные с 0 столбца
    EXPECT_EQ(1, m2[1].GetStartIndex()); // 1 строка - данные с 1 столбца

    m2[0][0] = 1; m2[0][1] = 2;
    m2[1][1] = 3;

    EXPECT_EQ(1, m2[0][0]);
    EXPECT_EQ(2, m2[0][1]);
    EXPECT_EQ(3, m2[1][1]);
}

TEST(TMat, Ari) {
    TMatrix<int> m1(3);
    m1[0][0] = 1; m1[0][1] = 2; m1[1][1] = 5;

    TMatrix<int> m2(3);
    m2[0][0] = 10; m2[0][1] = 20; m2[1][1] = 50;

    TMatrix<int> mSum = m1 + m2;
    EXPECT_EQ(11, mSum[0][0]);
    EXPECT_EQ(22, mSum[0][1]);

    TMatrix<int> mDiff = m2 - m1;
    EXPECT_EQ(9, mDiff[0][0]);
    EXPECT_EQ(45, mDiff[1][1]);

    TMatrix<int> mT(5);
    mT = m1;
    EXPECT_EQ(3, mT.GetSize());
    EXPECT_EQ(5, mT[1][1]);
}

TEST(TMat, Inc) {
    TMatrix<int> mSm(3);
    TMatrix<int> mLa(5);

    //операции с матрицами разного размера запрещены
    ASSERT_THROW(mSm + mLa, std::invalid_argument);
    ASSERT_THROW(mSm - mLa, std::invalid_argument);

    //попытка записать в нижний треугольник должна вызывать ошибку
    TMatrix<int> mTri(3);

    ASSERT_THROW(mTri[1][0] = 100, std::out_of_range);
    ASSERT_THROW(mTri[2][0] = 100, std::out_of_range);
    ASSERT_THROW(mTri[2][1] = 100, std::out_of_range);
    ASSERT_THROW(int x = mTri[1][0], std::out_of_range);
}

TEST(TMat, Che) {
    TMatrix<int> m1(3);
    m1[0][0] = 5; m1[1][1] = 5;

    TMatrix<int> m2(3);
    m2[0][0] = 5; m2[1][1] = 5;

    TMatrix<int> m3(3);
    m3[0][0] = 5; m3[1][1] = 9;

    EXPECT_TRUE(m1 == m2);
    EXPECT_FALSE(m1 == m3);
    EXPECT_TRUE(m1 != m3);
    EXPECT_TRUE(m1 == m1);
}