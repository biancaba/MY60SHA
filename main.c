#include <stddef.h>
#include <stdio.h>
#include <openssl/sha.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char* my60sha(unsigned char* s, int nibbles){
    unsigned char result[SHA_DIGEST_LENGTH];
    SHA1(s, strlen((char*)s), result);
    char* hash = malloc(nibbles+1);
    if(!hash) return NULL;
    strncpy(hash,(char*)result, nibbles);
    hash[nibbles] = '\0';
    return hash;
}

static char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (size) {
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

char* rand_string_alloc(size_t size)
{
    char *s = (char*)malloc(size + 1);
    if (s) {
        rand_string(s, size);
    }
    return s;
}

int main(){
    int NIBBLES = 4;
    char* str = "mark";
    char* hash = my60sha((unsigned char*)str, NIBBLES);
    for (int i = 0; i < NIBBLES; i++) {
        printf("%x%c", hash[i], i < (NIBBLES-1) ? ' ' : '\n');
    }
    
    srand(time(NULL) * NIBBLES);
    for(int i=1; i < 5; i++){
        char* rand = rand_string_alloc(10);
        printf("%s\n", rand);
    }

}
