#include <stdio.h>
#include "lightunit.h"

LU_SUITE_CREATE(suite1);
LU_SUITE_SETUP(suite1)
{
    printf("Suite test setup\n");
}

LU_SUITE_TEARDOWN(suite1)
{
    printf("Suite test teardown\n");
}

LU_TEST(suite1, test1)
{
    LU_ASSERT(1 == 1);
}

LU_TEST(suite1, test2)
{
    LU_ASSERT_STR_EQ("foo", "foo");
    LU_ASSERT_STR_EQ("foo", "bar");
}

LU_TEST(suite1, test3)
{
    char *foo = "foo";
    char *bar = "bar";
    LU_ASSERT_STR_EQ(foo, foo);
    LU_ASSERT_STR_EQ(foo, bar);
}

LU_SUITE_CREATE(suite2);
LU_TEST(suite2, test1)
{
    LU_ASSERT(NULL);
}
LU_TEST(suite2, test2)
{
    LU_ASSERT(0);
}

LU_SUITE_CREATE(passing);
LU_TEST(passing, pass_test)
{
    LU_ASSERT(1+1==2);
}

int main()
{
    LU_SUITE_RUN(suite1);
    LU_SUITE_REPORT(suite1);

    LU_SUITE_RUN(suite2);
    LU_SUITE_REPORT(suite2);

    return ((LU_SUITE_STATUS(suite1) == (-2)) &&
            (LU_SUITE_STATUS(suite2) == (-1)) &&
            (LU_SUITE_STATUS(passing) == 0))
             ? 0 : 1;
}
