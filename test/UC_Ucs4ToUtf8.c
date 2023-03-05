#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>

#include "uc/uc.h"

// NOLINTBEGIN(readability-magic-numbers)
void UC_Ucs4ToUtf8_U32z_U8zSize1(__attribute__((unused)) void **state) {
    uint32_t u32char = 0x0000007Au; /* z */
    uint8_t  u8char[5] = {0};
    size_t   size;
    uint8_t  test_value[] = {0x7A, 0x00, 0x00, 0x00, 0x00};

    size = UC_Ucs4ToUtf8(u32char, u8char);

    assert_int_equal(size, 1u);
    assert_memory_equal(u8char, test_value, 5u);
}

void UC_Ucs4ToUtf8_U32cyrillicYu_U8cyrillicYuSize2(
 __attribute__((unused)) void **state) {
    uint32_t u32char = 0x0000044Eu; /* ю */
    uint8_t  u8char[5] = {0};
    size_t   size;
    uint8_t  test_value[] = {0xD1, 0x8E, 0x00, 0x00, 0x00};

    size = UC_Ucs4ToUtf8(u32char, u8char);

    assert_int_equal(size, 2u);
    assert_memory_equal(u8char, test_value, 5u);
}

void UC_Ucs4ToUtf8_U32chinesseTiger_U8chinesseTigerSize3(
 __attribute__((unused)) void **state) {
    uint32_t u32char = 0x0000864Eu; /* 虎 */
    uint8_t  u8char[5] = {0};
    size_t   size;
    uint8_t  test_value[] = {0xE8, 0x99, 0x8E, 0x00, 0x00};

    size = UC_Ucs4ToUtf8(u32char, u8char);

    assert_int_equal(size, 3u);
    assert_memory_equal(u8char, test_value, 5u);
}

void UC_Ucs4ToUtf8_U32Smile_U8SmileSize4(__attribute__((unused)) void **state) {
    uint32_t u32char = 0x0001F603u; /* 😃 */
    uint8_t  u8char[5] = {0};
    size_t   size;
    uint8_t  test_value[] = {0xF0, 0x9F, 0x98, 0x83, 0x00};

    size = UC_Ucs4ToUtf8(u32char, u8char);

    assert_int_equal(size, 4u);
    assert_memory_equal(u8char, test_value, 5u);
}

void UC_Ucs4ToUtf8_U32tooBig_U8spaceSize1(
 __attribute__((unused)) void **state) {
    uint32_t u32char = 0x10000000u;
    uint8_t  u8char[5] = {0};
    size_t   size;
    uint8_t  test_value[] = {0x20, 0x00, 0x00, 0x00, 0x00};

    size = UC_Ucs4ToUtf8(u32char, u8char);

    assert_int_equal(size, 1u);
    assert_memory_equal(u8char, test_value, 5u);
}

void UC_Ucs4ToUtf8_U32zToPointerToNull_NothingSize0(
 __attribute__((unused)) void **state) {
    uint32_t u32char = 0x0000007Au; /* z */
    uint8_t *u8char = NULL;
    size_t   size;

    size = UC_Ucs4ToUtf8(u32char, u8char);

    assert_null(u8char);
    assert_true(size == 0u);
}

void UC_Ucs4ToUtf8_U32zToNull_NothingSize0(
 __attribute__((unused)) void **state) {
    uint32_t u32char = 0x0000007Au; /* z */
    size_t   size;

    size = UC_Ucs4ToUtf8(u32char, NULL);

    assert_true(size == 0u);
}
// NOLINTEND(readability-magic-numbers)

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
