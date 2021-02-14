#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_Utf8Size_Z_1(__attribute__((unused)) void **state) {
    size_t        size = 0xDEADBEEFu;
    const uint8_t u8Char[] = {0x7A, 0x00}; /* z */

    size = UC_Utf8Size(u8Char);

    assert_int_equal(size, 1u);
}

void UC_Utf8Size_CyrillicYu_2(__attribute__((unused)) void **state) {
    size_t        size = 0xDEADBEEFu;
    const uint8_t u8Char[] = {0xD1, 0x8E, 0x00}; /* ю */

    size = UC_Utf8Size(u8Char);

    assert_int_equal(size, 2u);
}

void UC_Utf8Size_ChinesseTiger_3(__attribute__((unused)) void **state) {
    size_t        size = 0xDEADBEEFu;
    const uint8_t u8Char[] = {0xE8, 0x99, 0x8E, 0x00}; /* 虎 */

    size = UC_Utf8Size(u8Char);

    assert_int_equal(size, 3u);
}

void UC_Utf8Size_TwoCyrillicYu_2(__attribute__((unused)) void **state) {
    size_t        size = 0xDEADBEEFu;
    const uint8_t u8Char[] = {0xD1, 0x8E, 0xD1, 0x8E, 0x00}; /* юю */

    size = UC_Utf8Size(u8Char);

    assert_int_equal(size, 2u);
}

void UC_Utf8Size_TooLongBytesSequence_0(__attribute__((unused)) void **state) {
    size_t        size = 0xDEADBEEFu;
    const uint8_t u8Char[] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00};

    size = UC_Utf8Size(u8Char);

    assert_int_equal(size, 0u);
}

void UC_Utf8Size_Null_0(__attribute__((unused)) void **state) {
    size_t size = 0xDEADBEEFu;

    size = UC_Utf8Size(NULL);

    assert_int_equal(size, 0u);
}

void UC_Utf8Size_EmptyUtf8Char_0(__attribute__((unused)) void **state) {
    size_t        size = 0xDEADBEEFu;
    const uint8_t u8Char[] = {0x00};

    size = UC_Utf8Size(u8Char);

    assert_int_equal(size, 0u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_Utf8Size_Z_1),
    cmocka_unit_test(UC_Utf8Size_CyrillicYu_2),
    cmocka_unit_test(UC_Utf8Size_ChinesseTiger_3),
    cmocka_unit_test(UC_Utf8Size_TwoCyrillicYu_2),
    cmocka_unit_test(UC_Utf8Size_TooLongBytesSequence_0),
    cmocka_unit_test(UC_Utf8Size_Null_0),
    cmocka_unit_test(UC_Utf8Size_EmptyUtf8Char_0),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
