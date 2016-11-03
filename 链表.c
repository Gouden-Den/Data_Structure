#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

struct Num
{
   int num;
   struct Num * next;
};

//(1)����������һ��Ԫ�أ�����һ����ͷ���ĵ�����������
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

//(2)����������ӡ����������
void printfList(struct Num * head)
{
    struct Num * p;
    p = head;
    if(head == NULL)
    {
        printf("������Ϊ�գ���\n");
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

//(3)���ѵ���������Ԫ�����ã������������µĽ��ռ䣩��
struct Num * convert(struct Num * head)
{
    struct Num * p1, * p2, *p3;
    int n = 0;
    p1 = head;
    if(head == NULL)
    {
        printf("���Ǹ���������\n");
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

//(4)���ڵ���������ɾ�����е�ż��Ԫ�ؽ�㡣
void deleteEvenNumber(struct Num * head)
{
    struct Num * p1, * p2, * p3;
    int n = 0;
    p1 = head;
    if(head == NULL)
    {
        printf("����һ����������\n");
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

//(5)���������������������Ԫ�ذ��շǵݼ���ʽ���У�ע�⣺����ʱ���Ҫ������������˳�򣬲���ͨ�������������ݣ�����Ҫʹ�øı�ָ��ķ�ʽ��������λ�á�����ʹ��ֱ�Ӳ��������㷨����
struct Num * sortList(struct Num * head)
{
    struct Num * target, * p1, * p2;
    struct Num * q1, * q2;//�����Ҫ�ȽϵĽڵ�͸ýڵ��ǰһ���ڵ�
    if(head == NULL)
    {
        printf("���Ǹ�������!!\n");
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
        int flag = 0;//�����Ƿ񽻻���
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

//(6)�������㷨5���������ǵݼ�����������Ȼ��ϲ���һ���ǵݼ�����
struct Num * digui(struct Num * p1, struct Num * p2)//�������õĵݹ�
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
    printf("�������һ�飺\n");
    p1 = createList();
    num = *p1;
    p1 = sortList(p1);
    printfList(p1);
    printf("������ڶ��飺\n");
    p2 = createList();
    p2 = sortList(p2);
    printfList(p2);
    p1 = digui(p1, p2);//�������˸���ѭ����������ʧ�ܣ��ĳɵݹ��ͳɹ���
    printfList(p1);
    p1 = sortList(p1);
}

//(7)�������㷨1����������ɾ�������е��ظ�Ԫ�ء�
void deleteNode(struct Num * head)
{
    struct Num * p1, * p2, *p3;
    if(head == NULL)
    {
        printf("���Ǹ���������\n");
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

//(8)�������㷨1����������ʵ�ֽ���ֽ��������������һ��ȫ��Ϊ��������һ��ȫ��Ϊż��������������֪�Ĵ洢�ռ䣩��
void separate(struct Num * head, struct Num * odd, struct Num * even)
{
    struct Num * ji, * ou;
    struct Num * p1;
    p1 = head;
    ji = ou = NULL;
    if(p1 == NULL)
    {
        printf("���Ǹ���������\n");
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
    printf("���������£�\n");
    printfList(odd);
    printf("ż�������£�\n");
    printfList(even);
}

//(9)���ж��㷨1���㷨5���ɵ���������ʾ�ļ����Ƿ���ȡ�
int isEqual(struct Num * head1, struct Num * head2)//head1����ȡ�㷨1�õ��ı�head2��ȡ�㷨5�õ��ı�
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
//(10)���������������һ���򵥵Ĳ˵����ֱ���������㷨��
int main (void)
{
    struct Num * p1, * odd, * even;
    p1 = odd = even = NULL;
    int num = -1;
    do{
        printf("(1)����������һ��Ԫ�أ�����һ����ͷ���ĵ�����������\n");
        printf("(2)����������ӡ����������\n");
        printf("(3)���ѵ���������Ԫ������\n");
        printf("(4)���ڵ���������ɾ�����е�ż��Ԫ�ؽ��\n");
        printf("(5)���������������������Ԫ�ذ��շǵݼ���ʽ����\n");
        printf("(6)�������㷨5���������ǵݼ�����������Ȼ��ϲ���һ���ǵݼ�����\n");
        printf("(7)�������㷨1����������ɾ�������е��ظ�Ԫ��\n");
        printf("(8)�������㷨1����������ʵ�ֽ���ֽ��������������һ��ȫ��Ϊ��������һ��ȫ��Ϊż��\n");
        printf("(9)���ж��㷨1���㷨5���ɵ���������ʾ�ļ����Ƿ����\n����0�˳�����\n");
        printf("����������ѡ��\n");
        scanf("%d", &num);
        switch(num)
        {
            case 1:
                printf("������Ҫ�����ֵ��\n");
                p1 = createList();
                printf("����������������\n");
                printfList(p1);
                break;
            case 2:
                printf("������������\n");
                printfList(p1);
                break;
            case 3:
                printf("���ú�Ľ�����£�\n");
                p1 = convert(p1);
                printfList(p1);
                break;
            case 4:
                printf("ɾ����Ľ�����£�\n");
                deleteEvenNumber(p1);
                printfList(p1);
                break;
            case 5:
                printf("�����Ľ�����£�\n");
                p1 = sortList(p1);
                printfList(p1);
                break;
            case 6:
                p1 = createBigList();
                printf("���ý�����£�\n");
                printfList(p1);
                break;
            case 7:
                printf("���ý�����£�\n");
                deleteNode(p1);
                printfList(p1);
                break;
            case 8:
                separate(p1, odd, even);
                break;
            case 9:
                printf("��������Ҫ���㷨1���ɵ���������ݣ�\n");
                struct Num * p2, * p3;
                p2 = createList();
                printf("��������Ҫ���㷨5���ɵ���������ݣ�\n");
                p3 = createList();
                p3 = sortList(p3);
                printf("�㷨1���㷨5���ɵ���������ʾ�ļ���%s��ȵ�", isEqual(p2, p3)?"��":"��");
                break;
            case 0:
                break;
            default:
                printf("��������ȷ��ֵ����\n\n\n");
        }
        printf("**************************************************************\n\n\n");
    }while(num != 0);

    return 0;
}
