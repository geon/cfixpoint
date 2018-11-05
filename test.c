#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "fix.h"


bool Converting_from_float_should_work () {

	float floatA = 1.0 / 3;
	Fix_16_16 fixA = fix_16_16_fromFloat(floatA);
	int unwrappedA = fix_16_16_unwrap(fixA);

	return unwrappedA == (1 << 16) / 3;
}

bool Converting_from_float_should_work_2 () {

	float floatA = 355.0 / 113;
	Fix_32_16 fixA = fix_32_16_fromFloat(floatA);
	int unwrappedA = fix_32_16_unwrap(fixA);

	return unwrappedA == (355 << 16) / 113;
}

bool Converting_to_float_should_work () {

	Fix_16_16 fixA = fix_16_16_wrap((1 << 16) / 3);
	float floatA = fix_16_16_toFloat(fixA);

	return fabs(floatA - (1.0 / 3)) < 0.001;
}

bool Converting_to_float_should_work_2 () {

	Fix_32_16 fixA = fix_32_16_wrap((355 << 16) / 113);
	float floatA = fix_32_16_toFloat(fixA);

	return fabs(floatA - (355.0 / 113)) < 0.001;
}

bool Addition_should_work () {

	float floatA = 1.23456789;
	float floatB = 9.87654321;
	float floatC = floatA + floatB;

	Fix_32_16 fixA = fix_32_16_fromFloat(floatA);
	Fix_32_16 fixB = fix_32_16_fromFloat(floatB);
	Fix_32_16 fixC = fix_32_16_add_32_16(fixA, fixB);

	return fabs(floatC - fix_32_16_toFloat(fixC)) < 0.001;
}

bool Addition_should_work_2 () {

	float floatA = 33.333 + 33.333 + 33.333;

	Fix_32_16 fixA = fix_32_16_fromFloat(33.333);
	Fix_32_16 fixB = fix_32_16_add_32_16(fixA, fixA);
	fixB = fix_32_16_add_32_16(fixB, fixA);

	return fabs(floatA - fix_32_16_toFloat(fixB)) < 0.001;
}

bool Addition_out_of_range_should_not_work () {

	float floatA = 1.23456789;
	float floatB = 9.87654321;
	float floatC = floatA + floatB;

	Fix_16_16 fixA = fix_16_16_fromFloat(floatA);
	Fix_16_16 fixB = fix_16_16_fromFloat(floatB);
	Fix_16_16 fixC = fix_16_16_add_16_16(fixA, fixB);

	return fabs(floatC - fix_16_16_toFloat(fixC)) > 0.001;
}

bool Multiplication_should_work () {

	float floatA = 1.23456789;
	float floatB = 9.87654321;
	float floatC = floatA * floatB;

	Fix_32_16 fixA = fix_32_16_fromFloat(floatA);
	Fix_32_16 fixB = fix_32_16_fromFloat(floatB);
	Fix_32_16 fixC = fix_32_16_multiply_32_16(fixA, fixB);

	return fabs(floatC - fix_32_16_toFloat(fixC)) < 0.001;
}

bool Multiplication_should_work_2 () {

	Fix_32_16 fixA = fix_32_16_fromFloat(123.456789);
	float floatA = fix_32_16_toFloat(fixA);

	float floatB = floatA * floatA;
	Fix_32_16 fixB = fix_32_16_multiply_32_16(fixA, fixA);

	return fabs(floatB - fix_32_16_toFloat(fixB)) < 0.001;
}


#define runTest(testName) \
if (!testName()) { \
	printf("%s\n", #testName); \
	return 1; \
}

int main(int argc, char *args[]) {

	runTest(Converting_from_float_should_work)
	runTest(Converting_from_float_should_work_2)
	runTest(Converting_to_float_should_work)
	runTest(Converting_to_float_should_work_2)
	runTest(Addition_should_work)
	runTest(Addition_should_work_2)
	runTest(Addition_out_of_range_should_not_work)
	runTest(Multiplication_should_work)
	runTest(Multiplication_should_work_2)

	printf("All tests passed.\n");
	return 0;
}
