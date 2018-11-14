#include <stdio.h>

#include "uconvert.h"

void CheckUtf8(uint8_t *utf8, const char *name) {
    if (utf8 == NULL)
        printf("%s is NULL \n", name);
    else
        printf("%s is not NULL \n", name);
}

int main(int argc, const char **argv) {
    uint8_t  *utf8Eng = UC_CreateUtf8FromChar("z");
    uint8_t  *utf8Rus = UC_CreateUtf8FromChar("ю");
    uint8_t  *utf8Chi = UC_CreateUtf8FromChar("虎");
    uint8_t  *utf8Empty = UC_CreateUtf8();
    uint8_t  *tempUtf8 = UC_CreateUtf8();
    size_t    tempSize;
    uint8_t  *utf8String = (uint8_t *)"Привет";
    size_t    i;
    size_t    pos;
    size_t    codepoints;
    size_t    convertedSymbols;
    size_t    convertedSize;
    uint32_t *ucs4String;
    uint8_t  *utf8String2;

    printf("UC_CreateUtf8FromChar(\"z\") %s \n", UC_CreateUtf8FromChar("z"));
    printf("UC_CreateUtf8FromChar(\"ю\") %s \n", UC_CreateUtf8FromChar("ю"));
    printf("UC_CreateUtf8FromChar(\"虎\") %s \n", UC_CreateUtf8FromChar("虎"));

    printf("UC_CreateUtf8() %s \n", UC_CreateUtf8());

    printf("UC_Utf8Size(utf8Eng) %lu \n", UC_Utf8Size(utf8Eng));
    printf("UC_Utf8Size(utf8Rus) %lu \n", UC_Utf8Size(utf8Rus));
    printf("UC_Utf8Size(utf8Chi) %lu \n", UC_Utf8Size(utf8Chi));
    printf("UC_Utf8Size(utf8Empty) %lu \n", UC_Utf8Size(utf8Empty));

    printf("UC_Utf8ToUcs4(utf8Eng) 0x%08X \n", UC_Utf8ToUcs4(utf8Eng));
    printf("UC_Utf8ToUcs4(utf8Rus) 0x%08X \n", UC_Utf8ToUcs4(utf8Rus));
    printf("UC_Utf8ToUcs4(utf8Chi) 0x%08X \n", UC_Utf8ToUcs4(utf8Chi));
    printf("UC_Utf8ToUcs4(utf8Empty) 0x%08X \n", UC_Utf8ToUcs4(utf8Empty));

    UC_Ucs4ToUtf8(0x0000007Au, &tempUtf8, &tempSize);
    printf(
     "UC_Ucs4ToUtf8(0x0000007A, &tempUtf8, &tempSize) - %s, size - %lu \n",
     tempUtf8, tempSize);
    UC_Ucs4ToUtf8(0x0000044Eu, &tempUtf8, &tempSize);
    printf(
     "UC_Ucs4ToUtf8(0x0000044Eu, &tempUtf8, &tempSize) - %s, size - %lu \n",
     tempUtf8, tempSize);
    UC_Ucs4ToUtf8(0x0000864Eu, &tempUtf8, &tempSize);
    printf(
     "UC_Ucs4ToUtf8(0x0000864Eu, &tempUtf8, &tempSize) - %s, size - %lu \n",
     tempUtf8, tempSize);
    UC_Ucs4ToUtf8(0x00000020u, &tempUtf8, &tempSize);
    printf(
     "UC_Ucs4ToUtf8(0x00000020u, &tempUtf8, &tempSize) - %s, size - %lu \n",
     tempUtf8, tempSize);

    UC_Utf8Copy(tempUtf8, utf8Eng);
    printf("UC_Utf8Copy(tempUtf8, utf8Eng) - %s, from %s \n", tempUtf8,
     utf8Eng);
    UC_Utf8Copy(tempUtf8, utf8Rus);
    printf("UC_Utf8Copy(tempUtf8, utf8Rus) - %s, from %s \n", tempUtf8,
     utf8Rus);
    UC_Utf8Copy(tempUtf8, utf8Chi);
    printf("UC_Utf8Copy(tempUtf8, utf8Chi) - %s, from %s \n", tempUtf8,
     utf8Chi);
    UC_Utf8Copy(tempUtf8, utf8Empty);
    printf("UC_Utf8Copy(tempUtf8, utf8Empty) - %s, from %s \n", tempUtf8,
     utf8Empty);

    CheckUtf8(utf8Eng, "utf8Eng");
    CheckUtf8(utf8Rus, "utf8Rus");
    CheckUtf8(utf8Chi, "utf8Chi");
    CheckUtf8(utf8Empty, "utf8Empty");

    UC_DeleteUtf8(&utf8Eng);
    UC_DeleteUtf8(&utf8Rus);
    UC_DeleteUtf8(&utf8Chi);
    UC_DeleteUtf8(&utf8Empty);

    CheckUtf8(utf8Eng, "utf8Eng");
    CheckUtf8(utf8Rus, "utf8Rus");
    CheckUtf8(utf8Chi, "utf8Chi");
    CheckUtf8(utf8Empty, "utf8Empty");

    pos = 0u;
    printf("UC_StringUtf8Codepoints(utf8String) - %lu \n",
     UC_StringUtf8Codepoints(utf8String));
    for (i = 0u; i < UC_StringUtf8Codepoints(utf8String); i++) {
        printf(
         "UC_StringUtf8NextCodepointOffset(tempUtf8, pos) pos - %lu, "
         "tempUtf8 - %s \n", pos, (uint8_t *)&utf8String[pos]);
        pos = UC_StringUtf8NextCodepointOffset(utf8String, pos);
    }

    tempUtf8 = utf8String;
    printf("UC_StringUtf8Codepoints(tempUtf8) - %lu \n",
     UC_StringUtf8Codepoints(tempUtf8));
    while(UC_StringUtf8Codepoints(tempUtf8) != 0u) {
        printf("UC_StringUtf8NextCodepoint(tempUtf8) %s \n", tempUtf8);
        tempUtf8 = UC_StringUtf8NextCodepoint(tempUtf8);
    }

    printf("UC_StringUtf8Size(utf8String) %lu \n",
     UC_StringUtf8Size(utf8String));

    printf("%s", "testing function UC_StringUtf8ToUcs4 \n");
    codepoints = UC_StringUtf8Codepoints(utf8String);
    ucs4String = malloc(sizeof(uint32_t) * (codepoints + 1));
    UC_StringUtf8ToUcs4(utf8String, &ucs4String, &convertedSymbols);
    printf("%s", "UCS-4 string: ");
    for (i = 0u; i < convertedSymbols; i++) {
        printf("0x%08X ", ucs4String[i]);
    }
    printf("%s", "\n");
    printf("Converted symbols: %lu \n", convertedSymbols);

    printf("UC_StringUcs4Len(ucs4String) %lu \n", UC_StringUcs4Len(ucs4String));
    printf("UC_StringUcs4Size(ucs4String) %lu \n",
     UC_StringUcs4Size(ucs4String));

    printf("%s", "testing function UC_StringUcs4ToUtf8 \n");
    utf8String2 = malloc(
     sizeof(uint8_t) * (UC_StringUcs4Len(ucs4String) * 6 + 1));
    UC_StringUcs4ToUtf8(ucs4String, &utf8String2, &convertedSymbols,
     &convertedSize);
    printf("UTF-8 string: %s \n", utf8String2);
    printf("Converted symbols: %lu \n", convertedSymbols);
    printf("Converted bytes: %lu \n", convertedSize);

    printf("UC_Ucs4UpperBytes(0x0000864E) 0x%06X \n",
     UC_Ucs4UpperBytes(0x0000864Eu));
    printf("UC_Ucs4LowerByte(0x0000864E) 0x%02X \n",
     UC_Ucs4LowerByte(0x0000864Eu));

    return 0;
}
