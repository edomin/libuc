#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_Utf8ToUcs4_Z_0x0000007A(void **state) {
    const uint8_t utf8[] = {'\x7A', '\0'}; /* z */
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(utf8);

    assert_true(ucs4 == 0x0000007Au);
}

void UC_Utf8ToUcs4_CyrillicYu_0x0000044E(void **state) {
    const uint8_t utf8[] = {'\xD1', '\x8E', '\0'}; /* ю */
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(utf8);

    assert_true(ucs4 == 0x0000044Eu);
}

void UC_Utf8ToUcs4_ChinesseTiger_0x0000864E(void **state) {
    const uint8_t utf8[] = {'\xE8', '\x99', '\x8E', '\0'}; /* 虎 */
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(utf8);

    assert_true(ucs4 == 0x0000864Eu);
}

void UC_Utf8ToUcs4_TwoCyrillicYu_0x0000044E(void **state) {
    const uint8_t utf8[] = {'\xD1', '\x8E', '\xD1', '\x8E', '\0'}; /* юю */
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(utf8);

    assert_true(ucs4 == 0x0000044Eu);
}

void UC_Utf8ToUcs4_TooLongSequence_0x00000020(void **state) {
    const uint8_t utf8[] = {'\x80', '\x80', '\x80', '\x80', '\x80', '\x80',
     '\x80', '\0'};
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(utf8);

    assert_true(ucs4 == 0x00000020u);
}

void UC_Utf8ToUcs4_Empty_0x00000020(void **state) {
    const uint8_t utf8[] = {'\0'};
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(utf8);

    assert_true(ucs4 == 0x00000020u);
}

void UC_Utf8ToUcs4_Null_0x00000020(void **state) {
    uint32_t      ucs4 = 0xDEADBEEFu;

    ucs4 = UC_Utf8ToUcs4(NULL);

    assert_true(ucs4 == 0x00000020u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_Utf8ToUcs4_Z_0x0000007A),
    cmocka_unit_test(UC_Utf8ToUcs4_CyrillicYu_0x0000044E),
    cmocka_unit_test(UC_Utf8ToUcs4_ChinesseTiger_0x0000864E),
    cmocka_unit_test(UC_Utf8ToUcs4_TwoCyrillicYu_0x0000044E),
    cmocka_unit_test(UC_Utf8ToUcs4_TooLongSequence_0x00000020),
    cmocka_unit_test(UC_Utf8ToUcs4_Empty_0x00000020),
    cmocka_unit_test(UC_Utf8ToUcs4_Null_0x00000020),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
