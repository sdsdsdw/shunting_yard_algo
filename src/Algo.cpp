#include "../include/Algo.h"

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_NONE
}Operator;

typedef enum {
    TOK_NUMBER,
    TOK_OPERATOR,
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_END
} TokenType;

int alfa(std::string input, std::stack<char>& st)
{
    for(char c : input) {
        if (c != ' ') 
        {
            st.push(c);
        }
    }
    return 0;
}