#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_StringUcs2Len_NULL_0u(__attribute__((unused)) void **state) {
    uint16_t *ucs2 = NULL;
    size_t    len = UC_StringUcs2Len(ucs2);

    assert_int_equal(len, 0u);
}

// NOLINTBEGIN(readability-magic-numbers)
void UC_StringUcs2Len_CyrillicHello_6u(__attribute__((unused)) void **state) {
    uint16_t ucs2[] = {0x041Fu, 0x0440u, 0x0438u, 0x0432u, 0x0435u, 0x0442u,
     0x0000u}; /* Привет */
    size_t   len = UC_StringUcs2Len(ucs2);

    assert_int_equal(len, 6u);
}
// NOLINTEND(readability-magic-numbers)

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUcs2Len_NULL_0u),
    cmocka_unit_test(UC_StringUcs2Len_CyrillicHello_6u),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
