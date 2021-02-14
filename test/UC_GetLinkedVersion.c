#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_GetLinkedVersion_IntPtrs_VerNum(__attribute__((unused)) void **state) {
    int verMajor = -1;
    int verMinor = -1;
    int verPatch = -1;

    UC_GetLinkedVersion(&verMajor, &verMinor, &verPatch);

    assert_int_not_equal(verMajor, -1);
    assert_int_not_equal(verMinor, -1);
    assert_int_not_equal(verPatch, -1);
}

void UC_GetLinkedVersion_NullPtrs_Nothing(
 __attribute__((unused)) void **state) {
    UC_GetLinkedVersion(NULL, NULL, NULL);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_GetLinkedVersion_IntPtrs_VerNum),
    cmocka_unit_test(UC_GetLinkedVersion_NullPtrs_Nothing),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
