#include <stdio.h>

#include "uconvert.h"

void CheckUtf8(uint8_t *utf8, const char *name) {
    if (utf8 == NULL)
        printf("%s is NULL \n", name);
    else
        printf("%s is not NULL \n", name);
}

void TestGetCompiledVersion(void) {
    printf("Compiled version major: %i \n", UC_VERSION_MAJOR);
    printf("Compiled version minor: %i \n", UC_VERSION_MINOR);
    printf("Compiled version patch: %i \n", UC_VERSION_PATCH);
}

void TestGetCompiledVersionString(void) {
    printf("Compiled version: %s \n", UC_VERSION);
}

void TestGetLinkedVersion(void) {
    int verMajor;
    int verMinor;
    int verPatch;

    UC_GetLinkedVersion(&verMajor, &verMinor, &verPatch);
    printf("Linked version major: %i \n", verMajor);
    printf("Linked version minor: %i \n", verMinor);
    printf("Linked version patch: %i \n", verPatch);
}

void TestGetLinkedVersionString(void) {
    printf("Linked version: %s \n", UC_GetLinkedVersionString());
}

void TestCreateUtf8FromChar(void) {
    printf("UC_CreateUtf8FromChar(\"z\") %s \n", UC_CreateUtf8FromChar("z"));
    printf("UC_CreateUtf8FromChar(\"ю\") %s \n", UC_CreateUtf8FromChar("ю"));
    printf("UC_CreateUtf8FromChar(\"虎\") %s \n", UC_CreateUtf8FromChar("虎"));
}

void TestCreateUtf8(void) {
    printf("UC_CreateUtf8() %s \n", UC_CreateUtf8());
}

void TestDeleteUtf8(void) {
    uint8_t *utf8Eng = UC_CreateUtf8FromChar("z");
    uint8_t *utf8Rus = UC_CreateUtf8FromChar("ю");
    uint8_t *utf8Chi = UC_CreateUtf8FromChar("虎");
    uint8_t *utf8Empty = UC_CreateUtf8();

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
}

void TestUtf8Size(void) {
    uint8_t *utf8Eng = UC_CreateUtf8FromChar("z");
    uint8_t *utf8Rus = UC_CreateUtf8FromChar("ю");
    uint8_t *utf8Chi = UC_CreateUtf8FromChar("虎");
    uint8_t *utf8Empty = UC_CreateUtf8();

    printf("UC_Utf8Size(utf8Eng) %lu \n", UC_Utf8Size(utf8Eng));
    printf("UC_Utf8Size(utf8Rus) %lu \n", UC_Utf8Size(utf8Rus));
    printf("UC_Utf8Size(utf8Chi) %lu \n", UC_Utf8Size(utf8Chi));
    printf("UC_Utf8Size(utf8Empty) %lu \n", UC_Utf8Size(utf8Empty));

    UC_DeleteUtf8(&utf8Eng);
    UC_DeleteUtf8(&utf8Rus);
    UC_DeleteUtf8(&utf8Chi);
    UC_DeleteUtf8(&utf8Empty);
}

void TestUtf8ToUcs4(void) {
    uint8_t *utf8Eng = UC_CreateUtf8FromChar("z");
    uint8_t *utf8Rus = UC_CreateUtf8FromChar("ю");
    uint8_t *utf8Chi = UC_CreateUtf8FromChar("虎");
    uint8_t *utf8Empty = UC_CreateUtf8();

    printf("UC_Utf8ToUcs4(utf8Eng) 0x%08X \n", UC_Utf8ToUcs4(utf8Eng));
    printf("UC_Utf8ToUcs4(utf8Rus) 0x%08X \n", UC_Utf8ToUcs4(utf8Rus));
    printf("UC_Utf8ToUcs4(utf8Chi) 0x%08X \n", UC_Utf8ToUcs4(utf8Chi));
    printf("UC_Utf8ToUcs4(utf8Empty) 0x%08X \n", UC_Utf8ToUcs4(utf8Empty));

    UC_DeleteUtf8(&utf8Eng);
    UC_DeleteUtf8(&utf8Rus);
    UC_DeleteUtf8(&utf8Chi);
    UC_DeleteUtf8(&utf8Empty);
}

void TestUcs4ToUtf8(void) {
    uint8_t *tempUtf8 = UC_CreateUtf8();
    size_t   tempSize;

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

    UC_DeleteUtf8(&tempUtf8);
}

void TestUtf8Copy(void) {
    uint8_t *utf8Eng = UC_CreateUtf8FromChar("z");
    uint8_t *utf8Rus = UC_CreateUtf8FromChar("ю");
    uint8_t *utf8Chi = UC_CreateUtf8FromChar("虎");
    uint8_t *utf8Empty = UC_CreateUtf8();
    uint8_t *tempUtf8 = UC_CreateUtf8();

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

    UC_DeleteUtf8(&utf8Eng);
    UC_DeleteUtf8(&utf8Rus);
    UC_DeleteUtf8(&utf8Chi);
    UC_DeleteUtf8(&utf8Empty);
    UC_DeleteUtf8(&tempUtf8);
}

void TestStringUtf8Codepoints(void) {
    uint8_t *utf8String = (uint8_t *)"Привет";

    printf("UC_StringUtf8Codepoints(utf8String) - %lu \n",
     UC_StringUtf8Codepoints(utf8String));
}

void TestStringUtf8Size(void) {
    uint8_t *utf8String = (uint8_t *)"Привет";

    printf("UC_StringUtf8Size(utf8String) %lu \n",
     UC_StringUtf8Size(utf8String));
}

void TestStringUtf8NextCodepointOffset(void) {
    uint8_t *utf8String = (uint8_t *)"Привет";
    size_t   i;
    size_t   pos;

    pos = 0u;
    for (i = 0u; i < UC_StringUtf8Codepoints(utf8String); i++) {
        printf(
         "UC_StringUtf8NextCodepointOffset(tempUtf8, pos) pos - %lu, "
         "tempUtf8 - %s \n", pos, (uint8_t *)&utf8String[pos]);
        pos = UC_StringUtf8NextCodepointOffset(utf8String, pos);
    }
}

void TestStringUtf8NextCodepoint(void) {
    uint8_t *utf8String = (uint8_t *)"Привет";
    uint8_t *tempUtf8;

    tempUtf8 = utf8String;
    while(UC_StringUtf8Codepoints(tempUtf8) != 0u) {
        printf("UC_StringUtf8NextCodepoint(tempUtf8) %s \n", tempUtf8);
        tempUtf8 = UC_StringUtf8NextCodepoint(tempUtf8);
    }
}

void TestUC_StringUtf8ToUcs4(void) {
    uint8_t  *utf8String = (uint8_t *)"Привет";
    size_t    i;
    size_t    codepoints;
    size_t    convertedSymbols;
    uint32_t *ucs4String;

    printf("%s", "testing function UC_StringUtf8ToUcs4 \n");
    codepoints = UC_StringUtf8Codepoints(utf8String);
    ucs4String = malloc(sizeof(uint32_t) * (codepoints + 1));
    UC_StringUtf8ToUcs4(utf8String, &ucs4String, &convertedSymbols);
    printf("%s", "UCS-4 string: ");
    for (i = 0u; i < convertedSymbols; i++)
        printf("0x%08X ", ucs4String[i]);
    printf("%s", "\n");
    printf("Converted symbols: %lu \n", convertedSymbols);
    free(ucs4String);
}

void TestStringUcs4Len(void) {
    uint8_t  *utf8String = (uint8_t *)"Привет";
    size_t    codepoints;
    size_t    convertedSymbols;
    uint32_t *ucs4String;

    codepoints = UC_StringUtf8Codepoints(utf8String);
    ucs4String = malloc(sizeof(uint32_t) * (codepoints + 1));
    UC_StringUtf8ToUcs4(utf8String, &ucs4String, &convertedSymbols);
    printf("UC_StringUcs4Len(ucs4String) %lu \n", UC_StringUcs4Len(ucs4String));
    free(ucs4String);
}

void TestStringUcs4Size(void) {
    uint8_t  *utf8String = (uint8_t *)"Привет";
    size_t    codepoints;
    size_t    convertedSymbols;
    uint32_t *ucs4String;

    codepoints = UC_StringUtf8Codepoints(utf8String);
    ucs4String = malloc(sizeof(uint32_t) * (codepoints + 1));
    UC_StringUtf8ToUcs4(utf8String, &ucs4String, &convertedSymbols);
    printf("UC_StringUcs4Size(ucs4String) %lu \n",
     UC_StringUcs4Size(ucs4String));
    free(ucs4String);
}

void TestStringUcs4ToUtf8(void) {
    uint8_t  *utf8String = (uint8_t *)"Привет";
    size_t    codepoints;
    size_t    convertedSymbols;
    size_t    convertedSize;
    uint32_t *ucs4String;
    uint8_t  *utf8String2;

    codepoints = UC_StringUtf8Codepoints(utf8String);
    ucs4String = malloc(sizeof(uint32_t) * (codepoints + 1));
    UC_StringUtf8ToUcs4(utf8String, &ucs4String, &convertedSymbols);
    printf("%s", "testing function UC_StringUcs4ToUtf8 \n");
    utf8String2 = malloc(
     sizeof(uint8_t) * (UC_StringUcs4Len(ucs4String) * 6 + 1));
    UC_StringUcs4ToUtf8(ucs4String, &utf8String2, &convertedSymbols,
     &convertedSize);
    printf("UTF-8 string: %s \n", utf8String2);
    printf("Converted symbols: %lu \n", convertedSymbols);
    printf("Converted bytes: %lu \n", convertedSize);
    UC_DeleteUtf8(&utf8String2);
    free(ucs4String);
}

void TestUcs4UpperBytes(void) {
    printf("UC_Ucs4UpperBytes(0x0000864E) 0x%06X \n",
     UC_Ucs4UpperBytes(0x0000864Eu));
}

void TestUcs4LowerByte(void) {
    printf("UC_Ucs4LowerByte(0x0000864E) 0x%02X \n",
     UC_Ucs4LowerByte(0x0000864Eu));
}

int main(int argc, const char **argv) {
    TestGetCompiledVersion();
    TestGetCompiledVersionString();
    TestGetLinkedVersion();
    TestGetLinkedVersionString();
    TestCreateUtf8FromChar();
    TestCreateUtf8();
    TestDeleteUtf8();
    TestUtf8Size();
    TestUtf8ToUcs4();
    TestUcs4ToUtf8();
    TestUtf8Copy();
    TestStringUtf8Codepoints();
    TestStringUtf8Size();
    TestStringUtf8NextCodepointOffset();
    TestStringUtf8NextCodepoint();
    TestUC_StringUtf8ToUcs4();
    TestStringUcs4Len();
    TestStringUcs4Size();
    TestStringUcs4ToUtf8();
    TestUcs4UpperBytes();
    TestUcs4LowerByte();

    return 0;
}
