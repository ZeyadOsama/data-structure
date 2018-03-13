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
        case '(':
            return 0;

        case '+':
        case '-':
            return 1;

        case '*':
        case '/':
            return 2;

        case '^':
            return 3;

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
    // assure an expression is received
    // avoiding run-time errors
    if (infix == NULL)
        return NULL;

    // stores operators
    Stack * operatorStack = constructStack(strlen(infix));

    // stores brackets
    // stack for validating a given infix
    Stack * bracketStack = constructStack(strlen(infix));

    // boolean for validating a given infix
    short hasOperand = false;

    // postfix string declaration
    char * postfix = NULL;

    // string iterator for reallocating and indexing
    int k = 0;


    // loop on string
    while ( *infix != '\0' )
    {
        // checks whether entered value is either
        // decimal digit or an uppercase or lowercase letter
        // i.e. can also be -> if ( isalnum(*infix) )
        if ( isNumericOperand(*infix) || isAlphaOperand(*infix) )
        {
            // assure valid expression
            hasOperand = true;

            postfix = realloc(postfix, (++k)*sizeof(char) );
            postfix[k-1] = *infix;
        }


        // scanned character is an '('
        else if ( *infix == '(' )
        {
            // assure valid expression
            // '( followed by operator
            if ( isOperator(*(infix + 1)) )
            {
                // deallocate due function stacks
                // deallocate string
                // avoid memory leakage
                destructStack(operatorStack);
                destructStack(bracketStack);
                free(postfix);

                return NULL;
            }

            // assure valid expression
            // bracket opened
            // push to stack
            push(bracketStack,'(');

            // push operand to stack
            push(operatorStack , *infix);
        }


        // scanned character is an ')'
        else if ( *infix == ')' )
        {
            // assure valid expression
            // ')' preceded by operator
            if ( isOperator(*(infix - 1)) )
            {
                // deallocate due function stacks
                // deallocate string
                // avoid memory leakage
                destructStack(operatorStack);
                destructStack(bracketStack);
                free(postfix);

                return NULL;
            }

            // assure valid expression
            // bracket closed
            if ( isEmptyStack(bracketStack) )
                return NULL;
            else
                pop(bracketStack);


            // dummy variable to store popped element to be added into postfix string
            char temp;

            // pop and output from the stack until an '(' is encountered
            while ( !isEmptyStack(operatorStack) && (temp = pop(operatorStack)) != '(')
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
            while ( getPriority(getPeekValue(operatorStack)) >= getPriority(*infix) )
            {
                // dummy variable to store popped element to be added into postfix string
                char temp = pop(operatorStack);

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
            push(operatorStack , *infix);
        }


        // scanned character is space
        // considered a delimiter
        // skipped
        else if ( isspace(*infix) );


        // scanned character is neither alphabetical/numerical operand nor operator
        // invalid expression
        else
        {
            // deallocate due function stacks
            // deallocate string
            // avoid memory leakage
            destructStack(operatorStack);
            destructStack(bracketStack);
            free(postfix);

            return NULL;
        }


        // increment pointer
        infix++;
    }


    // pop all left operators in stack into postfix string
    while (!isEmptyStack(operatorStack))
    {
        postfix = realloc(postfix, (++k)*sizeof(char) );
        postfix[k-1] = pop(operatorStack);
    }


    // add null character to end of string
    postfix = realloc(postfix, (++k)*sizeof(char) );
    postfix[k-1] = '\0';


    // assure valid expression.
    // check for mismatched parenthesis, operand stack must be empty at end of expression.
    // check for operands, boolean must be true.
    if ( !isEmptyStack(bracketStack) || !hasOperand )
    {
        // deallocate due function stacks
        // deallocate string
        // avoid memory leakage
        destructStack(operatorStack);
        destructStack(bracketStack);
        free(postfix);

        return NULL;
    }

    // deallocate due function stacks
    // deallocate string
    // avoid memory leakage
    destructStack(operatorStack);
    destructStack(bracketStack);

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
    Stack * operandStack = constructStack(strlen(postfix));

    // loop on string
    while ( *postfix != '\0')
    {
        // current element is operand
        // push to stack
        if ( isNumericOperand(*postfix) )
            push(operandStack, (TYPE) *postfix - '0');

        // current element is operator
        // pop last two operands stack
        else if ( isOperator(*postfix) )
        {
            // dummy variables to store last two popped operands
            int x,y;

            // first popped is second operand
            // sanity check
            if ( isEmptyStack(operandStack) )
            {
                // deallocate due function stack
                // avoid memory leakage
                destructStack(operandStack);

                return 0;
            }

            else
                y = pop(operandStack);


            // second popped is first operand
            // sanity check
            if ( isEmptyStack(operandStack) )
            {
                // deallocate due function stack
                // avoid memory leakage
                destructStack(operandStack);

                return 0;
            }

            else
                x = pop(operandStack);


            // operational step based on operator
            switch(*postfix)
            {
                case '+' :
                    push(operandStack, x+y);
                    break;

                case '-' :
                    push(operandStack, x-y);
                    break;

                case '*' :
                    push(operandStack, x*y);
                    break;

                case '/' :
                    // handling division by zero
                    // mathematical error
                    if(y == 0)
                    {
                        // deallocate due function stack
                        // avoid memory leakage
                        destructStack(operandStack);

                        return 0;
                    }

                    push(operandStack, x/y);
                    break;

                case '^' :
                    push(operandStack, pow(x,y));
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
        {
            // deallocate due function stack
            // avoid memory leakage
            destructStack(operandStack);

            return 0;
        }


        // increment pointer
        postfix++;
    }

    // stack at this point of time can not have more than one element
    if (operandStack->top != 1)
    {
        // deallocate due function stack
        // avoid memory leakage
        destructStack(operandStack);

        return 0;
    }

    // must be assigned before deallocation
    TYPE answer = getPeekValue(operandStack);

    // deallocate due function stack
    // avoid memory leakage
    destructStack(operandStack);

    return answer;
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
