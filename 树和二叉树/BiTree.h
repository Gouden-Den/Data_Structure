#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#define True 1
#define False 0
#define OK 1
#define Error 0

int MAX = 0;

typedef int Status;
typedef int Boolean;
typedef char ElemType;
typedef struct BiTNode{
    ElemType data;
    struct BiTNode * lchild, * rchild;
}BiTNode, * BiTree;

Status InitBiTree(BiTree t)
{
    t = NULL;
    return OK;
}

Boolean BiTreeEmpty(BiTree t)
{
    if(!t)
    {
    	printf("树为空，未初始化或输入值，请重新输入!!\n");
    	printf("\n************************************************************\n");
        return True;
    }
    return False;
}

BiTree CreateBiTree(BiTree t)//创建树，输入#时该方向结束
{
    ElemType e;
    scanf(" %c", &e);
    if(e != '#')
    {
        MAX++;
        t = (BiTree) malloc (sizeof(BiTNode));
        if(BiTreeEmpty(t))
        {
            printf("内存分配失败！！\n");
            exit(-1);
        }
        t->data = e;
        t->lchild = CreateBiTree(t->lchild);
        t->rchild = CreateBiTree(t->rchild);
    }
    else
    {
        t = NULL;
    }
    return t;
}

void PreOrderResu(BiTree t)//递归先序遍历树
{
    if(t != NULL)
    {
        printf("%c", t->data);
        PreOrderResu(t->lchild);
        PreOrderResu(t->rchild);
    }
}

void MidOrderResu(BiTree t)//递归中序遍历树
{
    if(t != NULL)
    {
        MidOrderResu(t->lchild);
        printf("%c", t->data);
        MidOrderResu(t->rchild);
    }
}

void PasOrderResu(BiTree t)//递归后序遍历树
{
    if(t != NULL)
    {
        PasOrderResu(t->lchild);
        PasOrderResu(t->rchild);
        printf("%c", t->data);
    }
}

void PreOrderNotResu(BiTree t)//非递归先序遍历树
{
    BiTree p = t;
    BiTree node[MAX];
    int top = 0;
    do
    {
        while(p != NULL)
        {
            node[top++] = p;
            printf("%c", p->data);
            p = p->lchild;
        }
        if(top > 0)
        {
            p = node[--top];
            p = p->rchild;
        }
    }while(top > 0 || p != NULL);
}

void MidOrderNotResu(BiTree t)//非递归中序遍历树
{
    BiTree p = t;
    BiTree node[MAX];
    int top = 0;
    do
    {
        while(p != NULL)
        {
            node[top++] = p;
            p = p->lchild;
        }
        if(top > 0)
        {
            p = node[--top];
            printf("%c", p->data);
            p = p->rchild;
        }
    }while(top > 0 || p != NULL);
}

void PasOrderNotResu(BiTree t)//非递归后序遍历树
{
    BiTree p = t;
    BiTree node[MAX];
    int top = 0;
    Boolean flag[MAX];//记录当前节点的右儿子是否访问过
    do
    {
        while(p != NULL)
        {
            flag[top] = False;
            node[top++] = p;
            p = p->lchild;
        }
        if(top > 0)
        {
            p = node[--top];
            if(p->rchild != NULL && !flag[top])
            {
                flag[top] = True;
                top++;
                p = p->rchild;
            }
            else
            {
                printf("%c", p->data);
                p = NULL;
            }
        }
    }while(top > 0 || p != NULL);
}

void BiTreeDepth(BiTree t, int level, int * depth)
{
    if(t != NULL)
    {
        if(level > *depth)
            *depth = level;
        BiTreeDepth(t->lchild, level+1, depth);
        BiTreeDepth(t->rchild, level+1, depth);
    }
}

int Leaf(BiTree t)
{
    if(t == NULL)
        return 0;
    else if(t->lchild == NULL && t->rchild == NULL)
        return 1;
    else
        return Leaf(t->lchild) + Leaf(t->rchild);
}

void DeleteNode(BiTree deleteElem)//删除传递过来的节点以及该节点的子节点
{
    if(deleteElem != NULL)
    {
        DeleteNode(deleteElem->lchild);
        DeleteNode(deleteElem->rchild);
        free(deleteElem);
    }
    deleteElem = NULL;
}

void DeleteChildTree(BiTree t, char x)
{
    BiTree p = t;
    int top = 0, count = 0;
    BiTree a[MAX], deleteElems[MAX];
    do
    {
        while(p != NULL)
        {
            if(p->data == x)
            {
                if(p == t)
                {
                    DeleteNode(p);
                    return;
                }
                else if(a[top]->rchild == p)
                {
                    a[top]->rchild = NULL;
                    deleteElems[count++] = p;
                }
                else if(a[top-1]->lchild == p)
                {
                    a[top-1]->lchild = NULL;
                    deleteElems[count++] = p;
                }
            }
            a[top++] = p;
            p = p->lchild;
        }
        if(top > 0)
        {
            p = a[--top];
            p = p->rchild;
        }
    }while(top > 0 || p != NULL);
    while(count > 0)
    {
        DeleteNode(deleteElems[--count]);
    }
}

void TraverseByQueue(BiTree t)
{
    BiTree p = t;
    BiTree que[MAX];
    int front = 0, rear = 0;
    if(p)
    {
        que[rear++] = p;
    }
    while(rear != front)
    {
        p = que[front++];
        printf("%c", p->data);
        if(p->lchild)
        {
            que[rear++] = p->lchild;
        }
        if(p->rchild)
        {
            que[rear++] = p->rchild;
        }
    }
}

int Menu()
{
    int choice;

    printf("1.初始化并创建树：\n");
    printf("2.先序遍历链表（递归）：\n");
    printf("3.中序遍历链表（递归）：\n");
    printf("4.后序遍历链表（递归）：\n");
    printf("5.先序遍历链表（非递归）：\n");
    printf("6.中序遍历链表（非递归）：\n");
    printf("7.后序遍历链表（非递归）：\n");
    printf("8.二叉树的高度：\n");
    printf("9.二叉树的叶子个数：\n");
    printf("10.请输入一个值，然后会删除树中每一个元素值为x的结点：\n");
    printf("11.实现二叉树的层次遍历：\n");
    printf("0.退出程序：\n");
    printf("请输入您的选择：\n");
    scanf("%d", &choice);
    return choice;
}

