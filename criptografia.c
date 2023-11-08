#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_line(FILE* file, char* buffer);
void criptografy(char* buffer, size_t size, int key, FILE* file);

int main() {
    char file_name[50];
    char operation;
    int key;
    
    printf("Name of the file: ");
    fgets(file_name, 50, stdin);
    file_name[strlen(file_name) - 1] = '\0';

    FILE* fd = fopen(file_name, "r");
    FILE* answer = fopen("criptografy.txt", "w");

    if(fd == NULL || answer == NULL) {printf("Error! Cannot open the file."); return 1;}

    printf("Operation letters\n\tencrypt --> e\n\tdecrypt --> d\n--> ");
    scanf("%c", &operation);

    printf("Type the key: ");
    scanf("%i", &key);

    while(!feof(fd)) {
        char line[500] = {0};
        int i = get_line(fd, line);
        printf("line: %s\n", line);
        if(operation == 'e') {
            criptografy(line, i, key, answer);
        }else if(operation == 'd') {
            criptografy(line, i, -key, answer);
        }
    }

    fclose(fd);
    fclose(answer);

    system("pause");

    return 0;
}

// get_line != fread
// fread reads more than one line, get_line reads only one line a time.
int get_line(FILE* file, char* buffer) {
    size_t i = 0;

    char c = getc(file); 
    while(c != '\n' && c != '\r' && !feof(file)) {
        buffer[i++] = c;
        c = getc(file);
    }

    return i;
}

void criptografy(char* buffer, size_t size, int key, FILE* file) {
    char* lf = "\n";

    for(size_t i = 0; i<size; i++) {
        buffer[i] += key;
    }

    printf("line encrypted: %s\n", buffer);

    fwrite(buffer, sizeof(char), size, file);
    fwrite(lf, sizeof(char), 1, file);
}