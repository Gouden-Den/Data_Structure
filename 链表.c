#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

struct Num
{
   int num;
   struct Num * next;
};

//(1)．键盘输入一组元素，建立一个无头结点的单向链表（无序）
struct Num * createList()
{
    struct Num * head = NULL;
    struct Num * p1, * p2;
    int n = 0;
    p1 = p2 = (struct Num *)malloc(sizeof(struct Num));
    scanf("%d", &p1->num);
    head = NULL;
    while(p1->num != 0)
    {
        n++;
        if(n == 1)
        {
            head = p1;
        }
        else
        {
            p2->next = p1;
        }
        p2 = p1;
        p1 = (struct Num *)malloc(sizeof(struct Num));
        scanf("%d", &p1->num);
    }
    p2->next = NULL;
    return head;
}

//(2)．遍历（打印）单向链表。
void printfList(struct Num * head)
{
    struct Num * p;
    p = head;
    if(head == NULL)
    {
        printf("该链表为空！！\n");
    }
    else
    {
        while(p != NULL)
        {
            printf("%d ", p->num);
            p = p->next;
        }
        printf("\n");
    }
}

//(3)．把单向链表中元素逆置（不允许申请新的结点空间）。
struct Num * convert(struct Num * head)
{
    struct Num * p1, * p2, *p3;
    int n = 0;
    p1 = head;
    if(head == NULL)
    {
        printf("这是个空链表！！\n");
        return NULL;
    }
    p2 = p1->next;
    p1->next = NULL;
    while(p2 != NULL)
    {
        p3 = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = p3;
    }
    return p1;
}

//(4)．在单向链表中删除所有的偶数元素结点。
void deleteEvenNumber(struct Num * head)
{
    struct Num * p1, * p2, * p3;
    int n = 0;
    p1 = head;
    if(head == NULL)
    {
        printf("这是一个空链表！！\n");
        return;
    }
    do{
        n++;
        p2 = p1->next;
        if(p1->num % 2 == 0)
        {
          if(n == 1)
          {
              free(p1);
          }
          else
          {
              free(p1);
              p1 = p3;
              p3->next = p2;
          }
        }
        p3 = p1;
        p1 = p2;
    }while(p2 != NULL);
}

//(5)：对链表排序，排序后链表元素按照非递减方式排列（注意：排序时如果要交换两个结点的顺序，不得通过交换结点的内容，而需要使用改变指针的方式交换结点的位置。建议使用直接插入排序算法）。
struct Num * sortList(struct Num * head)
{
    struct Num * target, * p1, * p2;
    struct Num * q1, * q2;//存放需要比较的节点和该节点的前一个节点
    if(head == NULL)
    {
        printf("这是个空链表!!\n");
        return NULL;
    }
    target = head->next;
    p1 = head;
    p2 = head->next->next;
    while(target != NULL)
    {
        q1 = head;
        q2 = head->next;
        if(target->num < head->num)
        {
            target->next = q1;
            p1->next = p2;
            head = target;
            target = p2;
            if(p2 != NULL)
                p2 = p2->next;
            continue;
        }
        int flag = 0;//检验是否交换过
        while(q2 != NULL)
        {
            if(target == q2)
                break;
            if(target->num < q2->num)
            {
                flag = 1;
                p1->next = p2;
                q1->next = target;
                target->next = q2;
                target = p2;
                if(p2 != NULL)
                    p2 = p2->next;
                break;
            }
            q1 = q2;
            if(q2 != NULL)
                q2 = q2->next;
        }
        if(flag)
            continue;
        p1 = p1->next;
        if(p2 != NULL)
            p2 = p2->next;
        target = target->next;
    }
    return head;
}

//(6)．利用算法5建立两个非递减有序单向链表，然后合并成一个非递减链表。
struct Num * digui(struct Num * p1, struct Num * p2)//不得已用的递归
{
    if(p1->next == NULL)
        p1->next = p2;
    else
        digui(p1->next, p2);
    return p1;
}

struct Num * createBigList()
{
    struct Num * p1, * p2;
    struct Num num;
    printf("请输入第一组：\n");
    p1 = createList();
    num = *p1;
    p1 = sortList(p1);
    printfList(p1);
    printf("请输入第二组：\n");
    p2 = createList();
    p2 = sortList(p2);
    printfList(p2);
    p1 = digui(p1, p2);//这里用了各种循环方法都是失败，改成递归后就成功了
    printfList(p1);
    p1 = sortList(p1);
}

//(7)．利用算法1建立的链表，删除链表中的重复元素。
void deleteNode(struct Num * head)
{
    struct Num * p1, * p2, *p3;
    if(head == NULL)
    {
        printf("这是个空链表！！\n");
        return;
    }
    p1 = p1 = head;
    while(p1 != NULL)
    {
        p3 = p1;
        p2 = p1->next;
        while(p2 != NULL)
        {
            if(p1->num == p2->num)
            {
                p3->next = p2->next;
                free(p2);
                p2 = p3->next;
            }
            else
            {
                p3 = p2;
                p2 = p2->next;
            }
        }
        p1 = p1->next;
    }
}

//(8)．利用算法1建立的链表，实现将其分解成两个链表，其中一个全部为奇数，另一个全部为偶数（尽量利用已知的存储空间）。
void separate(struct Num * head, struct Num * odd, struct Num * even)
{
    struct Num * ji, * ou;
    struct Num * p1;
    p1 = head;
    ji = ou = NULL;
    if(p1 == NULL)
    {
        printf("这是个空链表！！\n");
        return;
    }
    while(head != NULL)
    {
        if(head->num % 2)
        {
            head = head->next;
            p1->next = NULL;

            if(ji == NULL)
            {
                 ji = p1;
                odd = p1;
            }
            else
            {
               ji->next = p1;
               ji = ji->next;
            }
        }
        else
        {
            head = head->next;
            p1->next = NULL;

            if(ou == NULL)
            {
                ou = p1;
                even = p1;
            }
            else
            {
                ou->next = p1;
                ou = ou->next;
            }
        }
        p1 = head;
    }
    printf("奇数表如下：\n");
    printfList(odd);
    printf("偶数表如下：\n");
    printfList(even);
}

//(9)．判断算法1和算法5生成单链表所表示的集合是否相等。
int isEqual(struct Num * head1, struct Num * head2)//head1来获取算法1得到的表，head2获取算法5得到的表
{
    struct Num * p1, * p2;
    int flag = 0;
    p1 = head1;
    while(p1 != NULL)
    {
        p2 = head2;
        flag = 0;
        while(p2 != NULL)
        {
            if(p1->num != p2->num)
            {
                p2 = p2->next;
                continue;
            }
            else
            {
                flag = 1;
                break;
            }
        }

        if(!flag)
        {
            return 0;
        }
        p1 = p1->next;
    }

    p2 = head2;
    while(p2 != NULL)
    {
        p1 = head1;
        flag = 0;
        while(p1 != NULL)
        {
            if(p1->num != p2->num)
            {
                p1 = p1->next;
                continue;
            }
            else
            {
                flag = 1;
                break;
            }
        }

        if(!flag)
        {
            return 0;
        }
        p2 = p2->next;
    }

    return 1;
}
//(10)．在主函数中设计一个简单的菜单，分别调试上述算法。
int main (void)
{
    struct Num * p1, * odd, * even;
    p1 = odd = even = NULL;
    int num = -1;
    do{
        printf("(1)．键盘输入一组元素，建立一个无头结点的单向链表（无序）\n");
        printf("(2)．遍历（打印）单向链表\n");
        printf("(3)．把单向链表中元素逆置\n");
        printf("(4)．在单向链表中删除所有的偶数元素结点\n");
        printf("(5)：对链表排序，排序后链表元素按照非递减方式排列\n");
        printf("(6)．利用算法5建立两个非递减有序单向链表，然后合并成一个非递减链表\n");
        printf("(7)．利用算法1建立的链表，删除链表中的重复元素\n");
        printf("(8)．利用算法1建立的链表，实现将其分解成两个链表，其中一个全部为奇数，另一个全部为偶数\n");
        printf("(9)．判断算法1和算法5生成单链表所表示的集合是否相等\n输入0退出程序\n");
        printf("请输入您的选择：\n");
        scanf("%d", &num);
        switch(num)
        {
            case 1:
                printf("请输入要键入的值：\n");
                p1 = createList();
                printf("这是您建立的链表：\n");
                printfList(p1);
                break;
            case 2:
                printf("这是您的链表：\n");
                printfList(p1);
                break;
            case 3:
                printf("逆置后的结果如下：\n");
                p1 = convert(p1);
                printfList(p1);
                break;
            case 4:
                printf("删除后的结果如下：\n");
                deleteEvenNumber(p1);
                printfList(p1);
                break;
            case 5:
                printf("排序后的结果如下：\n");
                p1 = sortList(p1);
                printfList(p1);
                break;
            case 6:
                p1 = createBigList();
                printf("所得结果如下：\n");
                printfList(p1);
                break;
            case 7:
                printf("所得结果如下：\n");
                deleteNode(p1);
                printfList(p1);
                break;
            case 8:
                separate(p1, odd, even);
                break;
            case 9:
                printf("请输入您要由算法1生成的链表的内容：\n");
                struct Num * p2, * p3;
                p2 = createList();
                printf("请输入您要由算法5生成的链表的内容：\n");
                p3 = createList();
                p3 = sortList(p3);
                printf("算法1和算法5生成单链表所表示的集合%s相等的", isEqual(p2, p3)?"是":"不");
                break;
            case 0:
                break;
            default:
                printf("请输入正确的值！！\n\n\n");
        }
        printf("**************************************************************\n\n\n");
    }while(num != 0);

    return 0;
}
