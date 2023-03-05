#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_GetLinkedVersionString_Void_NonNull(
 __attribute__((unused)) void **state) {
    const char *version = NULL;

    version = UC_GetLinkedVersionString();

    assert_non_null(version);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_GetLinkedVersionString_Void_NonNull),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
