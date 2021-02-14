#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_StringUtf8NextCodepoint_NULL_NULL(
 __attribute__((unused)) void **state) {
    uint8_t       *utf8 = NULL;
    const uint8_t *nextCodepoint = UC_StringUtf8NextCodepoint(utf8);

    assert_null(nextCodepoint);
}

void UC_StringUtf8NextCodepoint_CyrillicHello_0xD180(
 __attribute__((unused)) void **state) {
    uint8_t        utf8[] = {
     0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0, 0xB5, 0xD1, 0x82,
     0x00
    }; /* Привет */
    const uint8_t *nextCodepoint = UC_StringUtf8NextCodepoint(utf8);
    uint8_t        test_value[] = {0xD1, 0x80};

    assert_memory_equal(nextCodepoint, test_value, 2u);
}

void UC_StringUtf8NextCodepoint_CyrillicHelloLastChar_NullTerm(
 __attribute__((unused)) void **state) {
    uint8_t        utf8[] = {
     0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0, 0xB5, 0xD1, 0x82,
     0x00
    }; /* Привет */
    const uint8_t *nextCodepoint = UC_StringUtf8NextCodepoint(&utf8[10]);
    uint8_t        test_value = 0x00;

    assert_memory_equal(nextCodepoint, &test_value, 1u);
}

void UC_StringUtf8NextCodepoint_CyrillicHelloNullTerm_NullTerm(
 __attribute__((unused)) void **state) {
    uint8_t        utf8[] = {
     0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0, 0xB5, 0xD1, 0x82,
     0x00
    }; /* Привет */
    const uint8_t *nextCodepoint = UC_StringUtf8NextCodepoint(&utf8[12]);

    assert_ptr_equal(nextCodepoint, &utf8[12]);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUtf8NextCodepoint_NULL_NULL),
    cmocka_unit_test(UC_StringUtf8NextCodepoint_CyrillicHello_0xD180),
    cmocka_unit_test(UC_StringUtf8NextCodepoint_CyrillicHelloLastChar_NullTerm),
    cmocka_unit_test(UC_StringUtf8NextCodepoint_CyrillicHelloNullTerm_NullTerm),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
