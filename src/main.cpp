#include "../include/expression_parser.hpp"
#include <iostream>

int main() {
    try {
        ExpressionParser parser;
        std::string expression = "-5 + 3";
        
        std::cout << "Выражение: " << expression << "\n\n";
        
        auto tokens = parser.tokenize(expression);
        parser.printTokens(tokens);
        
        std::cout << '\n';
        
        auto rpn = parser.convertToRPN(tokens);
        parser.printRPN(rpn);
        
        std::cout << '\n';
        
        int result = parser.evaluate(expression);
        std::cout << "Результат: " << result << '\n';
        
    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << '\n';
        return 1;
    }
    
    return 0;
}