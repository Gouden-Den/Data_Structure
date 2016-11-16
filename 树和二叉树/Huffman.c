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
                printf("*********************�������*************************\n");
                break;
            case 2:
                printf("���������ģ�\n");
                getchar();
                gets(str);
                Encoding(&ht, &hc, &n, str, &ch);
                printf("*********************�������*************************\n");
                break;
            case 3:
            	if(ht == NULL)
            	{
            		printf("��������Ϊ�գ�����ȷ���ڴ����л�������\n");
            		printf("*********************�������*************************\n");
            		continue;
				}
                printf("������Ϊ��\n");
                Decoding(ht, n, ch);
                printf("*********************�������*************************\n");
                break;
            case 4:
                printf("�����ļ��еĴ���Ϊ��\n");
                Print();
                printf("*********************�������*************************\n");
                break;
            case 5:
            	if(ht == NULL)
            	{
            		printf("��������Ϊ�գ�����ȷ���ڴ����л�������\n");
            		printf("*********************�������*************************\n");
            		continue;
				}
                printf("��ӡ����������\n");
                TreePrinting(ht, n);
                printf("*********************�������*************************\n");
                break;
            default:
                printf("����������Ч�����������룡��\n");
                break;
        }
        printf("\n");
    }
    FreeAll(ht, hc, ch);
    printf("*********************�˳�����*************************\n");
    return 0;
}

