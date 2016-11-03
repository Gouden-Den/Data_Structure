#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

struct SElemTypeList{
    char elem;
    struct SElemTypeList * pro;
};
typedef struct{
    struct SElemTypeList * base;
    struct SElemTypeList * top;
}SqStackList;
typedef struct{
    char * base;
    char * top;
    int stacksize;
}SqStackOrder;

SqStackList * InitStackList(SqStackList * s);
int ClearStackList(SqStackList * s);
int DestoryStackList(SqStackList * s);
void PushList(SqStackList * s, char ch);
int PopList(SqStackList * s, char * ch);
int isEqualList(SqStackList * s);
SqStackOrder * InitStackOrder(SqStackOrder * s);
void PushOrder(SqStackOrder * s, char ch);
int PopOrder(SqStackOrder * s, char * ch);
int isEqualOrder(SqStackOrder * s);
int DestoryStackOrder(SqStackOrder * s);
int ClearStackOrder(SqStackOrder * s);

int main (void)
{
    SqStackList * slist = NULL;
    SqStackOrder * sorder = NULL;

    int flag;
    printf("请选择您的操作(输入0结束):\n");
    printf("1.链式存储栈的初始化\n");
    printf("2.链式存储栈的入栈\n");
    printf("3.链式存储栈的出栈\n");
    printf("4.链式存储栈的字符匹配检验\n");
    printf("5.顺序存储栈的初始化\n");
    printf("6.顺序存储栈的入栈\n");
    printf("7.顺序存储栈的出栈\n");
    printf("8.链式存储栈的字符匹配检验\n");
    scanf("%d", &flag);
    while(flag)
    {
        char ch;
        switch(flag)
        {
            case 1:
                DestoryStackList(slist);
                slist = InitStackList(slist);
                break;
            case 2:
                printf("请输入要入栈的字符（以'\\n'结束）\n");
                getchar();
                while((ch = getchar()) != '\n')
                {
                    PushList(slist, ch);
                }
                break;
            case 3:
                printf("栈中的内容为（出栈）：\n");
                while(slist->top != NULL)
                {
                    PopList(slist, &ch);
                    putchar(ch);
                }
                putchar('\n');
                break;
            case 4:
                isEqualList(slist);
                break;
            case 5:
                DestoryStackOrder(sorder);
                sorder = InitStackOrder(sorder);
                break;
            case 6:
                printf("请输入要入栈的字符（以'\\n'结束）\n");
                getchar();
                while((ch = getchar()) != '\n')
                {
                    PushOrder(sorder, ch);
                }
                break;
            case 7:
                printf("栈中的内容为（出栈）：\n");
                while(sorder->top > sorder->base)
                {
                    PopOrder(sorder, &ch);
                    putchar(ch);
                }
                putchar('\n');
                break;
            case 8:
                isEqualOrder(sorder);
                break;
            default:
                break;
        }
        puts("************************************\n");
        printf("请选择您的操作(输入0结束):\n");
        printf("1.链式存储栈的初始化\n");
        printf("2.链式存储栈的入栈\n");
        printf("3.链式存储栈的出栈\n");
        printf("4.链式存储栈的字符匹配检验\n");
        printf("5.顺序存储栈的初始化\n");
        printf("6.顺序存储栈的入栈\n");
        printf("7.顺序存储栈的出栈\n");
        printf("8.顺序存储栈的字符匹配检验\n");
        scanf("%d", &flag);
    }
    DestoryStackList(slist);
    DestoryStackOrder(sorder);
    puts("*******************END********************\n");
    return 0;
}

SqStackList * InitStackList(SqStackList * s)
{
    s = (SqStackList*) malloc (sizeof(SqStackList));
    s->top = s->base = NULL;
    return s;
}

int ClearStackList(SqStackList * s)
{
    if(s == NULL)
    {
        printf("栈不存在!!\n");
        exit(-1);
    }
    if(s->top == NULL)
    {
        return 0;
    }
    while(s->top->pro != NULL)
    {
        struct SElemTypeList * l = s->top->pro;
        free(s->top);
        s->top = l;
    }
    free(s->top);

    return 1;
}

int DestoryStackList(SqStackList * s)
{
    if(s == NULL)
    {
        return 0;
    }
    if(s->top == NULL)
    {
        free(s);
        return 0;
    }
    ClearStackList(s);
    free(s);
    return 1;
}

void PushList(SqStackList * s, char ch)
{
    struct SElemTypeList * e = (struct SElemTypeList *) malloc (sizeof(struct SElemTypeList));
    e->elem = ch;
    e->pro = s->top;
    if(s->top == NULL)
    {
        s->base = e;
        e->pro = NULL;
    }
    s->top = e;
}

int PopList(SqStackList * s, char * ch)
{
    struct SElemTypeList * e;
    if(s->top == NULL)
    {
        s->base = NULL;
        printf("栈为空！！\n");
        return 0;
    }
    e = s->top;
    *ch = e->elem;
    s->top = s->top->pro;
    free(e);
    if(s->top == NULL)
    {
        s->base = NULL;
    }
    return 1;
}

int isEqualList(SqStackList * s)
{
    char ch, E[100]="";
    int i = 0;
    printf("输入一组表达式，判断表达式中括号'(', ')', '[', ']'是否配对。'#'为表达式的结束符\n");
    while((ch = getchar()) != '#' && i < 100)
    {
        E[i++] = ch;
    }
    int j = 0;
    while(j < i)
    {
        if(E[j] == '(' || E[j] == '[')
        {
            PushList(s, E[j]);
        }
        else if(E[j] == ')' || E[j] == ']')
        {
            if(E[j] == ')' && s->top->elem == '(')
            {
                PopList(s, &ch);
            }
            else if(E[j] == ']' && s->top->elem == '[')
            {
                PopList(s, &ch);
            }
            else
            {
                if(s->base == s->top)
                {
                    printf("表达式中括号'(', ')', '[', ']'不配对!!\n");
                    return 0;
                }
            }
        }
        j++;
    }
    if(s->top != NULL)
    {
        printf("表达式中括号'(', ')', '[', ']'不配对!!!\n");
        return 0;
    }
    printf("表达式中括号'(', ')', '[', ']'配对!!!\n");
    return 1;
}

SqStackOrder * InitStackOrder(SqStackOrder * s)
{
    s = (SqStackOrder *) malloc (sizeof(SqStackOrder));
    s->base = (char *) malloc (STACK_INIT_SIZE * sizeof(char));
    if(!s->base)
    {
        printf("内存分配失败！！\n");
        exit(-1);
    }
    s->top = s->base;
    s->stacksize = STACK_INIT_SIZE;
    return s;
}

void PushOrder(SqStackOrder * s, char ch)
{
    if(s->top - s->base >= s->stacksize)
    {
        s->base = (char *) realloc (s->base, (s->stacksize + STACKINCREMENT) * sizeof(char));
        if(!s->base)
	    {
	        printf("内存分配失败！！\n");
	        exit(-1);
	    }
	    s->top = s->base + s->stacksize;
	    s->stacksize += STACKINCREMENT;
    }

    *s->top++ = ch;
}

int PopOrder(SqStackOrder * s, char * ch)
{
    if(s->top == s->base)
    {
        printf("栈为空！！\n");
        return 0;
    }
    *ch = * --s->top;
    return 1;
}

int isEqualOrder(SqStackOrder * s)
{
    char ch, E[100]="", c;
    int i = 0;
    printf("输入一组表达式，判断表达式中括号'(', ')', '[', ']'是否配对。'#'为表达式的结束符\n");
    while((ch = getchar()) != '#' && i < 100)
    {
        E[i++] = ch;
    }
    int j = 0;
    while(j < i)
    {
        if(E[j] == '(' || E[j] == '[')
        {
            PushOrder(s, E[j]);
        }
        else if(E[j] == ')' || E[j] == ']')
        {
            if(E[j] == ')' && *(s->top - 1) == '(')
            {
                PopOrder(s, &c);
            }
            else if(E[j] == ']' && *(s->top - 1) == '[')
            {
                PopOrder(s, &c);
            }
            else
            {
                if(s->base == s->top)
                {
                    printf("表达式中括号'(', ')', '[', ']'不配对!!\n");
                    return 0;
                }
            }
        }
        j++;
    }
    if(s->top != s->base)
    {
        printf("表达式中括号'(', ')', '[', ']'不配对!!!\n");
        return 0;
    }
    printf("表达式中括号'(', ')', '[', ']'配对!!!\n");
    return 1;
}

int DestoryStackOrder(SqStackOrder * s)
{
    if(s == NULL)
    {
        return 0;
    }
    ClearStackOrder(s);
    free(s);
    return 1;
}

int ClearStackOrder(SqStackOrder * s)
{
    if(s->base != NULL)
    {
        free(s->base);
    }
    return 1;
}
