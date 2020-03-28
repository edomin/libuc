#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_StringUtf8NextCodepointOffset_NULL_UC_SIZE_ERROR(void **state) {
    uint8_t *utf8 = NULL;
    size_t nextCodepointOffset = UC_StringUtf8NextCodepointOffset(utf8, 0u);

    assert_true(nextCodepointOffset == UC_SIZE_ERROR);
}

void UC_StringUtf8NextCodepointOffset_CyrillicHello_2u(void **state) {
    uint8_t utf8[] = {'\xD0', '\x9F', '\xD1', '\x80', '\xD0', '\xB8',
     '\xD0', '\xB2', '\xD0', '\xB5', '\xD1', '\x82', '\0'}; /* Привет */
    size_t nextCodepointOffset = UC_StringUtf8NextCodepointOffset(utf8, 0u);

    assert_true(nextCodepointOffset == 2u);
}

void UC_StringUtf8NextCodepointOffset_CyrillicHello10u_12u(void **state) {
    uint8_t utf8[] = {'\xD0', '\x9F', '\xD1', '\x80', '\xD0', '\xB8',
     '\xD0', '\xB2', '\xD0', '\xB5', '\xD1', '\x82', '\0'}; /* Привет */
    size_t nextCodepointOffset = UC_StringUtf8NextCodepointOffset(utf8, 10u);

    assert_true(nextCodepointOffset == 12u);
}

void UC_StringUtf8NextCodepointOffset_CyrillicHello12u_12u(void **state) {
    uint8_t utf8[] = {'\xD0', '\x9F', '\xD1', '\x80', '\xD0', '\xB8',
     '\xD0', '\xB2', '\xD0', '\xB5', '\xD1', '\x82', '\0'}; /* Привет */
    size_t nextCodepointOffset = UC_StringUtf8NextCodepointOffset(utf8, 12u);

    assert_true(nextCodepointOffset == 12u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUtf8NextCodepointOffset_NULL_UC_SIZE_ERROR),
    cmocka_unit_test(UC_StringUtf8NextCodepointOffset_CyrillicHello_2u),
    cmocka_unit_test(UC_StringUtf8NextCodepointOffset_CyrillicHello10u_12u),
    cmocka_unit_test(UC_StringUtf8NextCodepointOffset_CyrillicHello12u_12u),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
