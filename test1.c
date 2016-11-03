#include<stdio.h>
#include<malloc.h>
typedef struct Num * pNode;
struct Num{
    int num;
    pNode next;
} Num;

int getLength(pNode head)
{
    pNode p1 = head->next;
    int length = 0;
    while(p1 != NULL)
    {
        length++;
        p1 = p1->next;
    }
    return length;
}

void convert(pNode head)
{
    struct Num * p1, * p2, *p3;
    int n = 0;
    p1 = head->next;
    if(head == NULL)
    {
        printf("这是个空链表！！\n");
        return;
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
    head->next = p1;
}

void printfList(pNode head)
{
    int flag = 0;
    pNode p;
    p = head;
    if(head == NULL)
    {
        printf("该链表为空！！\n");
    }
    else
    {
        printf("“");
        if(p->num == 0)
            printf("-");
        p = p->next;
        while(p != NULL)
        {
            if(p->num == 0)
            {
                if(flag)
                    printf("%d", p->num);
            }
            else
            {
                printf("%d", p->num);
                flag = 1;
            }
            p = p->next;
        }

        if(!flag)
        {
            printf("\r");
            printf("“");
            printf("%d", 0);
        }
        printf("”");
        printf("\n");
    }
}

pNode createList() //该函数将每一位的数字一字符的形式存入，然后根据对应的ascII码转化为数字。
{                   //创建的链表有头节点，头节点中的值为0代表数字为负值，为1代表为正值
    char a;
    int i;
    pNode head, p1;
    p1 = head = (pNode) malloc (sizeof(struct Num));
    head->num = 1;
    head->next = NULL;
    while((a = getchar()) != '\n')
    {
        if(a == '-')
        {
            head->num = 0;
            continue;
        }
        if((a != '-') && (a < '0' || a > '9'))
        {
            printf("输入了错误的内容！！程序退出！！\n");
            exit(1);
        }
        p1->next = (pNode) malloc (sizeof(struct Num));
        p1->next->num = a - 48;
        p1 = p1->next;
        p1->next = NULL;
    }
    return head;
}

pNode add(pNode head1, pNode head2)
{
    pNode p1, p2, head, p;
    int flag = 0;//记录某一位两个数相加是否大于等于10,如果flag为1，则大于等于10；如果为0,则小于10
    p = head = (pNode) malloc (sizeof(struct Num));
    convert(head1);//这一行和下一行代码是用来将数字进行翻转，翻转后才能方便进行相加
    convert(head2);
    p1 = head1->next;
    p2 = head2->next;
    if(head1->num == head2->num)//判断两个数字的符号是否相等，如果同号的话就执行下面的代码
    {
        head->num = head1->num;
        while(p1 != NULL && p2 != NULL)//循环执行的代码将相对应的位的数字相加，并判断是否该向高一位进一
        {
            p->next = (pNode) malloc (sizeof(struct Num));
            p = p->next;
            p->num = 0;
            if(flag)
            {
                p->num += 1;
                flag = 0;
            }
            p->num = p1->num + p2->num + p->num;

            if(p->num >= 10)
            {
                flag = 1;
                p->num %= 10;
            }

            p1 = p1->next;
            p2 = p2->next;
        }

        if(p1 == NULL && p2 != NULL) //两个数字位数不一样的情况
        {
            while(p2 != NULL)
            {
                p->next = (pNode) malloc (sizeof(struct Num));
                p = p->next;
                p->num = 0;
                if(flag)
                {
                    p->num += 1;
                    flag = 0;
                }
                p->num += p2->num;
                if(p->num >= 10)
                {
                    flag = 1;
                    p->num %= 10;
                }
                p2 = p2->next;
            }
        }
        else if(p1 != NULL && p2 == NULL) //两个数字位数不一样的情况
        {
            while(p1 != NULL)
            {
                p->next = (pNode) malloc (sizeof(struct Num));
                p = p->next;
                p->num = 0;
                if(flag)
                {
                    p->num += 1;
                    flag = 0;
                }
                p->num += p1->num;
                if(p->num >= 10)
                {
                    flag = 1;
                    p->num %= 10;
                }
                p1 = p1->next;
            }
        }

        if(p1 == NULL && p2 == NULL) //当两个链表都执行到最后时，判断是否应该向最高位进一
        {
            if(flag)  //如果进一的话，执行如下代码
            {
                p->next = (pNode) malloc (sizeof(struct Num));
                p = p->next;
                p->num = 1;
            }
            p->next = NULL;
        }
    }
    else //接下来的代码的作用是将不等号的两个数字相加
    {
        if(getLength(head1) > getLength(head2)) //如果两个数字位数不一样，head1所指的数的位数大于head2，相加后数字的符号应该是head1所指的数字的符号
        {
            head->num = head1->num;
            while(p2 != NULL)
            {
                p->next = (pNode) malloc (sizeof(struct Num));
                p = p->next;
                p->num = 0;
                if(flag)
                {
                    p->num -= 1;
                    flag = 0;
                }

                p->num = p1->num - p2->num + p->num;
                if(p->num < 0)
                {
                    p->num += 10;
                    flag = 1;
                }
                p1 = p1->next;
                p2 = p2->next;
            }

            while(p1 != NULL)
            {
                p->next = (pNode) malloc (sizeof(struct Num));
                p = p->next;
                p->num = 0;
                if(flag)
                {
                    p->num -= 1;
                    flag = 0;
                }

                p->num = p1->num + p->num;
                if(p->num < 0)
                {
                    p->num += 10;
                    flag = 1;
                }
                p1 = p1->next;
            }

            p->next = NULL;
        }
        else if(getLength(head1) < getLength(head2)) //head2所指的数的位数大于head1，相加后数字的符号应该是head2所指的数字的符号
        {
            head->num = head2->num;
            while(p1 != NULL)
            {
                p->next = (pNode) malloc (sizeof(struct Num));
                p = p->next;
                p->num = 0;
                if(flag)
                {
                    p->num -= 1;
                    flag = 0;
                }

                p->num = p2->num - p1->num + p->num;
                if(p->num < 0)
                {
                    p->num += 10;
                    flag = 1;
                }
                p1 = p1->next;
                p2 = p2->next;
            }

            while(p2 != NULL)
            {
                p->next = (pNode) malloc (sizeof(struct Num));
                p = p->next;
                p->num = 0;
                if(flag)
                {
                    p->num -= 1;
                    flag = 0;
                }

                p->num = p2->num + p->num;
                if(p->num < 0)
                {
                    p->num += 10;
                    flag = 1;
                }
                p2 = p2->next;
            }
        }
        else{                   //两个数字位数相等，执行如下代码
            while(p1 != NULL)
            {
                p->next = (pNode) malloc (sizeof(struct Num));
                p = p->next;
                p->num = 0;
                if(flag)
                {
                    p->num = -1;
                    flag = 0;
                }

                p->num = p1->num - p2->num + p->num;

                if(p->num < 0)
                {
                    p->num += 10;
                    flag = 1;
                }

                p1 = p1->next;
                p2 = p2->next;
            }

            if(flag)
                head->num = head2->num;
            else
                head->num = head1->num;
        }
         p->next = NULL;
    }

    convert(head); //再将运行后的数字翻转，得到想要的数字
    return head;
}

char toBigger(char c)
{
    if(c >= 'a' && c <= 'z')
    {
        c -= 32;
    }
    return c;
}
int main (void)
{
    char c;
    do{
        printf("请输入数字：（键入回车键结束该数字的输入）\n");
        pNode p1 = createList();

        printf("请输入数字：（键入回车键结束该数字的输入）\n");
        pNode p2 = createList();

        printf("两个数字相加为：\n");
        pNode head = add(p1, p2);
        printfList(head);
        printf("是否还要继续？（输入Y为继续）\n");
        scanf(" %c", &c);
        getchar();
        c = toBigger(c);
    }while(c == 'Y');
    return 0;
}
