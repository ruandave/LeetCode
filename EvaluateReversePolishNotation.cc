// Problem description:
// http://oj.leetcode.com/problems/evaluate-reverse-polish-notation/
// Evaluate the value of an arithmetic expression in Reverse Polish Notation.
// Valid operators are +, -, *, /. Each operand may be an integer or another expression.
// Some examples:
// ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
// ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
    public:
        // Using a stack. Consider only valid expression. 
        // (1) Operand input: push_back 
        // (2) Operator input: pop_back two operands, evaluate, and push the result back 
        // Time: O(n)
        // Space: O(n)
        int evalRPN(vector<string> &tokens) 
        {
            vector<int> stack;
            for(int i = 0; i < tokens.size(); i++)
            {
                try
                {
                    int op = stoi(tokens[i], NULL, 10); //convert a string token into number
                    stack.push_back(op);
                }
                catch(const std::invalid_argument& ia) // exception: operators (+-*/) found
                {
                    //cerr << "Operators found due to " << ia.what() << "\n";
                    int op2 = stack.back();
                    stack.pop_back();
                    int op1 = stack.back();
                    stack.pop_back();
                    if(tokens[i] == "+")
                        stack.push_back(op1+op2);
                    else if(tokens[i] == "-")
                        stack.push_back(op1-op2);
                    else if(tokens[i] == "*")
                        stack.push_back(op1*op2);
                    else
                        stack.push_back(op1/op2); // Consider only int operation due to prob. description 
                }
            }
            return stack.back();
        }
};

int main(int argc, char* argv[])
{
    Solution sol;
    // test benchmark
    vector<string> tokens;
    tokens.push_back("4");
    tokens.push_back("13");
    tokens.push_back("5");
    tokens.push_back("/");
    tokens.push_back("+");
    cout << sol.evalRPN(tokens) << "\n";
    return 1;
}
