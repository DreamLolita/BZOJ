#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;
const int M=N<<5;
const int mod=268435456;
int T,n,m,l,x,bas,bas2;
int a[N],f[M];
LL sum[N];

int read()
{
	int ret=0,f=1;char c='.';
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return ret*f;
}

struct Trie
{

	int sz,val[M],num[M],ch[M][2];
	
	void init()
	{
		ch[0][0]=ch[0][1]=0;
		sz=0;
	}
	
	int new_node()
	{
		++sz;
		ch[sz][0]=ch[sz][1]=0;val[sz]=-1;num[sz]=0;
		return sz;
	}
	
	void insert(int p,int id,int k,int now)
	{
		if(k==-1)
		{
			val[now]=f[id];
			return;
		}
		int t=((p>>k)&1);
		if(!ch[now][t])
			ch[now][t]=new_node();
		num[ch[now][t]]++;
		insert(p,id,k-1,ch[now][t]);
		val[now]=max(val[now],val[ch[now][t]]);
	}
	
	int query(int p,int q,int k,int now)
	{
		if(k==-1)
			return val[now];
		int t=((p>>k)&1),t2=((q>>k)&1),ret=-1;
		if(t2==1)
		{
			if(ch[now][t] && num[ch[now][t]])
				ret=max(ret,val[ch[now][t]]);
			if(ch[now][!t] && num[ch[now][!t]])
				ret=max(ret,query(p,q,k-1,ch[now][!t]));
		}
		else
		{
			if(ch[now][t] && num[ch[now][t]])
				ret=max(ret,query(p,q,k-1,ch[now][t]));
		}
		return ret;
	}
	
	void dele(int p,int k,int now)
	{
		if(k==-1)
		{
			if(num[now]==0)
				val[now]=-1;
			return;
		}
		int t=((p>>k)&1);
		num[ch[now][t]]--;
		dele(p,k-1,ch[now][t]);
		val[now]=val[ch[now][t]];
		if(ch[now][!t] && num[ch[now][!t]])
			val[now]=max(val[now],val[ch[now][!t]]);
	}
}tr;


int main()
{
	freopen("HDU5845.in","r",stdin);
	freopen("HDU5845.out","w",stdout);
	
	T=read();
	while(T--)
	{
		n=read();x=read();l=read();
		sum[1]=a[1]=read();bas=read();bas2=read();
		for(int i=2;i<=n;++i)
		{
			a[i]=(1ll*a[i-1]*bas+bas2)%mod;
			sum[i]=sum[i-1]^a[i];
//printf("%d\n",a[i]);
		}
		tr.init();
		memset(f,0,sizeof(f));
		tr.insert(0,0,30,0);f[0]=1;
		for(int i=1;i<=n;++i)
		{
			if(i>l && f[i-l-1])
				tr.dele(sum[i-l-1],30,0);
			int cnt=tr.query(sum[i],x,30,0);
			if(cnt>=0)
			{
				f[i]=cnt+1;
				tr.insert(sum[i],i,30,0);
			}
//			printf("%d\n",f[i]);
		}
		printf("%d\n",f[n]);
	}
	
	return 0;
}
