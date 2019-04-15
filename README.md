# lightunit
> Lightweight unit testing harness for C projects.

Inspired by [siu/minunit](https://github.com/siu/minunit) and [MinUnit](http://www.jera.com/techinfo/jtns/jtn002.html).

This unit testing harness uses GCC's [`__attribute__((constructor))`](https://gcc.gnu.org/onlinedocs/gcc-4.7.0/gcc/Function-Attributes.html)
magic to automagically register each test to its test suite without the need to do so explicitely.

On the other hand, it is a light and easily extensible framework, consisting of a single `.h` file.

## Usage:

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

    int main()
    {
        LU_SUITE_RUN(basic_suite);
        LU_SUITE_REPORT(basic_suite);
        printf("Suite Status: %d\n", LU_SUITE_STATUS(basic_suite));
        return 0;
    }
    
Prints:

    Suite test setup
    Suite test teardown
    Suite test setup
    Suite test teardown
    SUITE: basic_suite
     > test_2                        : -1 ('1 == 2' asserted to False)
     > test_1                        :  0 (OK)
    Suite Status: -1

## TODO
* Improve suite results reporting
* Add verbosity options
* Add more assertion types
** `ASSERT_STR_EQ`
** `ASSERT_FLT_EQ` / `ASSERT_DBL_EQ` for float/double approx.
** `FAIL(message)`
* Setup CI
* Tests timing
* Other compilers support
