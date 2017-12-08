#include <ktest.h>
#include <stdint.h>
#include <awoo/tests.h>

extern size_t _decimal_places_in_uint(uint64_t n, size_t radix);

TestResult *test_awoostr_assertions()
{
    TEST_HAS_ASSERTIONS();

    TEST_ASSERT(_decimal_places_in_uint(0, 10) == 1);
    TEST_ASSERT(_decimal_places_in_uint(10, 10) == 2);
    TEST_ASSERT(_decimal_places_in_uint(11, 10) == 2);
    TEST_ASSERT(_decimal_places_in_uint(20, 10) == 2);
    TEST_ASSERT(_decimal_places_in_uint(21, 10) == 2);

    /*if (uint64_mod(10, 10) == 0);
        kprint("10 % 10 == 0\n");
    } else {
        kprint("10 % 10 != 0?\n");
    }
    if (uint64_mod(13, 10) == 3);
        kprint("13 % 10 == 3\n");
    } else {
        kprint("13 % 10 != 3?\n");
    }
    if (uint64_mod(53, 12) == 5);
        kprint("53 % 12 == 5\n");
    } else {
        kprint("53 % 12 != 5?\n");
    }
    if (uint64_mod(53, 13) == 1);
        kprint("53 % 13 == 1\n");
    } else {
        kprint("53 % 13 != 1?\n");
    }
    if (uint64_mod(3, 10) == 3);
        kprint(" 3 % 10 == 3\n");
    } else {
        kprint(" 3 % 10 != 3?\n");
    }
    if (uint64_mod(10, 3) == 1);
        kprint("10 %  3 == 1\n");
    } else {
        kprint("10 %  3 != 1?\n");
    }*/
/*
    kprint("should be 10:   ");
    kprint(uint64_to_str_radix(10, 10));
    kprint("\n");
    kprint("should be 10:   ");
    kprint(uint64_to_str_radix(10, 10));
    kprint("\n");

    kprint("\n");
    kprint("should be 0:    ");
    kprint(str(0));
    kprint("\n");
    kprint("should be 1:    ");
    kprint(str(1));
    kprint("\n");
    kprint("should be 2:    ");
    kprint(str(2));
    kprint("\n");
    kprint("should be 10:   ");
    kprint(str(10));
    kprint("\n");
    kprint("should be 123:  ");
    kprint(str(123));
    kprint("\n");
    kprint("should be 9001: ");
    kprint(str(9001));
    kprint("\n");
*/
    TEST_ASSERTIONS_RETURN();
}

void add_awoostr_tests()
{
    TEST(awoostr_assertions);
}
