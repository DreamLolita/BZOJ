#include<bits/stdc++.h>
using namespace std;  
      
const int N=1e4+10;  
const int M=4e5+10;  
const int S=1e6+10;   
int n,m,tot,MaxMoney,mn,mx,c[N];
int las[233],mon[N],w[M],sum[M],top; 
int now[S],waste[S],I[S],pos[S],res[S];  
bool bo[N];  
      
inline bool dfs(int pos,int waste)  
{  
//  printf("%d %d\n",pos,waste);
	if (waste>mx) 
		return 0;  
    if (!pos) 
		return 1;  
    int tmp=las[w[pos]];  
    for (int i=tmp;i>=1;--i) 
	{  
        if (mon[i]<w[pos]) 
			continue;  
        mon[i]-=w[pos];  
        int add=0;  
        if (mon[i]<mn) 
			add=mon[i];  
        las[w[pos]]=i;  
        if(dfs(pos-1,waste+add)) 
			return 1;  
        mon[i]+=w[pos];  
    }  
    las[w[pos]]=tmp;  
    return 0;  
}  
  
inline bool check(int now)  
{  
	
    if(sum[now]>tot || w[now]>c[n]) 
		return 0;  
      
    mx=tot-sum[now];  
    for(int i=1;i<=n;++i) 
		mon[i]=c[i];  
    for (int i=1;i<= now;++i)  
        las[w[i]]=n;  
          
    return dfs(now,0);  
}  
  
int main()  
{  
	freopen("BZOJ3703.in","r",stdin);  
	freopen("BZOJ3703.out","w",stdout);  

    scanf("%d",&n);
    for(int i=1;i<= n;++i)   
        scanf("%d",&c[i]),tot+=c[i];  
    scanf("%d",&m);
    for(int i=1;i<=m;++i)  
    	scanf("%d",&w[i]); 
    sort(w+1,w+m+1);  
    for (int i=1;i<=n;++i)  
        if(c[i]<w[1])   
            tot-=c[i],bo[i]=1;  
    
    int ns=0;  
    for(int i=1;i<=n;++i)  
        if(!bo[i]) 
			c[++ns]=c[i];  
    sort(c+1,c+ns+1); n=ns;  
    for (int i=1;i<=m;++i)  
        sum[i]=sum[i-1]+w[i];  
      
    int L=0,R=m;  
    int posi=1;  
    for(int i=1;i<=m;++i) 
	{  
        while(posi<=n && w[i]>c[posi])   
            ++posi;  
        if(c[posi]>=w[i]) 
			++L,++posi;  
    }  
           
    while(L+1<R) 
	{  
        int mid=(L+R)>>1; 
        if(check(mid)) 
			L=mid;  
        else 
			R=mid;  
    }  
    if(check(R))
    	printf("%d\n",R);
    else
    	printf("%d\n",L);
    	
    return 0;  
}  
