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
using VI=vector<int>;
#define PB push_back

#define FOR(i,a,b) for(int i = (a); i <= (b); i++)
#define RE(i,n) FOR(i,1,n)

// acm-library-u warsaw Euler
struct Euler {
  struct Edge { int nei, nr; };
  vector<vector<Edge>> slo;
  VI ans, used, deg, beg;
  int e_num, n;
  Euler() : e_num(0), n(0) {}
  void AddEdge(int a, int b) {
    debug() << imie(a) << imie(b);
    e_num++;
    if (a > n || b > n) {
      n = max(a, b);
      slo.resize(n + 2);
      deg.resize(n + 2);
      beg.resize(n + 2);
    }
    used.PB(0);
    slo[a].PB({b, e_num});
    deg[a]++; deg[b]++;
  }
  VI FindEuler() { // if used many times, please clear ans, beg, used
    used.PB(0);
    assert(SZ(used) > e_num);
    RE (i, n) { if (deg[i] % 2 == 1) { return VI(); } }
    Go(1);
    reverse(ALL(ans));
    return ans;
  }
private:
  void Go(int v) {
    // debug() << imie(v);
    while (beg[v] < SZ(slo[v])) {
      Edge& e = slo[v][beg[v]];
      beg[v]++;
      int nei = e.nei;
      if (used[e.nr]) { continue; }
      used[e.nr] = 1;
      Go(nei);
      ans.PB(nei);
    }
  }
};

struct Matching {
  vector<vi> adj;
  int n;

  vi match_to;
  vector<bool> vis;
  Matching(int N) : adj(2 * N), n(2 * N), match_to(2 * N, -1) {}

  bool DfsMatch(int v) {
    if (vis[v]) { return false; }
    vis[v] = true;
    for (int s : adj[v]) {
      if (match_to[s] == -1 || DfsMatch(match_to[s])) {
        match_to[v] = s;
        match_to[s] = v;
        return true;
      }
    }
    return false;
  }

  int Match() {
    vis.resize(n);
    for (int i = 0; i < n; ++i) {
      random_shuffle(ALL(adj[i]));
    }
    bool any_impr;
    int ans = 0;
    do {
      fill(ALL(vis), false);
      any_impr = false;
      for (int i = 0; i < n / 2; ++i) {
        if (!vis[i] && match_to[i] == -1 && DfsMatch(i)) {
          any_impr = true;
          ++ans;
        }
      }
    } while (any_impr);
    return ans;
  }

  bool TryHaveEdge(int u, int v) {
    assert(u < n / 2);
    assert(v >= n / 2);
    assert(match_to[u] != -1);
    assert(match_to[v] != -1);
    if (match_to[u] == v) {
      return true;
    }
    const int au = match_to[u];
    const int av = match_to[v];
    match_to[u] = v;
    match_to[v] = u;
    match_to[au] = match_to[av] = -1;
    fill(ALL(vis), false);
    vis[u] = vis[v] = true;

    if (!DfsMatch(av)) {
      match_to[u] = au; match_to[v] = av;
      match_to[au] = u; match_to[av] = v;
      return false;
    } else {
      return true;
    }
  }
};

struct Testcase {
  int tidx_;

  Testcase(int idx) : tidx_{idx} {}

  int N, M;
  vector<pii> edges;

  string kImpossible = "IMPOSSIBLE";

  string Solve() {
    Matching matching(N);
    for (auto &[u, v] : edges) {
      cin >> u >> v;
      --u; --v;
      matching.adj[u].push_back(v + N);
      matching.adj[v + N].push_back(u);
    }
    if (matching.Match() != N) {
      return kImpossible;
    }
    Euler euler;

    for (auto [u, v] : edges) {
      if (!matching.TryHaveEdge(u, v + N)) {
        return kImpossible;
      }
      debug() << imie(u) << imie(v) << imie(matching.match_to);
      for (int i = 0; i < N; ++i) {
        assert(matching.match_to[i] >= N);
        euler.AddEdge(i + 1, matching.match_to[i] - N + 1);
      }
    }

    auto walk = euler.FindEuler();
    assert(!walk.empty());
    walk.insert(walk.begin(), walk.back());

    vector<int> num_vis(N + 1);
    for (int x : walk) {
      ++num_vis[x];
    }
    for (int i = 1; i <= N; ++i) {
      if (!num_vis[i]) {
        return kImpossible;
      }
    }
    for (int i = 2; i < N; ++i) {
      assert(num_vis[i] == num_vis[i + 1]);
    }
    assert(num_vis[1] == num_vis[2] + 1);

    stringstream ss;
    ss << SZ(walk) << "\n";
    for (int v : walk) {
      ss << v << " ";
    }
    return ss.str();
  }

  void Run() {
    cin >> N >> M;
    edges.resize(M);
    

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
