#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_StringUcs4ToUtf8_Ucs4null_MaxSize13u_Size1u_Codepoints0u_Utf80x00000000000000000000000000(void **state) {
    uint8_t stringUtf8[13] = {0};
    size_t  codepoints;
    size_t  size = UC_StringUcs4ToUtf8(NULL, stringUtf8, &codepoints, 12u);

    assert_memory_equal(stringUtf8, "\0\0\0\0\0\0\0\0\0\0\0\0\0", 13u);
    assert_true(size == 1u);
    assert_true(codepoints == 0u);
}

void UC_StringUcs4ToUtf8_Ucs4hello_Utf8null_MaxSize13u_Size0u_Codepoints0u(
 void **state) {
    uint32_t ucs4[] = {0x0000041Fu, 0x00000440u, 0x00000438u, 0x00000432u,
     0x00000435u, 0x00000442u, 0x00000000u}; /* Привет */
    size_t   codepoints;
    size_t   size = UC_StringUcs4ToUtf8(ucs4, NULL, &codepoints, 12u);

    assert_true(size == 0u);
    assert_true(codepoints == 0u);
}

void UC_StringUcs4ToUtf8_Ucs4hello_CodepointsNull_MaxSize13u_Size13u_Codepoints6u_Utf80xD09FD180D0B8D0B2D0B5D18200(void **state) {
    uint32_t ucs4[] = {0x0000041Fu, 0x00000440u, 0x00000438u, 0x00000432u,
     0x00000435u, 0x00000442u, 0x00000000u}; /* Привет */
    uint8_t  stringUtf8[13] = {0};
    size_t   size = UC_StringUcs4ToUtf8(ucs4, stringUtf8, NULL, 13u);

    assert_memory_equal(stringUtf8,
     "\xD0\x9F\xD1\x80\xD0\xB8\xD0\xB2\xD0\xB5\xD1\x82\0", 13u);
    assert_true(size == 13u);
}

void UC_StringUcs4ToUtf8_Ucs4hello_MaxSize12u_Size11u_Codepoints5u_Utf80xD09FD180D0B8D0B2D0B5D100(void **state) {
    uint32_t ucs4[] = {0x0000041Fu, 0x00000440u, 0x00000438u, 0x00000432u,
     0x00000435u, 0x00000442u, 0x00000000u}; /* Привет */
    uint8_t  stringUtf8[13] = {0};
    size_t   codepoints;
    size_t   size = UC_StringUcs4ToUtf8(ucs4, stringUtf8, &codepoints, 11u);

    assert_memory_equal(stringUtf8,
     "\xD0\x9F\xD1\x80\xD0\xB8\xD0\xB2\xD0\xB5\0\0\0", 13u);
    assert_true(size == 11u);
    assert_true(codepoints == 5u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_StringUcs4ToUtf8_Ucs4null_MaxSize13u_Size1u_Codepoints0u_Utf80x00000000000000000000000000),
    cmocka_unit_test(UC_StringUcs4ToUtf8_Ucs4hello_Utf8null_MaxSize13u_Size0u_Codepoints0u),
    cmocka_unit_test(UC_StringUcs4ToUtf8_Ucs4hello_CodepointsNull_MaxSize13u_Size13u_Codepoints6u_Utf80xD09FD180D0B8D0B2D0B5D18200),
    cmocka_unit_test(UC_StringUcs4ToUtf8_Ucs4hello_MaxSize12u_Size11u_Codepoints5u_Utf80xD09FD180D0B8D0B2D0B5D100),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
