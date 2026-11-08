#include "pch.h"

#include <utmatrix.h>
#include <_utmatrix.h>

//TVector
TEST(TestTVector, Create_TVector) {
	ASSERT_NO_THROW(TVector<int> v(10, 0));
	EXPECT_THROW(TVector<int> v(-10, 0), std::invalid_argument);
	EXPECT_THROW(TVector<int> v(10, -8), std::invalid_argument);
	EXPECT_THROW(TVector<int> v(100000001, 0), std::invalid_argument);
}

TEST(TestTVector, Constructor_Copy) {
	TVector<int> v1(10, 0);
	v1[7] = 5;
	TVector<int> v2(v1);
	EXPECT_EQ(v1.GetSize(), v2.GetSize());
	EXPECT_EQ(v1.GetStartIndex(), v2.GetStartIndex());
	EXPECT_EQ(v1[7], v2[7]);
}

TEST(TestTVector, Operator_access) {
	TVector<int> v(10, 7);
	ASSERT_NO_THROW(v[8]);
	EXPECT_THROW(v[5], std::out_of_range);
	EXPECT_THROW(v[100], std::out_of_range);
}

TEST(TestTVector, Operator_Comparison) {
	TVector<int> v1(10, 7), v2(10, 7), v3(15, 0);
	EXPECT_TRUE(v1 == v2);
	EXPECT_TRUE(v1 != v3);
	v2[10] = 4;
	EXPECT_FALSE(v1 == v2);

	TVector<int> v4(0, 0), v5(0, 0);
	EXPECT_TRUE(v4 == v5);
}

TEST(TestTVector, Operator_Assingment) {
	TVector<int> v1(100, 2), v2(1000, 5);
	v2[500] = 283;
	v1 = v2;
	EXPECT_EQ(283, v1[500]);
	
	//check self assingnment
	TVector<int> v3(100, 0);
	v3[1] = 44;
	v3[99] = 313;
	v3 = v3;
	EXPECT_EQ(44, v3[1]);
	EXPECT_EQ(313, v3[99]);
	EXPECT_EQ(0, v3.GetStartIndex());
	EXPECT_EQ(100, v3.GetSize());
}

TEST(TestTVector, Operation_With_Scalar) {
	int sz = 10;
	int stind = 2;
	TVector<int> v(sz, stind);
	for (int i = stind; i < sz + stind; i++) {
		v[i] = i - 2 + 1;
	}

	TVector<int> res = v + 5;
	EXPECT_EQ(sz, res.GetSize());
	EXPECT_EQ(stind, res.GetStartIndex());
	for (int i = stind; i < sz + stind; i++) {
		EXPECT_EQ(v[i] + 5, res[i]);
	}

	res = res - 2;
	for (int i = stind; i < sz + stind; i++) {
		EXPECT_EQ(v[i] + 5 - 2, res[i]);
	}

	res = res * 3;
	for (int i = stind; i < sz + stind; i++) {
		EXPECT_EQ((v[i] + 5 - 2)*3, res[i]);
	}
}

TEST(TestTVector, Operation_With_Vector) {
	int sz = 4;
	int stind = 2;
	TVector<int> v1(sz, stind); // 1 2 3 4
	TVector<int> v2(sz, stind); // 10 20 30 40

	for (int i = stind; i < stind + sz; i++) {
		v1[i] = i - stind + 1;
		v2[i] = (i - stind + 1) * 10;
	}

	TVector<int> resAdd = v1 + v2;
	EXPECT_EQ(sz, resAdd.GetSize());
	EXPECT_EQ(stind, resAdd.GetStartIndex());
	for (int i = stind; i < stind + sz; i++) {
		EXPECT_EQ(v1[i] + v2[i], resAdd[i]);
	}

	TVector<int> resSub = v2 - v1;
	EXPECT_EQ(sz, resSub.GetSize());
	EXPECT_EQ(stind, resSub.GetStartIndex());
	for (int i = stind; i < stind + sz; i++) {
		EXPECT_EQ(v2[i] - v1[i], resSub[i]);
	}

	// 1*10 + 2*20 + 3*30 + 4*40 = 300
	int res_scalar = v1 * v2;
	EXPECT_EQ(300, res_scalar);

	TVector<int> selfSub = v1 - v1;
	for (int i = stind; i < stind + sz; i++) {
		EXPECT_EQ(0, selfSub[i]);
	}
	EXPECT_EQ(30, v1 * v1); // 1*1 + 2*2 + 3*3 + 4*4 = 30

	TVector<int> vDiffSize(sz + 1, stind);
	EXPECT_ANY_THROW(v1 + vDiffSize);
	EXPECT_ANY_THROW(v1 - vDiffSize);
	EXPECT_ANY_THROW(v1 * vDiffSize);

	TVector<int> vDiffStart(sz, stind + 1);
	EXPECT_ANY_THROW(v1 + vDiffStart);
	EXPECT_ANY_THROW(v1 - vDiffStart);
	EXPECT_ANY_THROW(v1 * vDiffStart);
	
	TVector<int> single1(1, 0), single2(1, 0);
	single1[0] = 7;
	single2[0] = -3;
	EXPECT_EQ(4, (single1 + single2)[0]);
	EXPECT_EQ(10, (single1 - single2)[0]);
	EXPECT_EQ(-21, single1 * single2);

	TVector<int> empty1(0, 0), empty2(0, 0);
	EXPECT_NO_THROW(empty1 + empty2);
	EXPECT_NO_THROW(empty1 - empty2);
	EXPECT_EQ(0, empty1 * empty2);
}

//TMatrix
TEST(TestTMatrix, Create_TMatrix) {
	TMatrix<int> m1;
	EXPECT_EQ(10, m1.GetSize());
	EXPECT_EQ(0, m1.GetStartIndex());

	int sz = 4;
	TMatrix<int> m2(sz);
	EXPECT_EQ(sz, m2.GetSize());
	EXPECT_EQ(0, m2.GetStartIndex());

	for (int i = 0; i < sz; i++) {
		EXPECT_EQ(sz - i, m2[i].GetSize());
		EXPECT_EQ(i, m2[i].GetStartIndex());

		for (int j = i; j < sz; j++) {
			EXPECT_EQ(0, m2[i][j]);
		}
		EXPECT_THROW(m2[i][i - 1], std::out_of_range);
	}

	TMatrix<int> m3(1);
	EXPECT_EQ(1, m3.GetSize());
	EXPECT_EQ(1, m3[0].GetSize());
	EXPECT_EQ(0, m3[0].GetStartIndex());
	EXPECT_EQ(0, m3[0][0]);

	ASSERT_NO_THROW(TMatrix<int> m0(0));
	TMatrix<int> m0(0);
	EXPECT_EQ(0, m0.GetSize());

	EXPECT_THROW(TMatrix<int> m(-1), std::invalid_argument);
	EXPECT_THROW(TMatrix<int> m(-100), std::invalid_argument);
	EXPECT_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1), std::invalid_argument);
}

TEST(TestTMatrix, Constructor_Copy) {
	int sz = 3;
	TMatrix<int> m1(sz);

	for (int i = 0; i < sz; i++) {
		for (int j = i; j < sz; j++) {
			m1[i][j] = i + 3;
		}
	}

	TMatrix<int> m2(m1);
	EXPECT_EQ(m1.GetSize(), m2.GetSize());
	for (int i = 0; i < sz; i++) {
		EXPECT_EQ(m1[i].GetSize(), m2[i].GetSize());
		EXPECT_EQ(m1[i].GetStartIndex(), m2[i].GetStartIndex());
	}

	m1[0][0] = 999;
	m1[1][2] = -500;
	EXPECT_NE(m1[0][0], m2[0][0]);
	EXPECT_EQ(3, m2[0][0]);
	EXPECT_TRUE(m1 != m2);

	TMatrix<int> mSingle(1);
	mSingle[0][0] = 42;
	TMatrix<int> mSingleCopy(mSingle);
	EXPECT_EQ(42, mSingleCopy[0][0]);

	TMatrix<int> mEmpty(0);
	TMatrix<int> mEmptyCopy(mEmpty);
	EXPECT_EQ(0, mEmptyCopy.GetSize());
}

TEST(TestTMatrix, Constructor_TypeConversion) {
	int sz = 3;
	TVector<TVector<int>> v(sz, 0);
	for (int i = 0; i < sz; i++) {
		v[i] = TVector<int>(sz - i, i);
		for (int j = i; j < sz; j++) {
			v[i][j] = (i + 1) * 10 + j;
		}
	}

	TMatrix<int> m(v);
	EXPECT_EQ(sz, m.GetSize());
	for (int i = 0; i < sz; i++) {
		EXPECT_EQ(sz - i, m[i].GetSize());
		EXPECT_EQ(i, m[i].GetStartIndex());
		for (int j = i; j < sz; j++) {
			EXPECT_EQ(v[i][j], m[i][j]);
		}
	}
}

TEST(TestTMatrix, Operator_Comparison) {
	int sz = 3;
	TMatrix<int> m1(sz), m2(sz);

	for (int i = 0; i < sz; i++) {
		for (int j = i; j < sz; j++) {
			m1[i][j] = i + j + 1;
			m2[i][j] = i + j + 1;
		}
	}

	EXPECT_TRUE(m1 == m2);
	EXPECT_FALSE(m1 != m2);

	EXPECT_TRUE(m1 == m1);
	EXPECT_FALSE(m1 != m1);

	TMatrix<int> mDiffSize(sz + 1);
	EXPECT_FALSE(m1 == mDiffSize);
	EXPECT_TRUE(m1 != mDiffSize);

	TMatrix<int> empty1(0), empty2(0);
	EXPECT_TRUE(empty1 == empty2);
	EXPECT_FALSE(empty1 != empty2);

	TMatrix<int> single1(1), single2(1);
	single1[0][0] = 5;
	single2[0][0] = 5;
	EXPECT_TRUE(single1 == single2);
	EXPECT_FALSE(single1 != single2);
}

TEST(TestTMatrix, Operator_Assingment) {
	int sz = 3;
	TMatrix<int> m1(sz);
	for (int i = 0; i < sz; i++) {
		for (int j = i; j < sz; j++) {
			m1[i][j] = i * 10 + j + 1;
		}
	}

	TMatrix<int> m2(sz);
	m2 = m1;
	EXPECT_TRUE(m1 == m2);

	m1[0][0] = 777;
	EXPECT_NE(m1[0][0], m2[0][0]);
	EXPECT_EQ(1, m2[0][0]);
	m1[0][0] = 1;

	TMatrix<int> mDiffSize(sz + 3);
	mDiffSize = m1;
	EXPECT_EQ(sz, mDiffSize.GetSize());
	EXPECT_TRUE(m1 == mDiffSize);
	for (int i = 0; i < sz; i++) {
		EXPECT_EQ(sz - i, mDiffSize[i].GetSize());
		EXPECT_EQ(i, mDiffSize[i].GetStartIndex());
	}

	//check self assingnment
	EXPECT_NO_THROW(m1 = m1);
	EXPECT_EQ(sz, m1.GetSize());
	EXPECT_EQ(1, m1[0][0]);
}

TEST(TestTMatrix, Operator_Addition) {
	int sz = 3;
	TMatrix<int> m1(sz), m2(sz);

	for (int i = 0; i < sz; i++) {
		for (int j = i; j < sz; j++) {
			m1[i][j] = i + j + 1;
			m2[i][j] = (i + j + 1) * 10;
		}
	}

	TMatrix<int> res = m1 + m2;
	EXPECT_EQ(sz, res.GetSize());
	for (int i = 0; i < sz; i++) {
		EXPECT_EQ(sz - i, res[i].GetSize());
		EXPECT_EQ(i, res[i].GetStartIndex());
		for (int j = i; j < sz; j++) {
			EXPECT_EQ(m1[i][j] + m2[i][j], res[i][j]);
		}
	}

	EXPECT_EQ(1, m1[0][0]);
	EXPECT_EQ(10, m2[0][0]);

	TMatrix<int> mDiffSize(sz + 1);
	EXPECT_ANY_THROW(m1 + mDiffSize);

	TMatrix<int> single1(1), single2(1);
	single1[0][0] = 15;
	single2[0][0] = -20;
	TMatrix<int> resSingle = single1 + single2;
	EXPECT_EQ(-5, resSingle[0][0]);

	TMatrix<int> empty1(0), empty2(0);
	EXPECT_NO_THROW(empty1 + empty2);
	EXPECT_EQ(0, (empty1 + empty2).GetSize());
}

TEST(TestTMatrix, Operator_Subtraction) {
	int sz = 3;
	TMatrix<int> m1(sz), m2(sz);

	for (int i = 0; i < sz; i++) {
		for (int j = i; j < sz; j++) {
			m1[i][j] = (i + j + 1) * 10;
			m2[i][j] = i + j + 1;
		}
	}

	TMatrix<int> res = m1 - m2;
	EXPECT_EQ(sz, res.GetSize());
	for (int i = 0; i < sz; i++) {
		EXPECT_EQ(sz - i, res[i].GetSize());
		EXPECT_EQ(i, res[i].GetStartIndex());
		for (int j = i; j < sz; j++) {
			EXPECT_EQ(m1[i][j] - m2[i][j], res[i][j]);
		}
	}

	TMatrix<int> mDiffSize(sz - 1);
	EXPECT_ANY_THROW(m1 - mDiffSize);

	TMatrix<int> single1(1), single2(1);
	single1[0][0] = -5;
	single2[0][0] = -12;
	EXPECT_EQ(7, (single1 - single2)[0][0]);

	TMatrix<int> empty1(0), empty2(0);
	EXPECT_NO_THROW(empty1 - empty2);
	EXPECT_EQ(0, (empty1 - empty2).GetSize());
}