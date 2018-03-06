/*
 *
 * C Program To Handle Expressions.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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
            break;
    }

    // default case better be outside switch case
    // avoiding compiling warnings
    return false;
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
            break;
    }

    // default case better be outside switch case
    // avoiding compiling warnings
    return -1;
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

    // string iterator for reallocating and indexing
    int k = 0;

    // counter variables for mismatched parenthesis exception
    // should be equal at end of expression
    int openedBrackets = 0;
    int closedBrackets = 0;

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
        else if ( *infix == '(' )
        {
            // assure valid expression
            // '( followed by operator
            if ( isOperator(*(infix + 1)) )
                return NULL;

            // bracket opened
            openedBrackets++;

            // push to stack
            push(operators , *infix);
        }


        // scanned character is an ')'
        else if ( *infix == ')' )
        {
            // assure valid expression
            // ')' preceded by operator
            if ( isOperator(*(infix - 1)) )
                return NULL;

            // bracket closed
            closedBrackets++;

            // dummy variable to store popped element to be added into postfix string
            char temp;

            // pop and output from the stack until an '(' is encountered
            while ( !isEmptyStack(operators) && (temp = pop(operators)) != '(')
            {
                // i.e. brackets should not be added to postfix strings
                if( temp != '(' )
                {
                    postfix = realloc(postfix, (++k)*sizeof(char) );
                    postfix[k-1] = temp;
                }
            }
        }


        // scanned character is operator
        else if ( isOperator(*infix) )
        {
            // check priority
            while ( getPriority(getPeekValue(operators)) >= getPriority(*infix) )
            {
                // dummy variable to store popped element to be added into postfix string
                char temp = pop(operators);

                // scanned character priority is less than stack's peek value
                // pop all less prior
                // i.e. brackets should not be added to postfix strings
                if( temp != '(' )
                {
                    postfix = realloc(postfix, (++k)*sizeof(char) );
                    postfix[k-1] = temp;
                }
            }

            // then push scanned character
            push(operators , *infix);
        }


        // scanned character is space
        // considered a delimiter
        // skipped
        else if ( isspace(*infix) );


        // scanned character is neither alphabetical/numerical operand nor operator
        // invalid statement
        else
            return NULL;


        // increment pointer
        infix++;
    }


    // pop all left operators in stack into postfix string
    while (!isEmptyStack(operators))
    {
        postfix = realloc(postfix, (++k)*sizeof(char) );
        postfix[k-1] = pop(operators);
    }


    // add null character to end of string
    postfix = realloc(postfix, (++k)*sizeof(char) );
    postfix[k-1] = '\0';


    // check for mismatched parenthesis
    // should be equal at end of expression
    // i.e. opening parenthesis with no closing one
    if (openedBrackets != closedBrackets)
        return NULL;


    return postfix;
}


/* evaluates a given postfix expression
 */
TYPE evaluatePostfix (String postfix)
{
    // assure an expression is received
    // avoiding run-time errors
    if (postfix == NULL)
        return (TYPE) 0;

    // stack to store operands
    Stack * operands = constructStack(strlen(postfix));

    while ( *postfix != '\0' )
    {
        // delimiters should be excluded
        if ( !isOperator(*postfix) && !isNumericOperand(*postfix) )
            continue;


        // current element is operand
        // push to stack
        if ( isNumericOperand(*postfix) )
            push(operands, (TYPE) *postfix - '0');

        // current element is operator
        // pop last two operands stack
        else if ( isOperator(*postfix) )
        {
            // dummy variables to store last two popped operands
            int x,y;

            // first popped is second operand
            // sanity check
            if ( isEmptyStack(operands) )
                return 0;
            else
                y = pop(operands);


            // second popped is first operand
            // sanity check
            if ( isEmptyStack(operands) )
                return 0;
            else
                x = pop(operands);


            // operational step based on operator
            switch (*postfix)
            {
                case '+' :
                    push(operands, x+y);
                    break;

                case '-' :
                    push(operands, x-y);
                    break;

                case '*' :
                    push(operands, x*y);
                    break;

                case '/' :
                    // handling division by zero
                    // mathematical error
                    if(y == 0)
                        return 0;

                    push(operands, x/y);
                    break;

                case '^' :
                    push(operands, pow(x,y));
                    break;

                // unexpected error
                default :
                    return 0;
            }
        }


        // scanned character is space
        // considered a delimiter
        // skipped
        else if ( isspace(*postfix) );


        // scanned character is neither alphabetical/numerical operand nor operator
        // invalid statement
        else
            return NULL;

        // increment pointer
        postfix++;
    }

    // stack at this point of time can not have more than one element
    if (operands->top != 1)
        return 0;

    return getPeekValue(operands);
}


/* evaluates a given infix expression.
 * converts to postfix.
 * evaluate postfix.
 */
TYPE evaluateInfix (String infix)
{
    // converting step
    String postfix = infixToPostfix(infix);

    return evaluatePostfix(postfix);
}
