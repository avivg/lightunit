#include <stdio.h>
#include "lightunit.h"

static int g_var;
static const char *g_foo = "foo";

LU_SUITE_CREATE(suite);
LU_SUITE_SETUP(suite) {
    g_var = 1;
}

LU_TEST(suite, test1) {
    LU_ASSERT(g_var == 1);
    g_var++;
    LU_ASSERT_STR_EQ("foo", g_foo);
    LU_ASSERT(2 == 3);
}

LU_TEST(suite, test2) {
    LU_ASSERT(++g_var == 2);
    LU_ASSERT_STR_EQ("bar", g_foo);
}

int main() {
    LU_SUITE_RUN(suite);
    LU_SUITE_REPORT(suite);
    printf("Suite status: %d\n", LU_SUITE_STATUS(suite));
    return 0;
}
