#include <stdio.h>
#include <lightunit.h>
#include <clist.h>

/***************************************************/
typedef void (*test_fcn_t)(int *, char **);

typedef struct
{
    test_fcn_t test;
    int result;
    char *msg;
} test_info_t;

typedef struct
{
    clist_t tests;
    int status;
} suite_t;
/***************************************************/

/***************************************************/
suite_t basic_suite_obj;
suite_t *basic_suite = &basic_suite_obj;
__attribute__((constructor(101)))
void init_basic_suite()
{
    printf("Creating suite!\n");
    basic_suite->tests = clist_create(sizeof(test_info_t));
    basic_suite->status = 0;
}
__attribute__((destructor))
void destroy_basic_suite()
{
    printf("Releasing suite!\n");
    clist_free(basic_suite->tests);
}
/***************************************************/

/***************************************************/
test_info_t *test1_info;
void test1(int *result, char **msg)
{
    printf("In test 1\n");
    *result = 5;
    *msg = "test1 message";
}
__attribute__((constructor))
void register_test1()
{
    printf("Registering test\n");
    test1_info = clist_add_last(basic_suite->tests);
    test1_info->test = test1;
}
/***************************************************/

/***************************************************/
test_info_t *test2_info;
void test2(int *result, char **msg)
{
    printf("In test 2\n");
    *result = 5;
    *msg = "test2 message";
}
__attribute__((constructor))
void register_test2()
{
    printf("Registering test\n");
    test2_info = clist_add_last(basic_suite->tests);
    test2_info->test = test2;
}
/***************************************************/

static void lightunit_execute_suite(suite_t *suite)
{
    test_info_t *test;
    clist_iterate(suite->tests, test)
    {
        test->test(&test->result, &test->msg);
        suite->status |= test->result;
    }
}

static void lightunit_report_suite(suite_t *suite)
{
    test_info_t *test;
    clist_iterate(suite->tests, test)
    {
        printf("STATUS: %2d, MSG: %s\n", test->result, test->msg);
    }
}

static int lightunit_status_suite(suite_t *suite)
{
    return suite->status;
}

int main()
{
    printf("main start\n");
    // LU_SUITE_RUN(basic_suite);
    // LU_SUITE_REPORT(basic_suite);
    // return LU_SUITE_STATUS(basic_suite);
    lightunit_execute_suite(basic_suite);
    lightunit_report_suite(basic_suite);
    printf("Suite Status: %d\n", lightunit_status_suite(basic_suite));
    printf("main done\n");
    return 0;
}