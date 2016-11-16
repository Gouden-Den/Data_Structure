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
    	printf("��Ϊ�գ�δ��ʼ��������ֵ������������!!\n");
    	printf("\n************************************************************\n");
        return True;
    }
    return False;
}

BiTree CreateBiTree(BiTree t)//������������#ʱ�÷������
{
    ElemType e;
    scanf(" %c", &e);
    if(e != '#')
    {
        MAX++;
        t = (BiTree) malloc (sizeof(BiTNode));
        if(BiTreeEmpty(t))
        {
            printf("�ڴ����ʧ�ܣ���\n");
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

void PreOrderResu(BiTree t)//�ݹ����������
{
    if(t != NULL)
    {
        printf("%c", t->data);
        PreOrderResu(t->lchild);
        PreOrderResu(t->rchild);
    }
}

void MidOrderResu(BiTree t)//�ݹ����������
{
    if(t != NULL)
    {
        MidOrderResu(t->lchild);
        printf("%c", t->data);
        MidOrderResu(t->rchild);
    }
}

void PasOrderResu(BiTree t)//�ݹ���������
{
    if(t != NULL)
    {
        PasOrderResu(t->lchild);
        PasOrderResu(t->rchild);
        printf("%c", t->data);
    }
}

void PreOrderNotResu(BiTree t)//�ǵݹ����������
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

void MidOrderNotResu(BiTree t)//�ǵݹ����������
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

void PasOrderNotResu(BiTree t)//�ǵݹ���������
{
    BiTree p = t;
    BiTree node[MAX];
    int top = 0;
    Boolean flag[MAX];//��¼��ǰ�ڵ���Ҷ����Ƿ���ʹ�
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

void DeleteNode(BiTree deleteElem)//ɾ�����ݹ����Ľڵ��Լ��ýڵ���ӽڵ�
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

    printf("1.��ʼ������������\n");
    printf("2.������������ݹ飩��\n");
    printf("3.������������ݹ飩��\n");
    printf("4.������������ݹ飩��\n");
    printf("5.������������ǵݹ飩��\n");
    printf("6.������������ǵݹ飩��\n");
    printf("7.������������ǵݹ飩��\n");
    printf("8.�������ĸ߶ȣ�\n");
    printf("9.��������Ҷ�Ӹ�����\n");
    printf("10.������һ��ֵ��Ȼ���ɾ������ÿһ��Ԫ��ֵΪx�Ľ�㣺\n");
    printf("11.ʵ�ֶ������Ĳ�α�����\n");
    printf("0.�˳�����\n");
    printf("����������ѡ��\n");
    scanf("%d", &choice);
    return choice;
}

