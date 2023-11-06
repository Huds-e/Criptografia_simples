#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_line(FILE* file, char* buffer);
void criptografy(char* buffer, int size, int key, FILE* file);

int main() {
    char file_name[50];
    char operation;
    int key;
    
    printf("Name of the file: ");
    fgets(file_name, 50, stdin);
    file_name[strlen(file_name) - 1] = '\0';

    FILE* fd = fopen(file_name, "r+");
    FILE* answer = fopen("decrypt.txt", "w");

    if(fd == NULL || answer == NULL) return 1;

    printf("Operation letters\n\tencrypt --> e\n\tdecrypt --> d\n--> ");
    scanf("%c", &operation);

    printf("Type the key: ");
    scanf("%i", &key);


    while(!feof(fd)) {
        char line[500] = {0};
        int i = get_line(fd, line);
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
    char c; 
    int i = 0;

    while((c = getc(file)) != '\n' && i <= strlen(buffer)) {
        buffer[i++] = c;
    }

    return i;
}

void criptografy(char* buffer, int size, int key, FILE* file) {
    while(size >= 0) {
        printf("%c\n", buffer[size-1]);
        buffer[size-1] = buffer[size-1] + key;
        size--;
        printf("%c\n", buffer[size-1]);
    }

    fwrite(buffer, sizeof(char), strlen(buffer), file);
}