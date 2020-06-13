 #include <stdio.h>   //
#define inf 99999999 //设置inf为无穷大，
#define MAX_VERTEX_NUM 30

typedef struct graph{  
    int e[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//邻接矩阵 ,存放边的原始长度 
    int n, m;//顶点数和边数  
}Graph; 

Graph g,gTmp;

void print(int st, int n)//st为起点， n为顶点个数 
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (i == st)//起点到起点就跳过 
            continue;
        if (g.e[st][i] != inf) //两点的最短距离不是无穷大说明可以到达。
            printf("%c可达%c\n", 'A' + st, 'A' + i);
        else
            printf("%c不可达%c\n", 'A' + st, 'A' + i);
    }
}

//Graph G 图信息, int v0,起点 int p路径信息
void ShortestPath_DIJ(Graph G, int v0, int p[][MAX_VERTEX_NUM],int *D)  
{  
    int v, w, i, j, min;  
    int final[MAX_VERTEX_NUM];  
    

    for(v=0; v<G.n; v++)  
    {  
        final[v]=0;//标记当前的点未经过处理  
        D[v]=G.e[v0][v];//D[]存放v0到v得最短距离，初值为v0到v的直接距离  
        for(w=0; w<G.n; w++)  
            p[v][w]=-1;//设p[][]初值为-1，即没有路径  
        if(D[v]<inf)//v0到v有直接路径  
        {  
            p[v][0]=v0;//v0到v最短路径经过的第一个顶点  
            p[v][1]=v;//v0到v最短路径经过的第二个顶点  
        }  
    }  
      
    D[v0]=0;//v0到v0距离为0  
    final[v0]=1;//v0顶点并入S集  
      
    for(i=1; i<G.n; i++)//其余G.vexnum-1个顶点  
    {//开始主循环，每次求得v0到某个顶点v的最短路径，并将v并入S集，然后更新p和D  
        min=inf;  
        for(w=0; w<G.n; w++)//对所有顶点检查  
            if(!final[w] && D[w]<min)//在S集之外(即final[]=false)的顶点中找离v0最近的顶点，将其赋给v,距离赋给min  
            {  
                v=w;  
                min=D[w];  
            }  
        final[v]=1;//v并入S集  
        for(w=0; w<G.n; w++)//根据新并入的顶点，更新不在S集的顶点到v0的距离和路径数组  
        {  
            if(!final[w] && min<inf && G.e[v][w]<inf && (min+G.e[v][w]<D[w]))  
            {//w不属于S集且v0->v->w的距离<目前v0->w的距离  
                D[w]=min+G.e[v][w];//更新D[w]  
                for(j=0; j<G.n; j++)//修改p[w]，v0到w经过的顶点包括v0到v经过的所有顶点再加上顶点w  
                {  
                    p[w][j]=p[v][j];  
                    if(p[w][j]==-1)//在p[w][]第一个等于-1的地方加上顶点w  
                    {  
                        p[w][j]=w;  
                        break;  
                    }  
                }                      
            }  
        }  
    }     
}  

int main()
{
    int k, i, j, t3;
    unsigned char t1, t2;
	printf("请输入顶点数和边数:");
	fflush(stdin);
    scanf("%d %d", &g.n, &g.m); //n表示顶点个数，m表示边的条数

    for (i = 0; i <= g.n; i++) //初始化
        for (j = 0; j <= g.n; j++)
            if (i == j)
                g.e[i][j] = 0;//把自己到自己的距离设为0 
            else
                g.e[i][j] = inf;//把自己到不了的边设为无穷大 

    for (i = 0; i < g.m; i++)
    {
		printf("请输入 %d src dst len:",i);
		fflush(stdin);
        scanf("%c %c %d", &t1, &t2, &t3); //表示t1到t2的距离为t3
        g.e[(int)(t1 - 'A')][(int)(t2 - 'A')] = t3;
    }
	gTmp = g;
    for (k = 0; k < g.n; k++) //Floyd
        for (i = 0; i < g.n; i++)
            for (j = 0; j < g.n; j++)
            {
                if (g.e[i][j] > g.e[i][k] + g.e[k][j]) //当i，j的原来的边的最短距离，大于经过k点所到达的距离那么就替换。
                    g.e[i][j] = g.e[i][k] + g.e[k][j];
            }
    printf("输入起点.\n");
	fflush(stdin);
    scanf("%c", &t1);
    print(t1 - 'A', g.n);

	{	//单源最短路径
		g = gTmp;
		int p[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//最短路径数组p  
		int D[MAX_VERTEX_NUM] = {inf};
		printf("输入起点和终点\n");
		fflush(stdin);

		scanf("%c %c", &t1,&t2);

		ShortestPath_DIJ(g, t1 - 'A', p,D)  ;  
    
		printf("  最短路径为：");  
		for(j=0; j<g.n; j++)  
		{  
			if(p[t2 - 'A'][j]>-1)  
				printf("%c ",p[t2 - 'A'][j]+'A'); 
			if(p[t2 - 'A'][0]== -1)
			{
				printf("no way \n"); 
				break;
			}
		}  
		printf("\n");

	}
	
	{	//第4问
		int cusNum;
		char point[MAX_VERTEX_NUM];
		char strat;
		printf("请输入开始的点:");
		fflush(stdin);
		scanf("%c",&strat);

		printf("请输入经过的点的个数:");
		fflush(stdin);
		scanf("%d",&cusNum);
		for( i = 0 ;i < cusNum ;i++)
		{
			printf("请输入第 %d 个点:");
			fflush(stdin);
			scanf("%c",&point[i]);
		}
		
		printf("路线为:\n");

		for(i = 0 ;i < cusNum ;i++)
		{
			int p[MAX_VERTEX_NUM][MAX_VERTEX_NUM]={-1};//最短路径数组p  
			int D[MAX_VERTEX_NUM] = {inf};

			int shortIndex = 0,shortLen= inf;
			
			gTmp = g;
			ShortestPath_DIJ(g, strat - 'A', p,D)  ;  

			for(j = 0;j < cusNum ; j++)//寻找离当前节点最近的节点
			{
				if(shortLen > D[point[shortIndex] - 'A'])
				{
					shortIndex = j;
					strat = point[shortIndex];//下一次从这个点开始,寻找
				}
			}
			
			
			for(j=0; j<g.n; j++)  //打印路径
			{  
				if(p[point[shortIndex] - 'A'][j]>-1)  
					printf("%c ",p[point[shortIndex] - 'A'][j]+'A'); 
			}  
			printf("\n");
			

			for( j = shortIndex ; j< cusNum -1 ; j++)//已经经过这个点，下次不用再经过
			{
				point[j] = point[j+1];
			}

			cusNum -- ;
			i --;
			
			g = gTmp;

		}
	}
	return 0;
}
