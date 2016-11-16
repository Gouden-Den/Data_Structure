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
                printf("请输入树的内容（输入'#'时当前节点为空）\n");
                t = CreateBiTree(t);
                break;
            case 2:
                if(BiTreeEmpty(t))
                    continue;
                printf("先序遍历的结果为：\n");
                PreOrderResu(t);
                break;
            case 3:
                if(BiTreeEmpty(t))
                    continue;
                printf("中序遍历的结果为：\n");
                MidOrderResu(t);
                break;
            case 4:
                if(BiTreeEmpty(t))
                    continue;
                printf("后序遍历的结果为：\n");
                PasOrderResu(t);
                break;
            case 5:
                if(BiTreeEmpty(t))
                    continue;
                printf("先序遍历的结果为：\n");
                PreOrderNotResu(t);
                break;
            case 6:
                if(BiTreeEmpty(t))
                    continue;
                printf("中序遍历的结果为：\n");
                MidOrderNotResu(t);
                break;
            case 7:
                if(BiTreeEmpty(t))
                    continue;
                printf("后序遍历的结果为：\n");
                PasOrderNotResu(t);
                break;
            case 8:
                if(BiTreeEmpty(t))
                    continue;
                BiTreeDepth(t, 1, &depth);
                printf("树的深度为：%d\n", depth);
                break;
            case 9:
                if(BiTreeEmpty(t))
                    continue;
                printf("叶子的个数为：%d\n", Leaf(t));
                break;
            case 10:
                if(BiTreeEmpty(t))
                    continue;
                printf("请输入内容：\n");
                scanf(" %c", &ch);
                DeleteChildTree(t, ch);
                break;
            case 11:
                if(BiTreeEmpty(t))
                    continue;
                printf("层次遍历的结果为：\n");
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
