#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define bool unsigned char

#define abort(...) {fprintf(stderr,__VA_ARGS__);exit(-1);}


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

void encode(char *content,char * key, char(*do_encode)(char, int, char*)){
    int index=0;
    char letter;

    while(TRUE){
        letter = content[index];
        if(letter==0x0)
            break;
        if(in_alphabet(letter))
            content[index] = do_encode(letter, index, key);
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
        fcontent = (char*)malloc(size+2);
        fcontent[size+1] = 0x0;
        fread(fcontent, 1, size, fp);
        fclose(fp);
        return fcontent;
    }else{
        abort("Cant open file '%s'\n", file_name);
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
         abort("Unknown option");
       }

    if(!(is_caesar ^ is_vigener))
        abort("You must specify cifer\n");

    if (key == NULL)
        abort("You must specify key\n");

    content = get_content(file);

    if (is_caesar){
        char i_key = atoi(key);
        if(i_key == 0)
            abort("You must specify number\n");
        encode(content, &i_key,  
                [] (char letter, int index, char* key) -> char {
                    return ((letter - 'a' + *key) % LEN) + 'a'; });
    } else if(is_vigener){
        int index;
        for(index=0; index < strlen(key); index++)
            if(!in_alphabet(key[index]))
                abort("You must specify key from '%s'\n",ALPHABET);

        encode(content, key,
                [] (char letter, int index, char* key) -> char {
                    return ((letter - 'a' + key[index % strlen(key)] - 'a' + 1) % LEN) + 'a';});
    }

    fprintf(stdout,"%s",content);
    return 0;
 }
