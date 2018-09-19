#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
#include<wchar.h>
#define BUFFER_SIZE 50000

wchar_t *str_replace (wchar_t *source, wchar_t *find,  wchar_t *rep);

int main() {
    if (!setlocale(LC_CTYPE, "")) {
        fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");
        return 1;
    }

    FILE* inFile = fopen("./ettoday.rec", "r");
    FILE* outFile = fopen("./ettoday.csv", "w");

    wchar_t line[BUFFER_SIZE];
    int B_flag = 0;

    while(fgetws(line, sizeof(line), inFile) != NULL) {
        wchar_t url[BUFFER_SIZE], title[BUFFER_SIZE];
        
        if(wcsstr(line, L"@U") != NULL) {
            wcscpy(line, str_replace(line, L"@U:", L""));
            wcscpy(line, str_replace(line, L"\n", L""));
            wcscpy(url, line);
        } else if(wcsstr(line, L"@T") != NULL) {
            wcscpy(line, str_replace(line, L"@T:", L""));
            wcscpy(line, str_replace(line, L"\n", L""));
            wcscpy(title, line);
        }
        else if(B_flag == 1) {
            wcscpy(line, str_replace(line, L"                                 ", L""));
            wcscpy(line, str_replace(line, L"\n", L""));
            wchar_t delimiters[10] = L"。！？";
            wchar_t* buffer;
            wchar_t* token = wcstok(line, delimiters, &buffer);
            while(token != NULL) {
                wchar_t tmp[BUFFER_SIZE];
                wcscpy(tmp, token);
                fprintf(outFile, "%ls,%ls,%ls\n", url, title, tmp);
                token = wcstok(NULL, delimiters, &buffer);
            }

            // Clear Variable
            wcscpy(url, L"");
            wcscpy(title, L"");
            B_flag = 0;
        } else if(wcsstr(line, L"@B:") != NULL) {
            B_flag = 1;
        }
    }

    fclose(inFile);
    fclose(outFile);
    return 0;
}

wchar_t *str_replace (wchar_t *source, wchar_t *find,  wchar_t *rep){  
   // 搜尋文字的長度  
   int find_L=wcslen(find);  
   // 替換文字的長度  
   int rep_L=wcslen(rep);  
   // 結果文字的長度  
   int length=wcslen(source)+1;  
   // 定位偏移量  
   int gap=0;  
     
   // 建立結果文字，並複製文字  
   wchar_t *result = (wchar_t*)malloc(sizeof(wchar_t) * length);  
   wcscpy(result, source);      
     
   // 尚未被取代的字串  
   wchar_t *former=source;  
   // 搜尋文字出現的起始位址指標  
   wchar_t *location= wcsstr(former, find);  
     
   // 漸進搜尋欲替換的文字  
   while(location!=NULL){  
       // 增加定位偏移量  
       gap+=(location - former);  
       // 將結束符號定在搜尋到的位址上  
       result[gap]='\0';  
         
       // 計算新的長度  
       length+=(rep_L-find_L);  
       // 變更記憶體空間  
       result = (wchar_t*)realloc(result, length * sizeof(wchar_t));  
       // 替換的文字串接在結果後面  
       wcscat(result, rep);  
       // 更新定位偏移量  
       gap+=rep_L;  
         
       // 更新尚未被取代的字串的位址  
       former=location+find_L;  
       // 將尚未被取代的文字串接在結果後面  
       wcscat(result, former);  
         
       // 搜尋文字出現的起始位址指標  
       location= wcsstr(former, find);  
   }      
  
   return result;  
  
} 