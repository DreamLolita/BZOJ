#include<bits/stdc++.h>
using namespace std;

const int N=2001;
const int M=501;
const int S=6;  
int T,n,m,rt,H[M],L[M],R[M],f[M][N];  
char word[M][S],str[N],a[S],b[S];  
bool vis[M];  

int Hash(char *s)  
{  
    int res=0;  
    for(int i=0;s[i];++i)  
        res=res*29+(s[i]-'A'+1);  
    return res;  
}  

void dfs(int x)  
{  
    if(vis[x])  
        return;  
    vis[x]=1;  
    if(L[x]==-1)  
    {  
        for(int i=0;i<=n;++i)  
        {  
            int j=i;  
            for(int k=0;str[j] && word[x][k];++k)  
                if(str[j]==word[x][k])  
                    ++j;  
            f[x][i]=j;  
        }  
    }  
    else  
    {  
        dfs(L[x]);  
        dfs(R[x]);  
        for(int i=0;i<=n;++i)  
            f[x][i] = f[R[x]][f[L[x]][i]];  
    }  
}  
int main()  
{  
	freopen("BZOJ4060.in","r",stdin);
	freopen("BZOJ4060.out","w",stdout);
	
    scanf("%d", &T);  
    while(T--)  
    {  
        memset(L,-1,sizeof L);  
        memset(vis,0,sizeof vis); 
		 
        scanf("%d",&m);  
        for(int i=0;i<m;++i)  
        {  
            scanf("%s%*s%s",a,b);  
            H[i]=Hash(a);  
            if(b[0]>='a' && b[0]<='z')  
                strcpy(word[i],b);  
            else  
            {  
                L[i]=Hash(b);  
                scanf("%*s%s",b);  
                R[i]=Hash(b);  
            }  
        }  
        
        for(int i=0;i<m;++i)  
            if(L[i]!=-1)  
            {  
                for(int j=0;j<m;++j)  
                    if(L[i]==H[j])  
                    {  
                        L[i]=j;  
                        break;  
                    }  
                for(int j=0;j<m;++j)  
                    if(R[i]==H[j])  
                    {  
                        R[i]=j;  
                        break;  
                    }  
            }  
            
        scanf("%s%s",a,str);  
        rt=Hash(a);  
        for(int i=0;i<m;++i)  
            if(rt==H[i])  
            {  
                rt=i;  
                break;  
            }  
        n=strlen(str);  
        dfs(rt);  
        puts(f[rt][0]==n ? "YES" : "NO");  
    }  
    
    return 0;  
}  
