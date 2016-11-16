#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
typedef struct HTNode{
    unsigned int weight;
    unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;
typedef char ** HuffmanCode;

void Select(HuffmanTree ht, int i, int * section1, int * section2)
{
    int j, s1 = 0, s2 = 0;
    for(j = 1; j <= i; j++)
    {
        if(ht[j].parent == 0)
        {
            if(!s1 || ht[s1].parent)
            {
                s1 = j;
            }
            else
            {
                if(ht[s1].weight > ht[j].weight)
                    s1 = j;
            }
        }
    }
    for(j = 1; j <= i; j++)
    {
        if(ht[j].parent == 0 && j != s1)
        {
            if(!s2 || ht[s2].parent)
            {
                s2 = j;
            }
            else
            {
                if(ht[s2].weight > ht[j].weight)
                    s2 = j;
            }
        }
    }
    if(s1 < s2)
    {
        *section1 = s1;
        *section2 = s2;
    }
    else
    {
        *section2 = s1;
        *section1 = s2;
    }
}

void createHFMTreeFile(HuffmanTree ht, HuffmanCode hc, int n, char * ch)
{
    FILE * fp = NULL;
    int i;
    if((fp = fopen("hfmTree.txt", "wt")) == NULL)
    {
        printf("Cannot open file strike any key exit!");
        exit(1);
    }
    fprintf(fp, "%d\n", n);
    for(i = 1; i <= 2*n - 1; i++)
    {
        fprintf(fp, "%d %d %d %d\n", ht[i].weight, ht[i].parent, ht[i].lchild, ht[i].rchild);
        fflush(fp);
    }
    for(i = 1; i <= n; i++)
    {
        fputc(ch[i], fp);
        fputs(hc[i], fp);
        fputc('\n', fp);
        fflush(fp);
    }
    fclose(fp);
    fp = NULL;
}

void Initialization(HuffmanTree * ht, HuffmanCode * hc, int * N, char ** ch)
{
    HuffmanTree HT;
    HuffmanCode HC;
    char * CH;
    int m, n, i, section1, section2;
    printf("请输入字符集的大小:\n");
    scanf("%d", &n);
    int weig[n+1];
    m = 2 * n - 1;
    HT = (HuffmanTree) malloc ((m+1) * sizeof(HTNode));
    CH = (char*) malloc (n * sizeof(char));
    if(!HT || !CH)
    {
        printf("内存分配失败！！\n");
        exit(-1);
    }
    printf("请输入字符和该字符的权重：\n");
    for(i = 1; i <= n; i++)
    {
        getchar();
        CH[i] = getchar();
        scanf("%d", &weig[i]);
    }
    for(i = 1; i <= n; i++)
    {
        HT[i].weight = weig[i];
        HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
    }
    for(i = n+1; i <= m; i++)
    {
        HT[i].weight = HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
    }
    for(i = n+1; i <= m; i++)
    {
        Select(HT, i-1, &section1, &section2);
        HT[section1].parent = HT[section2].parent = i;
        HT[i].lchild = section1;
        HT[i].rchild = section2;
        HT[i].weight = HT[section1].weight + HT[section2].weight;
    }

    char * cd;
    HC = (HuffmanCode) malloc ((n+1) * sizeof(char *));
    cd = (char *) malloc (n * sizeof(char));
    cd[n-1] = '\0';
    for(i = 1; i <= n; i++)
    {
        int start = n-1, child = i, parent;
        for(parent = HT[i].parent; parent != 0; child = parent, parent = HT[parent].parent)
        {
            if(child == HT[parent].lchild)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        }
        HC[i] = (char *) malloc (n * sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    free(cd);
    createHFMTreeFile(HT, HC, n, CH);
    *ht = HT;
    *ch = CH;
    *N = n;
    *hc = HC;
}

void Encoding(HuffmanTree * ht, HuffmanCode * hc, int * n, char * str, char ** ch)
{
    FILE * fp = NULL;
    HuffmanTree HT = *ht;
    HuffmanCode HC = *hc;
    int N = *n;
    char * CH = *ch;
    if(*ht == NULL)
    {
        char code;
        int i = 1;
        if((fp = fopen("hfmTree.txt", "r")) == NULL)
        {
            printf("Cannot open file strike any key exit!");
            exit(1);
        }
        fscanf(fp, "%d", &N);
        HT = (HuffmanTree) malloc ((2*N) * sizeof(HTNode));
        HC = (HuffmanCode) malloc ((N+1) * sizeof(char *));
        CH = (char *) malloc ((N+1) * sizeof(char));
        for(i = 1; i <= 2*N - 1; i++)
        {
            fscanf(fp, "%d %d %d %d", &HT[i].weight, &HT[i].parent, &HT[i].lchild, &HT[i].rchild);
        }
        for(i = 1; i <= N; i++)
        {
            int j = 0;
            while((code = fgetc(fp)) == '\n');
            CH[i] = code;
            HC[i] = (char *) malloc (N * sizeof(char));
            while((code = fgetc(fp)) != '\n')
            {
                HC[i][j++] = code;
            }
            HC[i][j] = '\0';
        }
        fclose(fp);
        fp = NULL;
        *ht = HT;
        *hc = HC;
        *n = N;
        *ch = CH;
    }
    int i = 0;
    if((fp = fopen("CodeFile.txt", "wt")) == NULL)
    {
        printf("Cannot open file strike any key exit!");
        exit(1);
    }
    while(str[i] != '\0')
    {
        int j;
        for(j = 1; j <= N; j++)
        {
            if(str[i] == CH[j])
                break;
        }
        fputs(HC[j], fp);
        fputc('\n', fp);
        fflush(fp);
        i++;
    }
    fclose(fp);
    fp = NULL;
}

void Decoding(HuffmanTree ht, int n, char * ch)
{
    int m = 2 * n - 1;
    char code;
    FILE * fp1 = NULL, * fp2 = NULL;
    if((fp1 = fopen("CodeFile.txt", "rt")) == NULL)
    {
        printf("Cannot open file strike any key exit!");
        exit(1);
    }
    if((fp2 = fopen("TextFile.txt", "wt")) == NULL)
    {
        printf("Cannot open file strike any key exit!");
        exit(1);
    }
    while(1)
    {
        if(ht[m].lchild || ht[m].rchild)
        {
            code = fgetc(fp1);
            if(code == EOF)
                break;
            if(code == '0')
                m = ht[m].lchild;
            else if(code == '1')
                m = ht[m].rchild;
        }
        else
        {
            printf("%c", ch[m]);
            fprintf(fp2, "%c", ch[m]);
            fflush(fp2);
            m = 2 * n -1;
        }
    }
    printf("\n");
    fclose(fp1);
    fp1 = NULL;
    fclose(fp2);
    fp2 = NULL;
}

void Print()
{
    int count = 0;
    char code;
    FILE * fp1, * fp2;
    if((fp1 = fopen("CodeFile.txt", "rt")) == NULL)
    {
        printf("Cannot open file strike any key exit!");
        exit(1);
    }
    if((fp2 = fopen("CodePrint.txt", "wt")) == NULL)
    {
        printf("Cannot open file strike any key exit!");
        exit(1);
    }
    while((code = fgetc(fp1)) != EOF)
    {
        if(code == '\n')
            continue;
        putchar(code);
        fprintf(fp2, "%c", code);
        count++;
        if(!(count % 50))
        {
            putchar('\n');
            fprintf(fp2, "%c", '\n');
        }
    }
    printf("\n");
    fclose(fp1);
    fp1 = NULL;
    fclose(fp2);
    fp2 = NULL;
}

void TreePrint(HuffmanTree ht, HuffmanTree start, int count, FILE * fp)
{
    int i;
    if(start != ht)
    {
        TreePrint(ht, ht+start->rchild, count+1, fp);
        for(i = 0; i < count; i++)
        {
            printf("\t");
            fprintf(fp, "%c", '\t');
        }
        printf("%d\n", start->weight);
        fprintf(fp, "%d\n", start->weight);
        TreePrint(ht, ht+start->lchild, count+1, fp);
    }
}

void TreePrinting(HuffmanTree ht, int n)
{
    int m = 2 * n - 1, count = 0;
    FILE * fp = NULL;
    if((fp = fopen("TreePrint.txt", "wt")) == NULL)
    {
        printf("Cannot open file strike any key exit!");
        exit(1);
    }
    TreePrint(ht, ht+m, count, fp);
    fclose(fp);
    fp = NULL;
}

int Menu()
{
    int choice;
    printf("有以下选择：\n");
    printf("1.初始化\n");
    printf("2.编码\n");
    printf("3.译码\n");
    printf("4.印代码文件\n");
    printf("5.印哈夫曼树\n");
    printf("0.退出程序\n");
    printf("请输入您的选择：\n");
    scanf("%d", &choice);
    return choice;
}

void FreeAll(HuffmanTree ht, HuffmanCode hc, char * ch)
{
    free(ht);
    free(hc);
    free(ch);
}
