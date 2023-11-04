#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void help(char* exe_name) {
    printf("How to use:\n");
    printf("\t%s [txt_file_name] [/e] [/d]\n", exe_name);
    printf("\t/e\tEnters the encrypt mode. (don't use with /d)\n");
    printf("\t/d\tEnters the decrypt mode. (don't use with /e)\n");
    printf("\t[txt_file_name]\tIt's the file that will be encrypted/decrypted.\n");
}

int get_line(FILE* fd, char* buffer);

int main(int argc, char* argv[]) {

    if(argc == 2) {
        if(strcmp(argv[1], "help") == 0) {
            help(argv[0]);
        }else {
            printf("Error! type '%s help' for useful information.\n", argv[0]);
        }
    }else if(argc == 3) {
        FILE * fd = fopen(argv[1], "r+");
        if(fd == NULL) printf("Error! File not found.\n");
        
        else{
            char buffer[500];
            int i = get_line(fd, buffer);

            if(strcmp(argv[2], "/e") == 0) {
                // encrypt
            } else if(strcmp(argv[2], "/d") == 0) {
                // decrypt
            } else {
                printf("Error! type '%s help' for useful information.\n", argv[0]);
            }
        }        
    }else printf("Error! type '%s help' for useful information.\n", argv[0]);

    return 0;
}

// get_line != fread
// fread reads more than one line, get_line reads only one line a time.
int get_line(FILE* fd, char* buffer) {
    char c; 
    int i = 0;

    while((c = getc(fd)) != '\n' && i <= strlen(buffer)) {
        buffer[i++] = c;
    }

    return i;
}