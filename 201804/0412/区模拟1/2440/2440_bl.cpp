#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int n,q,k,m,len,ans,tot;
int ch[N][27];
int id[N][27];
char s[N];

void build(int beg)
{
	int now=0;
	for(int i=beg;i<=len;++i)
	{
		int v=s[i]-'a';
		if(!ch[now][v])
		{
			ch[now][v]=++tot;
			id[now][v]=beg;
		}
		now=ch[now][v];
//		printf("%d %d\n",now,ch[now][v]);
	}
}

void query(int &las,int ned,int now,int v)
{
//	printf("%d %d %d %d %d\n",las,ned,now,v,id[now][v]);
	if(ned==0)
		--las;
	if(las==0 && ans==-1)
	{
		ans=id[now][v];
		return;
	}
	if(ned<=0 || ans!=-1)
		return;

	int t=ch[now][v];
	for(int i=0;i<26;++i)
		if(ch[t][i])
			query(las,ned-1,t,i);
}

int main()
{
	freopen("2440.in","r",stdin);
	freopen("2440.out","w",stdout);
	
	scanf("%s",s+1);len=strlen(s+1);
	for(int i=1;i<=len;++i)
		build(i);	
	
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d%d",&k,&m);
		ans=-1;
		for(int i=0;i<26;++i)
		{
			if(ch[0][i])
				query(m,k-1,0,i);
		}
		if(ans==-1)
			puts("Not found");
		else
			printf("%d\n",ans-1);
	}
	
	return 0;
}
