#include<bits/stdc++.h>
using namespace std;

const int N=2e6+10;
const int C=2005;
const int M=30;
int n,q,la,len,l1,l2,sz,ans;
int trie[N][M],Max[N],Min[N],root[N];
char a[N],s[N],s1[N],s2[N];

struct Trie
{
	int sum;
	int ch[M];
};
Trie tr[N];

struct Tdata
{
	int st,ed;
};
Tdata loc[C];

int cmp(Tdata a,Tdata b)
{
    int l=a.st,r=b.st;
    while(l<=a.ed&&r<=b.ed)
    {
        if(s[l]<s[r]) 
			return 1;
        else 
		if(s[l]>s[r]) 
			return 0;
        ++l;++r;
    }
    if(l<=a.ed) 
		return 0;
    else 
	if(r<=b.ed) 
		return 1;
    return 0;
}

void insert(int &now,int l,int r)
{
    tr[++sz]=tr[now];++tr[sz].sum;now=sz;
    if (l>r) 
		return;
    int x=s[r]-'a';
    insert(tr[now].ch[x],l,r-1);
}

int query(int L,int R,int now)
{
    if(now==-1) 
		return tr[R].sum-tr[L].sum;
    int x=s2[now]-'a';
    return query(tr[L].ch[x],tr[R].ch[x],now-1);
}

int main()
{
//	freopen("BZOJ4212.in","r",stdin);
//	freopen("BZOJ4212.out","w",stdout);
	
	scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        scanf("%s",a);la=strlen(a);
        loc[i].st=len;
        for (int j=0;j<la;++j) 
			s[len++]=a[j];
        loc[i].ed=len-1;
    }
    sort(loc+1,loc+n+1,cmp);
    for (int i=1;i<=n;++i)
    {
        int now=0;
        for (int j=loc[i].st;j<=loc[i].ed;++j)
        {
            int x=s[j]-'a';
            if (!trie[now][x]) 
				trie[now][x]=++sz;
            now=trie[now][x];
            if (!Min[now]) 
				Min[now]=i;
            Max[now]=max(Max[now],i);
        }
    }
    
    sz=0;
    for (int i=1;i<=n;++i)
    {
        root[i]=root[i-1];
        insert(root[i],loc[i].st,loc[i].ed);
    }
    
    scanf("%d",&q);
    for (int i=1;i<=q;++i)
    {
        scanf("%s%s",s1,s2);
		l1=strlen(s1);l2=strlen(s2);
        for (int j=0;j<l1;++j) 
			s1[j]=(s1[j]-'a'+ans)%26+'a';
        for (int j=0;j<l2;++j) 
			s2[j]=(s2[j]-'a'+ans)%26+'a';
			
        int now=0,l=-1,r=-1;
        for(int j=0;j<l1;++j)
        {
            int x=s1[j]-'a';
            if (!trie[now][x]) 
				break;
            now=trie[now][x];
            if (j==l1-1) 
				l=Min[now],r=Max[now];
        }
        if(l==-1&&r==-1)
        {
            ans=0;printf("%d\n",ans);
            continue;
        }
        
        ans=query(root[l-1],root[r],l2-1);
        printf("%d\n",ans);
    }
	
	return 0;
}
