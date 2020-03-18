#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_StringUtf8ToUcs4_Utf8null_MaxLen6_Ucs4zeros_Len0(void **state) {
    uint32_t ucs4[7] = {0};
    size_t   len = UC_StringUtf8ToUcs4(NULL, ucs4, 6u);

    assert_true(ucs4[0] == 0x00000000u);
    assert_true(ucs4[1] == 0x00000000u);
    assert_true(ucs4[2] == 0x00000000u);
    assert_true(ucs4[3] == 0x00000000u);
    assert_true(ucs4[4] == 0x00000000u);
    assert_true(ucs4[5] == 0x00000000u);
    assert_true(ucs4[6] == 0x00000000u);
    assert_true(len == 0u);
}

void UC_StringUtf8ToUcs4_Utf8Privet_MaxLen6_Ucs4null_Len0(void **state) {
    uint8_t utf8[] = {'\xD0', '\x9F', '\xD1', '\x80', '\xD0', '\xB8',
     '\xD0', '\xB2', '\xD0', '\xB5', '\xD1', '\x82', '\0'}; /* Привет */
    size_t  len = UC_StringUtf8ToUcs4(utf8, NULL, 6u);

    assert_true(len == 0u);
}

void UC_StringUtf8ToUcs4_Utf8Privet_MaxLen6_Ucs4Privet_Len6(void **state) {
    uint8_t  utf8[] = {'\xD0', '\x9F', '\xD1', '\x80', '\xD0', '\xB8',
     '\xD0', '\xB2', '\xD0', '\xB5', '\xD1', '\x82', '\0'}; /* Привет */
    uint32_t ucs4[7] = {0};
    size_t   len = UC_StringUtf8ToUcs4(utf8, ucs4, 6u);

    assert_true(ucs4[0] == 0x0000041Fu);
    assert_true(ucs4[1] == 0x00000440u);
    assert_true(ucs4[2] == 0x00000438u);
    assert_true(ucs4[3] == 0x00000432u);
    assert_true(ucs4[4] == 0x00000435u);
    assert_true(ucs4[5] == 0x00000442u);
    assert_true(ucs4[6] == 0x00000000u);
    assert_true(len == 6u);
}

void UC_StringUtf8ToUcs4_Utf8Privet_MaxLen6_Ucs4Prive_Len5(void **state) {
    uint8_t  utf8[] = {'\xD0', '\x9F', '\xD1', '\x80', '\xD0', '\xB8',
     '\xD0', '\xB2', '\xD0', '\xB5', '\0'}; /* Приве */
    uint32_t ucs4[7] = {0};
    size_t   len = UC_StringUtf8ToUcs4(utf8, ucs4, 6u);

    assert_true(ucs4[0] == 0x0000041Fu);
    assert_true(ucs4[1] == 0x00000440u);
    assert_true(ucs4[2] == 0x00000438u);
    assert_true(ucs4[3] == 0x00000432u);
    assert_true(ucs4[4] == 0x00000435u);
    assert_true(ucs4[5] == 0x00000000u);
    assert_true(ucs4[6] == 0x00000000u);
    assert_true(len == 5u);
}

void UC_StringUtf8ToUcs4_Utf8Privet_MaxLen5_Ucs4Prive_Len5(void **state) {
    uint8_t  utf8[] = {'\xD0', '\x9F', '\xD1', '\x80', '\xD0', '\xB8',
     '\xD0', '\xB2', '\xD0', '\xB5', '\xD1', '\x82', '\0'}; /* Привет */
    uint32_t ucs4[7] = {0};
    size_t   len = UC_StringUtf8ToUcs4(utf8, ucs4, 5u);

    assert_true(ucs4[0] == 0x0000041Fu);
    assert_true(ucs4[1] == 0x00000440u);
    assert_true(ucs4[2] == 0x00000438u);
    assert_true(ucs4[3] == 0x00000432u);
    assert_true(ucs4[4] == 0x00000435u);
    assert_true(ucs4[5] == 0x00000000u);
    assert_true(ucs4[6] == 0x00000000u);
    assert_true(len == 5u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUtf8ToUcs4_Utf8null_MaxLen6_Ucs4zeros_Len0),
    cmocka_unit_test(UC_StringUtf8ToUcs4_Utf8Privet_MaxLen6_Ucs4null_Len0),
    cmocka_unit_test(UC_StringUtf8ToUcs4_Utf8Privet_MaxLen6_Ucs4Privet_Len6),
    cmocka_unit_test(UC_StringUtf8ToUcs4_Utf8Privet_MaxLen6_Ucs4Prive_Len5),
    cmocka_unit_test(UC_StringUtf8ToUcs4_Utf8Privet_MaxLen5_Ucs4Prive_Len5),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
