#include "StringPoolUnitTest.h"
#include "../Utility/StringPool.h"
#include "../Utility/PooledString.h"
#include "../Utility/HashedString.h"
#include <assert.h>
#define TEST_POOL_SIZE 128

bool StringPool_UnitTest() {
	StringPool* test_pool = StringPool::get_instance(TEST_POOL_SIZE);
	assert(test_pool);
	return true;
}