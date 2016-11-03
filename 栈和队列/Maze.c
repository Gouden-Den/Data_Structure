#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int r;
    int c;
} PosType;

typedef struct{
    int step;
    int rMax, cMax;
    char **ch;
}MazeType;

typedef struct{
    PosType pos;
    int di;
}ElemType;

typedef struct nodetype *LinkType;

typedef struct nodetype{
    ElemType data;
    LinkType next;
}NodeType;

typedef struct{
    LinkType base;
    LinkType top;
}Stack;

Stack * InitStack(Stack * s);
int ClearStack(Stack * s);
int DestoryStack(Stack * s);
int StackLength(Stack * s);
int StackEmpty(Stack * s);
void GetTop(Stack * s, ElemType * e);
void Push(Stack * s, ElemType e);
void Pop(Stack * s, ElemType * e);
void FootPrint(MazeType * maze, PosType pos);
void BlockedPrint(MazeType * maze, PosType pos);
PosType NextPos(PosType pos, int di);
MazeType * GetMaze(MazeType * maze);
MazeType * InitMaze(MazeType * maze);
int Pass(MazeType * maze, PosType pos);
int MazePath(Stack * s, MazeType * maze, PosType start, PosType en);
void PrintMazePosition(Stack * s, MazeType * maze);
void PrintMaze(MazeType * maze);

int main (void)
{
    Stack * s = NULL;
    MazeType * maze = (MazeType *) malloc (sizeof(MazeType));

    s = InitStack(s);
    maze = InitMaze(maze);

    PosType start = {1, 1};
    PosType en = {maze->rMax-2, maze->cMax-2};
    MazePath(s, maze, start, en);

    PrintMazePosition(s, maze);
    PrintMaze(maze);

    DestoryStack(s);
    free(maze);
    return 0;
}


Stack * InitStack(Stack * s)
{
    s = (Stack *) malloc (sizeof(Stack));
    if(!s)
    {
        printf("内存分配失败!!\n");
        exit(-1);
    }
    s->top = s->base = NULL;
    return s;
}

int ClearStack(Stack * s)
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
    while(s->top->next != NULL)
    {
        LinkType l = s->top->next;
        free(s->top);
        s->top = l;
    }
    free(s->top);

    return 1;
}

int DestoryStack(Stack * s)
{
    if(s == NULL)
    {
        printf("栈不存在!!\n");
        exit(-1);
    }
    if(s->top == NULL)
    {
        free(s);
        return 0;
    }
    ClearStack(s);
    free(s);
    return 1;
}

int StackLength(Stack * s)
{
    if(s == NULL)
    {
        printf("栈不存在!\n");
        exit(-1);
    }
    int count = 0;
    if(s->top == NULL)
    {
        printf("栈为空！！\n");
        return 0;
    }
    while(s->top != NULL)
    {
       s->top = s->top->next;
       count++;
    }
    return count;
}

int StackEmpty(Stack * s)
{
    if(s == NULL)
    {
        printf("栈不存在!!\n");
        exit(-1);
    }
    if(s->top == NULL)
    {
        printf("栈为空!!\n");
        return 1;
    }
    return 0;
}

void GetTop(Stack * s, ElemType * e)
{
    if(s == NULL)
    {
        printf("栈不存在!!\n");
        exit(-1);
    }
    else
    {
        if(s->top == NULL)
        {
            printf("栈为空!!\n");
        }
        else
        {
            *e = s->top->data;
        }
    }
}

void Push(Stack * s, ElemType e)
{
    if(s == NULL)
    {
        printf("栈不存在!!\n");
        exit(-1);
    }
    LinkType link = (LinkType) malloc (sizeof(NodeType));
    if(!link)
    {
        printf("内存分配失败！！\n");
        exit(-1);
    }
    link->data = e;
    link->next = s->top;
    if(s->top == NULL)
    {
        s->base = link;
    }
    s->top = link;
}

void Pop(Stack * s, ElemType * e)
{
    if(s == NULL)
    {
        printf("栈不存在!!\n");
        exit(-1);
    }
    if(s->top == NULL)
    {
        printf("栈为空！！\n");
    }
    else
    {
        *e = s->top->data;
        LinkType link = s->top;
        s->top = s->top->next;
        free(link);
    }
}

void FootPrint(MazeType * maze, PosType pos)
{
    maze->ch[pos.r][pos.c] = '*';
}

void BlockedPrint(MazeType * maze, PosType pos)
{
    maze->ch[pos.r][pos.c] = '#';
}

PosType NextPos(PosType pos, int di)
{
    switch(di)
    {
        case 1:
            pos.c += 1;
            break;
        case 2:
            pos.r += 1;
            break;
        case 3:
            pos.c -= 1;
            break;
        case 4:
            pos.r -= 1;
            break;
        default:
            break;
    }
    return pos;
}

MazeType * GetMaze(MazeType * maze)
{
    char ch, filename[100];
    int r = 0, c = 0;
    FILE * fp = NULL;
    printf("Please input filename:\n");
    scanf("%s", filename);
    if((fp = fopen(filename, "r")) == NULL)
    {
        printf("File can't be opened!!\n");
        exit(-1);
    }
    while((ch = getc(fp)) != '\n')
    {
        c++;
    }
    while((ch = getc(fp)) != EOF)
    {
        if(ch != '\n')
            r++;
    }
    r += c;
    r /= c;

    maze->rMax = r;
    maze->cMax = c;

    char ** arr = (char**) malloc (r * sizeof(char*));
    while(r--)
    {
        arr[r] = (char*) malloc (c * sizeof(char));
    }
    r = 0;
    if((fp = fopen(filename, "r")) == NULL)
    {
        printf("File can't be opened!!\n");
        exit(-1);
    }
    while((ch = getc(fp)) != EOF)
    {
        c = 0;
        do
        {
            arr[r][c++] = ch;
        }while((ch = getc(fp)) != '\n' && ch != EOF);
        r++;
    }
    fclose(fp);
    maze->ch = arr;
    return maze;
}

MazeType * InitMaze(MazeType * maze)
{
    maze->step = 0;
    maze = GetMaze(maze);
    return maze;
}

int Pass(MazeType * maze, PosType pos)
{
    if(maze->ch[pos.r][pos.c] == '0')
        return 1;
    return 0;
}

int MazePath(Stack * s, MazeType * maze, PosType start, PosType en)
{
    PosType curpos = start;
    do
    {
        if(Pass(maze, curpos))
        {
            maze->step++;
            FootPrint(maze, curpos);
            ElemType e;
            e.di = 1;
            e.pos = curpos;
            Push(s, e);
            if(curpos.c == en.c && curpos.r == en.r)
                return 1;
            curpos = NextPos(curpos, 1);
        }
        else
        {
            ElemType e;
            Pop(s, &e);
            while(e.di == 4 && !StackEmpty(s))
            {
                maze->step--;
                BlockedPrint(maze, e.pos);
                Pop(s, &e);
            }
            if(e.di < 4)
            {
                e.di++;
                Push(s, e);
                curpos = NextPos(e.pos, e.di);
            }
        }
    }while(!StackEmpty(s));
    return 0;
}

void PrintMazePosition(Stack * s, MazeType * maze)
{
    int i = maze->step;
    ElemType e[maze->step];
    while(s->top != NULL)
    {
        e[--i] = s->top->data;
        s->top = s->top->next;
    }
    printf("The path is:\n");
    for(i = 0; i < maze->step; i++)
    {
        printf("(%d, %d, %d)  ", e[i].pos.r, e[i].pos.c, e[i].di);
    }
    printf("\n");
}

void PrintMaze(MazeType * maze)
{
    int r, c;
    printf("The path is:\n");
    for(r = 0; r < maze->rMax; r++)
    {
        for(c = 0; c < maze->cMax; c++)
        {
            putchar(maze->ch[r][c]);
        }
        putchar('\n');
    }
}
