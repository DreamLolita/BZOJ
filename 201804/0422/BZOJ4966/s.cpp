#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#define N 500010
#define M 1000010
using namespace std;

int n, m, cur = 0, person, org[N];

struct Tnode{
    int val, cnt;
    Tnode() {}
    Tnode(int _val, int _cnt):val(_val), cnt(_cnt) {}
}tree[N<<2];

struct Treap{
    Treap *lson, *rson;
    int val, fix, size;
    int lsize(){return lson ? lson->size : 0;}
    int rsize(){return rson ? rson->size : 0;}
    void Recount(){size = lsize() + rsize() + 1;}
}*Root[N], Node[M+N];

void Up(int root, int Lson, int Rson){

    if(tree[Lson].val == tree[Rson].val)
      tree[root] = Tnode(tree[Lson].val, tree[Lson].cnt + tree[Rson].cnt);
    else if(tree[Lson].cnt > tree[Rson].cnt)
      tree[root] = Tnode(tree[Lson].val, tree[Lson].cnt - tree[Rson].cnt);
    else
      tree[root] = Tnode(tree[Rson].val, tree[Rson].cnt - tree[Lson].cnt);
}

void build(int root, int L, int R){
    if(L == R){
      tree[root] = Tnode(org[L], 1);
      return; 
    }
    int mid = (L + R) >> 1, Lson = root << 1, Rson = root << 1 | 1;
    build(Lson, L, mid);
    build(Rson, mid+1, R);

    Up(root, Lson, Rson);
}

void update(int root, int L, int R, int x, int y, int v){
    if(x > R || y < L)  return;
    if(x <= L && y >= R){
      tree[root] = Tnode(v, 1);
      return;
    }
    int mid = (L + R) >> 1, Lson = root << 1, Rson = root << 1 | 1;
    update(Lson, L, mid, x, y, v);
    update(Rson, mid+1, R, x, y, v);

    Up(root, Lson, Rson);
}

Tnode query(int root, int L, int R, int x, int y){
    if(x > R || y < L)  return Tnode(0, 0);
    if(x <= L && y >= R)  return tree[root];

    int mid = (L + R) >> 1, Lson = root << 1, Rson = root << 1 | 1;
    Tnode ans1 = query(Lson, L, mid, x, y);
    Tnode ans2 = query(Rson, mid+1, R, x, y);

    if(ans1.val == ans2.val)  return Tnode(ans1.val, ans1.cnt + ans2.cnt);
    else if(ans1.cnt > ans2.cnt)  return Tnode(ans1.val, ans1.cnt - ans2.cnt);
    else  return Tnode(ans2.val, ans2.cnt - ans1.cnt);
}

Treap *NewTnode(){
    Node[cur].lson = Node[cur].rson = NULL;
    return Node+cur++;
}

void Treap_L_Rot(Treap *&a){
    Treap *b = a->rson;
    a->rson = b->lson;
    b->lson = a;
    a = b;
    a->lson->Recount();
    a->Recount();
}

void Treap_R_Rot(Treap *&a){
    Treap *b = a->lson;
    a->lson = b->rson;
    b->rson = a;
    a = b;
    a->rson->Recount();
    a->Recount();
}

void Treap_Insert(Treap *&p, int val){
    if(!p){
      p = NewTnode();
      p->val = val;
      p->fix = rand();
      p->size = 1;
    }
    else if(val <= p->val){
      p->size ++;
      Treap_Insert(p->lson, val);
      if(p->lson->fix < p->fix)  Treap_R_Rot(p);
    }
    else{
      p->size ++;
      Treap_Insert(p->rson, val);
      if(p->rson->fix < p->fix)  Treap_L_Rot(p);
    }
}

void Treap_Del(Treap *&p, int val){
    if(p->val == val){
      if(!(p->lson && p->rson)){
        if(p->lson)  p = p->lson;
        else  p = p->rson;
      }
      else if(p->lson->fix < p->rson->fix){
        Treap_R_Rot(p);
        Treap_Del(p->rson, val);
        p->size --;
      }
      else{
        Treap_L_Rot(p);
        Treap_Del(p->lson, val);
        p->size --;
      }
    }
    else if(val < p->val)  Treap_Del(p->lson, val), p->size --;
    else  Treap_Del(p->rson, val), p->size --;
}

int Get(Treap *p, int x){
    if(!p)  return 0;
    if(p->val <= x)  return p->lsize() + 1 + Get(p->rson, x);
    else  return Get(p->lson, x);
}

int main(){

    scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; i++)  scanf("%d", &org[i]);
    build(1, 1, n);

    for(int i = 1; i <= n; i++)  Root[i] = NULL;
    for(int i = 1; i <= n; i++)  Treap_Insert(Root[org[i]], i);

    int l, r, s, k, a;
    for(int i = 1; i <= m; i++){
      scanf("%d%d%d%d", &l, &r, &s, &k);
      person = query(1, 1, n, l, r).val;
      if(Get(Root[person], r) - Get(Root[person], l-1) <= (r - l + 1) / 2)  person = s;

      printf("%d\n", person);

      for(int j = 1; j <= k; j++){
        scanf("%d", &a);
        update(1, 1, n, a, a, person);
        Treap_Del(Root[org[a]], a);
        Treap_Insert(Root[org[a] = person], a);
      }
    } 

    person = query(1, 1, n, 1, n).val;
    if(Get(Root[person], r) - Get(Root[person], l-1) <= n / 2)  person = -1;

    printf("%d\n", person);

    return 0;
}
