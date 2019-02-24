#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_Ucs4LowerByte_0x0000044E_0x4E(void **state) {
    uint32_t usc4 = 0x0000044Eu;
    unsigned lowerByte = 0xDEADBEEFu;

    lowerByte = UC_Ucs4LowerByte(usc4);

    assert_true(lowerByte == 0x4Eu);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_Ucs4LowerByte_0x0000044E_0x4E),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
