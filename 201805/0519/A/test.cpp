#include<bits/stdc++.h> 
using namespace std;
int n,a[105],sum;
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i],sum+=a[i];
    cout<<sum<<endl;
    sum&1?cout<<"Alice":cout<<"Bob";
    return 0;
}
