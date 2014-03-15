#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define bool unsigned char

const char *ALPHABET = "abcdefghijklmnopqrstuvwxyz\0";
const char LEN = 26;

bool in_alphabet(char letter){
    int index=0;

    while(TRUE){
        if(ALPHABET[index] == 0x0)
            return FALSE;
        if(letter==ALPHABET[index])
            return TRUE;
        else
            index ++;
    }
    return FALSE;
}

void caesar(char *content, int key){
    int index=0;
    char letter;

    while(TRUE){
        letter = content[index];
        if(letter==0x0)
            break;
        if(in_alphabet(letter))
            content[index] = ((letter - 'a' + key) % LEN) + 'a';
        index++;
    }
}

void vigener(char *content, char *key){
    int index=0;
    char letter;
    size_t key_size = strlen(key);
    
    while(TRUE){
        letter = content[index];
        if(letter==0x0)
            break;
        if(in_alphabet(letter))
            content[index] = ((letter - 'a' + key[index % key_size] - 'a' + 1) % LEN) + 'a';
        index++;

    }
}

char *get_content(char * file_name){
    FILE *fp;
    char *fcontent;
    long size;
    fp = fopen(file_name, "rb");
    if(fp){
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        fcontent = malloc(size+1);
        fcontent[size+1] = 0x0;
        fread(fcontent, 1, size, fp);
        fclose(fp);
        return fcontent;
    }else{
        fprintf(stderr,"Cant open file '%s'\n", file_name);
        exit(-1);
    }
}

int main (int argc, char **argv){
    bool is_caesar = FALSE;
    bool is_vigener = FALSE;
    char *key = NULL;
    char *file = NULL;
    char *content;
    char c;
 
    while ((c = getopt (argc, argv, "cvk:f:")) != -1)
        switch(c){
            case 'c':
                is_caesar = TRUE;
                break;
            case 'v':
                is_vigener = TRUE;
                break;
            case 'k':
                key = optarg;
                break;
            case 'f':
                file = optarg;
                break;
            case '?':
                if (optopt == 'k' || optopt == 'f')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
         return 1;
       default:
         exit(-1);
       }

    if(!(is_caesar ^ is_vigener)){
        fprintf(stderr, "You must specify cifer\n");
        exit(-1);
    }

    if (key == NULL){
        fprintf(stderr, "You must specify key\n");
        exit(-1);
    }


    content = get_content(file);

    if (is_caesar){
        int i_key = atoi(key);
        if(i_key == 0){
            fprintf(stderr, "You must specify number");
            exit(-1);
        }
        caesar(content,i_key);
    } else if(is_vigener){
        int index;
        for(index=0; index < strlen(key); index++)
            if(!in_alphabet(key[index])){
                fprintf(stderr, "You must specify key from '%s'",ALPHABET);
                exit(-1);
            }
        
        vigener(content, key);
    }

    fprintf(stdout,"%s",content);
    return 0;
 }
