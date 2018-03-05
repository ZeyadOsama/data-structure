/*
 *
 * C Program To Handle Expressions.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myString.h"
#include "stack.h"

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
 * higher returned value means higher precedence.
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


/* function that converts given infix expression to postfix expression.
 * returns NULL in exception cases.
 */
String infixToPostfix (String infix)
{
    // stores operators
    Stack * operators = constructStack(strlen(infix));

    // postfix string declaration
    char * postfix = NULL;

    // string iterator for reallocating and storing
    int k = 0;

    // boolean variable for mismatched parenthesis exception
    int waitingForClosingBracket = false;

    while ( *infix != '\0' )
    {
        // checks whether entered value is either
        // decimal digit or an uppercase or lowercase letter
        // i.e. can also be -> if ( isalnum(*infix) )
        if ( isNumericOperand(*infix) || isAlphaOperand(*infix) )
        {
            postfix = realloc(postfix, (++k)*sizeof(char) );
            postfix[k-1] = *infix;
        }


        // scanned character is an '('
        // push to stack
        else if ( *infix == '(' )
        {
            // bracket opened
            waitingForClosingBracket = true;
            
            push(operators , *infix);
        }


        // scanned character is an ')'
        // pop and output from the stack until an '(' is encountered
        else if ( *infix == ')' )
        {
            // bracket closed
            waitingForClosingBracket = false;

            // dummy variable to store popped element to be added to string later
            char temp;

            while ( !isEmptyStack(operators) && (temp = pop(operators)) != '(')
            {
                // check for mismatched parenthesis
                // i.e. closing parenthesis with no opening one
                if( isEmptyStack(operators) && temp != '(' )
                    return NULL;

                postfix = realloc(postfix, (++k)*sizeof(char) );
                postfix[k-1] = temp;
            }
        }


        else if ( isOperator(*infix) )
        {
            // check priority
            while ( getPriority(getPeekValue(operators)) >= getPriority(*infix) )
            {
                // scanned character priority is less than stack's peek value
                // pop all less prior
                postfix = realloc(postfix, (++k)*sizeof(char) );
                postfix[k-1] =pop(operators);
            }

            // then push scanned character
            push(operators , *infix);
        }

        // increment pointer
        infix++;
    }

    while (!isEmptyStack(operators))
    {
        postfix = realloc(postfix, (++k)*sizeof(char) );
        postfix[k-1] =pop(operators);
    }

    // add null char to end string
    postfix = realloc(postfix, (++k)*sizeof(char) );
    postfix[k-1] ='\0';


    // check for mismatched parenthesis
    // i.e. opening parenthesis with no closing one    
    if (waitingForClosingBracket)
        return NULL;

    return postfix;
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
            if(isEmptyStack(operands)) return (TYPE)NULL;
            else x = pop(operands);

            // second operand sanity check
            if(isEmptyStack(operands)) return (TYPE)NULL;
            else y = pop(operands);

            // switch on operator
            switch(postfix[i])
            {
                case '+' : push(operands, x+y); break;
                case '-' : push(operands, x-y); break;
                case '*' : push(operands, x*y); break;
                case '/' : push(operands, x/y); break;

                // error
                default : return (TYPE)NULL;
            }
        }
    }

    // stack at this point of time can not have more than one element
    if(operands->top != 1)
        return (TYPE)NULL;

    return getPeekValue(operands);
}


/* evaluates a given infix expression.
 * converts first to postfix.
 */
TYPE evaluateInfix (String infix)
{
    // converting step
    String postfix = infixToPostfix(infix);

    return evaluatePostfix(postfix);
}
