#include <stdio.h>
#include <lightunit.h>

LU_TEST_SUITE(basic_suite);

LU_SUITE_SETUP(basic_suite)
{
    printf("Suite test setup\n");
}

LU_SUITE_TEARDOWN(basic_suite)
{
    printf("Suite test teardown\n");
}

LU_TEST(basic_suite, test_1)
{
    LU_ASSERT(1 == 1);
}

LU_TEST(basic_suite, test_2)
{
    LU_ASSERT(1 == 2);
}

LU_TEST_SUITE(suite2);
LU_TEST(suite2, test_1)
{
    LU_ASSERT(NULL);
}
LU_TEST(suite2, test_2)
{
    LU_ASSERT(0);
}


int main()
{
    LU_SUITE_RUN(basic_suite);
    LU_SUITE_REPORT(basic_suite);

    LU_SUITE_RUN(suite2);
    LU_SUITE_REPORT(suite2);

    return 0;
}