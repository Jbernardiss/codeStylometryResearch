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

const string alphabet = "ACDEHIJKMORST";

struct Testcase {
  int tidx_;

  Testcase(int idx) : tidx_{idx} {}

  int N;
  vector<vi> adj;
  vi Li, Ri;


  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  string Solve() {
    const int K = 12;
    vector<int> deg_list(N + 1);
    queue<int> small_q;
    vector<int> coloring_order;
    for (int i = 1; i <= N; ++i) {
      deg_list[i] = SZ(adj[i]);
      if (deg_list[i] <= K) {
        small_q.push(i);
      }
    }

    while (!small_q.empty()) {
      const int v = small_q.front();
      small_q.pop();
      coloring_order.push_back(v);
      for (int s : adj[v]) {
        if (--deg_list[s] == K) {
          small_q.push(s);
        }
      }
    }

    vi colors(N + 1, -1);
    reverse(ALL(coloring_order));
    for (int x : coloring_order) {
      vector<bool> allowed(K + 1, true);
      debug() << imie(x) << imie(adj[x]);
      for (int s : adj[x]) {
        if (colors[s] != -1) {
          allowed[colors[s]] = false;
        }
      }
      int c = 0;
      while (!allowed[c]) { ++c; }
      colors[x] = c;
    }

    string ans;
    for (int i = 1; i <= N; ++i) {
      ans += alphabet[colors[i]];
    }
    return ans;
  }

  void Run() {
    cin >> N;
    adj.resize(N + 1);
    Li.resize(N + 1);
    Ri.resize(N + 1);
    for (int i = 1; i <= N; ++i) {
      cin >> Li[i];
    }
    for (int i = 1; i <= N; ++i) {
      cin >> Ri[i];
    }

    bool ok = true;
    for (int i = 1; i <= N; ++i) {
      set<int> S;
      for (int x : {Li[i], Ri[i]}) {
        for (int y : {x, Li[x], Ri[x]}) {
          if (y == i) { ok = false; }
          S.insert(y);
        }
      }
      for (int y : S) {
        AddEdge(i, y);
      }
    }

    string ans;
    if (!ok) {
      ans = "IMPOSSIBLE";
    } else {
      ans = Solve();
    }

    cout << "Case #" << tidx_ << ": " << ans << "\n";;
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
