#include <stdlib.h>
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

static void lightunit_execute_suite(suite_t *suite)
{
    test_info_t *test_info = suite->tests;
    while (test_info)
    {
        if (suite->setup) suite->setup();
        test_info->test_fcn(test_info);
        if (suite->teardown) suite->teardown();
        suite->status |= test_info->result;
        test_info = test_info->next_test;
    }
}

static void lightunit_report_suite(suite_t *suite)
{
    test_info_t *test_info = suite->tests;
    printf("SUITE: %s\n", suite->name);
    while (test_info)
    {
        printf(" > %-30s: % 2d (%s)\n", test_info->test_name, test_info->result, test_info->msg);
        test_info = test_info->next_test;
    }
}

static int lightunit_status_suite(suite_t *suite)
{
    return suite->status;
}

int main()
{
    lightunit_execute_suite(basic_suite);
    lightunit_report_suite(basic_suite);
    printf("Suite Status: %d\n", lightunit_status_suite(basic_suite));

    lightunit_execute_suite(suite2);
    lightunit_report_suite(suite2);
    printf("Suite Status: %d\n", lightunit_status_suite(suite2));

    printf("main done\n");
    return 0;
}