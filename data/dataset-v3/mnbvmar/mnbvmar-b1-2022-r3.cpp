//~ while (clock()<=69*CLOCKS_PER_SEC)
//~ #pragma comment(linker, "/stack:200000000")
#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
//~ #pragma GCC optimize("Ofast")
//~ #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//~ #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define st first
#define nd second

using namespace __gnu_pbds;
using namespace std;
 
template <typename T>
using ordered_set =
  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
  *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
 
#define shandom_ruffle random_shuffle
 
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using vi=vector<int>;
using vll=vector<ll>;

struct SegTree {
  struct Node {
    int max_val;
    int cnt_max;
    int push_add;

    Node() : max_val{0}, cnt_max{1}, push_add{0} {}
  };

  vector<Node> nodes;
  int base;

  SegTree(int n) : base{1} {
    while (base < n + 2) { base *= 2; }
    nodes.resize(base * 2);
    for (int i = base - 1; i > 0; --i) {
      nodes[i].cnt_max = nodes[i*2].cnt_max + nodes[i*2+1].cnt_max;
    }
  }

  int lq, rq, vq;

  void Push(int v) {
    for (int s : {v * 2, v * 2 + 1}) {
      nodes[s].max_val += nodes[v].push_add;
      nodes[s].push_add += nodes[v].push_add;
    }
    nodes[v].push_add = 0;
  }

  void AddIntvRec(int lb, int rb, int v) {
    if (lb >= rq || rb <= lq) { return; }
    if (lq <= lb && rb <= rq) {
      nodes[v].max_val += vq;
      nodes[v].push_add += vq;
      return;
    }
    Push(v);
    const int mid = (lb + rb) / 2;
    AddIntvRec(lb, mid, v * 2);
    AddIntvRec(mid, rb, v * 2 + 1);
    nodes[v].max_val = max(nodes[v*2].max_val, nodes[v*2+1].max_val);
    nodes[v].cnt_max = 0;
    if (nodes[v].max_val == nodes[v*2].max_val) {
      nodes[v].cnt_max += nodes[v*2].cnt_max;
    }
    if (nodes[v].max_val == nodes[v*2+1].max_val) {
      nodes[v].cnt_max += nodes[v*2+1].cnt_max;
    }
  }

  void AddIntv(int L, int R, int val) {
    debug() << imie(L) << imie(R) << imie(val);
    lq = L; rq = R; vq = val;
    AddIntvRec(0, base, 1);
  }

  pii GetMaxRec(int lb, int rb, int v) {
    if (lb >= rq || rb <= lq) { return pii{-1e9, 0}; }
    if (lq <= lb && rb <= rq) { return pii{nodes[v].max_val, nodes[v].cnt_max}; }
    Push(v);
    const int mid = (lb + rb) / 2;
    pii lhs = GetMaxRec(lb, mid, v * 2);
    pii rhs = GetMaxRec(mid, rb, v * 2 + 1);
    int mx = max(lhs.st, rhs.st);
    int cnt = 0;
    if (mx == lhs.st) { cnt += lhs.nd; }
    if (mx == rhs.st) { cnt += rhs.nd; }
    return pii{mx, cnt};
  }

  pii GetMaxIntv(int L, int R) {
    lq = L; rq = R;
    pii ans = GetMaxRec(0, base, 1);
    debug() << "get" << imie(L) << imie(R) << imie(ans);
    return ans;
  }
};

struct Testcase {
  int tidx_;

  Testcase(int idx) : tidx_{idx} {}

  int N, C;
  vector<vi> color_locs;
  vi mincol, maxcol;

  void Run() {
    cin >> N >> C;
    color_locs.resize(C + 1);
    mincol.resize(C + 1);
    maxcol.resize(C + 1);
    for (int i = 1; i <= C; ++i) {
      cin >> mincol[i] >> maxcol[i];
      if (mincol[i] == 0) { mincol[i] = 1; }
      if (maxcol[i] == 0) { maxcol[i] = mincol[i] = N + 1; }
    }
    vi order;
    for (int i = 0; i < N; ++i) {
      int v;
      cin >> v;
      order.push_back(v);
      color_locs[v].push_back(i);
    }
    for (int i = 0; i < N; ++i) {
      color_locs[order[i]].push_back(i + N);
    }


    struct Event {
      int y1, y2;
      bool is_add;
    };
    vector<vector<Event>> events(2 * N + 1);

    auto AddRect = [&](int x1, int x2, int y1, int y2) {
      debug() << imie(x1) << imie(x2) << imie(y1) << imie(y2);
      events[x1].push_back(Event{y1, y2, true});
      events[x2].push_back(Event{y1, y2, false});
    };



    for (int color = 1; color <= C; ++color) {
      debug() << imie(color);
      vi locs = color_locs[color];
      locs.insert(locs.begin(), -1);
      locs.push_back(2 * N);
      // empty
      for (int i = 0; i + 1 < SZ(locs); ++i) {
        const int L = locs[i];
        const int R = locs[i + 1];
        if (R - L >= 2) {
          AddRect(L + 1, R, L + 1, R);
        }
      }
      // with some
      for (int rhs_last = 1; rhs_last < SZ(locs) - 1; ++rhs_last) {
        const int Rmin = locs[rhs_last];
        const int Rmax = locs[rhs_last + 1];
        const int Lmin = locs[max(0, rhs_last - maxcol[color])] + 1;
        const int Lmax = locs[max(0, rhs_last - mincol[color] + 1)] + 1;
        if (Lmin == Lmax) { continue; }
        AddRect(Lmin, Lmax, Rmin, Rmax);
      }
    }

    SegTree st(2 * N + 5);

    ll ans = 0;
    for (int x = 0; x < N; ++x) {
      for (auto &ev : events[x]) {
        st.AddIntv(ev.y1, ev.y2, ev.is_add ? 1 : -1);
      }
      const pii res = st.GetMaxIntv(x + 1, x + N - 1);
      debug() << imie(x) << imie(res);
      if (res.st == C) {
        ans += res.nd;
      }
    }

    cout << "Case #" << tidx_ << ": " << ans << "\n";
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(11);
  cerr << fixed << setprecision(6);

  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    Testcase{i}.Run();
  }
}
