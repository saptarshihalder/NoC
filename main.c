#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    INTEGER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    ID,
    ASSIGN,
    SEMICOLON,
    IF,
    ELSE,
    WHILE,
    PRINT,
    STRING,
    LESS,
    GREATER,
    END
} TokenType;

typedef struct {
    TokenType type;
    int value;
    char* identifier;
} Token;

char* input;
int pos = 0;

void advance() {
    pos++;
}

char current_char() {
    return input[pos];
}

Token get_next_token() {
    while (current_char() != '\0') {
        if (isspace(current_char())) {
            advance();
            continue;
        }
        if (isdigit(current_char())) {
            int value = 0;
            while (isdigit(current_char())) {
                value = value * 10 + (current_char() - '0');
                advance();
            }
            return (Token){INTEGER, value, NULL};
        }
        if (isalpha(current_char())) {
            char* identifier = malloc(100 * sizeof(char));
            int i = 0;
            while (isalnum(current_char())) {
                identifier[i++] = current_char();
                advance();
            }
            identifier[i] = '\0';
            if (strcmp(identifier, "if") == 0 || strcmp(identifier, "else") == 0 ||
                strcmp(identifier, "while") == 0 || strcmp(identifier, "print") == 0)
                return (Token){PRINT, 0, identifier};
            else
                return (Token){ID, 0, identifier};
        }
        switch (current_char()) {
            case '+':
                advance();
                return (Token){PLUS, 0, NULL};
            case '-':
                advance();
                return (Token){MINUS, 0, NULL};
            case '*':
                advance();
                return (Token){MULTIPLY, 0, NULL};
            case '/':
                advance();
                return (Token){DIVIDE, 0, NULL};
            case '(':
                advance();
                return (Token){LPAREN, 0, NULL};
            case ')':
                advance();
                return (Token){RPAREN, 0, NULL};
            case '{':
                advance();
                return (Token){LBRACE, 0, NULL};
            case '}':
                advance();
                return (Token){RBRACE, 0, NULL};
            case '=':
                advance();
                return (Token){ASSIGN, 0, NULL};
            case ';':
                advance();
                return (Token){SEMICOLON, 0, NULL};
            case '<':
                advance();
                return (Token){LESS, 0, NULL};
            case '>':
                advance();
                return (Token){GREATER, 0, NULL};
            case '"':
                advance();
                char* string_literal = malloc(100 * sizeof(char));
                int i = 0;
                while (current_char() != '"') {
                    string_literal[i++] = current_char();
                    advance();
                }
                string_literal[i] = '\0';
                advance();
                return (Token){STRING, 0, string_literal};
            default:
                fprintf(stderr, "Invalid character: %c\n", current_char());
                exit(1);
        }
    }
    return (Token){END, 0, NULL};
}

void execute_code() {
    Token token;
    while ((token = get_next_token()).type != END) {
        if (token.type == PRINT) {
            token = get_next_token();
            if (token.type == LPAREN) {
                while ((token = get_next_token()).type != RPAREN) {
                    if (token.type == ID || token.type == STRING) {
                        printf("%s ", token.identifier);
                    } else if (token.type == INTEGER) {
                        printf("%d ", token.value);
                    }
                }
                printf("\n");
            }
        }
    }
}

int main() {
    printf("Enter code: ");
    input = malloc(100 * sizeof(char));
    fgets(input, 100, stdin);

    execute_code();

    free(input);
    return 0;
}
