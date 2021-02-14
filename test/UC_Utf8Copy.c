#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "uc/uc.h"

void UC_Utf8Copy_FromZToArrayOfZeroes_0x7A00000000(
 __attribute__((unused)) void **state) {
    uint8_t       toUtf8[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    const uint8_t fromUtf8[] = {0x7A, 0x00}; /* z */
    size_t        nbytes = 0xDEADBEEFu;
    uint8_t       test_value[] = {0x7A, 0x00, 0x00, 0x00, 0x00};

    nbytes = UC_Utf8Copy(toUtf8, fromUtf8);

    assert_int_equal(nbytes, 1u);
    assert_memory_equal(toUtf8, test_value, 5u);
}

void UC_Utf8Copy_FromCyrillicYuToArrayOfZeroes_0xD18E000000(
 __attribute__((unused)) void **state) {
    uint8_t       toUtf8[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    const uint8_t fromUtf8[] = {0xD1, 0x8E, 0x00}; /* ю */
    size_t        nbytes = 0xDEADBEEFu;
    uint8_t       test_value[] = {0xD1, 0x8E, 0x00, 0x00, 0x00};

    nbytes = UC_Utf8Copy(toUtf8, fromUtf8);

    assert_int_equal(nbytes, 2u);
    assert_memory_equal(toUtf8, test_value, 5u);
}

void UC_Utf8Copy_FromChinesseTigerToArrayOfZeroes_0xE8998E0000(
 __attribute__((unused)) void **state)
{
    uint8_t       toUtf8[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    const uint8_t fromUtf8[] = {0xE8, 0x99, 0x8E, 0x00}; /* 虎 */
    size_t        nbytes = 0xDEADBEEFu;
    uint8_t       test_value[] = {0xE8, 0x99, 0x8E, 0x00, 0x00};

    nbytes = UC_Utf8Copy(toUtf8, fromUtf8);

    assert_int_equal(nbytes, 3u);
    assert_memory_equal(toUtf8, test_value, 5u);
}

void UC_Utf8Copy_FromTwoCyrillicYuToArrayOfZeroes_0xD18E000000(
 __attribute__((unused)) void **state) {
    uint8_t       toUtf8[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    const uint8_t fromUtf8[] = {0xD1, 0x8E, 0xD1, 0x8E, 0x00}; /* юю */
    size_t        nbytes = 0xDEADBEEFu;
    uint8_t       test_value[] = {0xD1, 0x8E, 0x00, 0x00, 0x00};

    nbytes = UC_Utf8Copy(toUtf8, fromUtf8);

    assert_int_equal(nbytes, 2u);
    assert_memory_equal(toUtf8, test_value, 5u);
}

void UC_Utf8Copy_FromTooLongSequenceToArrayOfZeroes_ArrayOfZeroes(
 __attribute__((unused)) void **state) {
    uint8_t       toUtf8[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    const uint8_t fromUtf8[] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00};
    size_t        nbytes = 0xDEADBEEFu;
    uint8_t       test_value[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    nbytes = UC_Utf8Copy(toUtf8, fromUtf8);

    assert_int_equal(nbytes, 0u);
    assert_memory_equal(toUtf8, test_value, 5u);
}

void UC_Utf8Copy_FromNullToArrayOfZeroes_ArrayOfZeroes(
 __attribute__((unused)) void **state) {
    uint8_t toUtf8[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    size_t  nbytes = 0xDEADBEEFu;
    uint8_t       test_value[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    nbytes = UC_Utf8Copy(toUtf8, NULL);

    assert_int_equal(nbytes, 0u);
    assert_memory_equal(toUtf8, test_value, 5u);
}

void UC_Utf8Copy_FromEmptyUtf8CharToArrayOfZeroes_ArrayOfZeroes(
 __attribute__((unused)) void **state) {
    uint8_t       toUtf8[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    const uint8_t fromUtf8[] = {0x00};
    size_t        nbytes = 0xDEADBEEFu;
    uint8_t       test_value[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    nbytes = UC_Utf8Copy(toUtf8, fromUtf8);

    assert_int_equal(nbytes, 0u);
    assert_memory_equal(toUtf8, test_value, 5u);
}

void UC_Utf8Copy_FromCyrillicYuToNull_Nothing(
 __attribute__((unused)) void **state) {
    const uint8_t fromUtf8[] = {0xD1, 0x8E, 0x00}; /* ю */
    size_t        nbytes = 0xDEADBEEFu;

    nbytes = UC_Utf8Copy(NULL, fromUtf8);

    assert_int_equal(nbytes, 0u);
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
