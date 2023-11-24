#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100

int getPrecedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

void infixToPostfix(char infix[], char postfix[])
{
    char stack[max];
    int top = -1;
    int i, j;

    for (i = 0, j = 0; infix[i] != '\0'; i++)
    {
        char x = infix[i];

        if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
        {
            postfix[j++] = x;
        }
        else if (x == '(')
        {
            stack[++top] = x;
        }
        else if (x == ')')
        {

            while (top != -1 && stack[top] != '(')
            {
                postfix[j++] = stack[top--];
            }
            if (top != -1)
            {
                top--;
            }
        }
        else
        {
            while (top != -1 && getPrecedence(stack[top]) >= getPrecedence(x))
            {
                postfix[j++] = stack[top--];
            }
            stack[++top] = x;
        }
    }

    while (top != -1)
    {
        postfix[j++] = stack[top--];
    }

    postfix[j] = '\0';
}

int main()
{
    char infix[max], postfix[max];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}