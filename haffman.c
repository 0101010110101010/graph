#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MESS_LEN 1000

int encodelen = 0;

struct node
{
	char c[10];/*被字符*/
	double gl;/*字符的概率*/
	char * encode;/*存放此节点的编码*/
	struct node * parent;
	struct node *l;
	struct node *r;
};

sort(int *,int);

int printEncode(struct node * Node,char * value)
{
	char encode[1024] = {0};

	if(Node->parent)
	{
		Node->encode =(char *) malloc(sizeof(char) * (strlen(Node->parent->encode) + 2 ));
		strcpy(Node->encode,Node->parent->encode);
		strcpy(Node->encode +strlen(Node->encode),value);

	}
	if(Node->l)
	{
		printEncode(Node->l,"0");
	}
	if(Node->r)
	{
		printEncode(Node->r,"1");
	}
	if((NULL == Node->l) && (NULL == Node->r))
	{
		printf("%s:%s\n",Node->c,Node->encode);
		encodelen += MESS_LEN*Node->gl*strlen(Node->encode);
	}

	return 0;
}
/*数组的值从小到大排序*/
int sort(struct node **num,int len)
{
	int i,j,min_index ;
	struct node *tmp;
	for(i = 0; i< len ; i++)
	{
		min_index = i;
		for(j = i + 1; j< len ; j++)
		{
			if(num[j]->gl < num[min_index]->gl)
			{
				min_index = j;
			}
		}
		tmp = num[i];
		num[i] = num[min_index];
		num[min_index] = tmp;
	}
	return 0;
}

int main()
{
	int len,i;
	struct node **num;
	printf("请输入被编码字符的个数\n");
	scanf("%d",&len);

	num = (struct node  **)malloc(sizeof(struct node *) * len);
	if(num == NULL)
	{
		printf("申请内存失败\n");
		return 0;
	}

	/*输入字符和概率*/
	for(i = 0 ;i < len ;i++)
	{
		struct node * tmp = (struct node *)malloc(sizeof(struct node));
		memset(tmp , 0x00 ,sizeof(struct node));
		printf("请输入第 %d 个字符和概率\n",i);
		fflush(stdin);
		scanf("%s %lf",tmp->c,&tmp->gl);

		num[i] = tmp;
	}

	/*构建哈夫曼树*/
	while(len > 1)
	{
		struct node * stTmp;
		sort(num,len);
		stTmp = (struct node  *)malloc(sizeof(struct node));
		memset(stTmp,0x00,(sizeof(struct node)));
		
		stTmp->gl = num[0]->gl + num[1]->gl;
		num[0]->parent = stTmp;
		num[1]->parent = stTmp;
		stTmp->l = num[0];
		stTmp->r = num[1];
		num[1] = stTmp;
		for( i =1 ; i < len ;i++)
		{
			num[i - 1] = num[i];
		}
		len--;
	}
	
	num[0]->encode =(char *) malloc(sizeof(char) * ( 2 ));
	memset(num[0]->encode,0x00,sizeof(char) * ( 2 ));
	printEncode(num[0],"0");

	printf("编码后的报文长度 %d bit\n",encodelen);
	return 0;
}
