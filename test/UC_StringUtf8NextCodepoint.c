#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_StringUtf8NextCodepoint_NULL_NULL(void **state) {
    uint8_t *utf8 = NULL;
    const uint8_t *nextCodepoint = UC_StringUtf8NextCodepoint(utf8);

    assert_null(nextCodepoint);
}

void UC_StringUtf8NextCodepoint_CyrillicHello_0xD180(void **state) {
    uint8_t utf8[] = {'\xD0', '\x9F', '\xD1', '\x80', '\xD0', '\xB8',
     '\xD0', '\xB2', '\xD0', '\xB5', '\xD1', '\x82', '\0'}; /* Привет */
    const uint8_t *nextCodepoint = UC_StringUtf8NextCodepoint(utf8);

    assert_memory_equal(nextCodepoint, "\xD1\x80", 2u);
}

void UC_StringUtf8NextCodepoint_CyrillicHelloLastChar_NullTerm(void **state) {
    uint8_t utf8[] = {'\xD0', '\x9F', '\xD1', '\x80', '\xD0', '\xB8',
     '\xD0', '\xB2', '\xD0', '\xB5', '\xD1', '\x82', '\0'}; /* Привет */
    const uint8_t *nextCodepoint = UC_StringUtf8NextCodepoint(&utf8[10]);

    assert_memory_equal(nextCodepoint, "\0", 1u);
}

void UC_StringUtf8NextCodepoint_CyrillicHelloNullTerm_NullTerm(void **state) {
    uint8_t utf8[] = {'\xD0', '\x9F', '\xD1', '\x80', '\xD0', '\xB8',
     '\xD0', '\xB2', '\xD0', '\xB5', '\xD1', '\x82', '\0'}; /* Привет */
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
