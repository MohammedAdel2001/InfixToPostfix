
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node
{
    float data;
    struct Node *next;
} Node;

typedef struct
{
    Node *top;
} Stack;
typedef struct Nodechar
{
    char data;
    struct Nodechar *next;
} Nodechar;
typedef struct
{
    Nodechar *top;
} Stackchar;
Stackchar *initializechar()
{
    Stackchar *s = malloc (sizeof(Stackchar));
    s->top = NULL;
    return s;
}
Stack *initialize()
{
    Stack *s = malloc (sizeof(Stack));
    s->top = NULL;
    return s;
}
Nodechar *newnodechar(char value)
{
    Nodechar* n = malloc(sizeof(Nodechar));
    n->data = value;
    n->next = NULL;
    return n;
}
Node *newnode(float value)
{
    Node* n = malloc(sizeof(Node));
    n->data = value;
    n->next = NULL;
    return n;
}
int isEmptychar(Stackchar *s)
{
    return (s->top == NULL);
}
void pushchar(Stackchar *s, char value)
{
    Nodechar *n = newnodechar(value);

    if(isEmptychar(s))
        s->top= n;
    else
    {
        n->next = s->top;
        s->top = n;
    }
}
char popchar(Stackchar *s)
{
    if(isEmptychar(s))
    {
        printf("the stack is Empty");
        return -1;
    }
    else
    {
        if(s->top->next == NULL)
        {
            char x = s->top->data;
            free (s->top);
            s->top = NULL;
            return x;
        }
        else
        {
            Nodechar *temp = s->top;
            char y = s->top->data;
            s->top = s->top->next ;
            free(temp);
            return y;
        }
    }
}
char peekchar(Stackchar* s)
{
    if (s->top == NULL)
    {
        printf("the stack is Empty");
        return -1;
    }
    return s->top->data;
}
int isEmpty(Stack *s)
{
    return (s->top == NULL);
}
void push(Stack *s, float value)
{
    Node *n = newnode(value);

    if(isEmpty(s))
        s->top= n;
    else
    {
        n->next = s->top;
        s->top = n;
    }
}
float pop(Stack *s)
{
    if(isEmpty(s))
    {
        printf("the stack is Empty");
        return -1;
    }
    else
    {
        if(s->top->next == NULL)
        {
            float x = s->top->data;
            free (s->top);
            s->top = NULL;
            return x;
        }
        else
        {
            Node *temp = s->top;
            float y = s->top->data;
            s->top = s->top->next ;
            free(temp);
            return y;
        }
    }
}
float peek(Stack* s)
{
    if (s->top == NULL)
    {
        printf("the stack is Empty");
        return -1;
    }
    return s->top->data;
}
void display(Stack *s)
{
    Stack *temp = initialize();
    float x;
    while (!isEmpty(s))
    {
        x = pop(s);
        printf("%.2f\t", x);
        push(temp, x);

    }
    while(!isEmpty(temp))
    {
        push(s, pop(temp));
    }
    printf("\n");
}
void displayarray(char* arr)
{
    int len=strlen(arr);
    int i=0;
    printf("%c",arr[len]);
    while(arr[i]!= '\0'){
   // for (int i = 0; i < len; i++)
    //{
        printf("%c", arr[i]);
        i++;
   // }
   }
    printf("\n");
}
int isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int priority (char op)
{
    switch(op)
    {
    case '+':
    case '-':
        return 0;
    case '*':
    case '/':
    case '%':

        return 1;
    case '(':
        return 2;
    case '^':
        return 3;

    }
}
char* infixtopostfix(char *infix)
{
    int i;
    int len=strlen(infix)+1;
    char *post = malloc(len);
    Stackchar *s= initializechar();
    int j=0;
    for(i=0; i<len; i++)
    {

        if(isdigit(infix[i]))
        {

            while (isdigit(infix[i]))
            {
                post[j++] = infix[i++];
            }   //multi digit
          //  post[j++]=' ';

            if (infix[i] == '.')
            {
                post[j++] = infix[i++];
                while (isdigit(infix[i]))
                {
                    post[j++] = infix[i++];
                }
                          //  post[j++]=' ';


            }  // decimal points

           /* if (isdigit(infix[i+1]))
            {
                while (isdigit(infix[i+1]))
                {
                    post[j++] = infix[++i];
                }

            }*/
             post[j++]=' ';


        }
        else if(infix[i] == '-' && infix[i + 1] != ' '){
           //  post[j++]=' ';
            post[j++] = infix[i];}
        else if(isspace(infix[i]))
        {
            //post[j++]=' ';
            continue;   //spaces
        }

        else if (infix[i]=='(')
        {
            pushchar(s,infix[i]);
        }
        else if(infix[i]==')')
        {
            while(peekchar(s)!= '(' && !isEmptychar(s))
            {
                post[j++]=popchar(s);
               post[j++]=' ';
            }
            popchar(s);
        }
        else if (isEmpty(s))
        {
            pushchar(s,infix[i]);


        }
        else if(isOperator(infix[i]))
        {
            while(!isEmpty(s) && peekchar(s)!= '(' && priority(peekchar(s))>= priority(infix[i]))
            {
            post[j++]=popchar(s);
               post[j++]=' ';

            }

            pushchar(s,infix[i]);
        }
    }
    while(!isEmpty(s))
    {
        post[j++]=popchar(s);
        post[j++]=' ';

    }

    post[j]='\0';
    return post;

}
float calculate (float x, float y, char op)
{
    switch (op)
    {
    case '+':
        return x+y;
    case '-':
        return x-y;
    case '*':
        return x*y;
    case '/':
        return x/y;
    case '^':
        return pow(x,y);

    }
}
float evalaute_post (char* postfix)
{
    Stack *s = initialize();
    float x,y,result;
    int i;
    for(i=0; i<strlen(postfix); i++)
    {
        if(isdigit(postfix[i]))
        {
            int j=i;
            float num=0.0;
            while(isdigit(postfix[j]))
            {
                num= num* 10.0 + (postfix[j]-'0');
                j++;
            }
            if(postfix[j]== '.')
            {
                j++;
                float dec=0.1;
                while(isdigit(postfix[j]))
                {
                    num=num + (postfix[j]-'0') * dec;
                    dec /= 10.0;
                    j++;
                }
            }
            push(s,num);
            i=j-1;

        }
        else if(postfix[i]==' ')
        {
            continue;
        }
        else if(postfix[i]=='-' & isdigit(postfix[i+1]))
        {
            int j=i+1;
            float num=0.0;
            while(isdigit(postfix[j]))
            {
                num = num * 10.0 + (postfix[j]-'0');
                j++;
            }
            if(postfix[j]=='.')
            {
                j++;
                float dec=0.1;
                while(isdigit(postfix[j]))
                {
                    num = num + (postfix[j] - '0') * dec;
                    dec /= 10.0;
                    j++;
                }
            }
            push(s,-num);
            i=j-1;


        }
        else
        {
            x=pop(s);
            y=pop(s);
            result = calculate(y,x,postfix[i]);
            push(s,result);

        }
    }
    return pop(s);
}






int main()
{

    char* postfix;
    char infix[30];

    int func=10,j;
    while(func!=0)
    {
        printf("To Enter An Infix Expression Enter 1\nTo Exit The program Enter 0\n");
        printf("Enter Here:");
        scanf("%d",&func);
        if(func==1)
        {
            printf("\nPlease Insert Your Infix Expression:");
            getchar();
            gets(infix);
            //      fgets(infix, 30, stdin);

            postfix =infixtopostfix(infix);
            printf("The InFix Expression : ");
            displayarray(infix);
            printf("The PostFix Expression : ");
            displayarray(postfix);
            printf("your expression is being evaluated ");
            for(j=3;j>0;j--)
            {
                printf(".");
                 sleep(1);
            }

            float y;
            y=evalaute_post(postfix);
            printf("\nThe Value of the Expression is %.6f\n",y);

        }


    }
    if(func==0)
    {
        printf("Thank You!");
    }

}
