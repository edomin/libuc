#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_StringUtf8Codepoints_NULL_0u(void **state) {
    uint8_t *utf8 = NULL;
    size_t codepoints = UC_StringUtf8Codepoints(utf8);

    assert_true(codepoints == 0u);
}

void UC_StringUtf8Codepoints_CyrillicHello_6u(void **state) {
    uint8_t utf8[] = {'\xD0', '\x9F', '\xD1', '\x80', '\xD0', '\xB8',
     '\xD0', '\xB2', '\xD0', '\xB5', '\xD1', '\x82', '\0'}; /* Привет */
    size_t codepoints = UC_StringUtf8Codepoints(utf8);

    assert_true(codepoints == 6u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUtf8Codepoints_NULL_0u),
    cmocka_unit_test(UC_StringUtf8Codepoints_CyrillicHello_6u),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
