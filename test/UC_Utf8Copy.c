#include "uc.h"
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>

void UC_Utf8Copy_FromZToArrayOfZeroes_0x7A00000000(void **state) {
    uint8_t       toUtf8[5] = {'\0', '\0', '\0', '\0', '\0'};
    const uint8_t fromUtf8[] = {'\x7A', '\0'}; /* z */
    size_t        nbytes = 0xDEADBEEFu;

    nbytes = UC_Utf8Copy(toUtf8, fromUtf8);

    assert_memory_equal(toUtf8, "\x7A\0\0\0\0", 5u);
    assert_true(nbytes == 1u);
}

void UC_Utf8Copy_FromCyrillicYuToArrayOfZeroes_0xD18E000000(void **state) {
    uint8_t       toUtf8[5] = {'\0', '\0', '\0', '\0', '\0'};
    const uint8_t fromUtf8[] = {'\xD1', '\x8E', '\0'}; /* ю */
    size_t        nbytes = 0xDEADBEEFu;

    nbytes = UC_Utf8Copy(toUtf8, fromUtf8);

    assert_memory_equal(toUtf8, "\xD1\x8E\0\0\0", 5u);
    assert_true(nbytes == 2u);
}

void UC_Utf8Copy_FromChinesseTigerToArrayOfZeroes_0xE8998E0000(void **state)
{
    uint8_t       toUtf8[5] = {'\0', '\0', '\0', '\0', '\0'};
    const uint8_t fromUtf8[] = {'\xE8', '\x99', '\x8E', '\0'}; /* 虎 */
    size_t        nbytes = 0xDEADBEEFu;

    nbytes = UC_Utf8Copy(toUtf8, fromUtf8);

    assert_memory_equal(toUtf8, "\xE8\x99\x8E\0\0", 5u);
    assert_true(nbytes == 3u);
}

void UC_Utf8Copy_FromTwoCyrillicYuToArrayOfZeroes_0xD18E000000(void **state)
{
    uint8_t       toUtf8[5] = {'\0', '\0', '\0', '\0', '\0'};
    const uint8_t fromUtf8[] = {'\xD1', '\x8E', '\xD1', '\x8E', '\0'}; /* юю */
    size_t        nbytes = 0xDEADBEEFu;

    nbytes = UC_Utf8Copy(toUtf8, fromUtf8);

    assert_memory_equal(toUtf8, "\xD1\x8E\0\0\0", 5u);
    assert_true(nbytes == 2u);
}

void UC_Utf8Copy_FromTooLongSequenceToArrayOfZeroes_ArrayOfZeroes(void **state)
{
    uint8_t       toUtf8[5] = {'\0', '\0', '\0', '\0', '\0'};
    const uint8_t fromUtf8[] = {'\x80', '\x80', '\x80', '\x80', '\x80', '\x80',
     '\x80', '\0'};
    size_t        nbytes = 0xDEADBEEFu;

    nbytes = UC_Utf8Copy(toUtf8, fromUtf8);

    assert_memory_equal(toUtf8, "\0\0\0\0\0", 5u);
    assert_true(nbytes == 0u);
}

void UC_Utf8Copy_FromNullToArrayOfZeroes_ArrayOfZeroes(void **state) {
    uint8_t toUtf8[5] = {'\0', '\0', '\0', '\0', '\0'};
    size_t  nbytes = 0xDEADBEEFu;

    nbytes = UC_Utf8Copy(toUtf8, NULL);

    assert_memory_equal(toUtf8, "\0\0\0\0\0", 5u);
    assert_true(nbytes == 0u);
}

void UC_Utf8Copy_FromEmptyUtf8CharToArrayOfZeroes_ArrayOfZeroes(void **state) {
    uint8_t       toUtf8[5] = {'\0', '\0', '\0', '\0', '\0'};
    const uint8_t fromUtf8[] = {'\0'};
    size_t        nbytes = 0xDEADBEEFu;

    nbytes = UC_Utf8Copy(toUtf8, fromUtf8);

    assert_memory_equal(toUtf8, "\0\0\0\0\0", 5u);
    assert_true(nbytes == 0u);
}

void UC_Utf8Copy_FromCyrillicYuToNull_Nothing(void **state) {
    const uint8_t fromUtf8[] = {'\xd1', '\x8e', '\0'}; /* ю */
    size_t        nbytes = 0xDEADBEEFu;

    nbytes = UC_Utf8Copy(NULL, fromUtf8);
    assert_true(nbytes == 0u);
}

const struct CMUnitTest testsGroup[] = {
    cmocka_unit_test(UC_Utf8Copy_FromZToArrayOfZeroes_0x7A00000000),
    cmocka_unit_test(
     UC_Utf8Copy_FromCyrillicYuToArrayOfZeroes_0xD18E000000),
    cmocka_unit_test(
     UC_Utf8Copy_FromChinesseTigerToArrayOfZeroes_0xE8998E0000),
    cmocka_unit_test(
     UC_Utf8Copy_FromTwoCyrillicYuToArrayOfZeroes_0xD18E000000),
    cmocka_unit_test(
     UC_Utf8Copy_FromTooLongSequenceToArrayOfZeroes_ArrayOfZeroes),
    cmocka_unit_test(UC_Utf8Copy_FromNullToArrayOfZeroes_ArrayOfZeroes),
    cmocka_unit_test(
     UC_Utf8Copy_FromEmptyUtf8CharToArrayOfZeroes_ArrayOfZeroes),
    cmocka_unit_test(UC_Utf8Copy_FromCyrillicYuToNull_Nothing),
};

int main(void) {
    return cmocka_run_group_tests(testsGroup, NULL, NULL);
}
