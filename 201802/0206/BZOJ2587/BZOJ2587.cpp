#include<bits/stdc++.h> 
using namespace std;  

typedef long long LL;
const int N=1e6+10;
int n,cnt;
int head[N],nex[N],a[N],b[N],f[N],g[N],p[N],sz[N],ans[N]; 
bool bo[N];  

int read()
{  
    int x=0; char cr=getchar();  
    while (cr<'0' || cr>'9') cr=getchar();  
    while (cr>='0' && cr<='9'){ x=x*10+cr-'0'; cr=getchar(); }  
    return x;  
}  

void add(int x,int y)
{ 
	nex[y]=head[x]; 
	head[x]=y; 
}  

int main()
{  
//	freopen("BZOJ2587.in","r",stdin);
//	freopen("BZOJ2587.out","w",stdout);
	
    n=read();  
    for(int i=1;i<=n;++i)
	{  
        int x=read(); 
		add(x,i);  
    }  
    
    for(int i=n;i;--i)  
        for (int x=head[i];x;x=nex[x])
		{ 
			a[++cnt]=i; 
			b[cnt]=x; 
		}  
		
    memset(head,0,sizeof(head)); 
	memset(p,-1,sizeof(p));  
    f[a[1]]=1;g[a[1]]=a[1];p[a[1]]=0;  
    add(a[1]+a[a[1]+1],a[1]);  
    
    for(int i=a[1]+1;i<=n;++i)
	{  
        f[i]=f[i-1]; g[i]=(1ll*f[i-1]*g[i-1]==i-1)?g[i-1]+1:g[i-1];  
        for(int x=head[i];x;x=nex[x])  
            if(f[x]+1>f[i])
			{  
                f[i]=f[x]+1; 
				g[i]=max(g[x],i-x); 
				p[i]=x;  
            } 
			else 
			if(f[x]+1==f[i] && max(g[x],i-x)<g[i])
			{  
                g[i]=max(g[x],i-x); 
				p[i]=x;  
            }  
        add(i+a[i+1],i);  
    }
	  
    memset(head,0,sizeof(head)); 
	memset(bo,1,sizeof(bo)); 
	cnt=0; 
	
	printf("%d\n",f[n]);  
    for(int i=n;i>=a[1];i=(p[i]>=0)?p[i]:i-1)  
        if (p[i]>=0)
		{  
            cnt++;  
            for(int x=i;x>p[i];--x)
			{ 
				add(cnt,b[x]); 
				sz[cnt]++; 
				bo[x]=0; 
			}  
        }  
    for(int i=1,x=cnt;i<=n;++i) 
		if (bo[i])
		{  
	        while(sz[x]==g[n]) 
				--x;  
	        add(x,b[i]);
			++sz[x];  
	    }  
    for(int i=1;i<=cnt;i++)
	{  
        printf("%d",sz[i]);  
        for (int x=head[i];x;x=nex[x]) 
			printf(" %d",x); 
		puts("");  
    }  
    
    return 0;  
}  
