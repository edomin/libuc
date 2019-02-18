#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_CreateUtf8_Void_U8Allocated(void **state) {
    uint8_t *u8char = NULL;

    u8char = UC_CreateUtf8();

    assert_non_null(u8char);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_CreateUtf8_Void_U8Allocated),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
