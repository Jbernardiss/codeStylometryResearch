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

const int kMod = 1000 * 1000 * 1000 + 7;

inline void add_mod(int &a, int b) {
  a += b;
  if (a >= kMod) { a -= kMod; }
}

int mul_mod(int a, int b) {
  return (ll)a * b % kMod;
}

struct Testcase {
  int tidx_;

  Testcase(int idx) : tidx_{idx} {}

  int N;
  string form;
  vi nxt;
  vi cycle;
  vi saved_path;
  vector<bool> is_cycle;
  vector<bool> is_var_missing;

  struct Node {
    enum class Type {
      AND, OR, VAR, CONST
    };
    Type type;
    int lhs, rhs;
  };
  vector<Node> nodes;

  vector<int> node_idx;

  void FindCycle() {
    vector<bool> visc(N);
    vi path{N - 1};
    do {
      visc[path.back()] = true;
      path.push_back(nxt[path.back()]);
    } while (!visc[path.back()]);
    int fst = 0;
    while (path[fst] != path.back()) { ++fst; }
    cycle = vi(path.begin() + fst, path.end() - 1);
    is_cycle.resize(N);
    for (int x : cycle) { is_cycle[x] = true; }
    saved_path = path;
  }

  void Simulate(int length) {
    nodes.clear();
    nodes.resize(N);
    for (int i = 0; i < N; ++i) {
      if (form[i] == '?') {
        nodes[i].type = Node::Type::VAR;
        nodes[i].lhs = i;
        nodes[i].rhs = -1;
      } else {
        nodes[i].type = Node::Type::CONST;
        nodes[i].lhs = (form[i] == '.' ? 0 : 1);
        nodes[i].rhs = -1;
      }
    }
    node_idx.clear();
    node_idx.resize(N);
    iota(ALL(node_idx), 0);

    for (int iter = 0; iter < length; ++iter) {
      if (nxt[iter] == -1) { continue; }
      const int sz = SZ(nodes);
      const int a = node_idx[iter];
      const int b = node_idx[nxt[iter]];
      if (nodes[a].type == Node::Type::CONST && nodes[b].type == Node::Type::CONST) {
        nodes.push_back(Node{Node::Type::CONST, nodes[a].lhs && nodes[b].lhs, -1});
        nodes.push_back(Node{Node::Type::CONST, nodes[a].lhs || nodes[b].lhs, -1});
      } else {
        nodes.push_back(Node{Node::Type::AND, a, b});
        nodes.push_back(Node{Node::Type::OR, a, b});
      }
      node_idx[iter] = sz;
      node_idx[nxt[iter]] = sz + 1;
    }
  };

  vector<bool> vis;

  void Dbg(int v) {
    switch (nodes[v].type) {
      case Node::Type::CONST:
        cerr << nodes[v].lhs;
        return;
      
      case Node::Type::VAR:
        cerr << "x" << nodes[v].lhs;
        return;

      case Node::Type::AND:
        cerr << "AND(";
        Dbg(nodes[v].lhs);
        cerr << ", ";
        Dbg(nodes[v].rhs);
        cerr << ")";
        return;
      
      case Node::Type::OR:
        cerr << "OR(";
        Dbg(nodes[v].lhs);
        cerr << ", ";
        Dbg(nodes[v].rhs);
        cerr << ")";
        return;
      
      default:
        assert(false);
    }
  }

  vi SolveSim(int v) {
    assert(!vis[v]);
    vis[v] = true;
    switch (nodes[v].type) {
      case Node::Type::CONST:
      {
        vi ans{0, 0};
        ++ans[nodes[v].lhs];
        return ans;
      }

      case Node::Type::VAR:
        is_var_missing[nodes[v].lhs] = false;
        return {1, 1};
      
      case Node::Type::AND:
      {
        const vi lhs = SolveSim(nodes[v].lhs);
        const vi rhs = SolveSim(nodes[v].rhs);
        vi res{0, 0};
        for (int x : {0, 1}) {
          for (int y : {0, 1}) {
            add_mod(res[x & y], mul_mod(lhs[x], rhs[y]));
          }
        }
        return res;
      }

      case Node::Type::OR:
      {
        const vi lhs = SolveSim(nodes[v].lhs);
        const vi rhs = SolveSim(nodes[v].rhs);
        vi res{0, 0};
        for (int x : {0, 1}) {
          for (int y : {0, 1}) {
            add_mod(res[x | y], mul_mod(lhs[x], rhs[y]));
          }
        }
        return res;
      }

      default:
        assert(false);
    }
  }

  // void MarkVars(int v) {
  //   switch (nodes[v].type) {
  //     case Node::Type::VAR:
  //       is_early[nodes[v].lhs] = true;
  //       break;
      
  //     case Node::Type::AND:
  //     case Node::Type::OR:
  //       MarkVars(nodes[v].lhs);
  //       MarkVars(nodes[v].rhs);
  //       break;
        
  //     default:
  //       break;
  //   }
  // }

  int ProcessCycle() {
    for (int i = 0; i < N; ++i) {
      if (form[i] == '?') {
        is_var_missing[i] = true;
      }
    }

    const int sloc = min_element(ALL(cycle)) - cycle.begin();
    const int s = cycle[sloc];
    debug() << imie(s);
    const int t = cycle[(sloc + 1) % SZ(cycle)];
    debug() << imie(t);

    if (!is_cycle[N - 1]) {
      int last_before = -1;
      int first_in = -1;
      for (int i = 0; i < SZ(saved_path); ++i) {
        if (is_cycle[saved_path[i + 1]]) {
          last_before = saved_path[i];
          first_in = saved_path[i + 1];
          break;
        }
      }
      if ((first_in == s || first_in == t) && last_before < s) {
        nxt[first_in] = -1;
        Simulate(N);
        vis.clear();
        vis.resize(SZ(nodes));
        vi this_res = SolveSim(node_idx[N - 1]);
        debug() << "weird case" << imie(this_res);
        int coef = this_res[1];
        const int num_missing = count(ALL(is_var_missing), true);
        debug() << imie(coef) << imie(num_missing);
        for (int i = 0; i < num_missing; ++i) {
          coef = (coef * 2) % kMod;
        }
        return coef;
      }
    }

    // is_early.resize(N);
    Simulate(s);

    vis.clear();
    vis.resize(SZ(nodes));
    // Dbg(node_idx[s]); cerr << "\n";
    vi ress = SolveSim(node_idx[s]);
    // Dbg(node_idx[t]); cerr << "\n";
    vi rest = SolveSim(node_idx[t]);
    debug() << imie(ress);
    debug() << imie(rest);

    for (int i = 0; i < s; ++i) {
      if (nxt[i] != s && nxt[i] != t) { continue; }
      nxt[i] = -1;
    }
    debug() << imie(nxt);

    int ans = 0;

    for (int x : {0, 1}) {
      for (int y : {0, 1}) {
        form[s] = ".C"[x];
        form[t] = ".C"[y];
        Simulate(N);
        vis.clear();
        vis.resize(SZ(nodes));
        // Dbg(node_idx[N - 1]); cerr << "\n";
        vi this_res = SolveSim(node_idx[N - 1]);
        debug() << imie(x) << imie(y) << imie(this_res);
        int coef = mul_mod(this_res[1], mul_mod(ress[x], rest[y]));
        const int num_missing = count(ALL(is_var_missing), true);
        debug() << imie(coef) << imie(num_missing);
        for (int i = 0; i < num_missing; ++i) {
          coef = (coef * 2) % kMod;
        }
        add_mod(ans, coef);
      }
    }

    return ans;

    // is_early.resize(N);
    // MarkVars(node_idx[s]);
    // MarkVars(node_idx[t]);
    // is_early[s] = is_early[t] = false;
    // debug() << imie(is_early);
  }

  int Solve() {
    FindCycle();
    debug() << imie(cycle);
    is_var_missing.resize(N);
    return ProcessCycle();
  }

  void Run() {
    cin >> N >> form;
    nxt.resize(N);
    for (int i = 0; i < N; ++i) {
      cin >> nxt[i];
      --nxt[i];
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
