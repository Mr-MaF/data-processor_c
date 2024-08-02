// Code Breakdown

// 1. Includes and Namespace:

#include <bits/stdc++.h>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

// The #include <bits/stdc++.h> directive includes most of the standard C++ libraries, which is convenient but not recommended for production code due to potential performance issues.
//  using namespace std; is used to avoid prefixing standard library components with std::.

// 2. Operator Precedence Function:


int precedence(char operatorChar) {
    switch (operatorChar) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return -1;
    }
}

// Defines the precedence of operators: + and - have lower precedence than *, /, and %.

// 3. Apply Operator Function:


double applyOperator(char operatorChar, double b, double a) {
    switch (operatorChar) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                throw runtime_error("Division by zero");
            }
            return a / b;
        case '%':
            if (b == 0) {
                throw runtime_error("Modulus by zero");
            }
            return static_cast<int>(a) % static_cast<int>(b);
        default:
            throw runtime_error("Invalid operator");
    }
}

// Performs the arithmetic operations and handles division/modulus by zero exceptions.

// 4. Evaluate Expression Function:


double evaluateExpression(const string& expression) {
    stack<double> numbers;
    stack<char> operators;

    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];

        if (isdigit(c) || c == '.') {
            string number;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                number += expression[i++];
            }
            --i;
            numbers.push(stod(number));
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
            while (!operators.empty() && precedence(c) <= precedence(operators.top())) {
                double b = numbers.top(); numbers.pop();
                double a = numbers.top(); numbers.pop();
                numbers.push(applyOperator(operators.top(), b, a));
                operators.pop();
            }
            operators.push(c);
        } else {
            throw runtime_error("Invalid character in expression");
        }
    }

    while (!operators.empty()) {
        double b = numbers.top(); numbers.pop();
        double a = numbers.top(); numbers.pop();
        numbers.push(applyOperator(operators.top(), b, a));
        operators.pop();
    }

    return numbers.top();
}

  // Parses and evaluates the expression using stacks for numbers and operators.
  // Handles multi-digit numbers and floating-point numbers.

// 5. Main Function:


int main() {
    string expression;

    cout << "Enter a mathematical expression: ";
    getline(cin, expression);

    try {
        double result = evaluateExpression(expression);
        cout << "The result is: " << result << endl;
    } catch (const exception& e) {
        cout << "Invalid expression: " << e.what() << endl;
    }

    return 0;
}

//  Reads the expression from the user, evaluates it, and prints the result.
//  Handles exceptions and prints error messages if the expression is invalid.
