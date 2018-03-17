#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
int T,n,k;
char s[N];

struct Tsam
{
	int las,cnt;
	int ch[N][26],fa[N];
	int v[N],q[N],mx[N],val[N],sum[N];
	
	Tsam(){
		las=++cnt;
	}
	
	void extend(int c)
	{
		int p=las,np=las=++cnt;
		mx[np]=mx[p]+1;val[np]=1;
		while(!ch[p][c] && p)
			ch[p][c]=np,p=fa[p];
		if(!p)
			fa[np]=1;
		else
		{
			int q=ch[p][c];
			if(mx[p]+1==mx[q])
				fa[np]=q;
			else
			{
				int nq=++cnt;mx[nq]=mx[p]+1;
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				fa[nq]=fa[q];fa[np]=fa[q]=nq;
				while(ch[p][c]==q && p)
					ch[p][c]=nq,p=fa[p];
			}
		}
	}
	
	void init()
	{
		for(int i=1;i<=cnt;++i)
			v[mx[i]]++;
		for(int i=1;i<=n;++i)
			v[i]+=v[i-1];
		for(int i=cnt;i;--i)
			q[v[mx[i]]--]=i;
		for(int i=cnt;i;--i)
		{
			int t=q[i];
			if(T&1)
				val[fa[t]]+=val[t];
			else
				val[t]=1;
		}
		val[1]=0;
		for(int i=cnt;i;--i)
		{
			int t=q[i];sum[t]=val[t];
			for(int j=0;j<26;++j)
				sum[t]+=sum[ch[t][j]];
		}
	}
	
	void dfs(int x,int res)
	{
		if(res<=val[x])
			return;
		res-=val[x];
		for(int i=0;i<26;++i)
		{
			int t=ch[x][i];
			if(t)
			{
				if(res<=sum[t])
				{
					putchar(i+'a');
					dfs(t,res);
					return;
				}
				res-=sum[t];
			}
		}
	}
};
Tsam sam;

int main()
{
	freopen("BZOJ3998.in","r",stdin);
	freopen("BZOJ3998.out","w",stdout);
	
	scanf("%s",s);n=strlen(s);
	scanf("%d%d",&T,&k);
	for(int i=0;i<n;++i)
		sam.extend(s[i]-'a');
	sam.init();
	if(k>sam.sum[1])
		puts("-1");
	else
		sam.dfs(1,k);
	
	return 0;
}
