#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>

#include "uc/uc.h"

// NOLINTBEGIN(readability-magic-numbers)
void UC_Utf8ToUcs2_Z_0x007A(__attribute__((unused)) void **state) {
    const uint8_t utf8[] = {0x7A, 0x00}; /* z */
    uint16_t      ucs2 = 0xBEEFu;

    ucs2 = UC_Utf8ToUcs2(utf8);

    assert_int_equal(ucs2, 0x007Au);
}

void UC_Utf8ToUcs2_CyrillicYu_0x044E(__attribute__((unused)) void **state) {
    const uint8_t utf8[] = {0xD1, 0x8E, 0x00}; /* ю */
    uint16_t      ucs2 = 0xBEEFu;

    ucs2 = UC_Utf8ToUcs2(utf8);

    assert_int_equal(ucs2, 0x044Eu);
}

void UC_Utf8ToUcs2_ChinesseTiger_0x864E(
 __attribute__((unused)) void **state) {
    const uint8_t utf8[] = {0xE8, 0x99, 0x8E, 0x00}; /* 虎 */
    uint16_t      ucs2 = 0xBEEFu;

    ucs2 = UC_Utf8ToUcs2(utf8);

    assert_int_equal(ucs2, 0x864Eu);
}

void UC_Utf8ToUcs2_Smile_UC_UNKNOWN_SYMBOL_PLACEHOLDER(__attribute__((unused)) void **state) {
    const uint8_t utf8[] = {0xF0, 0x9F, 0x98, 0x83, 0x00}; /* 😃 */
    uint16_t      ucs2 = 0xBEEFu;

    ucs2 = UC_Utf8ToUcs2(utf8);

    assert_int_equal(ucs2, UC_UNKNOWN_SYMBOL_PLACEHOLDER);
}

void UC_Utf8ToUcs2_TwoCyrillicYu_0x044E(
 __attribute__((unused)) void **state) {
    const uint8_t utf8[] = {0xD1, 0x8E, 0xD1, 0x8E, 0x00}; /* юю */
    uint16_t      ucs2 = 0xBEEFu;

    ucs2 = UC_Utf8ToUcs2(utf8);

    assert_int_equal(ucs2, 0x044Eu);
}

void UC_Utf8ToUcs2_Empty_0x0020(__attribute__((unused)) void **state) {
    const uint8_t utf8[] = {0x00};
    uint16_t      ucs2 = 0xBEEFu;

    ucs2 = UC_Utf8ToUcs2(utf8);

    assert_int_equal(ucs2, 0x0020u);
}

void UC_Utf8ToUcs2_Null_0x0020(__attribute__((unused)) void **state) {
    uint16_t ucs2 = 0xBEEFu;

    ucs2 = UC_Utf8ToUcs2(NULL);

    assert_int_equal(ucs2, 0x0020u);
}
// NOLINTEND(readability-magic-numbers)

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_Utf8ToUcs2_Z_0x007A),
    cmocka_unit_test(UC_Utf8ToUcs2_CyrillicYu_0x044E),
    cmocka_unit_test(UC_Utf8ToUcs2_ChinesseTiger_0x864E),
    cmocka_unit_test(UC_Utf8ToUcs2_Smile_UC_UNKNOWN_SYMBOL_PLACEHOLDER),
    cmocka_unit_test(UC_Utf8ToUcs2_TwoCyrillicYu_0x044E),
    cmocka_unit_test(UC_Utf8ToUcs2_Empty_0x0020),
    cmocka_unit_test(UC_Utf8ToUcs2_Null_0x0020),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
