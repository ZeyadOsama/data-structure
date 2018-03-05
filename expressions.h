#ifndef EXPRESSIONS_H_INCLUDED
#define EXPRESSIONS_H_INCLUDED

#include "myString.h"
#include "stack.h"


// boolean checks
int isAlphaOperand (char character);
int isNumericOperand (char character);
int isOperator (char character);

// conversion functions
String infixToPostfix (String infix);
String postfixToInfix (String postfix);

// evaluation functions
TYPE evaluatePostfix (String postfix);
TYPE evaluateInfix (String postfix);

// utility functions
int getPriority (char character);


#endif // STACK_H_INCLUDED
