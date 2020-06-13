#include "stdio.h"

typedef struct edge
{
    int src;
    int dst;
    int weight;
}Edge;

//prim
int main()
{

    Edge edge;
    Edge allEdge[1000];
    int allNode[2000];
    int nodeNum = 0;//点的数量
    int num=0;//待存储的边的索引
    int i,j,k;
    int ch;
    int srcIn = 0 ,dstIn = 0;
    do
    {
        printf("请输入边的起点:");
        scanf("%d",&edge.src);

        printf("请输入边的终点:");
        scanf("%d",&edge.dst);

        printf("请输入边的权重:");
        scanf("%d",&edge.weight);

        for(i = 0 ;i< num ; i++)//寻找插入位置
        {
            if(allEdge[i].weight >= edge.weight)
            {
                break;
            }
        }
        for(k = 0,j = i; j < num ;j++,k++)//空出插入位置
        {
            allEdge[num - k] = allEdge[num - k -1];
        }
        allEdge[i] = edge; //插入
        num++;

        printf("是否继续 1:退出 其他值继续输入:");
        scanf("%d",&ch);
    }while(1 != ch);
    
	printf("所有边:\n");
	for(i = 0 ; i < num ; i++)
		printf(">%d %d\n",allEdge[i].src,allEdge[i].dst);

	printf("组成最小生成树的边:\n");
	allNode[nodeNum++] = allEdge[0].src;
    for(i = 0 ; i < num ; i++)
    {
        srcIn = 0 ,dstIn = 0;
        for(j = 0 ; j < nodeNum ; j++)
        {
            if(allEdge[i].src == allNode[j])
            {
                srcIn = 1;
                break;
            }
        }
        
        for(j = 0 ; j < nodeNum ; j++)
        {
            if(allEdge[i].dst == allNode[j])
            {
                dstIn = 1;
                break;
            }
        }

        if(srcIn^dstIn)
        {
            printf("%d -> %d\n",allEdge[i].src,allEdge[i].dst);
            if(0 == srcIn)
                allNode[nodeNum++] = allEdge[i].src;
            if(0 == dstIn)
                allNode[nodeNum++] = allEdge[i].dst;
			i = 0;
        }
    }

    return 0;
}
