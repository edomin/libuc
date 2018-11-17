#ifndef UCONVERT_H
#define UCONVERT_H

#include <stdlib.h>
#include <stdint.h>

#define UC_VERSION_MAJOR 1
#define UC_VERSION_MINOR 0
#define UC_VERSION_PATCH 0

#define XSTR(A) STR(A)
#define STR(A) #A

#define UC_VERSION \
 XSTR(UC_VERSION_MAJOR) "." XSTR(UC_VERSION_MINOR) "." XSTR(UC_VERSION_PATCH)

void UC_GetLinkedVersion(int *verMajor, int *verMinor, int *verPatch);

const char *UC_GetLinkedVersionString(void);

/* count num bytes of UTF8 symbol except leading zero */
size_t UC_Utf8Size(const uint8_t *utf8);

/* Create UTF8 symbol */
uint8_t *UC_CreateUtf8(void);

/* Create UTF8 symbol */
uint8_t *UC_CreateUtf8FromChar(const char *symbol);

/* Delete UTF8 symbol */
void UC_DeleteUtf8(uint8_t **utf8);

/* convert UCS4 symbol to UTF8 symbol. size - num bytes of UTF8 symbol except
 * leading zero */
void UC_Ucs4ToUtf8(uint32_t ucs4, uint8_t **utf8, size_t *size);

/* convert UTF8 symbol to UCS4 symbol */
uint32_t UC_Utf8ToUcs4(const uint8_t *utf8);

/* Copy first symbol from fromUtf8 to toUtf8 */
void UC_Utf8Copy(uint8_t *toUtf8, const uint8_t *fromUtf8);

/* Returns upper bytes of UCS4 code. Example: 0x2522 -> 0x25 */
unsigned UC_Ucs4UpperBytes(uint32_t ucs4);

/* Returns lower byte of UCS4 code. Example: 0x2522 -> 0x22 */
unsigned UC_Ucs4LowerByte(uint32_t ucs4);

/* return pointer to next codepoint of UTF8 string */
uint8_t *UC_StringUtf8NextCodepoint(uint8_t *stringUtf8);

/* return position of next UTF8 codepoint starting from begin pos */
size_t UC_StringUtf8NextCodepointOffset(uint8_t *stringUtf8, size_t beginPos);

/* return pointer to previous codepoint by given pointer of current UTF8
 * codepoint */
uint8_t *UC_StringUtf8PreviousCodepoint(uint8_t *stringUtf8);

/* return position of previous UTF8 codepoint starting from begin pos */
size_t UC_StringUtf8PreviousCodepointOffset(uint8_t *stringUtf8,
 size_t beginPos);

/* count codepoints of UTF8 string */
size_t UC_StringUtf8Codepoints(uint8_t *stringUtf8);

/* count size in bytes of UTF8 string */
size_t UC_StringUtf8Size(uint8_t *stringUtf8);

/* count size in symbols of UCS4 string */
size_t UC_StringUcs4Len(uint32_t *stringUcs4);

/* count size in bytes of UCS4 string */
size_t UC_StringUcs4Size(uint32_t *stringUcs4);

/* convert UCS4 string to UTF8 string */
void UC_StringUcs4ToUtf8(uint32_t *stringUcs4, uint8_t **stringUtf8,
 size_t *codepoints, size_t *size);

/* convert UTF8 string to UCS4 string */
void UC_StringUtf8ToUcs4(uint8_t *stringUtf8, uint32_t **stringUcs4,
 size_t *len);

#endif
