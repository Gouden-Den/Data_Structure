#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define NumberOfArray 500

//������˳���ĵط�
int getLength(int a[])
{
    int i = 0;
    int length = 0;
	while(a[i] != 0)
	{
		i++;
	}
	length = i;
	return length;
}

//1.����˳���,����ֵΪ0����
int * createArray()
{
	int a[NumberOfArray];
	int i = 0;
	do{
		scanf("%d", &a[i]);
	}while(a[i++] != 0);

	return a;
}

//2.ʵ�ָ�˳���ı���
void printfAllOfArray(int * a)
{
    if(a[0] == 0)
    {
        printf("���Ǹ���˳�����\n");
        return;
    }
    int i = 0;
	for(i = 0; i < getLength(a); i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

//3.�ڸ�˳������ĳһԪ�أ��ҵ�����1������0o
int findInArray(int * a, int num)
{
    if(a[0] == 0)
    {
        printf("���Ǹ���˳�����\n");
        return 0;
    }
    int i = 0;
	for(i = 0; i < 500 && a[i] != 0; i++)
	{
		if(a[i] == num)
		{
			return 1;
		}
	}
	return 0;
}

//4.�жϸ�˳�����Ԫ���Ƿ�Գ�,�ԳƷ���1,���򷵻�0
int isSymmetry(int * a)
{
    if(a[0] == 0)
    {
        printf("���Ǹ���˳�����\n");
        return 0;
    }
    int i = 0;
    int length = getLength(a);
	for(i = 0; i <= i/2; i++)
	{
		if(a[i] != a[length-i-1])
		{
			return 0;
		}
	}

	return 1;
}

//5.ʵ�ְѸñ���������������ż��֮ǰ,�����ǰ��Ϊ����,����Ϊż��
void five(int * a)
{
    if(a[0] == 0)
    {
        printf("���Ǹ���˳�����\n");
        return;
    }
    int length = getLength(a);
	int ji[NumberOfArray/2];
	int ou[NumberOfArray/2];
	int j = 0;
	int k = 0;
	int i = 0;

	for(; i < length; i++)
	{
		if(a[i] % 2 == 1)
		{
			ji[j++] = a[i];
		}
		else
		{
			ou[k++] = a[i];
		}
	}
	i--;
    --j;
    --k;
	while(k > -1)
	{
		a[i--] = ou[k--];
	}
	while(j > -1)
	{
		a[i--] = ji[j--];
	}
}

//6.��������Ԫ�������������������㷨����һ�������
int * createOrderlyForm()
{
    int a[NumberOfArray]= {0};
    int num;
    int count = 0;
    int flag;
    do{
        flag = 0;
        int i;
        scanf("%d", &num);
        if(num != 0)
        {
            for(i = 0; i < count; i++)
            {
                if(num < a[i])
                {
                    flag = 1;
                    int j = 0;
                    for(j = 0; j <= count-i-1; j++)
                    {
                        a[count-j] = a[count-j-1];
                    }
                    a[i] = num;
                    break;
                }
            }
        }
        if(!flag)
        {
             a[count] = num;
        }
        count++;
    }while(num != 0);
    return a;
}

//7.�����㷨6���������ǵݼ�����������Ǻϲ���һ���ǵݼ������
int * createBigOrderlyForm()
{
	int * a = createOrderlyForm();
	int c[2*NumberOfArray] = {0};
	int i = 0;
	int j = 0;
	while(a[i] != 0)
	{
		c[j++] = a[i++];

	}
	i = 0;
	printf("��������ֵ��\n");
    a = createOrderlyForm();
	while(a[i] != 0)
	{
		c[j++] = a[i++];
	}
	for(i = 0; i < j; i++)
	{
		int num;
		int k = 0;
		for(k = i+1; k < j; k++)
		{
			if(c[i] > c[k])
			{
				num = c[i];
				c[i] = c[k];
				c[k] = num;
			}
		}
	}
	return c;
}

int main(void)
{
    int num = -1;
    int a = 0;
    int * p = &a;
    do{
        printf("1.����˳���,����ֵΪ0����\n2.ʵ��˳���ı���\n3.�ڸ�˳������ĳһԪ�أ��ҵ�����1������0\n4.�жϸ�˳�����Ԫ���Ƿ�Գ�,�ԳƷ���1,���򷵻�0\n5.ʵ�ְѸñ���������������ż��֮ǰ,�����ǰ��Ϊ����,����Ϊż��");
        printf("\n6.��������Ԫ�������������������㷨����һ�������\n7.�����㷨6���������ǵݼ�����������Ǻϲ���һ���ǵݼ������\n����0�˳�����\n���������ѡ��\n");
        scanf("%d", &num);
        switch(num)
        {
            case 1:
                printf("������ֵ��\n");
                p = createArray();
                printfAllOfArray(p);
                break;
            case 2:
                printf("�����Ǳ�����ֵ:\n");
                printfAllOfArray(p);
                break;
            case 3:
                printf("������Ҫ���ҵ�Ԫ��\n");
                scanf("%d", &num);
                printf("��Ԫ��%s�������\n", findInArray(p, num)?"��":"����");
                break;
            case 4:
                printf("�����%s�Գ�\n", isSymmetry(p)?"":"��");
                break;
            case 5:
                five(p);
                printfAllOfArray(p);
                break;
            case 6:
                printf("������ֵ��\n");
                p = createOrderlyForm();
                printf("�����Ϊ��\n");
                printfAllOfArray(p);
                break;
            case 7:
                printf("������ֵ��\n");
                p = createBigOrderlyForm();
                printf("�ϳɵ������Ϊ��\n");
                printfAllOfArray(p);
                break;
            case 0:
                break;
            default:
                printf("��������ֲ���ȷ����");
                p = createArray();
                break;
        }
        printf("************************************\n\n\n");
    }while(num != 0);

	return 0;
}
