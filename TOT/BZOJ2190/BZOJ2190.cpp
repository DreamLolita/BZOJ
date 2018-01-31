#include<iostream>  
#include<cstring>  
#include<cstdio>
#include<algorithm>
using namespace std;  

const int MAXN=40007;  
bool flag[MAXN];
int phi[MAXN],p[MAXN];
int ans,n,cnt=0;  

void Get_phi()
{  
    cnt=0;  
    memset(flag,true,sizeof(flag));  
    phi[1]=1;  
    for(int i=2;i<MAXN;i++)
    {  
        if(flag[i])  
        {  
            p[cnt++]=i;  
            phi[i]=i-1;
        }  
        for(int j=0;j<cnt; j++)  
        {  
            if(i*p[j]>MAXN)  
                break;  
            flag[i*p[j]] = false;
            if(i%p[j] == 0)
            {  
                phi[i*p[j]] = p[j] * phi[i];  
                break;  
            }  
            else  
                phi[i*p[j]] = (p[j]-1) * phi[i];
        }  
    }  
}  

int main()  
{  
//	freopen("BZOJ2190.in","r",stdin);
//	freopen("BZOJ2190.out","w",stdout);
	
    Get_phi();  
    scanf("%d",&n);
    ans=0;
    for(int i=2;i<n;++i)
    {
 //   	printf("i:%d %d\n",i,phi[i]);
		ans+=phi[i];
	}
    ans=ans*2+3;
    if(n==1)
    	ans=0;
    printf("%d\n",ans);
    return 0;  
}  
