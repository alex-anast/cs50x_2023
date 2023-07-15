#include <stdio.h>
#include <assert.h>
#include "../ext/population.h"

void test_calculate_years(void)
{
    // Test Case 1
    assert(calculate_years(1200, 1300) == 1);

    // Test Case 2
    assert(calculate_years(-5, 3) == 8);
    assert(calculate_years(9, 5) == 8);
    assert(calculate_years(9, 18) == 8);

    // Test Case 3
    assert(calculate_years(20, 1) == 0);
    assert(calculate_years(20, 10) == 1);
    assert(calculate_years(20, 100) == 4);

    // Test Case 4
    assert(calculate_years(100, 1000000) == 115);

    printf("All test cases passed.\n");
}

int main(void)
{
    test_calculate_years();

    return 0;
}
