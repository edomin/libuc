#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>

#include "uc/uc.h"

// NOLINTBEGIN(readability-magic-numbers)
void UC_Utf8ToUcs4_Z_0x0000007A(__attribute__((unused)) void **state) {
    const uint8_t utf8[] = {0x7A, 0x00}; /* z */
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(utf8);

    assert_int_equal(ucs4, 0x0000007Au);
}

void UC_Utf8ToUcs4_CyrillicYu_0x0000044E(__attribute__((unused)) void **state) {
    const uint8_t utf8[] = {0xD1, 0x8E, 0x00}; /* ю */
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(utf8);

    assert_int_equal(ucs4, 0x0000044Eu);
}

void UC_Utf8ToUcs4_ChinesseTiger_0x0000864E(
 __attribute__((unused)) void **state) {
    const uint8_t utf8[] = {0xE8, 0x99, 0x8E, 0x00}; /* 虎 */
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(utf8);

    assert_int_equal(ucs4, 0x0000864Eu);
}

void UC_Utf8ToUcs4_Smile_0x0001F603(__attribute__((unused)) void **state) {
    const uint8_t utf8[] = {0xF0, 0x9F, 0x98, 0x83, 0x00}; /* 😃 */
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(utf8);

    assert_int_equal(ucs4, 0x0001F603u);
}

void UC_Utf8ToUcs4_TwoCyrillicYu_0x0000044E(
 __attribute__((unused)) void **state) {
    const uint8_t utf8[] = {0xD1, 0x8E, 0xD1, 0x8E, 0x00}; /* юю */
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(utf8);

    assert_int_equal(ucs4, 0x0000044Eu);
}

void UC_Utf8ToUcs4_TooLongSequence_0x00000020(
 __attribute__((unused)) void **state) {
    const uint8_t utf8[] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00};
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(utf8);

    assert_int_equal(ucs4, 0x00000020u);
}

void UC_Utf8ToUcs4_Empty_0x00000020(__attribute__((unused)) void **state) {
    const uint8_t utf8[] = {0x00};
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(utf8);

    assert_int_equal(ucs4, 0x00000020u);
}

void UC_Utf8ToUcs4_Null_0x00000020(__attribute__((unused)) void **state) {
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(NULL);

    assert_int_equal(ucs4, 0x00000020u);
}
// NOLINTEND(readability-magic-numbers)

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_Utf8ToUcs4_Z_0x0000007A),
    cmocka_unit_test(UC_Utf8ToUcs4_CyrillicYu_0x0000044E),
    cmocka_unit_test(UC_Utf8ToUcs4_ChinesseTiger_0x0000864E),
    cmocka_unit_test(UC_Utf8ToUcs4_Smile_0x0001F603),
    cmocka_unit_test(UC_Utf8ToUcs4_TwoCyrillicYu_0x0000044E),
    cmocka_unit_test(UC_Utf8ToUcs4_TooLongSequence_0x00000020),
    cmocka_unit_test(UC_Utf8ToUcs4_Empty_0x00000020),
    cmocka_unit_test(UC_Utf8ToUcs4_Null_0x00000020),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
