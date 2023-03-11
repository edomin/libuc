#include "uc/uc.h"

#include "dclspc.h"

#define UC_ONE_BYTE_SHIFT 8u
#define UC_ONE_BYTE_MASK  0xFFu

void UC_GetLinkedVersion(int *verMajor, int *verMinor, int *verPatch) {
    if (verMajor != NULL)
        *verMajor = UC_VERSION_MAJOR;
    if (verMinor != NULL)
        *verMinor = UC_VERSION_MINOR;
    if (verPatch != NULL)
        *verPatch = UC_VERSION_PATCH;
}

UC_ATTR(const) const char *UC_GetLinkedVersionString(void) {
    return UC_VERSION;
}

UC_ATTR(pure) size_t UC_Utf8Size(const uint8_t *utf8) {
    size_t i;

    if (utf8 == NULL)
        return 0u;

    for (i = 0u; i < UC_UTF8_CODEPOINT_SIZE_MAX; i++) {
        if (utf8[i] == 0x00u)
            return i;
        if (((utf8[i] & 0xC0u) != 0x80u) && (i != 0u))
            return i;
    }

    return 0u;
}

size_t UC_Ucs2ToUtf8(uint16_t ucs2, uint8_t *utf8) {
    if (utf8 == NULL)
        return 0u;

    if (ucs2 <= 0x007Fu) {
        utf8[0u] = (ucs2 & 0x7Fu);
        utf8[1u] = 0x00u;
        return 1u;
    }
    if (ucs2 <= 0x07FFu) {
        utf8[0u] = (uint8_t)((ucs2 & 0x7C0u) >> 6u) | 0xC0u;
        utf8[1u] = (uint8_t)((ucs2 & 0x3Fu) | 0x80u);
        utf8[2u] = 0x00u;
        return 2u;
    }

    utf8[0u] = (uint8_t)((ucs2 & 0xF000u) >> 12u) | 0xE0u;
    utf8[1u] = (uint8_t)((ucs2 & 0xFC0u) >> 6u) | 0x80u;
    utf8[2u] = (uint8_t)((ucs2 & 0x3Fu) | 0x80u);
    utf8[3u] = 0x00u;

    return 3u;

}

size_t UC_Ucs4ToUtf8(uint32_t ucs4, uint8_t *utf8) {
    if (utf8 == NULL)
        return 0u;

    if (ucs4 <= 0x0000007Fu) {
        utf8[0u] = ucs4 & 0x7Fu;
        utf8[1u] = 0x00u;
        return 1u;
    }
    if (ucs4 <= 0x000007FFu) {
        utf8[0u] = (uint8_t)((ucs4 & 0x7C0u) >> 6u) | 0xC0u;
        utf8[1u] = (uint8_t)((ucs4 & 0x3Fu) | 0x80u);
        utf8[2u] = 0x00u;
        return 2u;
    }
    if (ucs4 <= 0x0000FFFFu) {
        utf8[0u] = (uint8_t)((ucs4 & 0xF000u) >> 12u) | 0xE0u;
        utf8[1u] = (uint8_t)((ucs4 & 0xFC0u) >> 6u) | 0x80u;
        utf8[2u] = (uint8_t)((ucs4 & 0x3Fu) | 0x80u);
        utf8[3u] = 0x00u;
        return 3u;
    }
    if (ucs4 <= 0x001FFFFFu) {
        utf8[0u] = (uint8_t)((ucs4 & 0x1C0000u) >> 18u) | 0xF0u;
        utf8[1u] = (uint8_t)((ucs4 & 0x3F000u) >> 12u) | 0x80u;
        utf8[2u] = (uint8_t)((ucs4 & 0xFC0u) >> 6u) | 0x80u;
        utf8[3u] = (uint8_t)((ucs4 & 0x3Fu) | 0x80u);
        utf8[4u] = 0x00u;
        return 4u;
    }

    utf8[0u] = UC_UNKNOWN_SYMBOL_PLACEHOLDER;
    utf8[1u] = 0x00u;

    return 1u;
}

UC_ATTR(pure) uint16_t UC_Utf8ToUcs2(const uint8_t *utf8) {
    size_t size = UC_Utf8Size(utf8);

    if (size == 1u)
        return ((uint16_t)utf8[0u] & 0x7Fu);
    if (size == 2u)
        return (uint16_t)(((utf8[0u] & 0x1Fu) << 6u) | (utf8[1u] & 0x3Fu));
    if (size == 3u) {
        return (uint16_t)(((utf8[0u] & 0xFu) << 12u) |
         ((utf8[1u] & 0x3Fu) << 6u) |
         (utf8[2u] & 0x3Fu));
    }

    return UC_UNKNOWN_SYMBOL_PLACEHOLDER;
}

UC_ATTR(pure) uint32_t UC_Utf8ToUcs4(const uint8_t *utf8) {
    size_t size = UC_Utf8Size(utf8);

    if (size == 1u)
        return (utf8[0u] & 0x7Fu);
    if (size == 2u)
        return ((utf8[0u] & 0x1Fu) << 6u) | (utf8[1u] & 0x3Fu);
    if (size == 3u) {
        return ((utf8[0u] & 0xFu) << 12u) |
         ((utf8[1u] & 0x3Fu) << 6u) |
         (utf8[2u] & 0x3Fu);
    }
    if (size == 4u) {
        return ((utf8[0u] & 0x7u) << 18u) |
         ((utf8[1u] & 0x3Fu) << 12u) |
         ((utf8[2u] & 0x3Fu) << 6u) |
         (utf8[3u] & 0x3Fu);
    }

    return UC_UNKNOWN_SYMBOL_PLACEHOLDER;
}

size_t UC_Utf8Copy(uint8_t *toUtf8, const uint8_t *fromUtf8) {
    size_t i;
    size_t size = UC_Utf8Size(fromUtf8);

    if (toUtf8 == NULL)
        return 0u;

    for (i = 0u; i < size; i++)
        toUtf8[i] = fromUtf8[i];

    toUtf8[size] = 0u;

    return size;
}

UC_ATTR(const) uint_least24_t UC_Ucs4UpperBytes(uint32_t ucs4) {
    return ucs4 >> UC_ONE_BYTE_SHIFT;
}

UC_ATTR(const) unsigned UC_Ucs4LowerByte(uint32_t ucs4) {
    return ucs4 & UC_ONE_BYTE_MASK;
}

UC_ATTR(pure) const uint8_t *UC_StringUtf8NextCodepoint(
 const uint8_t *stringUtf8) {
    const uint8_t *pos = stringUtf8;

    if (stringUtf8 == NULL)
        return NULL;

    if (*stringUtf8 == '\0')
        return stringUtf8;

    do
        pos++;
    while ((pos[0u] & 0xC0u) == 0x80u);

    return pos;
}

UC_ATTR(pure) size_t UC_StringUtf8NextCodepointOffset(
 const uint8_t *stringUtf8, size_t beginPos) {
    size_t pos = beginPos;

    if (stringUtf8 == NULL)
        return UC_SIZE_ERROR;

    if (stringUtf8[beginPos] == '\0')
        return beginPos;

    do
        pos++;
    while ((stringUtf8[pos] & 0xC0u) == 0x80u);

    return pos;
}

UC_ATTR(pure) const uint8_t *UC_StringUtf8PreviousCodepoint(
 const uint8_t *stringUtf8) {
    const uint8_t *pos = stringUtf8;

    if (stringUtf8 == NULL)
        return NULL;

    do
        pos--;
    while ((pos[0u] & 0xC0u) == 0x80u);

    return pos;
}

UC_ATTR(pure) size_t UC_StringUtf8PreviousCodepointOffset(
 const uint8_t *stringUtf8, size_t beginPos) {
    size_t pos = beginPos;

    if (stringUtf8 == NULL)
        return UC_SIZE_ERROR;

    do
        pos--;
    while ((stringUtf8[pos] & 0xC0u) == 0x80u);

    return pos;
}

UC_ATTR(pure) size_t UC_StringUtf8Codepoints(
 const uint8_t *stringUtf8) {
    size_t codepoints = 0u;
    size_t currentPos = 0u;

    if (stringUtf8 == NULL)
        return 0u;

    while (stringUtf8[currentPos] != 0x00u) {
        currentPos = UC_StringUtf8NextCodepointOffset(stringUtf8, currentPos);
        if (currentPos == UC_SIZE_ERROR)
            return 0u;
        codepoints++;
    }

    return codepoints;
}

UC_ATTR(pure) size_t UC_StringUtf8Size(const uint8_t *stringUtf8) {
    size_t currentPos = 0u;

    if (stringUtf8 == NULL)
        return 0u;

    do
        currentPos++;
    while (stringUtf8[currentPos] != 0x00u);

    return ++currentPos;
}

UC_ATTR(pure) size_t UC_StringUcs2Len(const uint16_t *stringUcs2) {
    size_t currentPos = 0u;

    if (stringUcs2 == NULL)
        return 0u;

    while (stringUcs2[currentPos] != 0x0000u)
        currentPos++;

    return currentPos;
}

UC_ATTR(pure) size_t UC_StringUcs4Len(const uint32_t *stringUcs4) {
    size_t currentPos = 0u;

    if (stringUcs4 == NULL)
        return 0u;

    while (stringUcs4[currentPos] != 0x00000000u)
        currentPos++;

    return currentPos;
}

UC_ATTR(pure) size_t UC_StringUcs2Size(const uint16_t *stringUcs2) {
    size_t currentPos = 0u;

    if (stringUcs2 == NULL)
        return 0u;

    do
        currentPos++;
    while (stringUcs2[currentPos] != 0x0000u);

    return (currentPos + 1) * sizeof(uint16_t);
}

UC_ATTR(pure) size_t UC_StringUcs4Size(const uint32_t *stringUcs4) {
    size_t currentPos = 0u;

    if (stringUcs4 == NULL)
        return 0u;

    do
        currentPos++;
    while (stringUcs4[currentPos] != 0x00000000u);

    return (currentPos + 1) * sizeof(uint32_t);
}

UC_ATTR(pure) size_t UC_StringUcs2PredictUtf8Size(const uint16_t *stringUcs2) {
    uint8_t utf8Buf[UC_UTF8_CODEPOINT_SIZE_MAX];
    size_t  ucs2Len = UC_StringUcs2Len(stringUcs2);
    size_t  utf8Pos = 0u;
    size_t  i;

    if (stringUcs2 == NULL)
        return 0u;

    for (i = 0u; i < ucs2Len; i++)
        utf8Pos += UC_Ucs2ToUtf8(stringUcs2[i], utf8Buf);

    return ++utf8Pos;
}

UC_ATTR(pure) size_t UC_StringUcs4PredictUtf8Size(const uint32_t *stringUcs4) {
    uint8_t utf8Buf[UC_UTF8_CODEPOINT_SIZE_MAX];
    size_t  ucs4Len = UC_StringUcs4Len(stringUcs4);
    size_t  utf8Pos = 0u;
    size_t  i;

    if (stringUcs4 == NULL)
        return 0u;

    for (i = 0u; i < ucs4Len; i++)
        utf8Pos += UC_Ucs4ToUtf8(stringUcs4[i], utf8Buf);

    return ++utf8Pos;
}

size_t UC_StringUcs2ToUtf8(const uint16_t *stringUcs2, uint8_t *stringUtf8,
 size_t *codepoints, size_t sizeMax) {
    uint8_t utf8Buf[UC_UTF8_CODEPOINT_SIZE_MAX];
    size_t  ucs2Len = UC_StringUcs2Len(stringUcs2);
    size_t  utf8Pos = 0u;
    size_t  utf8Size;
    size_t  i;

    if (codepoints != NULL)
        *codepoints = 0u;

    if (stringUtf8 == NULL || sizeMax == 0)
        return 0u;

    if (stringUcs2 == NULL) {
        stringUtf8[0u] = 0x00u;

        return 1u;
    }

    for (i = 0u; i < ucs2Len; i++) {
        size_t j;

        utf8Size = UC_Ucs2ToUtf8(stringUcs2[i], utf8Buf);

        if (utf8Pos + utf8Size + 1 > sizeMax)
            break;

        for (j = 0u; j < utf8Size; j++)
            stringUtf8[utf8Pos + j] = utf8Buf[j];

        utf8Pos += utf8Size;

        if (codepoints != NULL)
            (*codepoints)++;
    }

    stringUtf8[utf8Pos] = 0x00u;

    return ++utf8Pos;
}

size_t UC_StringUcs4ToUtf8(const uint32_t *stringUcs4, uint8_t *stringUtf8,
 size_t *codepoints, size_t sizeMax) {
    uint8_t utf8Buf[UC_UTF8_CODEPOINT_SIZE_MAX];
    size_t  ucs4Len = UC_StringUcs4Len(stringUcs4);
    size_t  utf8Pos = 0u;
    size_t  utf8Size;
    size_t  i;

    if (codepoints != NULL)
        *codepoints = 0u;

    if (stringUtf8 == NULL || sizeMax == 0)
        return 0u;

    if (stringUcs4 == NULL) {
        stringUtf8[0u] = 0x00u;

        return 1u;
    }

    for (i = 0u; i < ucs4Len; i++) {
        size_t j;

        utf8Size = UC_Ucs4ToUtf8(stringUcs4[i], utf8Buf);

        if (utf8Pos + utf8Size + 1 > sizeMax)
            break;

        for (j = 0u; j < utf8Size; j++)
            stringUtf8[utf8Pos + j] = utf8Buf[j];

        utf8Pos += utf8Size;

        if (codepoints != NULL)
            (*codepoints)++;
    }

    stringUtf8[utf8Pos] = 0x00u;

    return ++utf8Pos;
}

size_t UC_StringUtf8ToUcs2(const uint8_t *stringUtf8, uint16_t *stringUcs2,
 size_t maxLen) {
    size_t         codepoints = UC_StringUtf8Codepoints(stringUtf8);
    const uint8_t *currentPos = stringUtf8;
    size_t         i;

    codepoints = (codepoints < maxLen) ? codepoints : maxLen;

    if (stringUcs2 == NULL)
        return 0u;

    if (stringUtf8 == NULL) {
        stringUcs2[0u] = 0x0000u;

        return 0u;
    }

    for (i = 0u; i < codepoints; i++) {
        stringUcs2[i] = UC_Utf8ToUcs2(currentPos);
        currentPos = UC_StringUtf8NextCodepoint(currentPos);
    }

    stringUcs2[codepoints] = 0x0000u;

    return codepoints;
}

size_t UC_StringUtf8ToUcs4(const uint8_t *stringUtf8, uint32_t *stringUcs4,
 size_t maxLen) {
    size_t         codepoints = UC_StringUtf8Codepoints(stringUtf8);
    const uint8_t *currentPos = stringUtf8;
    size_t         i;

    codepoints = (codepoints < maxLen) ? codepoints : maxLen;

    if (stringUcs4 == NULL)
        return 0u;

    if (stringUtf8 == NULL) {
        stringUcs4[0u] = 0x00000000u;

        return 0u;
    }

    for (i = 0u; i < codepoints; i++) {
        stringUcs4[i] = UC_Utf8ToUcs4(currentPos);
        currentPos = UC_StringUtf8NextCodepoint(currentPos);
    }

    stringUcs4[codepoints] = 0x00000000u;

    return codepoints;
}
