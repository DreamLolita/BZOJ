#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cctype>
#define N 1020
#pragma GCC optimize("O3")
using namespace std;

class Node
{
public:
    Node *s[2];
    char v;
    int z;
    bool f;

    Node(int _v = 0) : v(_v), z(1), f(false)
    {
        s[0] = s[1] = NULL;

        return;
    }

    int Size(int k)
    {
        return s[k] ? s[k] -> z : 0;
    }

    int Left(void)
    {
        return Size(0) + 1;
    }

    void Update(void)
    {
        z = Size(0) + Size(1) + 1;
        if(f)
        {
            f = false;
            if(s[0])
                s[0] -> f ^= 1;
            if(s[1])
                s[1] -> f ^= 1;
            swap(s[0], s[1]);
        }

        return;
    }
};

class Splay
{
public:
    Node *r;

    void InitSplay(Node *&x, char *a, int l, int r)
    {
        int m;

        if(l > r)
            return;
        m = (l + r) >> 1;
        x = new Node(a[m]);

        InitSplay(x -> s[0], a, l, m - 1);
        InitSplay(x -> s[1], a, m + 1, r);
        x -> Update();

        return;
    }

    void RotateSplay(Node *&x, int k)
    {
        Node *t;

        t = x -> s[!k];
        x -> s[!k] = t -> s[k];
        t -> s[k] = x;

        x -> Update();
        t -> Update();
        x = t;

        return;
    }

    void SplaySplay(Node *&x, int k)
    {
        x -> Update();
        if(k < x -> Left())
        {
            x -> s[0] -> Update();
            if(k < x -> s[0] -> Left())
            {
                SplaySplay(x -> s[0] -> s[0], k);
                RotateSplay(x, 1);
            }
            else if(k > x -> s[0] -> Left())
            {
                k -= x -> s[0] -> Left();
                SplaySplay(x -> s[0] -> s[1], k);
                RotateSplay(x -> s[0], 0);
            }
            RotateSplay(x, 1);
        }
        else if(k > x -> Left())
        {
            k -= x -> Left();
            x -> s[1] -> Update();
            if(k < x -> s[1] -> Left())
            {
                SplaySplay(x -> s[1] -> s[0], k);
                RotateSplay(x -> s[1], 1);
            }
            else if(k > x -> s[1] -> Left())
            {
                k -= x -> s[1] -> Left();
                SplaySplay(x -> s[1] -> s[1], k);
                RotateSplay(x, 0);
            }
            RotateSplay(x, 0);
        }

        return;
    }

    void OutputSplay(Node *&x)
    {
        if(!x)
            return;

        x -> Update();
        OutputSplay(x -> s[0]);
        if(x -> v)
            putchar(x -> v);
        OutputSplay(x -> s[1]);

        return;
    }
};

int n;
char a[N][N], b[N][N];
Splay x[N], y[N];
Node *p[N], *q[N];

inline void Convert(int &x, int &y)
{
    int t;

    t = x;
    x = n - y + 1;
    y = t;
    
    return;
}

void Rotate(int u, int v, int z)
{
    int a, b, i;

    /*Node *a, *b, *c, *d;
    int p, q;

    x[u].SplaySplay(x[u].r, v);
    x[u].SplaySplay(x[u].r -> s[1], v + z + 1 - x[u].r -> Left());
    a = x[u].r -> s[1] -> s[0];
    x[u].r -> s[1] -> s[0] = NULL;
    x[u].r -> s[1] -> Update();
    x[u].r -> Update();

    x[u + z].SplaySplay(x[u + z].r, v + 1);
    x[u + z].SplaySplay(x[u + z].r -> s[1], v + z + 2 - x[u + z].r -> Left());
    c = x[u + z].r -> s[1] -> s[0];
    x[u + z].r -> s[1] -> s[0] = NULL;
    x[u + z].r -> s[1] -> Update();
    x[u + z].r -> Update();

    //cerr<<u+z<<' '<<v<<endl;
    Convert(p = u + z, q = v);
    //cerr<<p<<' '<<q<<endl;
    y[p].SplaySplay(y[p].r, q);
    y[p].SplaySplay(y[p].r -> s[1], q + z + 1 - y[p].r -> Left());
    b = y[p].r -> s[1] -> s[0];
    y[p].r -> s[1] -> s[0] = NULL;
    y[p].r -> s[1] -> Update();
    y[p].r -> Update();*/

    Convert(a = u, b = v + z - 1);
    for(i = 1;i <= z;i ++)
    {
        x[u + i - 1].SplaySplay(x[u + i - 1].r, v);
        x[u + i - 1].SplaySplay(x[u + i - 1].r -> s[1], v + z + 1 - x[u + i - 1].r -> Left());
        p[i] = x[u + i - 1].r -> s[1] -> s[0];
        x[u + i - 1].r -> s[1] -> s[0] = NULL;
        x[u + i - 1].r -> s[1] -> Update();
        x[u + i - 1].r -> Update();

        y[a + i - 1].SplaySplay(y[a + i - 1].r, b);
        y[a + i - 1].SplaySplay(y[a + i - 1].r -> s[1], b + z + 1 - y[a + i - 1].r -> Left());
        q[i] = y[a + i - 1].r -> s[1] -> s[0];
        y[a + i - 1].r -> s[1] -> s[0] = NULL;
        y[a + i - 1].r -> s[1] -> Update();
        y[a + i - 1].r -> Update();
    }

    for(i = 1;i <= z;i ++)
    {
        x[u + i - 1].r -> s[1] -> s[0] = q[i];
        x[u + i - 1].r -> s[1] -> Update();
        x[u + i - 1].r -> Update();

        p[z - i + 1] -> f ^= 1;
        y[a + i - 1].r -> s[1] -> s[0] = p[z - i + 1];
        y[a + i - 1].r -> s[1] -> Update();
        y[a + i - 1].r -> Update();
    }

    return;
}

int main(void) //rotate.cpp
{
    int m, x, y, z;
    int i, j;

    freopen("rotate.in" , "r", stdin );
    freopen("rotate.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for(i = 1;i <= n;i ++)
        for(j = 1;j <= n;j ++)
            while(!islower(a[i][j] = getchar()))
                ;
    for(i = 1;i <= n;i ++)
    {
        for(j = 1;j <= n;j ++)
            b[n - j + 1][i] = a[i][j];
        ::x[i].InitSplay(::x[i].r, a[i], 0, n + 1);
    }

    /*for(i=1;i<=n;i++)
        cerr<<(b[i]+1)<<endl;*/
    for(i = 1;i <= n;i ++)
        ::y[i].InitSplay(::y[i].r, b[i], 0, n + 1);

    while(m --)
    {
        cin >> x >> y >> z;
        /*if(z > 1)
            for(i = 0, j = z - 1;j > 0;i ++, j -= 2)
                Rotate(x + i, y + i, j);*/
        if(z > 1)
            Rotate(x, y, z);
    }

    //::x[1].r->f=true;
    for(i = 1;i <= n;i ++)
    {
        ::x[i].OutputSplay(::x[i].r);
        putchar('\n');
    }

    return 0;
}
