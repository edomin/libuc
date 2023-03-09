#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>

#include "uc/uc.h"

// NOLINTBEGIN(readability-magic-numbers)
void UC_Ucs2ToUtf8_U16z_U8zSize1(__attribute__((unused)) void **state) {
    uint16_t u16char = 0x007Au; /* z */
    uint8_t  u8char[5] = {0};
    size_t   size;
    uint8_t  test_value[] = {0x7A, 0x00, 0x00, 0x00, 0x00};

    size = UC_Ucs2ToUtf8(u16char, u8char);

    assert_int_equal(size, 1u);
    assert_memory_equal(u8char, test_value, 5u);
}

void UC_Ucs2ToUtf8_U16cyrillicYu_U8cyrillicYuSize2(
 __attribute__((unused)) void **state) {
    uint16_t u16char = 0x044Eu; /* ю */
    uint8_t  u8char[5] = {0};
    size_t   size;
    uint8_t  test_value[] = {0xD1, 0x8E, 0x00, 0x00, 0x00};

    size = UC_Ucs2ToUtf8(u16char, u8char);

    assert_int_equal(size, 2u);
    assert_memory_equal(u8char, test_value, 5u);
}

void UC_Ucs2ToUtf8_U16chinesseTiger_U8chinesseTigerSize3(
 __attribute__((unused)) void **state) {
    uint16_t u16char = 0x864Eu; /* 虎 */
    uint8_t  u8char[5] = {0};
    size_t   size;
    uint8_t  test_value[] = {0xE8, 0x99, 0x8E, 0x00, 0x00};

    size = UC_Ucs2ToUtf8(u16char, u8char);

    assert_int_equal(size, 3u);
    assert_memory_equal(u8char, test_value, 5u);
}

void UC_Ucs2ToUtf8_U16zToPointerToNull_NothingSize0(
 __attribute__((unused)) void **state) {
    uint16_t u16char = 0x007Au; /* z */
    uint8_t *u8char = NULL;
    size_t   size;

    size = UC_Ucs2ToUtf8(u16char, u8char);

    assert_null(u8char);
    assert_true(size == 0u);
}

void UC_Ucs2ToUtf8_U16zToNull_NothingSize0(
 __attribute__((unused)) void **state) {
    uint16_t u16char = 0x007Au; /* z */
    size_t   size;

    size = UC_Ucs2ToUtf8(u16char, NULL);

    assert_true(size == 0u);
}
// NOLINTEND(readability-magic-numbers)

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_Ucs2ToUtf8_U16z_U8zSize1),
    cmocka_unit_test(UC_Ucs2ToUtf8_U16cyrillicYu_U8cyrillicYuSize2),
    cmocka_unit_test(UC_Ucs2ToUtf8_U16chinesseTiger_U8chinesseTigerSize3),
    cmocka_unit_test(UC_Ucs2ToUtf8_U16zToPointerToNull_NothingSize0),
    cmocka_unit_test(UC_Ucs2ToUtf8_U16zToNull_NothingSize0),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
