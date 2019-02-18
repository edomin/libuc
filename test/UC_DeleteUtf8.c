#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_DeleteUtf8_U8_Null(void **state) {
    uint8_t *u8char = UC_CreateUtf8();

    UC_DeleteUtf8(&u8char);

    assert_null(u8char);
}

void UC_DeleteUtf8_Null_Null(void **state) {
    uint8_t *u8char = NULL;

    UC_DeleteUtf8(&u8char);

    assert_null(u8char);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_DeleteUtf8_U8_Null),
    cmocka_unit_test(UC_DeleteUtf8_Null_Null),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
