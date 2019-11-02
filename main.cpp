#include <map>
#include <sstream>
#include <stddef.h>
#include <stdio.h>
#include <iostream>
#include <openssl/sha.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int NIBBLES = 14;
int BYTES = NIBBLES / 2;
int S_LENGTH = 10;

string my60sha(unsigned char* s, int nibbles){
    // Getting first nibbles of SHA1 hash
    unsigned char sha_result[SHA_DIGEST_LENGTH];
    SHA1(s, strlen((char*)s), sha_result);
    string hash = string((char*)sha_result, BYTES);

    // Converting the bytes to hex characters
    static const char* lut = "0123456789ABCDEF";
    string result; 
    result.reserve(NIBBLES);
    for (int i = 0; i < BYTES; i++) {
        unsigned char ch = hash[i];
        result += (lut[ch >> 4]);
        result += (lut[ch & 15]);
    }
    return result;
}

string rand_string(size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string result = "";
    for (size_t n = 0; n < size; n++) {
        int key = rand() % (int) (sizeof(charset) - 1);
        result += charset[key];
    }
    return result;
}

void find_collision(){
    map<string, string> map;
    while(true){
        string s = rand_string(S_LENGTH);
        string hash = my60sha((unsigned char*)s.c_str(), NIBBLES);
        
        // Check for collision
        auto temp = map.find(hash);
        if(temp != map.end()) {
            printf("%s, %s\nmap size: %d\n", temp->second.c_str(), s.c_str(), map.size());
            return;
        }

        // If hash not found, add to table
        map[hash] = s;
    }
}

int main(){
    srand(time(NULL) * NIBBLES);
    find_collision();
}