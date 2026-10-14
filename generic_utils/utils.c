#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

bool not_empty(char *str)
{
  return strlen(str) > 0;
}

answer_t convert_char(char *str) {
    answer_t result;
    result.character = str[0];
    return result;
}

bool is_valid_char(char *str) {
    if (strlen(str) != 1) {
        return false;
    }
  if (*(str) == 'L' ||
  *(str) == 'l' ||
  *(str) == 'T' ||
  *(str) == 't' ||
  *(str) == 'R' ||
  *(str) == 'r' ||
  *(str) == 'G' ||
  *(str) == 'g' ||
  *(str) == 'H' ||
  *(str) == 'h' ||
  *(str) == 'A' ||
  *(str) == 'a') {
  return true; 
} else {
    return false;
}
}


bool is_number(char *str) {
     if (str[0] == '\0'){
     return false;
     }

    for (int i = 0; i < strlen(str); i++) {
        
         //check if first char is null char or if its - then null char
        if (str[0] == '-' && str[1] == '\0') {
            return false;
        }
        
        //if first is - let next 
        if (str[0] == '-') {
            i = 1;
        }

        //check that every string is digit {
            if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;

    }

// bool is_float(char *str) {

//         bool seen_dot = false;  
//         int i = 0;

//              //check if first char is null char or if its - then null char
//         if (str[0] == '\0' || str[0] == '-' && str[1] == '\0') {
//             return false;
//         } // edge case for .
//         if (str[0] == '.' && str[1] == '\0') {
//             return false;
//         }
        
//         //if first is - let next 
//         if (str[0] == '-') {
//             i = 1;
//         }

// while (i < strlen(str)) {

//     if (isdigit(str[i])) {
//         i++;
//     }
//     else if (str[i] == '.') {
//         if (seen_dot == true) {
//             return false;
//         } else {
//             seen_dot = true;
//             i++;
//         }

//     } else if (!isdigit(str[i]) && str[i] != '.') {
//         return false;
//     }
// }
//     return true;
// }

   void clear_input_buffer(void) {

    int c;
        do {
            c = getchar();
           }

    while (c != '\n' && c != EOF);
     putchar('\n');
    }

int read_string(char *buf, int buf_siz) {
    int result = 0;
    int c;

    while (result < buf_siz -1) {
        //vi har nåt \n eller EOF printa resultat direkt
        c = getchar();
        if (c == '\n' || c == EOF) {
            buf[result] = '\0';
            return result;
        }
        buf[result] = c;
        result = result + 1;
    }
    //buffern fyller inte hela buf_sizen
    buf[result] = '\0';
    clear_input_buffer();
    return result;
}

bool is_valid_id(char *id) {
    int i = 0;
    if (isdigit(id[0]) || id[0] == '\0' || id[0] == '-' || id[0] == '.' || isspace(id[0])) {
    return false;
    }

    i = 1;

    while (i < strlen(id))  {

    if(!isdigit(id[i])) {
        return false;
    } else {
        i++;
    }
}
return true;
}


int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func *) atoi);
  return answer.int_value; // svaret som ett heltal
}

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func *) strdup).string_value;
}

char *ask_question_shelf(char *question) {
    return ask_question(question, is_valid_id, (convert_func *) strdup).string_value;
}

char ask_question_menu(char *question) {
    char c = ask_question(question, is_valid_char, convert_char).character;
    return toupper(c);
}

answer_t ask_question(char *question, check_func *check, convert_func *convert) {
    char buf [255];
    while (true) {
        printf("%s\n", question);
        read_string(buf, 255);
        if (check(buf)) {
            return convert(buf);
        }
            printf("Invalid\n");
        }
}



