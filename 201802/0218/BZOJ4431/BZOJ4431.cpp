#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define red(i, a, b) for(int i = (a); i >= (b); i--)
#define ll long long

const int N = 25;
const double eps = 1e-8;
int n, flag = 0, line[N], l[N], vis[N], used[N];
double xs, ys, xt, yt;

struct LINE
{
    double x, y, xx, yy; 
	int tag;
}w[N];

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0):x(x),y(y) { }
}p[N];


Point operator + (Point A, Point B) { return Point(A.x + B.x, A.y + B.y); }
Point operator - (Point A, Point B) { return Point(A.x - B.x, A.y - B.y); }
int dcmp(double x) 
{
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
bool operator == (const Point& A, const Point& B) {
    return dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y) == 0;
}
double dot(Point A, Point B) { return A.x * B.x + A.y * B.y; }
double cross(Point A, Point B) { return A.x * B.y - A.y * B.x; }

Point Get_Inter(Point p, Point v, LINE w) 
{
    double xt, yt;
    if (w.tag) {
        yt = w.y;
        xt = (yt - p.y) * v.x / v.y + p.x;
    }else {
        xt = w.x;
        yt = (xt - p.x) * v.y / v.x + p.y;
    }
    return Point(xt, yt);
}

bool On_Wall(Point p, LINE w) {
    if (w.tag) return (p.x >= w.x && p.x <= w.xx);
    else return (p.y >= w.y && p.y <= w.yy);
}

bool On_Seg(Point p, Point a1, Point a2) { return dcmp(dot(a1 - p, a2 - p)) <= 0; }

void solve(int m) 
{
    memset(used, 0, sizeof(used));
    double X = xt, Y = yt;
    rep(i, 1, m) l[i] = line[i]; l[m + 1] = 0;
    red(i, m, 1) {
        if (w[l[i]].tag) Y = 2 * w[l[i]].y - Y;
        else X = 2 * w[l[i]].x - X;
        p[i] = Point(X, Y);
    }
    p[++m] = Point(xt, yt);
    Point now = Point(0, 0);
    rep(i, 1, m) {
        Point dir = p[i] - now;
        Point rev_p;
        if (i != m) 
		{
            if (w[l[i]].tag == 1 && dcmp(dir.y) == 0) return;
            if (w[l[i]].tag == 0 && dcmp(dir.x) == 0) return;
            rev_p = Get_Inter(now, dir, w[l[i]]);
            if (!On_Seg(rev_p, now, p[i])) return;
            if (!On_Wall(rev_p, w[l[i]])) return;
        }
			else rev_p = p[m];
        rep(j, 1, n) 
		{
            if (used[j] || j == l[i]) continue;
            if (w[j].tag == 1 && dcmp(dir.y) == 0) continue;
            if (w[j].tag == 0 && dcmp(dir.x) == 0) continue;
            Point tmp = Get_Inter(now, dir, w[j]);
            if (!On_Wall(tmp, w[j])) continue;
            if (On_Seg(tmp, now, rev_p)) return; 
        }
        now = rev_p; used[l[i]] = 1;
    }
    flag = 1;
    return;
}
void dfs1(int lim, int dep) 
{
    if (dep > lim) { solve(lim); return; }
    rep(i, 1, n) 
	{
        if (vis[i]) continue;
        line[dep] = i; vis[i] = 1;
        dfs1(lim, dep + 1);
        if (flag) return;
        vis[i] = 0;
    }
}

int main() 
{
	freopen("BZOJ4431.in", "r", stdin);
	freopen("BZOJ4431.out", "w", stdout);
    
    scanf("%d",&n);
    if (n == 0) { printf("0\n"); return 0; }
    xs = ys = 0;
    scanf("%lf%lf",&xt,&yt);
    rep(i, 1, n) 
	{
    	int x,y,xx,yy;
    	scanf("%d%d%d%d",&x,&y,&xx,&yy);

        if (x > xx) swap(x, xx);
        if (y > yy) swap(y, yy);
        w[i].x = (double)x; w[i].y = (double)y;
        w[i].xx = (double)xx; w[i].yy = (double)yy;
        w[i].tag = dcmp(x - xx) != 0;
    }
    red(num, n, 0) 
	{
        memset(vis, 0, sizeof(vis));
        dfs1(num, 1);
        if (flag) { printf("%d\n", num); break; }
    }
    if (!flag) printf("impossible\n");
    return 0;
}
