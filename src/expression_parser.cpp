#include "../include/expression_parser.hpp"

Operator ExpressionParser::getOperator(const std::string& op) const {
    if (op == "+") return OP_ADD;
    if (op == "-") return OP_SUB;
    if (op == "*") return OP_MUL;
    if (op == "/") return OP_DIV;
    if (op == "~") return OP_NEG;
    return OP_NONE;
}

int ExpressionParser::getPrecedence(Operator op) const {
    switch (op) {
        case OP_NEG: return 4;
        case OP_MUL: case OP_DIV: return 3;
        case OP_ADD: case OP_SUB: return 2;
        default: return 0;
    }
}

char ExpressionParser::getAssociativity(Operator op) const {
    if (op == OP_NEG) return 'r';
    return 'l';
}

bool ExpressionParser::isOperator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::vector<Token> ExpressionParser::tokenize(const std::string& expression) {
    std::vector<Token> tokens;
    TokenType lastTokenType = TokenType::None;
    
    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];
        
        if (std::isspace(c)) {
            continue;
        }
        
        if (std::isdigit(c)) {
            std::string number;
            while (i < expression.length() && std::isdigit(expression[i])) {
                number += expression[i];
                i++;
            }
            i--;
            tokens.push_back({TokenType::Number, number});
            lastTokenType = TokenType::Number;
        }
        else if (c == '+' || c == '*' || c == '/') {
            tokens.push_back({TokenType::Operator, std::string(1, c)});
            lastTokenType = TokenType::Operator;
        }
        else if (c == '-') {
            if (lastTokenType == TokenType::None || 
                lastTokenType == TokenType::Operator || 
                lastTokenType == TokenType::LParen) {
                tokens.push_back({TokenType::Operator, "~"});
            } else {
                tokens.push_back({TokenType::Operator, "-"});
            }
            lastTokenType = TokenType::Operator;
        }
        else if (c == '(') {
            tokens.push_back({TokenType::LParen, "("});
            lastTokenType = TokenType::LParen;
        }
        else if (c == ')') {
            tokens.push_back({TokenType::RParen, ")"});
            lastTokenType = TokenType::RParen;
        }
        else {
            throw std::runtime_error("Invalid character: " + std::string(1, c));
        }
    }
    
    return tokens;
}

std::vector<Token> ExpressionParser::convertToRPN(const std::vector<Token>& tokens) {
    std::vector<Token> output;
    std::stack<Token> operators;
    
    for (const auto& token : tokens) {
        if (token.type == TokenType::Number) {
            output.push_back(token);
        }
        else if (token.type == TokenType::Operator) {
            Operator op1 = getOperator(token.value);
            
            while (!operators.empty() && operators.top().type == TokenType::Operator) {
                Operator op2 = getOperator(operators.top().value);
                
                if ((getPrecedence(op2) > getPrecedence(op1)) ||
                    (getPrecedence(op2) == getPrecedence(op1) && getAssociativity(op1) == 'l')) {
                    output.push_back(operators.top());
                    operators.pop();
                } else {
                    break;
                }
            }
            operators.push(token);
        }
        else if (token.type == TokenType::LParen) {
            operators.push(token);
        }
        else if (token.type == TokenType::RParen) {
            while (!operators.empty() && operators.top().type != TokenType::LParen) {
                output.push_back(operators.top());
                operators.pop();
            }
            
            if (operators.empty()) {
                throw std::runtime_error("Mismatched parentheses");
            }
            
            operators.pop();
        }
    }
    
    while (!operators.empty()) {
        if (operators.top().type == TokenType::LParen) {
            throw std::runtime_error("Mismatched parentheses");
        }
        output.push_back(operators.top());
        operators.pop();
    }
    
    return output;
}

int ExpressionParser::evaluateRPN(const std::vector<Token>& rpn) {
    std::stack<int> stack;
    
    for (const auto& token : rpn) {
        if (token.type == TokenType::Number) {
            stack.push(std::stoi(token.value));
        }
        else if (token.type == TokenType::Operator) {
            Operator op = getOperator(token.value);
            
            if (op == OP_NEG) {
                if (stack.empty()) {
                    throw std::runtime_error("Invalid expression");
                }
                int a = stack.top();
                stack.pop();
                stack.push(-a);
            }
            else {
                if (stack.size() < 2) {
                    throw std::runtime_error("Invalid expression");
                }
                
                int b = stack.top(); stack.pop();
                int a = stack.top(); stack.pop();
                
                switch (op) {
                    case OP_ADD: stack.push(a + b); break;
                    case OP_SUB: stack.push(a - b); break;
                    case OP_MUL: stack.push(a * b); break;
                    case OP_DIV:
                        if (b == 0) throw std::runtime_error("Division by zero");
                        stack.push(a / b);
                        break;
                    default:
                        throw std::runtime_error("Unknown operator");
                }
            }
        }
    }
    
    if (stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }
    
    return stack.top();
}

int ExpressionParser::evaluate(const std::string& expression) {
    tokens = tokenize(expression);
    output = convertToRPN(tokens);
    return evaluateRPN(output);
}

void ExpressionParser::printTokens(const std::vector<Token>& tokens) const {
    std::cout << "Токены:\n";
    for (const auto& token : tokens) {
        std::cout << (token.type == TokenType::Number ? "Число: " : "Оператор: ") 
                  << token.value << '\n';
    }
}

void ExpressionParser::printRPN(const std::vector<Token>& rpn) const {
    std::cout << "ОПЗ: ";
    for (const auto& token : rpn) {
        std::cout << token.value << ' ';
    }
    std::cout << '\n';
}