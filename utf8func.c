#include "utf8func.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int32_t is_ascii(char str[]){
    for(int i = 0; str[i] != 0; i++){
        if (str[i] > 127 || str[i] < 0){
            return 0;
        }
    }
    return 1;
}

int32_t capitalize_ascii(char str[]){
    int32_t inc = 0;
    for(int i = 0; str[i] != 0; i++){
        if(str[i] >= 97 && str[i] <= 122){
            str[i] -= 32;
            inc += 1;
        }
    }
    return inc;
}

int32_t width_from_start_byte(char start_byte){
    if (((start_byte & 0b10000000) == 0b00000000)){
        return 1;
    }
    else if(((start_byte & 0b11110000) == 0b11000000)){
        return 2;
    }
    else if(((start_byte & 0b11110000) == 0b11100000)){
        return 3;
    }
    else if(((start_byte & 0b11111000) == 0b11110000)){
        return 4;
    }
    else{
        return -1;
    }
}

int32_t utf8_strlen(char str[]){
    int32_t cpi = 0;
    for(int i = 0; str[i] != 0; i++){
        if (width_from_start_byte(str[i]) != -1){
            cpi += 1;
        }
    }
    return cpi;
}

int32_t codepoint_index_to_byte_index(char str[], int32_t cpi){
    int32_t bi = 0;
    for(int i = 0; i < cpi; i++){
        if(width_from_start_byte(str[i]) != -1){
            bi += width_from_start_byte(str[i]);
        }
        else{
            cpi++;
        }
    }
    if (bi < cpi){
        return -1;
    }
    else{
        return bi;
    }
}

void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[]){
    if (cpi_start < cpi_end && cpi_start >= 0 && cpi_end >= 0){
        int bi_start = codepoint_index_to_byte_index(str, cpi_start);
        int bi_end = codepoint_index_to_byte_index(str, cpi_end);
        //printf("Bi_Start Test: %d\n", bi_start);
        //printf("Bi_End Test: %d\n", bi_end);
        int ri = 0;
        for(int i = bi_start; i <= bi_end; i++){
            result[ri] = str[i];
            ri++;
        }
        result[ri] = 0;
    }
    else if (cpi_start == cpi_end && cpi_start >= 0 && cpi_end >= 0){
        int bi_start = codepoint_index_to_byte_index(str, cpi_start);
        int bi_end = bi_start + width_from_start_byte(str[bi_start]) - 1;
        //printf("Bi_Start Test: %d\n", bi_start);
        //printf("Bi_End Test: %d\n", bi_end);
        int ri = 0;
        for(int i = bi_start; i <= bi_end; i++){
            result[ri] = str[i];
            ri++;
        }
        result[ri] = 0;
    }
    else{
        result[0] = '\0';
    }
}

int32_t codepoint_at(char str[], int32_t cpi){
    //could have created a char variable to use instead of str[codepoint_index_to_byte_index()] everytime
    if(width_from_start_byte(str[codepoint_index_to_byte_index(str, cpi)]) == 1){
        return str[codepoint_index_to_byte_index(str,cpi)];
    }
    else if(width_from_start_byte(str[codepoint_index_to_byte_index(str, cpi)]) == 2){
        char c1 = str[codepoint_index_to_byte_index(str, cpi)];
        char c2 = str[codepoint_index_to_byte_index(str, cpi) + 1];
        return (c1 & 0b00011111) * 64 + (c2 & 0b00111111);
    }
    else if(width_from_start_byte(str[codepoint_index_to_byte_index(str, cpi)]) == 3){
        char c1 = str[codepoint_index_to_byte_index(str, cpi)];
        char c2 = str[codepoint_index_to_byte_index(str, cpi) + 1];
        char c3 = str[codepoint_index_to_byte_index(str, cpi) + 2];
        return (c1 & 0b00001111) * 4096 + (c2 & 0b00111111) * 64 + (c3 & 0b00111111);
    }
    else if(width_from_start_byte(str[codepoint_index_to_byte_index(str, cpi)]) == 4){
        char c1 = str[codepoint_index_to_byte_index(str, cpi)];
        char c2 = str[codepoint_index_to_byte_index(str, cpi) + 1];
        char c3 = str[codepoint_index_to_byte_index(str, cpi) + 2];
        char c4 = str[codepoint_index_to_byte_index(str, cpi) + 3];
        return (c1 & 0b00000111) * 262144 + (c2 & 0b00111111) * 4096 + (c3 & 0b00111111) * 64 + (c4 & 0b00111111);
    }
    else{
        return -1;
    }
}

char is_animal_emoji_at(char str[], int32_t cpi){
    //int bi = codepoint_index_to_byte_index(str, cpi);
    int cp = codepoint_at(str, cpi);
    //printf("Bi Test: %d\n", bi);
    //printf("Cp Test: %d\n", cp);

    if (cp >= 129408 && cp <= 129454){
        return 1;
    }
    else if (cp >= 128000 && cp <= 128063){
        return 1;
    }
    else{
        return 0;
    }
}

void next_utf8_char(char str[], int32_t cpi, char result[]){
    if(utf8_strlen(str) > 4){
        int32_t cp = codepoint_at(str, cpi);
        cp += 1;
        if(cp >= 0 && cp <= 127){
            result[0] = cp;
            result[1] = 0;
        }
        else if(cp >= 128 && cp <= 2047){
            result[0] = 192 + (cp / 64);
            result[1] = 128 + (cp % 64);
            result[2] = 0;
        }
        else if(cp >= 2048 && cp <= 65535){
            result[0] = 224 + (cp / 4096);
            result[1] = 128 + ((cp / 64) % 64);
            result[2] = 128 + (cp % 64);
            result[3] = 0;
        }
        else if(cp >= 65536 && cp <= 1114111){
            result[0] = 240 + (cp / 262144);
            result[1] = 128 + ((cp / 4096) % 64);
            result[2] = 128 + ((cp / 64) % 64);
            result[3] = 128 + (cp % 64);
            result[4] = 0;
        }
    }
}