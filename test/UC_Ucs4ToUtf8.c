#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_Ucs4ToUtf8_U32z_U8zSize1(void **state) {
    uint32_t u32char = 0x0000007Au; /* z */
    uint8_t  u8char[5] = {0};
    size_t   size;

    size = UC_Ucs4ToUtf8(u32char, u8char);

    assert_memory_equal(u8char, "\x7A\0\0\0\0", 5u);
    assert_true(size == 1u);
}

void UC_Ucs4ToUtf8_U32cyrillicYu_U8cyrillicYuSize2(void **state) {
    uint32_t u32char = 0x0000044Eu; /* ю */
    uint8_t  u8char[5] = {0};
    size_t   size;

    size = UC_Ucs4ToUtf8(u32char, u8char);

    assert_memory_equal(u8char, "\xD1\x8E\0\0\0", 5u);
    assert_true(size == 2u);
}

void UC_Ucs4ToUtf8_U32chinesseTiger_U8chinesseTigerSize3(void **state) {
    uint32_t u32char = 0x0000864Eu; /* 虎 */
    uint8_t  u8char[5] = {0};
    size_t   size;

    size = UC_Ucs4ToUtf8(u32char, u8char);

    assert_memory_equal(u8char, "\xE8\x99\x8E\0\0", 5u);
    assert_true(size == 3u);
}

void UC_Ucs4ToUtf8_U32Smile_U8SmileSize4(void **state) {
    uint32_t u32char = 0x0001F603u; /* 😃 */
    uint8_t  u8char[5] = {0};
    size_t   size;

    size = UC_Ucs4ToUtf8(u32char, u8char);

    assert_memory_equal(u8char, "\xF0\x9F\x98\x83\0", 5u);
    assert_true(size == 4u);
}

void UC_Ucs4ToUtf8_U32tooBig_U8spaceSize1(void **state) {
    uint32_t u32char = 0x10000000u;
    uint8_t  u8char[5] = {0};
    size_t   size;

    size = UC_Ucs4ToUtf8(u32char, u8char);

    assert_memory_equal(u8char, "\x20\0\0\0\0", 5u);
    assert_true(size == 1u);
}

void UC_Ucs4ToUtf8_U32zToPointerToNull_NothingSize0(void **state) {
    uint32_t u32char = 0x0000007Au; /* z */
    uint8_t *u8char = NULL;
    size_t   size;

    size = UC_Ucs4ToUtf8(u32char, u8char);

    assert_null(u8char);
    assert_true(size == 0u);
}

void UC_Ucs4ToUtf8_U32zToNull_NothingSize0(void **state) {
    uint32_t u32char = 0x0000007Au; /* z */
    size_t   size;

    size = UC_Ucs4ToUtf8(u32char, NULL);

    assert_true(size == 0u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_Ucs4ToUtf8_U32z_U8zSize1),
    cmocka_unit_test(UC_Ucs4ToUtf8_U32cyrillicYu_U8cyrillicYuSize2),
    cmocka_unit_test(UC_Ucs4ToUtf8_U32chinesseTiger_U8chinesseTigerSize3),
    cmocka_unit_test(UC_Ucs4ToUtf8_U32Smile_U8SmileSize4),
    cmocka_unit_test(UC_Ucs4ToUtf8_U32tooBig_U8spaceSize1),
    cmocka_unit_test(UC_Ucs4ToUtf8_U32zToPointerToNull_NothingSize0),
    cmocka_unit_test(UC_Ucs4ToUtf8_U32zToNull_NothingSize0),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
