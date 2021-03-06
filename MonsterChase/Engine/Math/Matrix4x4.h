#pragma once
#include <cmath>
#include "Vector4D.h"
#include <xmmintrin.h>
#define SHUFFLE_PARAM(x, y, z, w) \
((x) | ((y) << 2) | ((z) << 4) | ((w) << 6))

#define _mm_replicate_x_ps(v) _mm_shuffle_ps((v), (v), SHUFFLE_PARAM(0, 0, 0, 0))
#define _mm_replicate_y_ps(v) _mm_shuffle_ps((v), (v), SHUFFLE_PARAM(1, 1, 1, 1))
#define _mm_replicate_z_ps(v) _mm_shuffle_ps((v), (v), SHUFFLE_PARAM(2, 2, 2, 2))
#define _mm_replicate_w_ps(v) _mm_shuffle_ps((v), (v), SHUFFLE_PARAM(3, 3, 3, 3))

class Matrix4x4
{
public:
	Matrix4x4() = default;
	Matrix4x4(float i_00, float i_01, float i_02, float i_03,
		float i_10, float i_11, float i_12, float i_13,
		float i_20, float i_21, float i_22, float i_23,
		float i_30, float i_31, float i_32, float i_33)
		: m_00(i_00), m_01(i_01), m_02(i_02), m_03(i_03),
		m_10(i_10), m_11(i_11), m_12(i_12), m_13(i_13),
		m_20(i_20), m_21(i_21), m_22(i_22), m_23(i_23),
		m_30(i_30), m_31(i_31), m_32(i_32), m_33(i_33) {
		
		row0 = _mm_set_ps(i_00, i_01, i_02, i_03);
		row1 = _mm_set_ps(i_10, i_11, i_12, i_13);
		row2 = _mm_set_ps(i_20, i_21, i_22, i_23);
		row3 = _mm_set_ps(i_30, i_31, i_32, i_33);

	}
	
	__m128 row0;
	__m128 row1;
	__m128 row2;
	__m128 row3;

	// returns a new matrix whose rows are the columns of the original
	inline Matrix4x4 & get_transpose() const {
		Matrix4x4 matrix;
		matrix.set_each_elem(
			m_00, m_10, m_20, m_30,
			m_01, m_11, m_21, m_31,
			m_02, m_12, m_22, m_32,
			m_03, m_13, m_23, m_33);

		return matrix;
	}

	Vector4D operator[] (const size_t i_row) const {
		switch (i_row) {
		case 0:
			return Vector4D(m_00, m_01, m_02, m_03);
		case 1:
			return Vector4D(m_10, m_11, m_12, m_13);
		case 2:
			return Vector4D(m_20, m_21, m_22, m_23);
		case 3:
			return Vector4D(m_30, m_31, m_32, m_33);
		default:
			return Vector4D(0.0f, 0.0f, 0.0f, 0.0f);
		}

	}

	inline void set_row(int i_row, float i_1, float i_2, float i_3, float i_4) {
		//matrix_vec[i_row - 1] = Vector4D(i_1, i_2, i_3, i_4);
		switch (i_row)
		{
		case 0: 
			row0 = _mm_set_ps(i_1, i_2, i_3, i_4);
			m_00 = i_1;
			m_01 = i_2;
			m_02 = i_3;
			m_03 = i_4;
			break;
		case 1:
			row1 = _mm_set_ps(i_1, i_2, i_3, i_4);
			m_10 = i_1;
			m_11 = i_2;
			m_12 = i_3;
			m_13 = i_4;
			break;
		case 2:
			row2 = _mm_set_ps(i_1, i_2, i_3, i_4);
			m_20 = i_1;
			m_21 = i_2;
			m_22 = i_3;
			m_23 = i_4;
			break;
		case 3:
			row3 = _mm_set_ps(i_1, i_2, i_3, i_4);
			m_30 = i_1;
			m_31 = i_2;
			m_32 = i_3;
			m_33 = i_4;
			break;
		default:
			break;
		}
	}


	// set values for each element in the matrix
	inline void set_each_elem(float i_00, float i_01, float i_02, float i_03,
		float i_10,	float i_11, float i_12, float i_13,
		float i_20, float i_21, float i_22, float i_23,
		float i_30, float i_31, float i_32, float i_33) {
		m_00 = i_00;
		m_01 = i_01;
		m_02 = i_02;
		m_03 = i_03;
		m_10 = i_10;
		m_11 = i_11;
		m_12 = i_12;
		m_13 = i_13;
		m_20 = i_20;
		m_21 = i_21;
		m_22 = i_22;
		m_23 = i_23;
		m_30 = i_30;
		m_31 = i_31;
		m_32 = i_32;
		m_33 = i_33;

		row0 = _mm_set_ps(i_00, i_01, i_02, i_03);
		row1 = _mm_set_ps(i_10, i_11, i_12, i_13);
		row2 = _mm_set_ps(i_20, i_21, i_22, i_23);
		row3 = _mm_set_ps(i_30, i_31, i_32, i_33);
	}

	void scale(Vector4D & i_target_vec, Vector4D & i_scale_vec);
	void scale(Vector3D i_scale_vec); 
	void rotate(Vector4D & i_target_vec, Vector4D & i_rot_vec);
	void translate(Vector4D & i_target_vec, Vector4D & i_trans_vec);

	// return the determinant of a matrix4x4
	inline float get_det() {
		float result =
			m_00 * (m_11*m_22*m_33 + m_21*m_32*m_13 + m_31*m_12*m_23
				- m_31*m_22*m_13 - m_21*m_12*m_33 - m_11*m_32*m_23)
			+ m_01 * (m_30*m_22*m_13 + m_20*m_12*m_33 + m_10*m_32*m_23
				- m_10*m_22*m_33 - m_20*m_32*m_13 - m_30*m_12*m_23)
			+ m_02 * (m_10*m_22*m_33 + m_20*m_32*m_13 + m_30*m_11*m_23
				- m_30*m_22*m_13 - m_20*m_11*m_33 - m_10*m_32*m_23)
			+ m_03 * (m_30*m_21*m_12 + m_20*m_11*m_32 + m_10*m_31*m_22
				- m_10*m_21*m_32 - m_20*m_31*m_12 - m_30*m_11*m_22);
		return result;
	}
	
	// get inversed matrix, if it exists
	Matrix4x4 & get_inverse();

	// rotate around different axis
	void rotate_x(Vector4D & i_target_vec, float angle);

	void rotate_y(Vector4D & i_target_vec, float angle);

	void rotate_z(Vector4D & i_target_vec, float angle);

	~Matrix4x4() {
	}

private:
	float m_00, m_01, m_02, m_03,
		m_10, m_11, m_12, m_13,
		m_20, m_21, m_22, m_23,
		m_30, m_31, m_32, m_33;
};

inline bool operator== (Matrix4x4 & i_lmat, Matrix4x4 & i_rmat) {
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (i_lmat[i][j] != i_rmat[i][j]) {
				return false;
			}
		}
	}
	return true;
}

// performs Matrix4x4 and Vector4D multiplication
inline Vector4D operator * (const Matrix4x4& i_mat, Vector4D i_vec) {
	Vector4D o_vec;
	const __m128 vec_sse = _mm_set_ps(i_vec.v(), i_vec.u(), i_vec.y(), i_vec.x());
	const __m128 vec_sse_x = _mm_replicate_x_ps(vec_sse);
	const __m128 vec_sse_y = _mm_replicate_y_ps(vec_sse);
	const __m128 vec_sse_z = _mm_replicate_z_ps(vec_sse);
	const __m128 vec_sse_w = _mm_replicate_w_ps(vec_sse);

	const __m128 col_0 = _mm_set_ps(i_mat[3][0], i_mat[2][0], i_mat[1][0], i_mat[0][0]);
	const __m128 col_1 = _mm_set_ps(i_mat[3][1], i_mat[2][1], i_mat[1][1], i_mat[0][1]);
	const __m128 col_2 = _mm_set_ps(i_mat[3][2], i_mat[2][2], i_mat[1][2], i_mat[0][2]);
	const __m128 col_3 = _mm_set_ps(i_mat[3][3], i_mat[2][3], i_mat[1][3], i_mat[0][3]);

	const __m128 x_col = _mm_mul_ps(vec_sse_x, col_0);
	const __m128 y_col = _mm_mul_ps(vec_sse_y, col_1);
	const __m128 z_col = _mm_mul_ps(vec_sse_z, col_2);
	const __m128 w_col = _mm_mul_ps(vec_sse_w, col_3);
	
	__m128 result = _mm_add_ps(x_col, y_col);
	result = _mm_add_ps(result, z_col);
	result = _mm_add_ps(result, w_col);

	__declspec(align(16)) float f_arr[4];
	_mm_store_ps(f_arr, result);

	o_vec.set_all_coords(f_arr[0], f_arr[1], f_arr[2], f_arr[3]);

	/*for (size_t i = 0; i <= 3; i++) {
		float temp = 0.0f;
		size_t j = 0;
		for (; j <= 3; j++) {
			temp += i_mat[i][j] * i_vec[j];
		}
		o_vec[i] = temp;
	}*/
	return o_vec;
}
