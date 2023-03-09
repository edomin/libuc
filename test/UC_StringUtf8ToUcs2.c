#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>

#include "uc/uc.h"

// NOLINTBEGIN(readability-magic-numbers)
void UC_StringUtf8ToUcs2_Utf8null_MaxLen6_Ucs2zeros_Len0(
 __attribute__((unused)) void **state) {
    uint16_t ucs2[7] = {0};
    size_t   len = UC_StringUtf8ToUcs2(NULL, ucs2, 6u);
    uint16_t test_value[] = {
     0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u, 0x0000u
    };

    assert_int_equal(len, 0u);
    assert_memory_equal(ucs2, test_value, sizeof(uint16_t) * 7);
}

void UC_StringUtf8ToUcs2_Utf8Privet_MaxLen6_Ucs2null_Len0(
 __attribute__((unused)) void **state) {
    uint8_t utf8[] = {0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0,
     0xB5, 0xD1, 0x82, 0x00}; /* Привет */
    size_t  len = UC_StringUtf8ToUcs2(utf8, NULL, 6u);

    assert_true(len == 0u);
}

void UC_StringUtf8ToUcs2_Utf8Privet_MaxLen6_Ucs2Privet_Len6(
 __attribute__((unused)) void **state) {
    uint8_t  utf8[] = {0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0,
     0xB5, 0xD1, 0x82, 0x00}; /* Привет */
    uint16_t ucs2[7] = {0};
    size_t   len = UC_StringUtf8ToUcs2(utf8, ucs2, 6u);
    uint16_t test_value[] = {
     0x041Fu, 0x0440u, 0x0438u, 0x0432u, 0x0435u, 0x0442u, 0x0000u
    };

    assert_int_equal(len, 6u);
    assert_memory_equal(ucs2, test_value, sizeof(uint16_t) * 7);
}

void UC_StringUtf8ToUcs2_Utf8Privet_MaxLen6_Ucs2Prive_Len5(
 __attribute__((unused)) void **state) {
    uint8_t  utf8[] = {0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0,
     0xB5, 0x00}; /* Приве */
    uint16_t ucs2[7] = {0};
    size_t   len = UC_StringUtf8ToUcs2(utf8, ucs2, 6u);
    uint16_t test_value[] = {
     0x041Fu, 0x0440u, 0x0438u, 0x0432u, 0x0435u, 0x0000u, 0x0000u
    };

    assert_int_equal(len, 5u);
    assert_memory_equal(ucs2, test_value, sizeof(uint16_t) * 7);
}

void UC_StringUtf8ToUcs2_Utf8Privet_MaxLen5_Ucs2Prive_Len5(
 __attribute__((unused)) void **state) {
    uint8_t  utf8[] = {0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0,
     0xB5, 0xD1, 0x82, 0x00}; /* Привет */
    uint16_t ucs2[7] = {0};
    size_t   len = UC_StringUtf8ToUcs2(utf8, ucs2, 5u);
    uint16_t test_value[] = {
     0x041Fu, 0x0440u, 0x0438u, 0x0432u, 0x0435u, 0x0000u, 0x0000u
    };

    assert_int_equal(len, 5u);
    assert_memory_equal(ucs2, test_value, sizeof(uint16_t) * 7);
}
// NOLINTEND(readability-magic-numbers)

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUtf8ToUcs2_Utf8null_MaxLen6_Ucs2zeros_Len0),
    cmocka_unit_test(UC_StringUtf8ToUcs2_Utf8Privet_MaxLen6_Ucs2null_Len0),
    cmocka_unit_test(UC_StringUtf8ToUcs2_Utf8Privet_MaxLen6_Ucs2Privet_Len6),
    cmocka_unit_test(UC_StringUtf8ToUcs2_Utf8Privet_MaxLen6_Ucs2Prive_Len5),
    cmocka_unit_test(UC_StringUtf8ToUcs2_Utf8Privet_MaxLen5_Ucs2Prive_Len5),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
