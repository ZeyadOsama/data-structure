/*
 *
 * C Program To Handle Expressions
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myString.h"
#include "stack.h"
#include "expressions.h"

#define true 1
#define false 0


/* boolean check.
 * checks if a given character is alphabetical operand.
 */
int isAlphaOperand (char character)
{
    return ( character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z' );
}


/* boolean check.
 * checks if a given character is numerical operand.
 */
int isNumericOperand (char character)
{
    return ( character >='0' && character<='9' );
}


/* boolean check.
 * checks if a given character is operator.
 */
int isOperator (char character)
{
    switch (character)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return true;

        default:
            return false;
    }

}
 

/* utility function.
 * returns precedence of a given operator.
 * higher returned value means higher precedence,
 */
int getPriority (char character)
{
    switch (character)
    {
        case '+':
        case '-':
            return 1;
     
        case '*':
        case '/':
            return 2;
     
        case '^':
            return 3;

        case '(':
            return 9;

        default:
            return -1;
    }
}


/* function that converts given infix expression to postfix expression
 */
String infixToPostfix (String infix)
{

    String postfix;

    // iterators
    int i, k;
 
    // create a stack of capacity to push operators.
    // stack is equal to expression size.
    Stack * stack = constructStack(strlen(infix)-1);
    
 
    // pop all the operators from the stack
    while (!isEmptyStack(stack))
        exp[++k] = pop(stack );
 
    exp[++k] = '\0';

    // return postfix string
    return exp;
}


/* function that converts given postfix expression to infix expression
 */
String postfixToInfix (String postfix)
{
    
    return infix;
}
 

/* evaluates a given postfix expression
 */
TYPE evaluatePostfix (String postfix)
{
    // stack to store operands
    Stack * operands = constructStack(strlen(postfix));

    int i;
    for (i=0 ; i<strlen(postfix) ; i++)
    {
        // delimiters should be excluded
        if ( !isOperator(postfix[i]) && !isNumericOperand(postfix[i]) )
            continue;


        // current element is operand
        // push to stack
        if ( isNumericOperand(postfix[i]) )
            push(operands, (TYPE)postfix[i]-'0');

        // current element is operator
        // pop last two operands stack
        else if ( isOperator(postfix[i]) )
        {
            // dummy variables to store last two popped operands
            int x,y;

            // first operand sanity check
            if(isEmptyStack(operands)) return NULL;
            else x = pop(operands);

            // second operand sanity check
            if(isEmptyStack(operands)) return NULL;
            else y = pop(operands);

            // switch on operator
            switch(postfix[i])
            {
                case '+' : push(operands, x+y); break;
                case '-' : push(operands, x-y); break;
                case '*' : push(operands, x*y); break;
                case '/' : push(operands, x/y); break;

                // error
                default : return NULL;
            }
        }
    }

    // stack at this point of time can not have more than one element
    if(operands->top != 1)
        return NULL;

    return getPeekValue(operands);
}


/* evaluates a given infix expression.
 * converts first to postfix.
 */
TYPE evaluateInfix (String postfix)
{
    // converting step
    char postfix[] = infixToPostfix (String infix);

    return evaluatePostfix(postfix);
}