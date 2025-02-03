#pragma once
#include "common.h"

constexpr unsigned int str2int(const char* str, int h){
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}