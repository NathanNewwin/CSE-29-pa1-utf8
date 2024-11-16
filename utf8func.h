#ifndef MYMATH_H
#define MYMATH_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

int32_t is_ascii(char str[]);
int32_t capitalize_ascii(char str[]);
int32_t width_from_start_byte(char start_byte);
int32_t utf8_strlen(char str[]);
int32_t codepoint_index_to_byte_index(char str[], int32_t cpi);
void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[]);
int32_t codepoint_at(char str[], int32_t cpi);
char is_animal_emoji_at(char str[], int32_t cpi);
void next_utf8_char(char str[], int32_t cpi, char result[]);

#endif