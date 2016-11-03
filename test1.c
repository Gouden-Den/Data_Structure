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
        printf("���Ǹ���������\n");
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
        printf("������Ϊ�գ���\n");
    }
    else
    {
        printf("��");
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
            printf("��");
            printf("%d", 0);
        }
        printf("��");
        printf("\n");
    }
}

pNode createList() //�ú�����ÿһλ������һ�ַ�����ʽ���룬Ȼ����ݶ�Ӧ��ascII��ת��Ϊ���֡�
{                   //������������ͷ�ڵ㣬ͷ�ڵ��е�ֵΪ0��������Ϊ��ֵ��Ϊ1����Ϊ��ֵ
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
            printf("�����˴�������ݣ��������˳�����\n");
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
    int flag = 0;//��¼ĳһλ����������Ƿ���ڵ���10,���flagΪ1������ڵ���10�����Ϊ0,��С��10
    p = head = (pNode) malloc (sizeof(struct Num));
    convert(head1);//��һ�к���һ�д��������������ֽ��з�ת����ת����ܷ���������
    convert(head2);
    p1 = head1->next;
    p2 = head2->next;
    if(head1->num == head2->num)//�ж��������ֵķ����Ƿ���ȣ����ͬ�ŵĻ���ִ������Ĵ���
    {
        head->num = head1->num;
        while(p1 != NULL && p2 != NULL)//ѭ��ִ�еĴ��뽫���Ӧ��λ��������ӣ����ж��Ƿ�����һλ��һ
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

        if(p1 == NULL && p2 != NULL) //��������λ����һ�������
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
        else if(p1 != NULL && p2 == NULL) //��������λ����һ�������
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

        if(p1 == NULL && p2 == NULL) //����������ִ�е����ʱ���ж��Ƿ�Ӧ�������λ��һ
        {
            if(flag)  //�����һ�Ļ���ִ�����´���
            {
                p->next = (pNode) malloc (sizeof(struct Num));
                p = p->next;
                p->num = 1;
            }
            p->next = NULL;
        }
    }
    else //�������Ĵ���������ǽ����Ⱥŵ������������
    {
        if(getLength(head1) > getLength(head2)) //�����������λ����һ����head1��ָ������λ������head2����Ӻ����ֵķ���Ӧ����head1��ָ�����ֵķ���
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
        else if(getLength(head1) < getLength(head2)) //head2��ָ������λ������head1����Ӻ����ֵķ���Ӧ����head2��ָ�����ֵķ���
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
        else{                   //��������λ����ȣ�ִ�����´���
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

    convert(head); //�ٽ����к�����ַ�ת���õ���Ҫ������
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
        printf("���������֣�������س������������ֵ����룩\n");
        pNode p1 = createList();

        printf("���������֣�������س������������ֵ����룩\n");
        pNode p2 = createList();

        printf("�����������Ϊ��\n");
        pNode head = add(p1, p2);
        printfList(head);
        printf("�Ƿ�Ҫ������������YΪ������\n");
        scanf(" %c", &c);
        getchar();
        c = toBigger(c);
    }while(c == 'Y');
    return 0;
}
