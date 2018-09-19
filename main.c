#include<stdio.h>
#include<string.h>
#define BUFFER_SIZE 1000

int main(int argc, char *argv[]) {
    char cmd1[7];
    char cmd2[100];
    char cmd3[14];
    
    if(argc > 1) {
        strcpy(cmd1, "grep '");
        strcpy(cmd2, argv[1]);
        strcpy(cmd3, "' ettoday.csv");
        strcat(cmd1, cmd2);
        strcat(cmd1, cmd3);
        FILE* result = popen(cmd1, "r");
        char buffer[BUFFER_SIZE];

        while(fgets(buffer, sizeof(buffer), result) != NULL) {
            if(strstr(buffer, "二進位格式檔案") == NULL) {
                printf("%s", buffer);
            }
        }
    }

    return 0;
}