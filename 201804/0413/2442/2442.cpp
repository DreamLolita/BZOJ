#include<bits/stdc++.h>
using namespace std;

const int N=55;
const int M=2e5+10;
int len,n,tot,totans;
int ans[N],f[N][N],g[N][M];
int w[M],ch[M][27];
char s[N],a[N];

void inse(int l,int c)
{
	int now=0;
	for(int i=1;i<=l;++i)
	{
		int v=a[i]-'a';
		if(!ch[now][v])
			ch[now][v]=++tot;
		now=ch[now][v];
	}
	w[now]=max(w[now],c);
}

int main()
{
	freopen("2442.in","r",stdin);
	freopen("2442.out","w",stdout);
	
	for(int i=1;i<M;i++)w[i]=-1;
	scanf("%s",s+1);len=strlen(s+1);
	for(int i=1;i<=len;i++)
		s[i]-='a';
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		int c,l;
		scanf("%s%d",a+1,&c);l=strlen(a+1);
		inse(l,c);
		reverse(a+1,a+l+1);
		inse(l,c);
	}
//printf("%d\n",tot);
	for(int i=0;i<=len+1;i++)
		for(int j=0;j<=len+1;j++)
			f[i][j]=-1;
	for(int i=len;i;--i)
	{
		for(int j=i-1;j<=len+1;++j)
			for(int k=0;k<=tot;++k)
				g[j][k]=-1;
		g[i-1][0]=0;
		for(int j=i-1;j<=len;++j)
			for(int k=0;k<=tot;++k)
				if(~g[j][k])
				{
					for(int q=j+1;q<=len;++q)
						if(~f[j+1][q])
							g[q][k]=max(g[q][k],g[j][k]+f[j+1][q]);
					if(j<len)
					{
						int p=ch[k][s[j+1]];
						if(p)
						{
							g[j+1][p]=max(g[j+1][p],g[j][k]);
							if(~w[p])
								g[j+1][0]=max(g[j+1][0],g[j][k]+w[p]);
						}
					}
					if(!k)
						f[i][j]=max(f[i][j],g[j][k]);
				}
	}
	for(int i=1;i<=len;++i)
	{
		ans[i]=ans[i-1];
		for(int j=1;j<=i;++j)
			if(~f[j][i])
				ans[i]=max(ans[i],ans[j-1]+f[j][i]);
//		totans=max(totans,ans[i]);
	}
	printf("%d\n",ans[len]);
	
	return 0;
}
