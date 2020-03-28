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

#define UC_VERSION_MAJOR 0
#define UC_VERSION_MINOR 1
#define UC_VERSION_PATCH 1

#define XSTR(A) STR(A)
#define STR(A) #A

/** Library version macro.
 */
#define UC_VERSION \
 XSTR(UC_VERSION_MAJOR) "." XSTR(UC_VERSION_MINOR) "." XSTR(UC_VERSION_PATCH)

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
 *  @return    size of UTF8 symbol in bytes
 */
size_t UC_Utf8Size(const uint8_t *utf8);

/** Convert UCS4 symbol to UTF8 symbol.
 *
 *  Null termiantor will be appended after last byte of result UTF8 symbol.
 *  Size of destination buffer must be at least 5 bytes: 4 bytes for
 *  UTF8-character and 1 byte for null-terminator.
 *
 *  @param[in]  ucs4 source UCS4 symbol.
 *  @param[out] utf8 destination buffer for one UTF8 symbol.
 *  @return     number of bytes placed in destination buffer except terminating
 *              zero.
 */
size_t UC_Ucs4ToUtf8(uint32_t ucs4, uint8_t *utf8);

/** Convert UTF8 symbol to UCS4 symbol.
 *
 *  Source buffer can contain multiple UTF8 characters. This function will
 *  convert only first character.
 *
 *  @param[in] utf8 source buffer with UTF8 symbol.
 *  @return    UCS4 symbol.
 */
uint32_t UC_Utf8ToUcs4(const uint8_t *utf8);

/** Copy UTF8 symbol.
 *
 *  Copy first UTF8 symbol from source buffer to destination buffer. Null
 *  terminator will be appended after last byte of UTF8 symbol in destination
 *  buffer.
 *
 *  @param[out] toUtf8 destination buffer.
 *  @param[in]  fromUtf8 source buffer with UTF8 symbols.
 *  @return     num bytes actually copied.
 */
size_t UC_Utf8Copy(uint8_t *toUtf8, const uint8_t *fromUtf8);

/** Get upper bytes of UCS4 symbol.
 *
 *  Return 3 upper bytes of UCS4 symbol. Example:
 *  UC_Ucs4UpperBytes(0x00002522u) will return 0x00000025u
 *
 *  @param[in]  ucs4 UCS4 symbol.
 *  @return     3 upper bytes of UCS4 symbol.
 */
unsigned UC_Ucs4UpperBytes(uint32_t ucs4);

/** Get lower byte of UCS4 symbol.
 *
 *  Return one lower byte of UCS4 symbol. Example:
 *  UC_Ucs4UpperBytes(0x00002522u) will return 0x00000022u
 *
 *  @param[in]  ucs4 UCS4 symbol.
 *  @return     one lower byte of UCS4 symbol.
 */
unsigned UC_Ucs4LowerByte(uint32_t ucs4);

/** Return pointer to next character of UTF8 string.
 *
 *  If argument point to null terminator of string then pointer to same
 *  byte will be returned. Comparing argument and result may be used for
 *  checking when reached end of line while you iterate whole string with this
 *  function. In this case returned pointer will be equal argument pointer.
 *
 *  @param[in]  stringUtf8 pointer to symbol (first or not) of UTF8 string.
 *  @return     pointer to next symbol of given string.
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
 *  @param[in]  stringUtf8 pointer to first symbol of UTF8 string.
 *  @param[in]  beginPos offset in bytes to symbol relatively first character
 *              of string.
 *  @return     offset of next symbol in given string.
 */
size_t UC_StringUtf8NextCodepointOffset(const uint8_t *stringUtf8,
 size_t beginPos);

/** Return pointer to previous character in UTF8 string.
 *
 *  There is not way to check if argument pointed to first character in string.
 *  In this case bad things may happen. This is why don't use this function if
 *  you do not know lower bound of string.
 *
 *  @param[in]  stringUtf8 pointer to symbol of UTF8 string.
 *  @return     pointer to previous symbol of given string.
 */
const uint8_t *UC_StringUtf8PreviousCodepoint(const uint8_t *stringUtf8);

/* return position of previous UTF8 codepoint starting from begin pos */
size_t UC_StringUtf8PreviousCodepointOffset(const uint8_t *stringUtf8,
 size_t beginPos);

/* count codepoints of UTF8 string except terminating zero */
size_t UC_StringUtf8Codepoints(const uint8_t *stringUtf8);

/* count size in bytes of UTF8 string with terminating zero */
size_t UC_StringUtf8Size(const uint8_t *stringUtf8);

/* count size in symbols of UCS4 string except terminating zero */
size_t UC_StringUcs4Len(const uint32_t *stringUcs4);

/* count size in bytes of UCS4 string with terminating zero */
size_t UC_StringUcs4Size(const uint32_t *stringUcs4);

/* count size in bytes of UTF8 string after converting from UCS4 string with
 * terminating zero */
size_t UC_StringUcs4PredictUtf8Size(const uint32_t *stringUcs4);

/* convert UCS4 string to UTF8 string
 * Args:
 * stringUcs4 - source UCS4 string
 * stringUtf8 - destination UTF8 string
 * codepoints - pointer to var where result codepoints count will be writed
 * sizeMax - max size in bytes with terminating zero of destination buffer
 * Return:
 * Bytes count (including terminating zero) actually writen to stringUtf8 */
size_t UC_StringUcs4ToUtf8(const uint32_t *stringUcs4, uint8_t *stringUtf8,
 size_t *codepoints, size_t sizeMax);

/* convert UTF8 string to UCS4 string
 * Args:
 * stringUtf8 - source UTF8 string
 * stringUcs4 - destination UCS4 string
 * maxLen - max symbols count which can be writen in destination buffer (not
 * counting terminating zero)
 * Return:
 * Symbols count (without terminating zero) actually writen to stringUcs4 */
size_t UC_StringUtf8ToUcs4(const uint8_t *stringUtf8, uint32_t *stringUcs4,
 size_t maxLen);

#endif /* UC_H */
