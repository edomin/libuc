#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_GetLinkedVersionString_Void_NonNull(void **state) {
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
