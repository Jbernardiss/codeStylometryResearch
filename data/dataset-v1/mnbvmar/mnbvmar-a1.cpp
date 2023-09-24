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

struct Testcase {
  int tidx_;

  Testcase(int idx) : tidx_{idx} {}

  vector<vi> adj;
  int N, M;
  int alice, queen;
  vector<bool> is_path;
  vector<bool> vis;
  vector<bool> is_on_cycle;

  const string kSafe = "SAFE";


  int last_depth;
  int root;

  bool DfsStrat(int v, int d) {
    vis[v] = true;
    last_depth = max(last_depth, d);
    if (is_on_cycle[v]) { return true; }
    for (int s : adj[v]) {
      if (vis[s]) { continue; }
      if (DfsStrat(s, d + 1)) { return true; }
    }
    return false;
  }

  // int cnt_up = 0;
  // vi cnts_down;

  vi vislow;
  vi low;
  vi pre;
  int tm;

  void DfsCycle(int v, int p) {
    pre[v] = tm++;
    vislow[v] = 1;
    for (int s : adj[v]) {
      if (vislow[s] == 0) {
        DfsCycle(s, v);
        low[v] = min(low[v], low[s]);
      }
      if (vislow[s] == 1 && s != p) {
        low[v] = min(low[v], pre[s]);
        debug() << imie(v) << imie(s);
      }
    }
    debug() << imie(v) << imie(low[v]) << imie(pre[v]);
    is_on_cycle[v] = (low[v] <= pre[v]);
    vislow[v] = 2;
  }

  void MakeCycle() {
    is_on_cycle.resize(N + 1);
    // cnts_down.resize(N + 1);
    vislow.resize(N + 1);
    low.resize(N + 1, 1e9);
    pre.resize(N + 1);
    tm = 0;
    DfsCycle(alice, -1);
    fill(ALL(vis), false);
  }

  string Solve() {
    vi dist(N + 1, 1e9);
    vi prv(N + 1, -1);
    dist[alice] = 0;
    queue<int> Q;
    Q.push(alice);

    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      for (int s : adj[v]) {
        if (dist[s] > dist[v] + 1) {
          dist[s] = dist[v] + 1;
          prv[s] = v;
          Q.push(s);
        }
      }
    }

    if (dist[queen] > N) {
      return kSafe;
    }

    vis.resize(N + 1);
    MakeCycle();
    is_path.resize(N + 1);
    vector<int> aq_path;
    aq_path.push_back(queen);
    vis[queen] = true;
    while (aq_path.back() != alice) {
      aq_path.push_back(prv[aq_path.back()]);
      vis[aq_path.back()] = is_path[aq_path.back()] = true;
    }
    reverse(ALL(aq_path));
    debug() << imie(aq_path);
    debug() << imie(is_on_cycle);

    int lptr = 0, rptr = SZ(aq_path) - 1;
    int ans = SZ(aq_path) - 1, cur_pref = 0;
    while (lptr < rptr) {
      last_depth = 0;
      if (DfsStrat(aq_path[lptr], 0)) {
        return kSafe;
      }
      debug() << imie(last_depth) << imie(lptr);
      ans = max(ans, 2 * (SZ(aq_path) - lptr - 1) + 2 * last_depth);
      ++cur_pref;
      ++lptr;
      --rptr;
    }
    return to_string(ans);
  }

  void Run() {
    cin >> N >> M >> alice >> queen;
    adj.resize(N + 1);
    for (int i = 0; i < M; ++i) {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    cout << "Case #" << tidx_ << ": " << Solve() << "\n";
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
