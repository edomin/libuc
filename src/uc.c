#include "uc.h"

void UC_GetLinkedVersion(int *verMajor, int *verMinor, int *verPatch) {
    if (verMajor != NULL)
        *verMajor = UC_VERSION_MAJOR;
    if (verMinor != NULL)
        *verMinor = UC_VERSION_MINOR;
    if (verPatch != NULL)
        *verPatch = UC_VERSION_PATCH;
}

const char *UC_GetLinkedVersionString(void) {
    return UC_VERSION;
}

size_t UC_Utf8Size(const uint8_t *utf8) {
    size_t i;

    if (utf8 == NULL)
        return 0u;

    for (i = 0u; i < 5u; i++) {
        if (utf8[i] == 0x00u)
            return i;
        if (((utf8[i] & 0xC0u) != 0x80u) && (i != 0u))
            return i;
    }

    return 0u;
}

uint8_t *UC_CreateUtf8(void) {
    return malloc(sizeof(uint8_t) * 5u);
}

uint8_t *UC_CreateUtf8FromChar(const char *symbol) {
    uint8_t *newSymbol = UC_CreateUtf8();

    UC_Utf8Copy(newSymbol, (const uint8_t *)symbol);

    return newSymbol;
}

void UC_DeleteUtf8(uint8_t **utf8) {
    if (*utf8 != NULL) {
        free(*utf8);
        *utf8 = NULL;
    }
}

void UC_Ucs4ToUtf8(uint32_t ucs4, uint8_t **utf8, size_t *size) {
    if (utf8 == NULL) {
        if (size != NULL)
            *size = 0u;
        return;
    }

    if (ucs4 <= 0x0000007Fu) {
        (*utf8)[0] = (ucs4 & 0x7Fu);
        (*utf8)[1] = 0x00u;
        if (size != NULL)
            *size = 1u;
    } else if (ucs4 <= 0x000007FFu) {
        (*utf8)[0] = ((ucs4 & 0x7C0u) >> 6u) | 0xC0u;
        (*utf8)[1] = (ucs4 & 0x3Fu) | 0x80u;
        (*utf8)[2] = 0x00u;
        if (size != NULL)
            *size = 2u;
    } else if (ucs4 <= 0x0000FFFFu) {
        (*utf8)[0] = ((ucs4 & 0xF000u) >> 12u) | 0xE0u;
        (*utf8)[1] = ((ucs4 & 0xFC0u) >> 6u) | 0x80u;
        (*utf8)[2] = (ucs4 & 0x3Fu) | 0x80u;
        (*utf8)[3] = 0x00u;
        if (size != NULL)
            *size = 3u;
    } else if (ucs4 <= 0x001FFFFFu) {
        (*utf8)[0] = ((ucs4 & 0x1C0000u) >> 18u) | 0xF0u;
        (*utf8)[1] = ((ucs4 & 0x3F000u) >> 12u) | 0x80u;
        (*utf8)[2] = ((ucs4 & 0xFC0u) >> 6u) | 0x80u;
        (*utf8)[3] = (ucs4 & 0x3Fu) | 0x80u;
        (*utf8)[4] = 0x00u;
        if (size != NULL)
            *size = 4u;
    } else {
        (*utf8)[0] = 0x20u;
        (*utf8)[1] = 0x00u;
        if (size != NULL)
            *size = 1u;
    }
}

uint32_t UC_Utf8ToUcs4(const uint8_t *utf8) {
    size_t size = UC_Utf8Size(utf8);

    if (size == 1u)
        return ((uint32_t)utf8[0] & 0x7Fu);
    else if (size == 2u) {
        return (((uint32_t)utf8[0] & 0x1Fu) << 6u) |
         ((uint32_t)utf8[1] & 0x3Fu);
    } else if (size == 3u) {
        return (((uint32_t)utf8[0] & 0xFu) << 12u) |
         (((uint32_t)utf8[1] & 0x3Fu) << 6u) |
         ((uint32_t)utf8[2] & 0x3Fu);
    } else if (size == 4u) {
        return (((uint32_t)utf8[0u] & 0x7u) << 18u) |
         (((uint32_t)utf8[1u] & 0x3Fu) << 12u) |
         (((uint32_t)utf8[2u] & 0x3Fu) << 6u) |
         ((uint32_t)utf8[3u] & 0x3Fu);
    } else
        return 0x00000020u;
}

void UC_Utf8Copy(uint8_t *toUtf8, const uint8_t *fromUtf8) {
    size_t i;
    size_t size = UC_Utf8Size(fromUtf8);

    for (i = 0u; i < size; i++)
        toUtf8[i] = fromUtf8[i];

    toUtf8[size] = 0u;
}

unsigned UC_Ucs4UpperBytes(uint32_t ucs4) {
    return ucs4 >> 8;
}

unsigned UC_Ucs4LowerByte(uint32_t ucs4) {
    return ucs4 & 0xFFu;
}

uint8_t *UC_StringUtf8NextCodepoint(uint8_t *stringUtf8) {
    uint8_t *pos = stringUtf8;

    if (stringUtf8 == NULL)
        return NULL;

    do
        pos++;
    while ((pos[0] & 0xC0u) == 0x80u);

    return pos;
}

size_t UC_StringUtf8NextCodepointOffset(uint8_t *stringUtf8, size_t beginPos) {
    size_t pos = beginPos;

    if (stringUtf8 == NULL)
        return 0u;

    do
        pos++;
    while ((stringUtf8[pos] & 0xC0u) == 0x80u);

    return pos;
}

uint8_t *UC_StringUtf8PreviousCodepoint(uint8_t *stringUtf8) {
    uint8_t *pos = stringUtf8;

    if (stringUtf8 == NULL)
        return NULL;

    do
        pos--;
    while ((pos[0] & 0xC0u) == 0x80u);

    return pos;
}

size_t UC_StringUtf8PreviousCodepointOffset(uint8_t *stringUtf8,
 size_t beginPos) {
    size_t pos = beginPos;

    if (stringUtf8 == NULL)
        return 0u;

    do
        pos--;
    while ((stringUtf8[pos] & 0xC0u) == 0x80u);

    return pos;
}

size_t UC_StringUtf8Codepoints(uint8_t *stringUtf8) {
    size_t codepoints = 0u;
    size_t currentPos = 0u;

    if (stringUtf8 == NULL)
        return 0u;

    while (stringUtf8[currentPos] != 0x00u) {
        currentPos = UC_StringUtf8NextCodepointOffset(stringUtf8, currentPos);
        codepoints++;
    }

    return codepoints;
}

size_t UC_StringUtf8Size(uint8_t *stringUtf8) {
    size_t currentPos = 0u;

    if (stringUtf8 == NULL)
        return 0u;

    while (stringUtf8[currentPos] != 0x00u)
        currentPos++;

    return currentPos;
}

size_t UC_StringUcs4Len(uint32_t *stringUcs4) {
    size_t currentPos = 0u;

    if (stringUcs4 == NULL)
        return 0u;

    while (stringUcs4[currentPos] != 0x00000000u)
        currentPos++;

    return currentPos;
}

size_t UC_StringUcs4Size(uint32_t *stringUcs4) {
    return UC_StringUcs4Len(stringUcs4) * sizeof(uint32_t);
}

void UC_StringUcs4ToUtf8(uint32_t *stringUcs4, uint8_t **stringUtf8,
 size_t *codepoints, size_t *size) {
    uint8_t  utf8Buf[5u];
    uint8_t *utf8 = utf8Buf;
    size_t   ucs4Len = UC_StringUcs4Len(stringUcs4);
    size_t   utf8Pos = 0u;
    size_t   utf8Size;
    size_t   i;

    if (stringUtf8 == NULL) {
        if (codepoints != NULL)
            *codepoints = 0;
        if (size != NULL)
            *size = 0;
        return;
    }

    if (stringUcs4 == NULL) {
        (*stringUtf8)[0] = 0x00u;

        if (codepoints != NULL)
            *codepoints = 0;
        if (size != NULL)
            *size = 0;
        return;
    }

    for (i = 0u; i < ucs4Len; i++) {
        size_t j;

        UC_Ucs4ToUtf8(stringUcs4[i], &utf8, &utf8Size);
        for (j = 0; j < utf8Size; j++)
            (*stringUtf8)[utf8Pos + j] = utf8[j];
        utf8Pos += utf8Size;
    }
    (*stringUtf8)[utf8Pos] = 0x00u;

    if (codepoints != NULL)
        *codepoints = ucs4Len;

    if (size != NULL)
        *size = utf8Pos;
}

void UC_StringUtf8ToUcs4(uint8_t *stringUtf8, uint32_t **stringUcs4,
 size_t *len) {
    size_t   codepoints = UC_StringUtf8Codepoints(stringUtf8);
    uint8_t *currentPos = stringUtf8;
    size_t   i;

    if (stringUcs4 == NULL) {
        if (len != NULL)
            *len = 0u;
        return;
    }

    if (stringUtf8 == NULL) {
        (*stringUcs4)[0] = 0x00000000u;
        if (len != NULL)
            *len = 0u;
        return;
    }

    for (i = 0u; i < codepoints; i++) {
        (*stringUcs4)[i] = UC_Utf8ToUcs4(currentPos);
        currentPos = UC_StringUtf8NextCodepoint(currentPos);
    }

    (*stringUcs4)[codepoints] = 0x00000000u;

    if (len != NULL)
        *len = codepoints;
}
