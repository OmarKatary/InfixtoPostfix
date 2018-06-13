#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxSize 100


typedef struct
{
    int top;
    char items[maxSize];
} Stack;


void initialise(Stack *S)
{
    S->top=0;
}

void push(Stack *S, char value)
{
    S->items[S->top]=value;
    S->top++;
}

char pop(Stack *S)
{
    char value;
    S->top--;
    value= S->items[S->top];
    return value;
}

int isEmpty(Stack *S)
{
    if(S->top==0)
        return 1;
    return 0;
}

char top(Stack *S)
{

    char value = pop(S);
    push(S,value);
    return value;
}

int evaluate(char x,int op1,int op2)
{
    if(x=='+')
        return(op1+op2);
    if(x=='-')
        return(op1-op2);
    if(x=='*')
        return(op1*op2);
    if(x=='/')
        return(op1/op2);
    if(x=='%')
        return(op1%op2);
}

int evaluatePostfix(char *exp)
{
    Stack s;
    int op1,op2,val;
    initialise(&s);
    int i;
    for(i=0; i<strlen(exp); i++)
    {
        if(isdigit(exp[i]))
            push(&s,exp[i]-'0');
        else
        {
            op2=pop(&s);
            op1=pop(&s);
            val=evaluate(exp[i],op1,op2);
            push(&s,val);
        }
    }
    val=pop(&s);
    return val;
}

int priority(char x)
{


    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x == '/')
        return 2;
    if(x == '(')
        return 0;
}


void infixTopostfix(char infix[], char postfix[])
{

    int i,j=0;
    char temp,ch;
    Stack s;
    initialise(&s);



    for(i=0 ; i<strlen(infix) ; i++)
    {

        ch = infix[i];
        if(ch>='0' && ch<='9')
        {
            postfix[j]=ch;
            j++;
        }
        //****************************
        else if(ch=='('){
                    push(&s,ch);

                }
        else if(ch==')'){
            while(top(&s)!='('){

                postfix[j]=pop(&s);
                              printf("%c\n",postfix[j]);
                j++;
            }
            //to remove the (
            pop(&s);;
        }

        //****************************
        else if(ch=='*'||ch=='/'||ch=='+'||ch=='-')
        {

            if(isEmpty(&s))
            {
                push(&s,ch);
            }
            else if(priority(top(&s))<priority(ch))
            {
                push(&s,ch);
            }
            else if(priority(top(&s))>=priority(ch))
            {
                while(priority(top(&s)>=priority(ch)))
                {
                    temp=pop(&s);
                    postfix[j] = temp;
                    j++;
                }
                push(&s,ch);

            }

        }

    }

    while(!isEmpty(&s)){

        postfix[j]=pop(&s);
            j++;
    }
    postfix[j]='\0';



}

int main()
{

    char infix[30];
    char postfix[30];

        scanf("%s",infix);

    infixTopostfix(infix, postfix);
    printf("%s\n",postfix);
    printf("%d",evaluatePostfix(postfix));



    return 0;
}



