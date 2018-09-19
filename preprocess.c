#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define BUFFER_SIZE 1000

char *str_replace (char *source, char *find,  char *rep);

int main() {
    FILE* inFile = fopen("./ettoday.rec", "r");
    FILE* outFile = fopen("./ettoday.csv", "w");

    char line[BUFFER_SIZE];
    int B_flag = 0;

    while(fgets(line, sizeof(line), inFile) != NULL) {
        char url[BUFFER_SIZE], title[BUFFER_SIZE];

        if(strstr(line, "@U") != NULL) {
            strcpy(line, str_replace(line, "@U:", ""));
            strcpy(line, str_replace(line, "\n", ""));
            strcpy(url, line);
        } else if(strstr(line, "@T") != NULL) {
            strcpy(line, str_replace(line, "@T:", ""));
            strcpy(line, str_replace(line, "\n", ""));
            strcpy(title, line);
        } else if(B_flag == 1) {
            strcpy(line, str_replace(line, "                                 ", ""));
            strcpy(line, str_replace(line, "\n", ""));
            char delimiters[10] = "。！？";
            char* token = strtok(line, delimiters);
            while(token != NULL) {
                char tmp[BUFFER_SIZE];
                strcpy(tmp, token);
                if(strlen(tmp) > 10) fprintf(outFile, "%s,%s,%s\n", url, title, tmp);
                token = strtok(NULL, delimiters);
            }

            // Clear Variable
            strcpy(url, "");
            strcpy(title, "");
            B_flag = 0;
        } else if(strstr(line, "@B:") != NULL) {
            B_flag = 1;
        }
    }

    fclose(inFile);
    fclose(outFile);
    return 0;
}

char *str_replace (char *source, char *find,  char *rep){  
   // 搜尋文字的長度  
   int find_L=strlen(find);  
   // 替換文字的長度  
   int rep_L=strlen(rep);  
   // 結果文字的長度  
   int length=strlen(source)+1;  
   // 定位偏移量  
   int gap=0;  
     
   // 建立結果文字，並複製文字  
   char *result = (char*)malloc(sizeof(char) * length);  
   strcpy(result, source);      
     
   // 尚未被取代的字串  
   char *former=source;  
   // 搜尋文字出現的起始位址指標  
   char *location= strstr(former, find);  
     
   // 漸進搜尋欲替換的文字  
   while(location!=NULL){  
       // 增加定位偏移量  
       gap+=(location - former);  
       // 將結束符號定在搜尋到的位址上  
       result[gap]='\0';  
         
       // 計算新的長度  
       length+=(rep_L-find_L);  
       // 變更記憶體空間  
       result = (char*)realloc(result, length * sizeof(char));  
       // 替換的文字串接在結果後面  
       strcat(result, rep);  
       // 更新定位偏移量  
       gap+=rep_L;  
         
       // 更新尚未被取代的字串的位址  
       former=location+find_L;  
       // 將尚未被取代的文字串接在結果後面  
       strcat(result, former);  
         
       // 搜尋文字出現的起始位址指標  
       location= strstr(former, find);  
   }      
  
   return result;  
  
}  