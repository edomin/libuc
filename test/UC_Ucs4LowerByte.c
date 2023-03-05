#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>

#include "uc/uc.h"

// NOLINTBEGIN(readability-magic-numbers)
void UC_Ucs4LowerByte_0x0000044E_0x4E(__attribute__((unused)) void **state) {
    uint32_t usc4 = 0x0000044Eu;
    unsigned lowerByte = 0xAAu;

    lowerByte = UC_Ucs4LowerByte(usc4);

    assert_int_equal(lowerByte, 0x4Eu);
}
// NOLINTEND(readability-magic-numbers)

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_Ucs4LowerByte_0x0000044E_0x4E),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
