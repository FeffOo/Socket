#pragma once
#include "common.h"


//Converte la stringa in un hash
constexpr unsigned int str2int(const char* str, int h){
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

constexpr char* strsegm(char* str){
    strtok(str, " ");
    return str;
}