#include<stdio.h>
#include<string.h>
#define BUFFER_SIZE 1000

int main(int argc, char *argv[]) {
    char cmd[] = "grep '";
    char cmd2[100];
    
    if(argc > 1) {
        strcat(cmd, argv[1]);
        strcat(cmd, "' ettoday.csv");
        strcat(cmd, " | sort");
        FILE* result = popen(cmd, "r");
        char buffer[BUFFER_SIZE];

        while(fgets(buffer, sizeof(buffer), result) != NULL) {
            if(strstr(buffer, "二進位格式檔案") == NULL) {
                printf("%s", buffer);
            }
        }
    }

    return 0;
}