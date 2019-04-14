#ifndef LIGHTUNIT_HEADER_FILE_INCLUDED
#define LIGHTUNIT_HEADER_FILE_INCLUDED

typedef struct test_info_s test_info_t;
typedef void (*test_fcn_t)(test_info_t*);

struct test_info_s
{
    test_info_t *next_test;
    test_fcn_t test_fcn;
    int result;
    char *msg;
};

typedef struct
{
    test_info_t *tests;
    int status;
} suite_t;


#define LU_TEST_SUITE(suite_name__)     \
suite_t suite_name__##_obj;   \
suite_t *suite_name__ = &suite_name__##_obj;  \
__attribute__((constructor(101)))   \
void init_##suite_name__()    \
{   \
    suite_name__->tests = NULL; \
    suite_name__->status = 0;   \
}   \
__attribute__((destructor)) \
void destroy_##suite_name__() {   \
    test_info_t *cur = suite_name__->tests, *next = NULL;   \
    while (cur) \
    {   \
        next = cur->next_test;  \
        free(cur);  \
        cur = next; \
    }}


#endif /* LIGHTUNIT_HEADER_FILE_INCLUDED */
