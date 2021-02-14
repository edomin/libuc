#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_Ucs4LowerByte_0x0000044E_0x4E(__attribute__((unused)) void **state) {
    uint32_t usc4 = 0x0000044Eu;
    uint8_t  lowerByte = 0xAAu;

    lowerByte = UC_Ucs4LowerByte(usc4);

    assert_int_equal(lowerByte, 0x4Eu);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_Ucs4LowerByte_0x0000044E_0x4E),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
