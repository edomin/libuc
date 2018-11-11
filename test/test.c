#include <stdio.h>

#include "uconvert.h"

void CheckUtf8(uint8_t *utf8, const char *name) {
    if (utf8 == NULL)
        printf("%s is NULL \n", name);
    else
        printf("%s is not NULL \n", name);
}

int main(int argc, const char **argv) {
    uint8_t *utf8Eng = UC_CreateUtf8FromChar("z");
    uint8_t *utf8Rus = UC_CreateUtf8FromChar("ю");
    uint8_t *utf8Chi = UC_CreateUtf8FromChar("虎");
    uint8_t *utf8Empty = UC_CreateUtf8();
    uint8_t *tempUtf8 = UC_CreateUtf8();
    size_t   tempSize;

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
    printf("UC_Ucs4ToUtf8(0x0000007A, &tempUtf8, &tempSize) - %s, size - %lu \n", tempUtf8, tempSize);
    UC_Ucs4ToUtf8(0x0000044Eu, &tempUtf8, &tempSize);
    printf("UC_Ucs4ToUtf8(0x0000044Eu, &tempUtf8, &tempSize) - %s, size - %lu \n", tempUtf8,
     tempSize);
    UC_Ucs4ToUtf8(0x0000864Eu, &tempUtf8, &tempSize);
    printf("UC_Ucs4ToUtf8(0x0000864Eu, &tempUtf8, &tempSize) - %s, size - %lu \n", tempUtf8,
     tempSize);
    UC_Ucs4ToUtf8(0x00000020u, &tempUtf8, &tempSize);
    printf("UC_Ucs4ToUtf8(0x00000020u, &tempUtf8, &tempSize) - %s, size - %lu \n", tempUtf8,
     tempSize);

    UC_Utf8Copy(tempUtf8, utf8Eng);
    printf("UC_Utf8Copy(tempUtf8, utf8Eng) - %s, from %s \n", tempUtf8, utf8Eng);
    UC_Utf8Copy(tempUtf8, utf8Rus);
    printf("UC_Utf8Copy(tempUtf8, utf8Rus) - %s, from %s \n", tempUtf8, utf8Rus);
    UC_Utf8Copy(tempUtf8, utf8Chi);
    printf("UC_Utf8Copy(tempUtf8, utf8Chi) - %s, from %s \n", tempUtf8, utf8Chi);
    UC_Utf8Copy(tempUtf8, utf8Empty);
    printf("UC_Utf8Copy(tempUtf8, utf8Empty) - %s, from %s \n", tempUtf8, utf8Empty);

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

    return 0;
}
