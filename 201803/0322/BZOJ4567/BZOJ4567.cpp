#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
const int M=6e5+10;

int n,top,tot,cnt=1,ind=1;
int siz[N],head[N],nex[N],vs[N],q[N];
int f[M],ch[M][26];
char s[M];
LL ans,sum;

bool cmp(int x,int y)
{
	return siz[x]<siz[y];
}

void add(int u,int v)
{
	++tot;
	vs[tot]=v;nex[tot]=head[u];head[u]=tot;
}

void insert(char c[])
{
	int len=strlen(c),now=1;
	for(int i=len-1;~i;--i)
		if(ch[now][c[i]-'a'])
			now=ch[now][c[i]-'a'];
		else
			now=ch[now][c[i]-'a']=++ind;
	f[now]=1;
}

void build(int k,int x)
{
	if(f[x])
		add(k,++cnt),siz[k=cnt]=1;
	for(int i=0;i<26;++i)
		if(ch[x][i])
			build(k,ch[x][i]);
}

void pushup(int x)
{
	for(int i=head[x];i;i=nex[i])
		pushup(vs[i]),siz[x]+=siz[vs[i]];
}

void dfs(int k,int w)
{
	++sum;ans+=sum-w;w=sum;
	int l=top+1,r=top;
	for(int i=head[k];i;i=nex[i])
		q[++r]=vs[i];
	sort(q+l,q+r+1,cmp);
	top=r;
	for(int i=l;i<=r;++i)
		dfs(q[i],w);
	top=l-1;
}

int main()
{
	freopen("BZOJ4567.in","r",stdin);
	freopen("BZOJ4567.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%s",s),insert(s);
	build(1,1);pushup(1);dfs(1,1);
	printf("%lld\n",ans);
	
	return 0;
}
