#include <iostream>
#include <string>
#include <stack>
#include "../include/Algo.h"

using std::cout, std::string, std::stack;

int main()
{
    try
    {
        stack<char> st;
        string input;
        
        cout << "Write smth: ";
        std::getline(std::cin, input);
        
        alfa(input, st);

        cout << "LIFO: ";
        while(!st.empty()) 
        {
            cout << (char)st.top();
            st.pop();
        }
        cout << '\n';
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
    
    return 0;
}
