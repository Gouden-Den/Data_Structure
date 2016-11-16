#include<stdio.h>
#include"HuffMan.h"
int main (void)
{
    HuffmanTree ht = NULL;
    HuffmanCode hc = NULL;
    int n = 0, choice;
    char * ch = NULL;
    char str[100];
    while((choice = Menu()) != 0)
    {
        switch(choice)
        {
            case 1:
                Initialization(&ht, &hc, &n, &ch);
                printf("*********************操作完毕*************************\n");
                break;
            case 2:
                printf("请输入正文：\n");
                getchar();
                gets(str);
                Encoding(&ht, &hc, &n, str, &ch);
                printf("*********************操作完毕*************************\n");
                break;
            case 3:
            	if(ht == NULL)
            	{
            		printf("霍夫曼树为空，请先确保内存中有霍夫曼树\n");
            		printf("*********************操作完毕*************************\n");
            		continue;
				}
                printf("译码结果为：\n");
                Decoding(ht, n, ch);
                printf("*********************操作完毕*************************\n");
                break;
            case 4:
                printf("代码文件中的代码为：\n");
                Print();
                printf("*********************操作完毕*************************\n");
                break;
            case 5:
            	if(ht == NULL)
            	{
            		printf("霍夫曼树为空，请先确保内存中有霍夫曼树\n");
            		printf("*********************操作完毕*************************\n");
            		continue;
				}
                printf("打印霍夫曼树：\n");
                TreePrinting(ht, n);
                printf("*********************操作完毕*************************\n");
                break;
            default:
                printf("输入内容无效，请重新输入！！\n");
                break;
        }
        printf("\n");
    }
    FreeAll(ht, hc, ch);
    printf("*********************退出程序*************************\n");
    return 0;
}

