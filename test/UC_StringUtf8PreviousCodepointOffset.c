#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_StringUtf8PreviousCodepointOffset_NULL_UC_SIZE_ERROR(
 __attribute__((unused)) void **state) {
    uint8_t *utf8 = NULL;
    size_t   nextCodepointOffset = UC_StringUtf8PreviousCodepointOffset(utf8,
     0u);

    assert_int_equal(nextCodepointOffset, UC_SIZE_ERROR);
}

void UC_StringUtf8PreviousCodepointOffset_CyrillicHello_4u_2u(
 __attribute__((unused)) void **state) {
    uint8_t utf8[] = {
     0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0, 0xB5, 0xD1, 0x82,
     0x00
    }; /* Привет */
    size_t  previousCodepointOffset = UC_StringUtf8PreviousCodepointOffset(utf8,
     4u);

    assert_int_equal(previousCodepointOffset, 2u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUtf8PreviousCodepointOffset_NULL_UC_SIZE_ERROR),
    cmocka_unit_test(UC_StringUtf8PreviousCodepointOffset_CyrillicHello_4u_2u),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
