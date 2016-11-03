#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#define SIZE 10

typedef struct QNode * QLink;
struct QNode{
    int data;
    QLink next;
};
typedef struct{
    QLink qfront;
    QLink qrear;
}LinkQueueList;
typedef struct{
    int qfront;
    int qrear;
    int qbase[SIZE];
}LinkQueueOrder;

LinkQueueList * InitQueueList(LinkQueueList * q);
void EnQueueList(LinkQueueList * q, int data);
int DeQueueList(LinkQueueList * q);
void DestoryQueueList(LinkQueueList * q);
int ClearQueueList(LinkQueueList * q);

void InitQueueOrder(LinkQueueOrder * q);
int EnQueueOrder(LinkQueueOrder * q, int e);
int DeQueueOrder(LinkQueueOrder * q);
void DestoryQueueOrder(LinkQueueOrder * q);
void ClearQueueOrder(LinkQueueOrder * q);

int main(void)
{
    LinkQueueList * q = NULL;
    LinkQueueOrder link;

    int i, flag;
    printf("请选择您的操作(输入0结束):\n");
    printf("1.链式存储队列的初始化\n");
    printf("2.链式存储队列的入队\n");
    printf("3.链式存储队列的出队\n");
    printf("4.顺序存储队列的初始化\n");
    printf("5.顺序存储队列的入队\n");
    printf("6.顺序存储队列的出队\n");
    scanf("%d", &flag);
    while(flag)
    {
        switch (flag)
        {
            case 1:
                DestoryQueueList(q);
                q = InitQueueList(q);
                break;
            case 2:
                printf("请输入入队的int值(值为-1结束)：\n");
                while(scanf("%d", &i), i != -1)
                {
                    EnQueueList(q, i);
                }
                break;
            case 3:
                printf("队列的值为：\n");
                while(q->qfront != q->qrear)
                {
                    printf("%d   ", DeQueueList(q));
                }
                printf("\n");
                break;
            case 4:
                InitQueueOrder(&link);
                break;
            case 5:
                printf("请输入入队的int值(值为-1结束)：\n");
                while(scanf("%d", &i), i != -1)
                {
                    EnQueueOrder(&link, i);
                }
                break;
            case 6:
                printf("队列的值为：\n");
                while(link.qfront != link.qrear)
                {
                    printf("%d   ", DeQueueOrder(&link));
                }
                printf("\n");
                break;
            default:
                break;
        }
        printf("请选择您的操作(输入0结束):\n");
        printf("1.链式存储队列的初始化\n");
        printf("2.链式存储队列的入队\n");
        printf("3.链式存储队列的出队\n");
        printf("4.顺序存储队列的初始化\n");
        printf("5.顺序存储队列的入队\n");
        printf("6.顺序存储队列的出队\n");
        scanf("%d", &flag);
    }
	DestoryQueueList(q);
    return 0;
}

LinkQueueList * InitQueueList(LinkQueueList * q)
{
    q = (LinkQueueList *) malloc (sizeof(LinkQueueList));
    q->qfront = q->qrear = (QLink) malloc (sizeof(struct QNode));
    if(!q->qfront)
    {
        printf("内存分配失败！！");
        exit(-1);
    }
    q->qfront->next = NULL;
    return q;
}

void EnQueueList(LinkQueueList * q, int data)
{
    QLink p = (QLink) malloc (sizeof(struct QNode));
    if(!p)
    {
        printf("内存分配失败！！\n");
        return;
    }
    p->data = data;
    q->qrear->next = p;
    q->qrear = p;
    q->qrear->next = NULL;
}

int DeQueueList(LinkQueueList * q)
{
    int data;
    QLink p;
    if(q->qfront == q->qrear)
    {
        printf("队列为空！！\n");
        return -1;
    }
    p = q->qfront->next;
    q->qfront->next = p->next;
    data = p->data;
    if(q->qrear == p)
    {
        q->qrear = q->qfront;
    }
    free(p);
    return data;
}

void DestoryQueueList(LinkQueueList * q)
{
    if(q == NULL)
    {
        return;
    }
    ClearQueueList(q);
    free(q);
}

int ClearQueueList(LinkQueueList * q)
{
    if(q->qfront == q->qrear)
    {
        return 0;
    }
    while(q->qfront != q->qrear)
    {
        QLink link = q->qfront;
        q->qfront = link->next;
        free(link);
    }
    free(q->qfront);
    return 1;
}

void InitQueueOrder(LinkQueueOrder * q)
{
    int i;
    for(i = 0; i < SIZE; i++)
        q->qbase[i] = -1;
    q->qfront = q->qrear = 0;
}

int EnQueueOrder(LinkQueueOrder * q, int e)
{
    if((q->qrear+1) % SIZE == q->qfront)
    {
        printf("队列已满！！\n");
        return 0;
    }
    q->qbase[q->qrear] = e;
    q->qrear = (q->qrear+1) % SIZE;
    return 1;
}

int DeQueueOrder(LinkQueueOrder * q)
{
    if(q->qfront == q->qrear)
    {
        printf("队列为空！！\n");
        return 0;
    }
    int i = q->qbase[q->qfront];
    q->qfront = (q->qfront + 1) % SIZE;
    return i;
}
