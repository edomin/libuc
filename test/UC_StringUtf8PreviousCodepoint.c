#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_StringUtf8PreviousCodepoint_NULL_NULL(
 __attribute__((unused)) void **state) {
    uint8_t       *utf8 = NULL;
    const uint8_t *nextCodepoint = UC_StringUtf8PreviousCodepoint(utf8);

    assert_null(nextCodepoint);
}

// NOLINTBEGIN(readability-magic-numbers)
void UC_StringUtf8PreviousCodepoint_CyrillicHello_3rd_letter_0xD180(
 __attribute__((unused)) void **state) {
    uint8_t        utf8[] = {
     0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0, 0xB5, 0xD1, 0x82,
     0x00
    }; /* Привет */
    uint8_t       *putf8 = &utf8[4u];
    const uint8_t *previousCodepoint = UC_StringUtf8PreviousCodepoint(putf8);

    assert_memory_equal(previousCodepoint, "\xD1\x80", 2u);
}
// NOLINTEND(readability-magic-numbers)

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUtf8PreviousCodepoint_NULL_NULL),
    cmocka_unit_test(
     UC_StringUtf8PreviousCodepoint_CyrillicHello_3rd_letter_0xD180),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
