// Hudson Henrique da Silva
// 09/11/2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions
// ---------------------------------------------------------------------
int get_line(FILE* file, char* buffer);
void inverter(char* buffer, size_t size);
void criptografy(char* buffer, size_t size, int key, FILE* file);
// ---------------------------------------------------------------------

int main() {

    char file_name[50];
    char operation;
    int key;
    
    // Getting the name of the file and opening the file.
    printf("Name of the file: ");
    fgets(file_name, 50, stdin);
    file_name[strlen(file_name) - 1] = '\0';

    if(strcmp(file_name, "criptografy.txt") == 0) {printf("Cannot use the criptografy file to encode/decode text.\n"); return 1;}

    FILE* fd = fopen(file_name, "r");
    FILE* answer = fopen("criptografy.txt", "w"); // this is a file where the encoded text will be storage.

    if(fd == NULL || answer == NULL) {printf("Error! Cannot open the file."); return 1;}

    printf("Operation letters\n\tencrypt --> e\n\tdecrypt --> d\n--> ");
    scanf("%c", &operation);

    printf("Type the key (key must bee between 1 and 120): ");
    scanf("%i", &key);

    if(key > 120) {printf("Invalid Key.\n"); return 1;}

    // loop for encrypt/decrypt all the lines of the file.
    while(!feof(fd)) {
        char line[500] = {0};
        int i = get_line(fd, line);
        if(operation == 'e') {
            inverter(line, i);
            criptografy(line, i, key, answer);
        }else if(operation == 'd') {
            inverter(line, i);
            criptografy(line, i, -key, answer);
        }
        else {
            printf("Invalid mode, try again.\n");
            return 1;
        }
    }

    fclose(fd);
    fclose(answer);

    if(operation == 'e') printf("Encrypted file created.\n");
    else printf("Decrypted file created.\n");

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

    buffer[i] = '\0';

    return i;
}

// this functon inverts the words that are stored in the buffer.
void inverter(char* buffer, size_t size) {
    int begin = 0;
    int end = size-1;
    char aux;

    while(begin != end && begin < end) {
        aux = buffer[begin];
        buffer[begin] = buffer[end];
        buffer[end] = aux;

        begin++;
        end--;
    }

}

// Aplies the Caesar Chiper technique into the buffer.
void criptografy(char* buffer, size_t size, int key, FILE* file) {
    char* lf = "\n";
    int distance;

    for(size_t i = 0; i<size; i++) {
        if(buffer[i] + key > 127) {
            distance = key - (127 - buffer[i]);
            buffer[i] = distance;
        } else if(buffer[i] + key < 0) {
            distance = buffer[i];
            buffer[i] = 127 + (key + distance);
        }

    }

    fwrite(buffer, sizeof(char), size, file);
    fwrite(lf, sizeof(char), 1, file);
}