#include<stdio.h>
#include "BiTree.h"

int main(void)
{
    BiTree t = NULL;
    char ch;
    int choice, depth = 0;
    while((choice = Menu()) != 0)
    {
        switch(choice)
        {
            case 1:
                InitBiTree(t);
                printf("�������������ݣ�����'#'ʱ��ǰ�ڵ�Ϊ�գ�\n");
                t = CreateBiTree(t);
                break;
            case 2:
                if(BiTreeEmpty(t))
                    continue;
                printf("��������Ľ��Ϊ��\n");
                PreOrderResu(t);
                break;
            case 3:
                if(BiTreeEmpty(t))
                    continue;
                printf("��������Ľ��Ϊ��\n");
                MidOrderResu(t);
                break;
            case 4:
                if(BiTreeEmpty(t))
                    continue;
                printf("��������Ľ��Ϊ��\n");
                PasOrderResu(t);
                break;
            case 5:
                if(BiTreeEmpty(t))
                    continue;
                printf("��������Ľ��Ϊ��\n");
                PreOrderNotResu(t);
                break;
            case 6:
                if(BiTreeEmpty(t))
                    continue;
                printf("��������Ľ��Ϊ��\n");
                MidOrderNotResu(t);
                break;
            case 7:
                if(BiTreeEmpty(t))
                    continue;
                printf("��������Ľ��Ϊ��\n");
                PasOrderNotResu(t);
                break;
            case 8:
                if(BiTreeEmpty(t))
                    continue;
                BiTreeDepth(t, 1, &depth);
                printf("�������Ϊ��%d\n", depth);
                break;
            case 9:
                if(BiTreeEmpty(t))
                    continue;
                printf("Ҷ�ӵĸ���Ϊ��%d\n", Leaf(t));
                break;
            case 10:
                if(BiTreeEmpty(t))
                    continue;
                printf("���������ݣ�\n");
                scanf(" %c", &ch);
                DeleteChildTree(t, ch);
                break;
            case 11:
                if(BiTreeEmpty(t))
                    continue;
                printf("��α����Ľ��Ϊ��\n");
                TraverseByQueue(t);
                break;
            default:
                break;
        }
        printf("\n************************************************************\n");
    }
    printf("*****************************END****************************\n");
    return 0;
}
