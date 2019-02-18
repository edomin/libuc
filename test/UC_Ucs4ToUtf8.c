#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_UC_Ucs4ToUtf8_U32z_U8zSize1(void **state) {
    uint32_t u32char = 0x0000007Au; /* z */
    uint8_t  u8char[5] = {'\0', '\0', '\0', '\0', '\0'};
    size_t   size = 0xDEADBEEFu;

    UC_Ucs4ToUtf8(u32char, u8char, size);

    assert_memory_equal(u8char, "\x7A\0\0\0\0", 5u);
    assert_true(nbytes == 1u);
}

void UC_UC_Ucs4ToUtf8_U32cyrillicYu_U8cyrillicYuSize2(void **state) {
    uint32_t u32char = 0x0000044Eu; /* ю */
    uint8_t  u8char[5] = {'\0', '\0', '\0', '\0', '\0'};
    size_t   size = 0xDEADBEEFu;

    UC_Ucs4ToUtf8(u32char, u8char, size);

    assert_memory_equal(u8char, "\xD1\x8E\0\0\0", 5u);
    assert_true(nbytes == 2u);
}

void UC_UC_Ucs4ToUtf8_U32chinesseTiger_U8chinesseTigerSize3(void **state) {
    uint32_t u32char = 0x0000864Eu; /* 虎 */
    uint8_t  u8char[5] = {'\0', '\0', '\0', '\0', '\0'};
    size_t   size = 0xDEADBEEFu;

    UC_Ucs4ToUtf8(u32char, u8char, size);

    assert_memory_equal(u8char, "\xE8\x99\x8E\0\0", 5u);
    assert_true(nbytes == 3u);
}

void UC_UC_Ucs4ToUtf8_U32tooBig_U8spaceSize1(void **state) {
    uint32_t u32char = 0x10000000u;
    uint8_t  u8char[5] = {'\0', '\0', '\0', '\0', '\0'};
    size_t   size = 0xDEADBEEFu;

    UC_Ucs4ToUtf8(u32char, u8char, size);

    assert_memory_equal(u8char, "\x20\0\0\0\0", 5u);
    assert_true(nbytes == 1u);
}

void UC_UC_Ucs4ToUtf8_U32zToNull_NothingSize0(void **state) {
    uint32_t u32char = 0x0000007Au; /* z */
    size_t   size = 0xDEADBEEFu;

    UC_Ucs4ToUtf8(u32char, NULL, size);

    assert_true(nbytes == 0u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_UC_Ucs4ToUtf8_U32z_U8zSize1),
    cmocka_unit_test(UC_UC_Ucs4ToUtf8_U32cyrillicYu_U8cyrillicYuSize2),
    cmocka_unit_test(UC_UC_Ucs4ToUtf8_U32chinesseTiger_U8chinesseTigerSize3),
    cmocka_unit_test(UC_UC_Ucs4ToUtf8_U32tooBig_U8spaceSize1),
    cmocka_unit_test(UC_UC_Ucs4ToUtf8_U32zToNull_NothingSize0),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
