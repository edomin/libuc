#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_StringUtf8Size_NULL_0u(__attribute__((unused)) void **state) {
    uint8_t *utf8 = NULL;
    size_t   size = UC_StringUtf8Size(utf8);

    assert_int_equal(size, 0u);
}

void UC_StringUtf8Size_CyrillicHello_13u(__attribute__((unused)) void **state) {
    uint8_t utf8[] = {0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0,
     0xB5, 0xD1, 0x82, 0x00}; /* Привет */
    size_t  size = UC_StringUtf8Size(utf8);

    assert_int_equal(size, 13u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUtf8Size_NULL_0u),
    cmocka_unit_test(UC_StringUtf8Size_CyrillicHello_13u),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
