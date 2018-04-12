#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<stdio.h>
#include<algorithm>
using namespace std;

const int maxn=100100;
const int maxl=20;

struct Tnode
{
	int L,R,Size,fix;
	Tnode *lson,*rson;
} tree[maxn<<2];
Tnode *Root=NULL;
int cur=-1;

struct data
{
	int K,M,Time;
} ask[maxn];
int id[maxn];

int cnt[maxn];
int temp1[maxn];
int temp2[maxn];
int *X=temp1,*Y=temp2;

int sa[maxn];
int height[maxn];
int ST[maxn][maxl];

int a[maxn];
char s[maxn];
int ans[maxn];
int n,m=300,q;

bool Comp(int *r,int p,int q,int l)
{
	return ( r[p]==r[q] && r[p+l]==r[q+l] );
}

void Da()
{
	for (int i=0; i<m; i++) cnt[i]=0;
	for (int i=0; i<n; i++) cnt[ X[i]=a[i] ]++;
	for (int i=1; i<m; i++) cnt[i]+=cnt[i-1];
	for (int i=n-1; i>=0; i--) sa[ --cnt[ X[i] ] ]=i;
	
	//for (int i=0; i<n; i++) printf("%d ",sa[i]);
	//printf("\n");
	
	int p=1;
	for (int j=1; p<n; j<<=1,m=p)
	{
		p=0;
		for (int i=n-j; i<n; i++) Y[p++]=i;
		for (int i=0; i<n; i++) if (sa[i]>=j) Y[p++]=sa[i]-j;
		
		for (int i=0; i<m; i++) cnt[i]=0;
		for (int i=0; i<n; i++) cnt[ X[ Y[i] ] ]++;
		for (int i=1; i<m; i++) cnt[i]+=cnt[i-1];
		for (int i=n-1; i>=0; i--) sa[ --cnt[ X[ Y[i] ] ] ]=Y[i];
		
		p=1;
		swap(X,Y);
		X[ sa[0] ]=0;
		for (int i=1; i<n; i++) X[ sa[i] ]=( Comp(Y,sa[i-1],sa[i],j)? p-1:p++ );
		
		/*printf("%d\n",j);
		for (int i=0; i<n; i++) printf("%d ",sa[i]);
		printf("\n");
		printf("%d\n",p);*/
	}
}

void Calc_height()
{
	height[0]=0;
	int k=0;
	for (int i=0; i<n; i++)
	{
		if (k) k--;
		if (!X[i]) continue;
		int j=sa[ X[i]-1 ];
		while (a[i+k]==a[j+k]) k++;
		height[ X[i] ]=k;
	}
}

void Calc_ST()
{
	for (int i=0; i<n; i++) ST[i][0]=sa[i];
	for (int j=1; j<maxl; j++)
		for (int i=0; i<n; i++)
		{
			int mid=i+(1<<(j-1));
			if (mid>=n) mid=n-1;
			ST[i][j]=min(ST[i][j-1],ST[mid][j-1]);
		}
}

bool Comp1(data x,data y)
{
	return x.K>y.K;
}

bool Comp2(int x,int y)
{
	return height[x]>height[y];
}

Tnode *New_node(int vL,int vR)
{
	cur++;
	tree[cur].L=vL;
	tree[cur].R=vR;
	tree[cur].Size=1;
	tree[cur].fix=rand();
	tree[cur].lson=tree[cur].rson=NULL;
	return tree+cur;
}

void Recount(Tnode *P)
{
	P->Size=1;
	if (P->lson) P->Size+=P->lson->Size;
	if (P->rson) P->Size+=P->rson->Size;
}

void Right_turn(Tnode *&P)
{
	Tnode *W=P->lson;
	P->lson=W->rson;
	W->rson=P;
	P=W;
	Recount(P->rson);
	Recount(P);
}

void Left_turn(Tnode *&P)
{
	Tnode *W=P->rson;
	P->rson=W->lson;
	W->lson=P;
	P=W;
	Recount(P->lson);
	Recount(P);
}

void Insert(Tnode *&P,int vL,int vR)
{
	if (!P) P=New_node(vL,vR);
	else
		if (vL<P->L)
		{
			Insert(P->lson,vL,vR);
			if ( P->lson->fix < P->fix ) Right_turn(P);
			else Recount(P);
		}
		else
		{
			Insert(P->rson,vL,vR);
			if ( P->rson->fix < P->fix ) Left_turn(P);
			else Recount(P);
		}
}

Tnode *Find_prev(Tnode *P,int vL,Tnode *op)
{
	if (!P) return op;
	if (P->L<=vL) return Find_prev(P->rson,vL,P);
	else return Find_prev(P->lson,vL,op);
}

void Delete(Tnode *&P,int vL)
{
	if (P->L==vL)
		if (P->lson)
			if (P->rson)
				if ( P->lson->fix < P->rson->fix )
				{
					Right_turn(P);
					Delete(P->rson,vL);
					Recount(P);
				}
				else
				{
					Left_turn(P);
					Delete(P->lson,vL);
					Recount(P);
				}
			else P=P->lson;
		else P=P->rson;
	else
	{
		if (vL<P->L) Delete(P->lson,vL);
		else Delete(P->rson,vL);
		Recount(P);
	}
}

Tnode *Find(Tnode *P,int Rank)
{
	int Ls=1;
	if (P->lson) Ls+=P->lson->Size;
	if (Ls==Rank) return P;
	if (Ls<Rank) return Find(P->rson,Rank-Ls);
	return Find(P->lson,Rank);
}

int Query(int L,int R)
{
	int lg=0;
	while (L+(1<<(lg+1))-1<=R) lg++;
	R=R-(1<<lg)+1;
	return min(ST[L][lg],ST[R][lg]);
}

int main()
{
	freopen("2440.in","r",stdin);
	freopen("2440_std.out","w",stdout);
	
	scanf("%s",s);
	n=strlen(s);
	for (int i=0; i<n; i++) a[i]=(int)s[i];
	a[n++]=0;
	
	Da();
	Calc_height();
	Calc_ST();
	
	//for (int i=0; i<n; i++) printf("%d ",height[i]);
	//printf("\n");
	
	scanf("%d",&q);
	for (int i=1; i<=q; i++) scanf("%d%d",&ask[i].K,&ask[i].M),ask[i].Time=i;
	sort(ask+1,ask+q+1,Comp1);
	
	for (int i=0; i<n; i++) id[i]=i;
	sort(id,id+n,Comp2);
	
	srand(19260817);
	int ta=0,ti=-1;
	n--;
	for (int i=n; i>=1; i--)
	{
		Insert(Root,X[n-i],X[n-i]);
		while ( ti<n-1 && height[ id[ti+1] ]>=i )
		{
			ti++;
			Tnode *P=Find_prev(Root,id[ti]-1,NULL);
			Tnode *Q=Find_prev(Root,id[ti],NULL);
			int vL=P->L;
			int vR=Q->R;
			
			Delete(Root,P->L);
			Delete(Root,Q->L);
			Insert(Root,vL,vR);
		}
		
		while ( ta<q && ask[ta+1].K>=i )
		{
			ta++;
			if (ask[ta].M>Root->Size) ans[ ask[ta].Time ]=-1;
			else
			{
				Tnode *P=Find(Root,ask[ta].M);
				ans[ ask[ta].Time ]=Query(P->L,P->R);
			}
		}
	}
	
	for (int i=1; i<=q; i++)
		if (ans[i]==-1) printf("Not found\n");
		else printf("%d\n",ans[i]);
	
	return 0;
}



























