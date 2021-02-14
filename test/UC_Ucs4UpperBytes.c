#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_Ucs4UpperBytes_0x0000044E_0x04(__attribute__((unused)) void **state) {
    uint32_t       usc4 = 0x0000044Eu;
    uint_least24_t upperBytes = 0xDEADBEEFu;

    upperBytes = UC_Ucs4UpperBytes(usc4);

    assert_int_equal(upperBytes, 0x04u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_Ucs4UpperBytes_0x0000044E_0x04),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
