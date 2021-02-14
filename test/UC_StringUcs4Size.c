#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_StringUcs4Size_NULL_0u(__attribute__((unused)) void **state) {
    uint32_t *ucs4 = NULL;
    size_t    size = UC_StringUcs4Size(ucs4);

    assert_int_equal(size, 0u);
}

void UC_StringUcs4Size_CyrillicHello_28u(__attribute__((unused)) void **state) {
    uint32_t ucs4[] = {0x0000041Fu, 0x00000440u, 0x00000438u, 0x00000432u,
     0x00000435u, 0x00000442u, 0x00000000u}; /* Привет */
    size_t   size = UC_StringUcs4Size(ucs4);

    assert_int_equal(size, 28u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUcs4Size_NULL_0u),
    cmocka_unit_test(UC_StringUcs4Size_CyrillicHello_28u),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
