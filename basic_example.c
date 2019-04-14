#include <stdlib.h>
#include <stdio.h>

#include <lightunit.h>

// suite_t basic_suite_obj;
// suite_t *basic_suite = &basic_suite_obj;
// __attribute__((constructor(101)))
// void init_basic_suite()
// {
//     basic_suite->tests = NULL;
//     basic_suite->status = 0;
// }
// __attribute__((destructor))
// void destroy_basic_suite()
// {
//     test_info_t *cur = basic_suite->tests, *next = NULL;
//     while (cur)
//     {
//         next = cur->next_test;
//         free(cur);
//         cur = next;
//     }
// }
LU_TEST_SUITE(basic_suite)
/***************************************************/

/***************************************************/
test_info_t *test1_info;
void test1(test_info_t *test_info)
{
    test_info->result = 5;
    test_info->msg = "test1 message";
}
__attribute__((constructor))
void register_test1()
{
    test1_info = calloc(1, sizeof(test_info_t));
    test1_info->next_test = basic_suite->tests;
    basic_suite->tests = test1_info;
    test1_info->test_fcn = test1;
}
/***************************************************/

/***************************************************/
test_info_t *test2_info;
void test2(test_info_t *test_info)
{
    test_info->result = 3;
    test_info->msg = "test2 message";
}
__attribute__((constructor))
void register_test2()
{
    test2_info = calloc(1, sizeof(test_info_t));
    test2_info->next_test = basic_suite->tests;
    basic_suite->tests = test2_info;
    test2_info->test_fcn = test2;
}
/***************************************************/

static void lightunit_execute_suite(suite_t *suite)
{
    test_info_t *test_info = suite->tests;
    while (test_info)
    {
        test_info->test_fcn(test_info);
        suite->status |= test_info->result;
        test_info = test_info->next_test;
    }
}

static void lightunit_report_suite(suite_t *suite)
{
    test_info_t *test_info = suite->tests;
    while (test_info)
    {
        printf("STATUS: %2d, MSG: %s\n", test_info->result, test_info->msg);
        test_info = test_info->next_test;
    }
}

static int lightunit_status_suite(suite_t *suite)
{
    return suite->status;
}

int main()
{
    // LU_SUITE_RUN(basic_suite);
    // LU_SUITE_REPORT(basic_suite);
    // return LU_SUITE_STATUS(basic_suite);
    lightunit_execute_suite(basic_suite);
    lightunit_report_suite(basic_suite);
    printf("Suite Status: %d\n", lightunit_status_suite(basic_suite));
    printf("main done\n");
    return 0;
}