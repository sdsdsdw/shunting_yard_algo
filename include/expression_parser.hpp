#ifndef EXPRESSION_PARSER_HPP
#define EXPRESSION_PARSER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <cctype>

enum class TokenType {
    Number,
    Operator,
    LParen,
    RParen,
    None
};

struct Token {
    TokenType type;
    std::string value;
};

enum Operator {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_NEG,
    OP_NONE
};

class ExpressionParser {
    private:
        std::vector<Token> tokens;
        std::vector<Token> output;
        
        Operator getOperator(const std::string& op) const;
        int getPrecedence(Operator op) const;
        char getAssociativity(Operator op) const;
        bool isOperator(char c) const;
        
        int evaluateRPN(const std::vector<Token>& rpn);
        
    public:
        std::vector<Token> tokenize(const std::string& expression);
        std::vector<Token> convertToRPN(const std::vector<Token>& tokens);
        int evaluate(const std::string& expression);
        void printTokens(const std::vector<Token>& tokens) const;
        void printRPN(const std::vector<Token>& rpn) const;
};

#endif // EXPRESSION_PARSER_HPP