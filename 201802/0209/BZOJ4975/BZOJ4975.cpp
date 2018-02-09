#include<bits/stdc++.h>
using namespace std;

const int N=55;
int n,ans;
int a[N];

int main()
{
	freopen("BZOJ4975.in","r",stdin);
	freopen("BZOJ4975.out","w",stdout);
	
    scanf("%d",&n);
    for (int i=1;i<=n;++i) 
		scanf("%d",&a[i]);
  
    for(int i=1;i<n;++i)
        for(int j=i+1;j<=n;j++)
            if(a[i]<a[j])
				ans^=1;
    if(!ans) 
		puts("T");
    else 
		puts("Q");
    return 0;
}
