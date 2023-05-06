#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
typedef struct arcnode//����
{
	int data;//����
	struct arcnode *next;//��һ������ָ��
}arcnode;
typedef struct vnode//������
{
	int d;//����
	int indegree,outdegree;//��ȳ���
	struct arcnode *first;//��һ�������ý��Ļ�
	bool visited;//ͳ���Ƿ񱻷���
}vnode;
typedef struct gragh//����ͼ
{
	vnode a[100];//�ڽӱ�
	int vexnum,arcnum;//����������
}graph;
typedef struct
{
	vnode da[100];
	int top;
}stack;
void initstack(stack &s)
{
	s.top=-1;
}
bool stackempty(stack s)
{
	if(s.top==-1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool push(stack &s,vnode x)
{
	if(s.top==100-1)
	{
		return false;
	}
	else
	{
		s.da[++s.top]=x;
		return true;
	}
}
vnode pop(stack &s)
{
	return s.da[s.top--];
}
int location(gragh *g,int data)
{
	int i;
	for(i=0;i<g->vexnum;i++)
	{
		if(g->a[i].d==data)
		{
			return i;
		}
	}
	return -1;
}
graph *cre()
{
	int i,j,start;
	gragh *g=new gragh;
	arcnode *p;
	cout<<"������ͼ�Ķ�������";
	scanf("%d",&g->vexnum);
	for(i=0;i<g->vexnum;i++)
	{
		g->a[i].first=NULL;
	}
	cout<<"������ͼ�ı�����";
	scanf("%d",&g->arcnum);
	for(i=0;i<g->vexnum;i++)
	{
		printf("�������%d�����㣺",i+1);
		scanf("%d",&g->a[i].d);
	}
	for(i=0;i<g->arcnum;i++)
	{
		cout<<"����ߵ���㣺";
		scanf("%d",&start);
		for(j=0;j<g->vexnum;j++)
		{
			if(g->a[j].d==start)
			{
				p=new arcnode;
				p->next=NULL;
				cout<<"����ߵ��յ㣺";
				scanf("%d",&p->data);
				p->next=g->a[j].first;
				g->a[j].first=p;
			}
		}
	}
	return g;
}
void findoutdegree(gragh *g)
{
	int i;
	arcnode *p;
	for(i=0;i<g->vexnum;i++)
	{
		g->a[i].outdegree=0;
	}
	for(i=0;i<g->vexnum;i++)
	{
		p=g->a[i].first;
		while(p)    
		{
			g->a[i].outdegree++;
			p=p->next;
		}
	}
}
void findindegree(graph *g)
{
	int i;
	arcnode *p;
	for(i=0;i<g->vexnum;i++)
	{
		g->a[i].indegree=0;
	}
	for(i=0;i<g->vexnum;i++)
	{
		p=g->a[i].first;
		while(p)
		{
			g->a[location(g,p->data)].indegree++;
			p=p->next;
		}
	}
}
int main()
{
	int i,j,count=0;
	stack s;
	vnode v;
	arcnode *q;
	graph *g=cre();
	for(i=0;i<g->vexnum;i++)
	{
		g->a[i].visited=false;
	}
	initstack(s);
	findindegree(g);
	findoutdegree(g);
	for(i=0;i<g->vexnum;i++)
	{
		if(g->a[i].outdegree==0||g->a[i].indegree==0)
		{
			push(s,g->a[i]);
			g->a[i].visited=true;
		}
	}
	while(!stackempty(s))
	{
		v=pop(s);
		count++;
		for(q=v.first;q;q=q->next)
		{
			g->a[location(g,q->data)].indegree--;
		}
		for(j=0;j<g->vexnum;j++)
		{
			for(q=g->a[j].first;q;q=q->next)
			{
				if(q->data==v.d)
				{
					g->a[j].outdegree--;
				}
			}
		}
		for(i=0;i<g->vexnum;i++)
		{
			if((g->a[i].outdegree==0||g->a[i].indegree==0)&&g->a[i].visited==false)
			{
				push(s,g->a[i]);
				g->a[i].visited=true;
			}
		}
	}
	if(count<g->vexnum)
	{
		cout<<"���ڻ�"<<endl;
		cout<<"���ɻ��Ķ���Ϊ��"<<endl;
		for(i=0;i<g->vexnum;i++)
		{
			if(g->a[i].visited==false)
			{
				printf("%d ",g->a[i].d);
			}
		}
	}
	else
	{
		cout<<"�����ڻ�"<<endl;
		cout<<"����������������"<<endl;
		stack s;
		vnode v;
	    arcnode *q;
		/*graph *g=cre();*/
		for(i=0;i<g->vexnum;i++)
		{
			g->a[i].visited=false;
		}
		int n[100];int k=0;
		initstack(s);
		findindegree(g);
		findoutdegree(g);
		for(i=0;i<g->vexnum;i++)
		{                
			if(g->a[i].indegree==0)
			{n[k]=g->a[i].d;
				k++;
				push(s,g->a[i]);
				
				g->a[i].visited=true;
			}
		}
		while(!stackempty(s))
		{
			v=pop(s);
			for(q=v.first;q;q=q->next)
			{
				g->a[location(g,q->data)].indegree--;
			}
			for(i=0;i<g->vexnum;i++)
			{
				if(g->a[i].indegree==0&&g->a[i].visited==false)
				{n[k]=g->a[i].d;
				    k++;
					push(s,g->a[i]);
					
					g->a[i].visited=true;	
				}
			}
		}
			for(i=0;i<count;i++)
			{
				printf("%d ",n[i]);
			}
	}	
		system("pause");                    
		return 0;
}

			






