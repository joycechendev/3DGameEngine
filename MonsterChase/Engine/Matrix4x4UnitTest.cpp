#include "Matrix4x4UnitTest.h"
#include "Matrix4x4.h"

#include <assert.h>
#include <algorithm>
#include <vector>
#include "time.h"
bool Matrix4x4_UnitTest() {
	Matrix4x4 test_matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	
	// test constructor and [][] operator
	assert(test_matrix[0][0] == 1.0f);
	assert(test_matrix[1][2] == 7.0f);
	assert(test_matrix[2][1] == 10.0f);
	assert(test_matrix[3][3] == 16.0f);

	// test set row
	// set the first row to all 0.0
	test_matrix.set_row(1, 0.0f, 0.0f, 0.0f, 0.0f);
	assert(test_matrix[0][0] == 0.0f);
	assert(test_matrix[0][1] == 0.0f);
	assert(test_matrix[0][2] == 0.0f);
	assert(test_matrix[0][3] == 0.0f);

	Matrix4x4 test_matrix_trans = test_matrix.get_transpose();
	/*
	0 5 9 13
	0 6 10 14
	0 7 11 15
	0 8 12 16
	*/
	assert(test_matrix_trans[0][1] == 5.0f);
	assert(test_matrix_trans[1][1] == 6.0f);
	assert(test_matrix_trans[2][2] == 11.0f);
	assert(test_matrix_trans[3][2] == 12.0f);

	// test == operator
	Matrix4x4 test_trans_target(0.0f, 5.0f, 9.0f, 13.0f, 0.0f, 6.0f, 10.0f, 14.0f, 0.0f, 7.0f, 11.0f, 15.0f, 0.0f, 8.0f, 12.0f, 16.0f);
	assert(test_matrix_trans == test_trans_target);

	// test matrix vector multiplication
	Matrix4x4 test_matrix_id(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	Vector4D test_vec(1.0f, 2.0f, 3.0f, 1.0f);
	Vector4D test_vec_target(1.0f, 2.0f, 3.0f, 1.0f);
	Vector4D test_matrix_multi = test_matrix_id * test_vec;
	assert(test_matrix_multi == test_vec_target);

	return true;
}