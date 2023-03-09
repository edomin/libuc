#include <setjmp.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stddef.h>
#include <stdint.h>

#include <cmocka.h>

#include "uc/uc.h"

// NOLINTBEGIN(readability-magic-numbers)
void UC_StringUcs4ToUtf8_Ucs4null_MaxSize13u_Size1u_Codepoints0u_Utf80x00000000000000000000000000(
 __attribute__((unused)) void **state) {
    uint8_t stringUtf8[13] = {0};
    size_t  codepoints;
    size_t  size = UC_StringUcs4ToUtf8(NULL, stringUtf8, &codepoints, 13u);
    uint8_t test_value[] = {
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00
    };

    assert_int_equal(size, 1u);
    assert_int_equal(codepoints, 0u);
    assert_memory_equal(stringUtf8, test_value, 13u);
}

void UC_StringUcs4ToUtf8_Ucs4hello_Utf8null_MaxSize13u_Size0u_Codepoints0u(
 __attribute__((unused)) void **state) {
    uint32_t ucs4[] = {0x0000041Fu, 0x00000440u, 0x00000438u, 0x00000432u,
     0x00000435u, 0x00000442u, 0x00000000u}; /* Привет */
    size_t   codepoints;
    size_t   size = UC_StringUcs4ToUtf8(ucs4, NULL, &codepoints, 13u);

    assert_int_equal(size, 0u);
    assert_int_equal(codepoints, 0u);
}

void UC_StringUcs4ToUtf8_Ucs4hello_Utf8null_MaxSize0u_Size0u_Codepoints0u(
 __attribute__((unused)) void **state) {
    uint32_t ucs4[] = {0x0000041Fu, 0x00000440u, 0x00000438u, 0x00000432u,
     0x00000435u, 0x00000442u, 0x00000000u}; /* Привет */
    size_t   codepoints;
    size_t   size = UC_StringUcs4ToUtf8(ucs4, NULL, &codepoints, 0u);

    assert_int_equal(size, 0u);
    assert_int_equal(codepoints, 0u);
}

void UC_StringUcs4ToUtf8_Ucs4hello_CodepointsNull_MaxSize13u_Size13u_Codepoints6u_Utf80xD09FD180D0B8D0B2D0B5D18200(
 __attribute__((unused)) void **state) {
    uint32_t ucs4[] = {0x0000041Fu, 0x00000440u, 0x00000438u, 0x00000432u,
     0x00000435u, 0x00000442u, 0x00000000u}; /* Привет */
    uint8_t  stringUtf8[13] = {0};
    size_t   size = UC_StringUcs4ToUtf8(ucs4, stringUtf8, NULL, 13u);
    uint8_t  test_value[] = {
     0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0, 0xB5, 0xD1, 0x82,
     0x00
    };

    assert_int_equal(size, 13u);
    assert_memory_equal(stringUtf8, test_value, 13u);
}

void UC_StringUcs4ToUtf8_Ucs4hello_MaxSize12u_Size11u_Codepoints5u_Utf80xD09FD180D0B8D0B2D0B5D100(
 __attribute__((unused)) void **state) {
    uint32_t ucs4[] = {0x0000041Fu, 0x00000440u, 0x00000438u, 0x00000432u,
     0x00000435u, 0x00000442u, 0x00000000u}; /* Привет */
    uint8_t  stringUtf8[13] = {0};
    size_t   codepoints;
    size_t   size = UC_StringUcs4ToUtf8(ucs4, stringUtf8, &codepoints, 11u);
    uint8_t  test_value[] = {
     0xD0, 0x9F, 0xD1, 0x80, 0xD0, 0xB8, 0xD0, 0xB2, 0xD0, 0xB5, 0x00, 0x00,
     0x00
    };

    assert_int_equal(size, 11u);
    assert_int_equal(codepoints, 5u);
    assert_memory_equal(stringUtf8, test_value, 13u);
}
// NOLINTEND(readability-magic-numbers)

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUcs4ToUtf8_Ucs4null_MaxSize13u_Size1u_Codepoints0u_Utf80x00000000000000000000000000),
    cmocka_unit_test(UC_StringUcs4ToUtf8_Ucs4hello_Utf8null_MaxSize13u_Size0u_Codepoints0u),
    cmocka_unit_test(UC_StringUcs4ToUtf8_Ucs4hello_Utf8null_MaxSize0u_Size0u_Codepoints0u),
    cmocka_unit_test(UC_StringUcs4ToUtf8_Ucs4hello_CodepointsNull_MaxSize13u_Size13u_Codepoints6u_Utf80xD09FD180D0B8D0B2D0B5D18200),
    cmocka_unit_test(UC_StringUcs4ToUtf8_Ucs4hello_MaxSize12u_Size11u_Codepoints5u_Utf80xD09FD180D0B8D0B2D0B5D100),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
