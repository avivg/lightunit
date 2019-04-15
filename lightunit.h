#ifndef LIGHTUNIT_HEADER_FILE_INCLUDED
#define LIGHTUNIT_HEADER_FILE_INCLUDED

typedef struct test_info_s test_info_t;
typedef void (*test_fcn_t)(test_info_t*);

struct test_info_s
{
    test_info_t *next_test;
    test_fcn_t test_fcn;
    int result;
    const char *msg;
    const char *test_name;
};

typedef struct
{
    test_info_t *tests;
    void (*setup)();
    void (*teardown)();
    int status;
    char *name;
} suite_t;


#define LU_TEST_SUITE(suite_name__)                         \
suite_t suite_name__##_obj = {0};                           \
suite_t *suite_name__ = &suite_name__##_obj;                \
__attribute__((constructor))                                \
void init_##suite_name__()                                  \
{                                                           \
    suite_name__->name = #suite_name__ ;                    \
}                                                           \
__attribute__((destructor))                                 \
void destroy_##suite_name__() {                             \
    test_info_t *cur = suite_name__->tests, *next = NULL;   \
    while (cur)                                             \
    {                                                       \
        next = cur->next_test;                              \
        free(cur);                                          \
        cur = next;                                         \
    }                                                       \
}                                                           \
void suite_name__##_dummy_fcn(void)


#define LU_SUITE_SETUP(suite_name__)                        \
static void suite_name__##_setup__();                       \
__attribute__((constructor))                                \
void suite_name__##_setup_registration__()                  \
{                                                           \
    suite_name__->setup = suite_name__##_setup__;           \
}                                                           \
static void suite_name__##_setup__()


#define LU_SUITE_TEARDOWN(suite_name__)                     \
static void suite_name__##_teardown__();                    \
__attribute__((constructor))                                \
void suite_name__##_teardown_registration__()               \
{                                                           \
    suite_name__->teardown = suite_name__##_teardown__;     \
}                                                           \
static void suite_name__##_teardown__()


#define TEST_FCN(snm__, tnm__)     snm__##__##tnm__
#define TEST_INF(snm__, tnm__)     snm__##__##tnm__##__info
#define TEST_REG(snm__, tnm__)     snm__##__##tnm__##__register

#define LU_TEST(suite_name__, test_name__)                                                  \
test_info_t * TEST_INF(suite_name__, test_name__);                                          \
extern void TEST_FCN(suite_name__, test_name__)(test_info_t *);                             \
__attribute__((constructor))                                                                \
void TEST_REG(suite_name__, test_name__)()                                                  \
{                                                                                           \
    TEST_INF(suite_name__, test_name__) = calloc(1, sizeof(test_info_t));                   \
    TEST_INF(suite_name__, test_name__)->next_test = suite_name__->tests;                   \
    suite_name__->tests = TEST_INF(suite_name__, test_name__);                              \
                                                                                            \
    TEST_INF(suite_name__, test_name__)->test_fcn = TEST_FCN(suite_name__, test_name__);    \
    TEST_INF(suite_name__, test_name__)->test_name = #test_name__;                          \
    TEST_INF(suite_name__, test_name__)->msg = "OK";                                        \
}                                                                                           \
void TEST_FCN(suite_name__, test_name__)(test_info_t *test_info)


#define LU_ASSERT(expr__)                                       \
do{                                                             \
    if(!(expr__))                                               \
    {                                                           \
        test_info->result = -1;                                 \
        test_info->msg = "'" #expr__ "' asserted to False";     \
        return;                                                 \
    }                                                           \
} while(0)

#endif /* LIGHTUNIT_HEADER_FILE_INCLUDED */
