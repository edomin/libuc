#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_StringUtf8Codepoints_NULL_0u(__attribute__((unused)) void **state) {
    uint8_t *utf8 = NULL;
    size_t codepoints = UC_StringUtf8Codepoints(utf8);

    assert_int_equal(codepoints, 0u);
}

void UC_StringUtf8Codepoints_CyrillicHello_6u(
 __attribute__((unused)) void **state) {
    uint8_t utf8[] = {0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0,
     0xB5, 0xD1, 0x82, 0x00}; /* Привет */
    size_t codepoints = UC_StringUtf8Codepoints(utf8);

    assert_int_equal(codepoints, 6u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUtf8Codepoints_NULL_0u),
    cmocka_unit_test(UC_StringUtf8Codepoints_CyrillicHello_6u),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
