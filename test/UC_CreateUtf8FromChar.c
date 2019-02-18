#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_CreateUtf8FromChar_Z_0x7A000000000000(void **state) {
    uint8_t *u8char = NULL;

    u8char = UC_CreateUtf8FromChar("z");

    assert_memory_equal(u8char, "\x7A\0\0\0\0\0\0", 5u);
}

void UC_CreateUtf8FromChar_CyrillicYu_0xD18E0000000000(void **state) {
    uint8_t *u8char = NULL;

    u8char = UC_CreateUtf8FromChar("ю");

    assert_memory_equal(u8char, "\xD1\x8E\0\0\0\0\0", 5u);
}

void UC_CreateUtf8FromChar_ChinesseTiger_0xE8998E00000000(void **state) {
    uint8_t *u8char = NULL;

    u8char = UC_CreateUtf8FromChar("虎");

    assert_memory_equal(u8char, "\xE8\x99\x8E\0\0\0\0", 5u);
}

void UC_CreateUtf8FromChar_TwoCyrillicYu_0xD18E0000000000(void **state) {
    uint8_t *u8char = NULL;

    u8char = UC_CreateUtf8FromChar("юю");

    assert_memory_equal(u8char, "\xD1\x8E\0\0\0\0\0", 5u);
}

void UC_CreateUtf8FromChar_Null_ArrayOfZeroes(void **state) {
    uint8_t *u8char = NULL;

    u8char = UC_CreateUtf8FromChar(NULL);

    assert_memory_equal(u8char, "\0\0\0\0\0\0\0", 5u);
}

void UC_CreateUtf8FromChar_EmptyCharArray_ArrayOfZeroes(void **state) {
    uint8_t *u8char = NULL;

    u8char = UC_CreateUtf8FromChar("");

    assert_memory_equal(u8char, "\0\0\0\0\0\0\0", 5u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_CreateUtf8FromChar_Z_0x7A000000000000),
    cmocka_unit_test(UC_CreateUtf8FromChar_CyrillicYu_0xD18E0000000000),
    cmocka_unit_test(UC_CreateUtf8FromChar_ChinesseTiger_0xE8998E00000000),
    cmocka_unit_test(UC_CreateUtf8FromChar_TwoCyrillicYu_0xD18E0000000000),
    cmocka_unit_test(UC_CreateUtf8FromChar_Null_ArrayOfZeroes),
    cmocka_unit_test(UC_CreateUtf8FromChar_EmptyCharArray_ArrayOfZeroes),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
