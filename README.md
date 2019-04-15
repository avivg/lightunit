# LightUnit [![Build Status](https://travis-ci.org/avivg/lightunit.svg?branch=master)](https://travis-ci.org/avivg/lightunit)
> Lightweight unit testing harness for C projects.

Inspired by [siu/minunit](https://github.com/siu/minunit) and [MinUnit](http://www.jera.com/techinfo/jtns/jtn002.html).

This unit testing harness uses GCC's [`__attribute__((constructor))`](https://gcc.gnu.org/onlinedocs/gcc-4.7.0/gcc/Function-Attributes.html)
magic to automagically register each test to its test suite without the need to do so explicitely.

### Strengths
- Lightweight and easy to install (just a `.h` file)
- Simple tests management interface
  - define suites and define the tests.
  - No need to add the tests to the suites explicitly.
- Easily extensible (PRs wellcome).

### Weaknesses
- Requires support for `__attribute__((constructor))` from the compiler.

## Usage:

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
        return LU_SUITE_STATUS(suite);
    }
    
Prints:

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    SUITE: suite
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    > test2                         : -2 (readme_example.c+20: Strings different: "bar" <> g_foo)
    > test1                         : -1 (readme_example.c+15: '2 == 3' asserted to False)
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    STATUS: FAIL (2 tests, 2 fails, 5 assertions)
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## TODO
* Add verbosity options to report
* Add more assertion types
  * `ASSERT_FLT_EQ` / `ASSERT_DBL_EQ` for float/double approx.
  * `FAIL(message)`
* Time tests
* Other compilers support
