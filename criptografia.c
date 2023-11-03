#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_line(FILE* fd, char* buffer);

int main(int argc, char* argv[]) {

    if(strcmp(argv[1], 'c') == 0) {
        // Modo de criptografia
    } else if(strcmp(argv[1], 'd') == 0) {
        // Modo de descriptografia
    } else if(strcmp(argv[1], "help") == 0) {
        // Ajuda, mostrar modo de uso do programa
    }

    return 0;
}

// get_line != fread
// fread lê mais de uma linha por vez, get_line nãos
int get_line(FILE* fd, char* buffer) {
    char c; 
    int i = 0;

    while(c = getc(fd) != '\n' && i <= strlen(buffer)) {
        buffer[i++] = c;
    }

    return i;
}