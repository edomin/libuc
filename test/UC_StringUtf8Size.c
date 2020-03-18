#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_StringUtf8Size_NULL_0u(void **state) {
    uint8_t *utf8 = NULL;
    size_t size = UC_StringUtf8Size(utf8);

    assert_true(size == 0u);
}

void UC_StringUtf8Size_CyrillicHello_13u(void **state) {
    uint8_t utf8[] = {'\xD0', '\x9F', '\xD1', '\x80', '\xD0', '\xB8',
     '\xD0', '\xB2', '\xD0', '\xB5', '\xD1', '\x82', '\0'}; /* Привет */
    size_t size = UC_StringUtf8Size(utf8);

    assert_true(size == 13u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUtf8Size_NULL_0u),
    cmocka_unit_test(UC_StringUtf8Size_CyrillicHello_13u),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
