#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

char* createString(char character) {
    char* str = (char*)malloc(2 * sizeof(char));
    str[0] = character;
    str[1] = '\0';
    return str;
}

bool isSpecialChar(char ch) {
    return (ch == ':' || ch == '<' || ch == '>' || ch == '=' ||
            ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == '(' || ch == ')' || ch == ';' || ch == '{' ||
            ch == '}' || ch == '_');
}

bool isTwoCharSpecialChar(const char* token) {
    return (strcmp(token, ":=") == 0 || strcmp(token, "!=") == 0 || strcmp(token, ">=") == 0 ||
            strcmp(token, "<=") == 0 || strcmp(token, "==") == 0 || strcmp(token, "++") == 0 || strcmp(token, "--") == 0);
}

int getSpecialCharIndex(const char* token) {
    if (strcmp(token, ":=") == 0) {
        return 0;
    } else if (strcmp(token, "!=") == 0) {
        return 1;
    } else if (strcmp(token, ">=") == 0) {
        return 2;
    } else if (strcmp(token, "<=") == 0) {
        return 3;
    } else if (strcmp(token, "==") == 0) {
        return 4;
    } else if (strcmp(token, "++") == 0) {
        return 5;
    } else if (strcmp(token, "--") == 0) {
        return 6;
    }
    return -1;
}

int getKeywordIndex(const char* token) {
    if (strcmp(token, "read") == 0) {
        return 0;
    } else if (strcmp(token, "write") == 0) {
        return 1;
    } else if (strcmp(token, "while") == 0) {
        return 2;
    } else if (strcmp(token, "do") == 0) {
        return 3;
    } else if (strcmp(token, "od") == 0) {
        return 4;
    }
    return -1;
}

bool isLowercase(const char* token) {
    for (size_t i = 0; i < strlen(token); ++i) {
        if (!islower(token[i])) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    if (argc == 2) {
        char line[256];
        FILE* inputFile = fopen(argv[1], "r");

        if (inputFile != NULL) {
            printf("Custom Analyzer :: R11723071\n");

            while (fgets(line, sizeof(line), inputFile)) {
                int pointer = 0;
                int lineLength = strlen(line);

                while (pointer < lineLength) {
                    char currentChar = line[pointer];

                    if (isdigit(currentChar)) {
                        int digitCounter = 0;
                        int digitValue = 0;

                        while (isdigit(line[pointer + digitCounter])) {
                            int num = line[pointer + digitCounter] - '0';
                            digitValue = digitValue * 10 + num;
                            digitCounter++;
                        }
                        printf("%d      INT_LIT\n", digitValue);
                        pointer += digitCounter;
                    } else if (isalpha(currentChar) || currentChar == '_') {
                        char currentToken[256] = "";
                        int tokenCounter = 0;

                        while (isalpha(line[pointer + tokenCounter]) || line[pointer + tokenCounter] == '_') {
                            strncat(currentToken, &line[pointer + tokenCounter], 1);
                            tokenCounter++;
                        }

                        if (!isLowercase(currentToken)) {
                            printf("%s      UNKNOWN\n", currentToken);
                        }

                        int keywordIndex = getKeywordIndex(currentToken);

                        switch (keywordIndex) {
                            case 0:
                                printf("%s      KEY_READ\n", currentToken);
                                break;
                            case 1:
                                printf("%s      KEY_WRITE\n", currentToken);
                                break;
                            case 2:
                                printf("%s      KEY_WHILE\n", currentToken);
                                break;
                            case 3:
                                printf("%s      KEY_DO\n", currentToken);
                                break;
                            case 4:
                                printf("%s      KEY_OD\n", currentToken);
                                break;
                            default:
                                printf("%s      IDENT\n", currentToken);
                                break;
                        }
                        pointer += tokenCounter;
                    } else if (isSpecialChar(currentChar)) {
                        char specialToken[3] = "";
                        specialToken[0] = currentChar;
                        specialToken[1] = '\0';

                        if (pointer + 1 < lineLength) {
                            strncat(specialToken, &line[pointer + 1], 1);

                            if (isTwoCharSpecialChar(specialToken)) {
                                int specialTokenIndex = getSpecialCharIndex(specialToken);

                                switch (specialTokenIndex) {
                                    case 0:
                                        printf("%s      ASSIGN_OP\n", specialToken);
                                        break;
                                    case 1:
                                        printf("%s      NEQUAL_OP\n", specialToken);
                                        break;
                                    case 2:
                                        printf("%s      GEQUAL_OP\n", specialToken);
                                        break;
                                    case 3:
                                        printf("%s      LEQUAL_OP\n", specialToken);
                                        break;
                                    case 4:
                                        printf("%s      EQUAL_OP\n", specialToken);
                                        break;
                                    case 5:
                                        printf("%s      INC_OP\n", specialToken);
                                        break;
                                    case 6:
                                        printf("%s      DEC_OP\n", specialToken);
                                        break;
                                    default:
                                        printf("%s      UNKNOWN\n", specialToken);
                                        break;
                                }
                                pointer += 2;
                            } else {
                                switch (currentChar) {
                                    case '<':
                                        printf("%c      LESSER_OP\n", currentChar);
                                        break;
                                    case '>':
                                        printf("%c      GREATER_OP\n", currentChar);
                                        break;
                                    case '=':
                                        printf("%c      ASSIGN_OP\n", currentChar);
                                        break;
                                    case '+':
                                        printf("%c      ADD_OP\n", currentChar);
                                        break;
                                    case '-':
                                        printf("%c      SUB_OP\n", currentChar);
                                        break;
                                    case '*':
                                        printf("%c      MULT_OP\n", currentChar);
                                        break;
                                    case '/':
                                        printf("%c      DIV_OP\n", currentChar);
                                        break;
                                    case '(':
                                        printf("%c      LEFT_PAREN\n", currentChar);
                                        break;
                                    case ')':
                                        printf("%c      RIGHT_PAREN\n", currentChar);
                                        break;
                                    case '{':
                                        printf("%c      LEFT_CBRACE\n", currentChar);
                                        break;
                                    case '}':
                                        printf("%c      RIGHT_CBRACE\n", currentChar);
                                        break;
                                    case ';':
                                        printf("%c      SEMICOLON\n", currentChar);
                                        break;
                                    default:
                                        printf("%c      UNKNOWN\n", currentChar);
                                        break;
                                }
                                pointer++;
                            }
                        } else {
                            switch (currentChar) {
                                case '<':
                                    printf("%c      LESSER_OP\n", currentChar);
                                    break;
                                case '>':
                                    printf("%c      GREATER_OP\n", currentChar);
                                    break;
                                case '=':
                                    printf("%c      EQUAL_OP\n", currentChar);
                                    break;
                                case '+':
                                    printf("%c      ADD_OP\n", currentChar);
                                    break;
                                case '-':
                                    printf("%c      SUB_OP\n", currentChar);
                                    break;
                                case '*':
                                    printf("%c      MULT_OP\n", currentChar);
                                    break;
                                case '/':
                                    printf("%c      DIV_OP\n", currentChar);
                                    break;
                                case '(':
                                    printf("%c      LEFT_PAREN\n", currentChar);
                                    break;
                                case ')':
                                    printf("%c      RIGHT_PAREN\n", currentChar);
                                    break;
                                case '{':
                                    printf("%c      LEFT_CBRACE\n", currentChar);
                                    break;
                                case '}':
                                    printf("%c      RIGHT_CBRACE\n", currentChar);
                                    break;
                                case ';':
                                    printf("%c      SEMICOLON\n", currentChar);
                                    break;
                                default:
                                    printf("%c      UNKNOWN\n", currentChar);
                                    break;
                            }
                            pointer++;
                        }
                    } else if (currentChar == ' ' || currentChar == '\t' ||
                               currentChar == '\n' || currentChar == '\v' ||
                               currentChar == '\f' || currentChar == '\r') {
                        pointer++;
                    } else {
                        printf("%c      UNKNOWN\n", currentChar);
                        pointer++;
                    }
                }
            }
            fclose(inputFile);
        } else {
            printf("Unable to open the file\n");
        }
    } else {
        printf("Insufficient arguments provided\n");
    }
    return 0;
}
