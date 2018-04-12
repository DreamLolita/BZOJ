// Author: Luka Kalinovcic
#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

using namespace std;

#define MAX 300000

int n;
struct Buffalo {
  int x, y;
} b[MAX];

int m;
struct Settler {
  int x, y;
  int x_fence = 0;
  int y_fence = 0;
  int buffalos_start = 0;
  int buffalos_end = 0;
  int parent_end = -1;
} s[MAX];

struct Group {
  Group* parent = nullptr;
  int rank = 0;
  int buffalos = 0;
} group[MAX];

void Input() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &b[i].x, &b[i].y);
  }
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &s[i].x, &s[i].y);
  }
}

struct Vertical {
  int x, index;
};
bool operator<(const Vertical& a, const Vertical& b) {
  return a.x != b.x ? a.x < b.x : a.index < b.index;
}
struct Event {
  int y, index;
  enum Type { FENCE_POST = 1, BUFFALO = 2 } type;
};
bool operator<(const Event &a, const Event& b) {
  return a.y != b.y ? a.y > b.y : a.type < b.type;
}

void Sweep() {
  set<Vertical> active;
  vector<Event> events;
  events.reserve(n + m);
  for (int i = 0; i < n; ++i) {
    events.push_back(Event{b[i].y, i, Event::BUFFALO});
  }
  for (int i = 0; i < m; ++i) {
    events.push_back(Event{s[i].y, i, Event::FENCE_POST});
  }
  sort(events.begin(), events.end());
  for (const Event& e : events) {
    if (e.type == Event::FENCE_POST) {
      const auto it = active.insert(Vertical{s[e.index].x, e.index}).first;
      auto next = it;
      if (++next != active.end()) {
        s[e.index].parent_end = next->index;
      }
      
      auto curr = it;
      auto prev = curr;
      while (prev != active.begin()) {
        --prev;
        if (prev->index < e.index) break;
        s[prev->index].y_fence = e.y;
        curr = prev;
      }
      if (prev != curr) {
        s[e.index].x_fence = prev->x; 
      }
      active.erase(curr, it);
    } else {
      const auto it = active.lower_bound(Vertical{b[e.index].x, -1});
      if (it != active.end()) {
        ++s[it->index].buffalos_end;
      }
    }
  }
}

Group* Find(Group* a) {
  if (a->parent == nullptr) return a;
  return a->parent = Find(a->parent);
}

Group* Union(Group* a, Group* b) {
  if (a->rank < b->rank) swap(a, b);
  if (a->rank == b->rank) ++a->rank;
  b->parent = a;
  a->buffalos += b->buffalos;
  return a;
}

int main() {
     freopen("c.in", "r", stdin);
     freopen("cac.out", "w", stdout);
     
  Input();
  Sweep();
  for (int i = m - 1; i >= 0; --i) {
    Group* g = Find(&group[i]);
    g->buffalos += s[i].buffalos_end;
    s[i].buffalos_start = g->buffalos;
    if (s[i].parent_end != -1) {
      Group* p = Find(&group[s[i].parent_end]);
      Union(g, p);
    }
  }
  for (int i = 0; i < m; ++i) {
    printf("%d\n", s[i].buffalos_start);
  }
  return 0;
}
