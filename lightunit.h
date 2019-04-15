#ifndef LIGHTUNIT_HEADER_FILE_INCLUDED
#define LIGHTUNIT_HEADER_FILE_INCLUDED

#include <stdlib.h>
#include <stdio.h>

/*****************************************************
 *             ASSERTIONS                            *
 *****************************************************/

/*
 * Check if condition is true. Stops the test with
 * negative result if it is not.
 */
#define LU_ASSERT(expr)     \
            _LU_ASSERT(expr)


/*****************************************************
 *             TEST SUITE INTERFACE                  *
 *****************************************************/

/**
 * Create a test suite
 */
#define LU_TEST_SUITE(suite_name)   \
            _LU_TEST_SUITE(suite_name)

/**
 * Create a setup procedure to be called before each test.
 * The procedure code block must follow the macro, i.e
 * LU_SUITE_SETUP(some_suite)
 * {
 *    test setup code...
 * }
 */
#define LU_SUITE_SETUP(suite_name)  \
            _LU_SUITE_SETUP(suite_name)

/**
 * Create a teardown (cleanup) procedure to be called after
 * each test. The procedure code block must follow the macro,
 * i.e
 * LU_SUITE_TEARDOWN(some_suite)
 * {
 *    test cleanup code...
 * }
 */
#define LU_SUITE_TEARDOWN(suite_name)   \
            _LU_SUITE_TEARDOWN(suite_name)

/**
 * Add a test to the suite. The test body must follow the
 * macro. i.e:
 * LU_TEST(some_suite, some_test)
 * {
 *     test code...
 * }
 */
#define LU_TEST(suite_name, test_name)  \
            _LU_TEST(suite_name, test_name)

/**
 * Execute all the test in the testing suite.
 */
#define LU_SUITE_RUN(suite_name)     \
            _LU_SUITE_RUN(suite_name)

/**
 * Print a report of the suite tests and their result.
 */
#define LU_SUITE_REPORT(suite_name)  \
            _LU_SUITE_REPORT(suite_name)

/**
 * Return the status of the suite
 * (result_1 | result_2 | ...)
 */
#define LU_SUITE_STATUS(suite_name)     \
            _LU_SUITE_STATUS(suite_name)


/*******************************************************
 *                  IMPLEMENTATION                     *
 *******************************************************/

#define _LU_TEST_SUITE(snm__)                           \
suite_t snm__##_obj = {0};                              \
suite_t *snm__ = &snm__##_obj;                          \
__attribute__((constructor))                            \
void init_##snm__()                                     \
{                                                       \
    snm__->name = #snm__ ;                              \
}                                                       \
__attribute__((destructor))                             \
void destroy_##snm__() {                                \
    lut_test_info_t *cur = snm__->tests, *next = NULL;  \
    while (cur)                                         \
    {                                                   \
        next = cur->next_test;                          \
        free(cur);                                      \
        cur = next;                                     \
    }                                                   \
}                                                       \
void snm__##_dummy_fcn(void)


#define _LU_SUITE_SETUP(snm__)          \
static void snm__##_setup__();          \
__attribute__((constructor))            \
void snm__##_setup_registration__()     \
{                                       \
    snm__->setup = snm__##_setup__;     \
}                                       \
static void snm__##_setup__()


#define _LU_SUITE_TEARDOWN(snm__)           \
static void snm__##_teardown__();           \
__attribute__((constructor))                \
void snm__##_teardown_registration__()      \
{                                           \
    snm__->teardown = snm__##_teardown__;   \
}                                           \
static void snm__##_teardown__()


#define TEST_FCN(snm__, tnm__)     snm__##__##tnm__
#define TEST_INF(snm__, tnm__)     snm__##__##tnm__##__info
#define TEST_REG(snm__, tnm__)     snm__##__##tnm__##__register

#define _LU_TEST(snm__, tnm__)                                      \
lut_test_info_t * TEST_INF(snm__, tnm__);                           \
extern void TEST_FCN(snm__, tnm__)(lut_test_info_t *);              \
__attribute__((constructor))                                        \
void TEST_REG(snm__, tnm__)()                                       \
{                                                                   \
    TEST_INF(snm__, tnm__) = calloc(1, sizeof(lut_test_info_t));    \
    TEST_INF(snm__, tnm__)->next_test = snm__->tests;               \
    snm__->tests = TEST_INF(snm__, tnm__);                          \
    TEST_INF(snm__, tnm__)->test_fcn = TEST_FCN(snm__, tnm__);      \
    TEST_INF(snm__, tnm__)->test_name = #tnm__;                     \
    TEST_INF(snm__, tnm__)->msg = "OK";                             \
}                                                                   \
void TEST_FCN(snm__, tnm__)(lut_test_info_t *lut_tst_info__)

#define _LU_SUITE_RUN(snm__)  _lightunit_execute_suite(snm__)

#define _LU_SUITE_REPORT(snm__) _lightunit_report_suite(snm__)

#define _LU_SUITE_STATUS(snm__) ((snm__)->status)

#define _LU_ASSERT(expr__)                                          \
do{                                                                 \
    if(!(expr__))                                                   \
    {                                                               \
        lut_tst_info__->result = -1;                                \
        lut_tst_info__->msg = "'" #expr__ "' asserted to False";    \
        return;                                                     \
    }                                                               \
} while(0)


typedef struct lut_test_info_s lut_test_info_t;
typedef void (*lut_test_fcn_t)(lut_test_info_t*);

struct lut_test_info_s
{
    lut_test_info_t *next_test;
    lut_test_fcn_t test_fcn;
    int result;
    const char *msg;
    const char *test_name;
};

typedef struct
{
    lut_test_info_t *tests;
    void (*setup)();
    void (*teardown)();
    int status;
    char *name;
} suite_t;


static void _lightunit_execute_suite(suite_t *suite)
{
    lut_test_info_t *test_info = suite->tests;
    while (test_info)
    {
        if (suite->setup) suite->setup();
        test_info->test_fcn(test_info);
        if (suite->teardown) suite->teardown();
        suite->status |= test_info->result;
        test_info = test_info->next_test;
    }
}

static void _lightunit_report_suite(suite_t *suite)
{
    lut_test_info_t *test_info = suite->tests;
    int tests = 0, fails = 0;
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("SUITE: %s\n", suite->name);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    while (test_info)
    {
        tests++;
        printf("> %-30s: % 2d (%s)\n", test_info->test_name,
               test_info->result, test_info->msg);
        fails += ((test_info->result != 0) ? 1 : 0);
        test_info = test_info->next_test;
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("STATUS: %s (%d fails / %d tests)\n",
            LU_SUITE_STATUS(suite) ? "FAIL" : "PASS",
            fails, tests);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}


#endif /* LIGHTUNIT_HEADER_FILE_INCLUDED */
