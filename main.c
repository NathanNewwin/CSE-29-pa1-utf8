#include "utf8func.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(){
    printf("%s\n", "Enter a UTF-8 encoded string:");
    char buffer[100];
    char copy[100];
    char result[100];
    char animal[100];
    int bi = 0;
    fgets(buffer,100,stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    utf8_substring(buffer, 0, 5, result);
    for(int i = 0; buffer[i] != 0; i++){
        copy[i] = buffer[i];
        bi += 1;
    }
    copy[bi] = 0;

    //Analyzer
    printf("Valid ASCII: %s\n", is_ascii(buffer) ? "true" : "false");
    capitalize_ascii(copy);
    printf("Uppercased ASCII: \"%s\"\n", copy);
    printf("Length in bytes: %d\n", bi);
    printf("Number of code points: %d\n", utf8_strlen(buffer));
    printf("%s", "Bytes per code point:");
    for(int i = 0; buffer[i] != 0; i++){
        if(width_from_start_byte(buffer[i]) != -1){
            printf(" %d", width_from_start_byte(buffer[i]));
        }
    }
    printf("\nSubstring of the first 6 code points: \"%s\"\n", result);
    printf("%s", "Code points as decimal numbers:");
    for(int i = 0; i < utf8_strlen(buffer); i++){
        printf(" %d", codepoint_at(buffer, i));
    }
    printf("\nAnimal emojis:");
    for(int i = 0; i < utf8_strlen(buffer); i++){
        if(is_animal_emoji_at(buffer, i)){
            utf8_substring(buffer, i, i, animal);
            printf(" %s", animal);
        }
    }
    char results[5];
    next_utf8_char(buffer, 3, results);
    printf("\nNext Character of Codepoint at Index 3: %s\n", results);
    //My 🐩’s name is Erdős.

    //char c1 = 0b11100000;
    //char c2 = 0b10000000;
    //char c3 = 0b10100001;
    //printf("%d\n", (c1 & 0b00001111) * 4096 + (c2 & 0b00111111) * 64 + (c3 & 0b00111111));

    /*
    //IS_ASCII TEST
    printf("Is 🔥 ASCII? %d\n", is_ascii("🔥"));
    printf("Is abcd ASCII? %d\n", is_ascii("abcd"));
    
    //CAPITALIZE_ASCII TEST
    int32_t ret = 0;
    char str[] = "abcd";
    ret = capitalize_ascii(str);
    printf("Capitalized String: %s\nCharacters updated: %d\n", str, ret);
    
    //WIDTH_FROM_START_BYTE TEST
    char s[] = "Héy"; // same as { 'H', 0xC3, 0xA9, 'y', 0 },   é is start byte + 1 cont. byte
    printf("Width: %d bytes\n", width_from_start_byte(s[1])); // start byte 0xC3 indicates 2-byte sequence
    printf("Width: %d bytes\n", width_from_start_byte(s[2])); // start byte 0xA9 is a continuation byte, not a start byte
    
    //UTF8_STRLEN TEST
    char sttr[] = "Joséph";
    printf("Length of string %s is %d\n", sttr, utf8_strlen(sttr));  // 6 codepoints, (even though 7 bytes)

    //CODEPOINT_INDEX_TO_BYTE_INDEX TEST
    int32_t idx = 4;
    printf("Codepoint index %d is byte index %d\n", idx, codepoint_index_to_byte_index("Joséph", idx));

    //UTF8_SUBSTRING TEST
    char result[17];
    utf8_substring("🦀🦮🦮🦀🦀🦮🦮", 3, 7, result);
    printf("String: %s\nSubstring: %s\n", "🦀🦮🦮🦀🦀🦮🦮", result); // these emoji are 4 bytes long
    
    //CODEPOINT_AT TEST
    char sttrr[] = "Joséph";
    int32_t idxx = 4;
    printf("Codepoint at %d in %s is %d\n", idxx, sttrr, codepoint_at(sttrr, idxx)); // 'p' is the 4th codepoint
    
    //IS_ANIMAL_EMOJI_AT TEST
    char animal[] = "ヶ🦀";
    printf("Start Byte Test: %d\n", width_from_start_byte(animal[0]));
    printf("Start Byte Test: %d\n", width_from_start_byte(animal[3]));
    if (is_animal_emoji_at(animal, 1)){
        printf("Is animal\n");
    }
    else{
        printf("Not animal\n");
    }
    return 0;
    */
}