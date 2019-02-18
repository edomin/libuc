#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_Utf8Size_Z_1(void **state) {
    size_t        size = 0xDEADBEEFu;
    const uint8_t u8Char[] = {'\x7a', '\0'}; /* z */

    size = UC_Utf8Size(u8Char);

    assert_true(size == 1u);
}

void UC_Utf8Size_CyrillicYu_2(void **state) {
    size_t        size = 0xDEADBEEFu;
    const uint8_t u8Char[] = {'\xd1', '\x8e', '\0'}; /* ю */

    size = UC_Utf8Size(u8Char);

    assert_true(size == 2u);
}

void UC_Utf8Size_ChinesseTiger_3(void **state) {
    size_t        size = 0xDEADBEEFu;
    const uint8_t u8Char[] = {'\xe8', '\x99', '\x8e', '\0'}; /* 虎 */

    size = UC_Utf8Size(u8Char);

    assert_true(size == 3u);
}

void UC_Utf8Size_TwoCyrillicYu_2(void **state) {
    size_t        size = 0xDEADBEEFu;
    const uint8_t u8Char[] = {'\xd1', '\x8e', '\xd1', '\x8e', '\0'}; /* юю */

    size = UC_Utf8Size(u8Char);

    assert_true(size == 2u);
}

void UC_Utf8Size_TooLongBytesSequence_0(void **state) {
    size_t        size = 0xDEADBEEFu;
    const uint8_t u8Char[] = {'\x80', '\x80', '\x80', '\x80', '\x80', '\x80',
     '\x80', '\0'};

    size = UC_Utf8Size(u8Char);

    assert_true(size == 0u);
}

void UC_Utf8Size_Null_0(void **state) {
    size_t size = 0xDEADBEEFu;

    size = UC_Utf8Size(NULL);

    assert_true(size == 0u);
}

void UC_Utf8Size_EmptyUtf8Char_0(void **state) {
    size_t        size = 0xDEADBEEFu;
    const uint8_t u8Char[] = {'\0'};

    size = UC_Utf8Size(u8Char);

    assert_true(size == 0u);
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
