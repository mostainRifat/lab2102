#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

// Function to check if the given string is a valid infix expression
bool isValidInfixExpression(string expression)
{
    string operators = "+-*/()";
    string operands = "0123456789";

    // Check if the expression starts and ends with an operand
    if (expression[0] not in operands || expression[-1] not in operands)
    {
        return false;
    }

    // Check if consecutive characters are not both operators
    for (int i = 1; i < expression.length(); i++)
    {
        if (expression[i] in operators && expression[i - 1] in operators)
        {
            return false;
        }
    }

    // Check if there are matching parentheses
    stack<char> stack;
    for (char c : expression)
    {
        if (c == '(')
        {
            stack.push(c);
        }
        else if (c == ')')
        {
            if (!stack.empty() && stack.top() == '(')
            {
                stack.pop();
            }
            else
            {
                return false;
            }
        }
    }

    return stack.empty();
}

// Function to determine the precedence of operators
int precedence(char operator1, char operator2)
{
    if (operator1 == '+' || operator1 == '-')
    {
        return 1;
    }
    else if (operator1 == '*' || operator1 == '/')
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

// Function to evaluate the infix expression
int evaluateInfixExpression(string expression)
{
    // Convert infix expression to postfix expression using two stacks
    stack<char> operatorStack;
    string postfixExpression = "";

    for (char c : expression)
    {
        if (c.isdigit())
        {
            postfixExpression += c;
        }
        else if (c == '(')
        {
            operatorStack.push(c);
        }
        else if (c == ')')
        {
            while (!operatorStack.empty() && operatorStack.top() != '(')
            {
                postfixExpression += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
        }
        else
        {
            while (!operatorStack.empty() && precedence(operatorStack.top(), c) >= precedence(c, c))
            {
                postfixExpression += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);
        }
    }

    while (!operatorStack.empty())
    {
        postfixExpression += operatorStack.top();
        operatorStack.pop();
    }

    // Evaluate the postfix expression
    stack<int> operandStack;
    for (char c : postfixExpression)
    {
        if (c.isdigit())
        {
            operandStack.push(c - '0');
        }
        else
        {
            int operand2 = operandStack.top();
            operandStack.pop();
            int operand1 = operandStack.top();
            operandStack.pop();

            switch (c)
            {
            case '+':
                operandStack.push(operand1 + operand2);
                break;
            case '-':
                operandStack.push(operand1 - operand2);
                break;
            case '*':
                operandStack.push(operand1 * operand2);
                break;
            case '/':
                operandStack.push(operand1 / operand2);
                break;
            }
        }
    }

    return operandStack.top();
}

// Main function
int main()
{
    string expression;

    cout << "Enter an infix expression: ";
    cin >> expression;

    if (isValidInfixExpression(expression))
    {
        int result = evaluateInfixExpression(expression);
        cout << "Result: " << result << endl;
    }
    else
    {
        cout << "Invalid infix expression" << endl;
    }

    return 0;
}
