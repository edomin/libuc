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
    printf("UC_CreateUtf8FromChar(\"z\") %s \n", UC_CreateUtf8FromChar("z"));
    printf("UC_CreateUtf8FromChar(\"ю\") %s \n", UC_CreateUtf8FromChar("ю"));
    printf("UC_CreateUtf8FromChar(\"虎\") %s \n", UC_CreateUtf8FromChar("虎"));
    printf("UC_CreateUtf8() %s \n", UC_CreateUtf8());
    printf("UC_Utf8Size(utf8Eng) %lu \n", UC_Utf8Size(utf8Eng));
    printf("UC_Utf8Size(utf8Rus) %lu \n", UC_Utf8Size(utf8Rus));
    printf("UC_Utf8Size(utf8Chi) %lu \n", UC_Utf8Size(utf8Chi));
    printf("UC_Utf8Size(utf8Empty) %lu \n", UC_Utf8Size(utf8Empty));

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
