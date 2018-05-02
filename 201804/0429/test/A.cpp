#include<bits/stdc++.h>
using namespace std;

const int N=555;
int n,s,nowh,nowm,nowh2,nowm2;
int m[N],h[N];

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
	return f?ret:-ret;
}

int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	
	n=read();s=read();
	for(int i=1;i<=n;++i)
		h[i]=read(),m[i]=read();
	int nowh=h[1],nowm=m[1];
	if(nowm>s || nowh)
	{
		puts("0 0");
		return 0;
	}
	for(int i=1;i<n;++i)
	{
		nowm=m[i]+s+1;nowh=h[i];
		if(nowm>=60)
			nowm-=60,++nowh;
//printf("%d %d ",nowh,nowm);
		nowm2=m[i+1]-s-1;nowh2=h[i+1];
		if(nowm2<0)
			nowm2+=60,--nowh2;
		if(nowm2<0)
			nowm2+=60,--nowh2;
//printf("%d %d\n",nowh2,nowm2);
		if(nowh2<nowh || (nowh2==nowh && nowm2<nowm))
			continue;
		printf("%d %d\n",nowh,nowm);
		return 0;
	}
	nowm=m[n]+s+1;nowh=h[n];
	if(nowm>=60)
		nowm-=60,++nowh;
	printf("%d %d\n",nowh,nowm);
	
	
	return 0;
}
