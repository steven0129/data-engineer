#include<stdio.h>
#include<wchar.h>
#include<locale.h>
#include<regex.h>

int main() {
    if (!setlocale(LC_CTYPE, "")) {
        fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");
        return 1;
    }

    wchar_t* testStr = L"你好a";
    printf("%d\n", isChinese(testStr));
    return 0;
}

int isChinese(wchar_t* data)
{
    for (unsigned x = 0; x < wcslen(data); x++)
    {
        char hex[5];
        char *ptr;
        long result;
        sprintf(hex, "%04x", data[x]);
        result = strtol(hex, &ptr, 16);
        printf("%04x ", result);
        if(!(0x4e00 <= result && result <= 0x9fa5)) return 0;
    }

    return 1;
}