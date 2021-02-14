/** \file uc.h
 *  Main header file.
 */

/* For resolving mess when we count terminating zero or not:
 * When we counting symbols in string we do not counting terminating zero.
 * Example is std function strlen. Codepoint is character of nonfixed-wide
 * encoding.
 * When we counting size of string in bytes we counting also terminating zero.
 * Examples:
 * * Length of UCS4 string {0x0000041Fu, 0x00000440u, 0x00000438u, 0x00000432u,
 *   0x00000435u, 0x00000442u, 0x00000000u} is 6. String consist of 6
 *   characters and null terminator.
 * * Size in bytes of UCS4 string {0x0000041Fu, 0x00000440u, 0x00000438u,
 *   0x00000432u, 0x00000435u, 0x00000442u, 0x00000000u} is 28. String consist
 *   of 6 characters and null terminator. Each is 4 bytes wide.
 *   (6 + 1) * 4 = 28
 * * UTF8 string "Привет" have 6 codepoints: "П", "р", "и", "в", "е" and "т".
 *   This string also have null terminator.
 * * Size of string "Привет 1" in bytes is 15. Symbols "П", "р", "и", "в", "е"
 *   and "т" is 2-bytes wide. Symbols " " and "1" is 1-byte wide. Also size of
 *   null terminator of UTF8 string is 1 byte.
 *   2 + 2 + 2 + 2 + 2 + 2 + 1 + 1 + 1 = 15
 * */

#ifndef UC_H
#define UC_H

#include <stddef.h>
#include <stdint.h>

/** Library major version number.
 */
#define UC_VERSION_MAJOR 1
/** Library minor version number.
 */
#define UC_VERSION_MINOR 0
/** Library patch version number.
 */
#define UC_VERSION_PATCH 1

#define XSTR(A) STR(A)
#define STR(A) #A

/** Library dotted version string.
 */
#define UC_VERSION \
 XSTR(UC_VERSION_MAJOR) "." XSTR(UC_VERSION_MINOR) "." XSTR(UC_VERSION_PATCH)

/** Value for indicating error when expect to get size.
 */
#define UC_SIZE_ERROR SIZE_MAX

/** Get library version components as integers.
 *
 *  @param[out] verMajor destination where major version number will be writen.
 *  @param[out] verMinor destination where minor version number will be writen.
 *  @param[out] verPatch destination where patch version number will be writen.
 */
void UC_GetLinkedVersion(int *verMajor, int *verMinor, int *verPatch);

/** Get library version string.
 *
 *  @return version string
 */
const char *UC_GetLinkedVersionString(void);

/** Count size in bytes of UTF8 symbol.
 *
 *  @param[in] utf8 UTF8 symbol.
 *  @return    size of UTF8 symbol in bytes. 0 if pointer to symbol's buffer is
 *             NULL
 */
size_t UC_Utf8Size(const uint8_t *utf8);

/** Convert UCS4 symbol to UTF8 symbol.
 *
 *  Null termiantor will be appended after last byte of result UTF8 symbol.
 *  Size of destination buffer must be at least 5 bytes: 4 bytes for
 *  UTF8-character and 1 byte for null-terminator.
 *
 *  @param[in]  ucs4 source UCS4 symbol. Must not be bigger than 0x001FFFFF.
 *  @param[out] utf8 destination buffer for one UTF8 symbol. If ucs4 argument
 *              is bigger than 0x001FFFFF then bytes 0x20 (space) and 0x00
 *              (null-terminator) will be writen to destination buffer.
 *  @return     number of bytes placed in destination buffer except terminating
 *              zero. If utf8 argument is NULL then this function returns 0.
 */
size_t UC_Ucs4ToUtf8(uint32_t ucs4, uint8_t *utf8);

/** Convert UTF8 symbol to UCS4 symbol.
 *
 *  Source buffer can contain multiple UTF8 characters. This function will
 *  convert only first character.
 *
 *  @param[in] utf8 source buffer with UTF8 symbol.
 *  @return    UCS4 symbol. If utf8 argument points to empty null-terminated
 *             buffer (first byte of buffer is 0x00) or incorrect UTF8 sequence
 *             or utf8 argument is NULL then 0x00000020 (space) will be
 *             returned
 */
uint32_t UC_Utf8ToUcs4(const uint8_t *utf8);

/** Copy UTF8 symbol.
 *
 *  Copy first UTF8 symbol from source buffer to destination buffer. Null
 *  terminator will be appended after last byte of UTF8 symbol in destination
 *  buffer.
 *
 *  @param[out] toUtf8 destination buffer.
 *  @param[in]  fromUtf8 source buffer with UTF8 symbols. If fromUtf8 argument
 *              points to empty null-terminated buffer (first byte of buffer is
 *              0x00) or incorrect UTF8 sequence or utf8 argument is NULL then
 *              only null-termilator will be writen to destination buffer
 *  @return     num bytes actually copied.
 */
size_t UC_Utf8Copy(uint8_t *toUtf8, const uint8_t *fromUtf8);

/** Get upper bytes of UCS4 symbol.
 *
 *  Return 3 upper bytes of UCS4 symbol. Example:
 *  UC_Ucs4UpperBytes(0x00002522u) will return 0x00000025u
 *
 *  @param[in] ucs4 UCS4 symbol.
 *  @return    3 upper bytes of UCS4 symbol.
 */
unsigned UC_Ucs4UpperBytes(uint32_t ucs4);

/** Get lower byte of UCS4 symbol.
 *
 *  Return one lower byte of UCS4 symbol. Example:
 *  UC_Ucs4UpperBytes(0x00002522u) will return 0x00000022u
 *
 *  @param[in] ucs4 UCS4 symbol.
 *  @return    one lower byte of UCS4 symbol.
 */
unsigned UC_Ucs4LowerByte(uint32_t ucs4);

/** Return pointer to next character of UTF8 string.
 *
 *  If argument points to null terminator of string then pointer to same
 *  byte will be returned. Comparing argument and result may be used for
 *  checking when reached end of line while you iterate whole string with this
 *  function. In this case returned pointer will be equal argument pointer.
 *
 *  @param[in] stringUtf8 pointer to symbol (first or not) of UTF8 string.
 *  @return    pointer to next symbol of given string. NULL if stringUtf8 is
 *             NULL. Null terminator if stringUtf8 is last symbol of string or
 *             stringUtf8 is null terminator of string.
 */
const uint8_t *UC_StringUtf8NextCodepoint(const uint8_t *stringUtf8);

/** Return offset to next character of UTF8 string.
 *
 *  Offset argument is offset to current character relatively of pointer to
 *  beginning of the string. Return value is offset to next character.
 *  If character placed by offset is null terminator of string then offset to
 *  same byte will be returned. Comparing argument and result may be used for
 *  checking when reached end of line while you iterate whole string with this
 *  function. In this case returned offset will be equal argument offset.
 *
 *  @param[in] stringUtf8 pointer to first symbol of UTF8 string.
 *  @param[in] beginPos offset in bytes to symbol relatively first character
 *             of string.
 *  @return    offset of next symbol in given string. UC_SIZE_ERROR if
 *             stringUtf8 is NULL. Offset to null terminator of string if
 *             stringUtf8 is last symbol of string or stringUtf8 is
 *             null-terminator of string.
 */
size_t UC_StringUtf8NextCodepointOffset(const uint8_t *stringUtf8,
 size_t beginPos);

/** Return pointer to previous character in UTF8 string.
 *
 *  There is not way to check if argument pointed to first character in string.
 *  In this case bad things may happen. This is why don't use this function if
 *  you do not know lower bound of string.
 *
 *  @param[in] stringUtf8 pointer to symbol of UTF8 string.
 *  @return    pointer to previous symbol of given string. NULL if stringUtf8
 *             is NULL.
 */
const uint8_t *UC_StringUtf8PreviousCodepoint(const uint8_t *stringUtf8);

/** Return offset to previous character of UTF8 string.
 *
 *  Offset argument is offset to current character relatively of pointer to
 *  beginning of the string. Return value is offset to previous character.
 *  There is not way to check lower bound of string. This is why don't use this
 *  function if you do not know bounds of string.
 *
 *  @param[in] stringUtf8 pointer to first symbol of UTF8 string.
 *  @param[in] beginPos offset in bytes to symbol relatively first character
 *             of string.
 *  @return    offset of previous symbol in given string. UC_SIZE_ERROR if
 *             stringUtf8 is NULL.
 */
size_t UC_StringUtf8PreviousCodepointOffset(const uint8_t *stringUtf8,
 size_t beginPos);

/** Get count of characters in UTF8 string.
 *
 *  Return value don't count terminating zero.
 *
 *  @param[in] stringUtf8 pointer to UTF8 string.
 *  @return    count of codepoints in UTF8 string. 0 if stringUtf8 is NULL.
 */
size_t UC_StringUtf8Codepoints(const uint8_t *stringUtf8);

/** Get size of UTF8 string.
 *
 *  Return value also counts 1 byte for terminating zero.
 *
 *  @param[in] stringUtf8 pointer to UTF8 string.
 *  @return    size in bytes of UTF8 string. 0 if stringUtf8 is NULL.
 */
size_t UC_StringUtf8Size(const uint8_t *stringUtf8);

/** Get length of UCS4 string.
 *
 *  Return value don't count terminating zero.
 *
 *  @param[in] stringUcs4 pointer to UCS4 string.
 *  @return    count of symbols in UCS4 string except terminating zero. 0 if
 *             stringUcs4 is NULL.
 */
size_t UC_StringUcs4Len(const uint32_t *stringUcs4);

/** Get size in bytes of USC4 string.
 *
 *  Return value also counts 4 bytes for terminating zero.
 *  Example:
 *  \code{.c}
 *  uint32_t ucs4[] = {
 *      0x0000041Fu, // 'П'  - 4 bytes
 *      0x00000440u, // 'р'  - 4 bytes
 *      0x00000438u, // 'и'  - 4 bytes
 *      0x00000432u, // 'в'  - 4 bytes
 *      0x00000435u, // 'е'  - 4 bytes
 *      0x00000442u, // 'т'  - 4 bytes
 *      0x00000000u  // '\0' - 4 bytes
 *  }                // --------------
 *                   //       28 bytes overall
 *  \endcode
 *  Each character of this UCS4 string is 4-bytes wide. Null terminator also
 *  4 bytes. Value returned by function UC_StringUcs4Size with pointer to
 *  string above as argument is 28.
 *
 *  @param[in] stringUcs4 pointer to UCS4 string.
 *  @return    size in bytes of UCS4 string. 0 if stringUcs4 is NULL
 */
size_t UC_StringUcs4Size(const uint32_t *stringUcs4);

/** Get size in bytes of UTF8 string converted from UCS4 string.
 *
 *  This function return size in bytes of UTF8 string converted from UCS4
 *  string given in argument of this function. This function don't do actual
 *  conversion. Return value also counts terminating zero.
 *
 *  @param[in] stringUcs4 pointer to UCS4 string.
 *  @return    size in bytes of UCS8 string. 0 if stringUcs4 is NULL.
 */
size_t UC_StringUcs4PredictUtf8Size(const uint32_t *stringUcs4);

/** Convert UCS4 string to UTF8 string.
 *
 *  Size of result string will not bigger than sizeMax.
 *
 *  @param[in]  stringUcs4 source UCS4 string.
 *  @param[out] stringUtf8 destination UTF8 string.
 *  @param[out] codepoints pointer to var where result codepoints count will be
 *              writed. 0 will be writen if stringUcs4 is empty or stringUtf8
 *              is NULL.
 *  @param[in]  sizeMax max size in bytes with terminating zero of destination
 *              buffer.
 *  @return     Bytes count (including terminating zero) actually writen to
 *              stringUtf8. 1 if stringUcs4 is NUll (null term only will be
 *              writen in destination buffer). 0 if stringUtf8 is NULL.
 */
size_t UC_StringUcs4ToUtf8(const uint32_t *stringUcs4, uint8_t *stringUtf8,
 size_t *codepoints, size_t sizeMax);

/** Convert UTF8 string to UCS4 string.
 *
 *  Length of result string will not bigger than maxLen.
 *
 *  @param[in]  stringUtf8 source UTF8 string.
 *  @param[out] stringUcs4 destination UCS4 string.
 *  @param[in]  maxLen max symbols count which can be writen in destination
 *              buffer (not counting terminating zero).
 *  @return     Symbols count (without terminating zero) actually writen to
 *              stringUcs4. 0 if stringUtf8 or stringUcs4 is NULL.
 */
size_t UC_StringUtf8ToUcs4(const uint8_t *stringUtf8, uint32_t *stringUcs4,
 size_t maxLen);

#endif /* UC_H */
