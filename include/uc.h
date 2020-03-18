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

#include <stdint.h>
#include <stdlib.h>

#define UC_VERSION_MAJOR 1
#define UC_VERSION_MINOR 0
#define UC_VERSION_PATCH 0

#define XSTR(A) STR(A)
#define STR(A) #A

#define UC_VERSION \
 XSTR(UC_VERSION_MAJOR) "." XSTR(UC_VERSION_MINOR) "." XSTR(UC_VERSION_PATCH)

#define UC_SIZE_ERROR SIZE_MAX

void UC_GetLinkedVersion(int *verMajor, int *verMinor, int *verPatch);

const char *UC_GetLinkedVersionString(void);

/* count num bytes of UTF8 symbol except leading zero */
size_t UC_Utf8Size(const uint8_t *utf8);

/* convert UCS4 symbol to UTF8 symbol. size - num bytes of UTF8 symbol except
 * leading zero */
size_t UC_Ucs4ToUtf8(uint32_t ucs4, uint8_t *utf8);

/* convert UTF8 symbol to UCS4 symbol */
uint32_t UC_Utf8ToUcs4(const uint8_t *utf8);

/* Copy first symbol from fromUtf8 to toUtf8. Returns num bytes copied */
size_t UC_Utf8Copy(uint8_t *toUtf8, const uint8_t *fromUtf8);

/* Returns upper bytes of UCS4 code. Example: 0x2522 -> 0x25 */
unsigned UC_Ucs4UpperBytes(uint32_t ucs4);

/* Returns lower byte of UCS4 code. Example: 0x2522 -> 0x22 */
unsigned UC_Ucs4LowerByte(uint32_t ucs4);

/* return pointer to next codepoint of UTF8 string */
const uint8_t *UC_StringUtf8NextCodepoint(const uint8_t *stringUtf8);

/* return position of next UTF8 codepoint starting from begin pos */
size_t UC_StringUtf8NextCodepointOffset(const uint8_t *stringUtf8,
 size_t beginPos);

/* return pointer to previous codepoint by given pointer of current UTF8
 * codepoint */
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

#endif
