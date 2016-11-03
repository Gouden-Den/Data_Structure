#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define NumberOfArray 500

//这里是顺序表的地方
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

//1.建立顺序表,输入值为0结束
int * createArray()
{
	int a[NumberOfArray];
	int i = 0;
	do{
		scanf("%d", &a[i]);
	}while(a[i++] != 0);

	return a;
}

//2.实现该顺序表的遍历
void printfAllOfArray(int * a)
{
    if(a[0] == 0)
    {
        printf("这是个空顺序表！！\n");
        return;
    }
    int i = 0;
	for(i = 0; i < getLength(a); i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

//3.在该顺序表查找某一元素，找到返回1，否则0o
int findInArray(int * a, int num)
{
    if(a[0] == 0)
    {
        printf("这是个空顺序表！！\n");
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

//4.判断该顺序表中元素是否对称,对称返回1,否则返回0
int isSymmetry(int * a)
{
    if(a[0] == 0)
    {
        printf("这是个空顺序表！！\n");
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

//5.实现把该表中所有奇数排在偶数之前,即表的前面为奇数,后面为偶数
void five(int * a)
{
    if(a[0] == 0)
    {
        printf("这是个空顺序表！！\n");
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

//6.输入整型元素序列利用有序表插入算法建立一个有序表
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

//7.利用算法6建立两个非递减有序表并把它们合并成一个非递减有序表
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
	printf("请再输入值：\n");
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
        printf("1.建立顺序表,输入值为0结束\n2.实现顺序表的遍历\n3.在该顺序表查找某一元素，找到返回1，否则0\n4.判断该顺序表中元素是否对称,对称返回1,否则返回0\n5.实现把该表中所有奇数排在偶数之前,即表的前面为奇数,后面为偶数");
        printf("\n6.输入整型元素序列利用有序表插入算法建立一个有序表\n7.利用算法6建立两个非递减有序表并把它们合并成一个非递减有序表\n输入0退出程序\n请输入你的选择：\n");
        scanf("%d", &num);
        switch(num)
        {
            case 1:
                printf("请输入值：\n");
                p = createArray();
                printfAllOfArray(p);
                break;
            case 2:
                printf("下面是遍历的值:\n");
                printfAllOfArray(p);
                break;
            case 3:
                printf("请输入要查找的元素\n");
                scanf("%d", &num);
                printf("该元素%s这个表里\n", findInArray(p, num)?"在":"不在");
                break;
            case 4:
                printf("这个表%s对称\n", isSymmetry(p)?"":"不");
                break;
            case 5:
                five(p);
                printfAllOfArray(p);
                break;
            case 6:
                printf("请输入值：\n");
                p = createOrderlyForm();
                printf("有序表为：\n");
                printfAllOfArray(p);
                break;
            case 7:
                printf("请输入值：\n");
                p = createBigOrderlyForm();
                printf("合成的有序表为：\n");
                printfAllOfArray(p);
                break;
            case 0:
                break;
            default:
                printf("输入的数字不正确！！");
                p = createArray();
                break;
        }
        printf("************************************\n\n\n");
    }while(num != 0);

	return 0;
}
