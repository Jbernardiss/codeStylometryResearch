#include <bits/stdc++.h>
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rep1(i,n) for(int i = 1; i <= (n); ++i)
#define drep(i,n) for(int i = (n)-1; i >= 0; --i)
#define srep(i,s,t) for (int i = s; i < (t); ++i)
#define rng(a) a.begin(),a.end()
#define rrng(a) a.rbegin(),a.rend()
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define pob pop_back
#define sz(x) (int)(x).size()
#define pcnt __builtin_popcountll
#define snuke srand((unsigned)clock()+(unsigned)time(NULL));
#define newline puts("")
using namespace std;
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
template<typename T> using PQ = priority_queue<T,vc<T>,greater<T>>;
using uint = unsigned; using ull = unsigned long long;
using vi = vc<int>; using vvi = vv<int>; using vvvi = vv<vi>;
using ll = long long; using vl = vc<ll>; using vvl = vv<ll>; using vvvl = vv<vl>;
using P = pair<int,int>; using vp = vc<P>; using vvp = vv<P>;
int getInt(){int x;scanf("%d",&x);return x;}
vi pm(int n, int s=0) { vi a(n); iota(rng(a),s); return a;}
template<typename T>istream& operator>>(istream&i,vc<T>&v){rep(j,sz(v))i>>v[j];return i;}
template<typename T>string join(const T&v,const string& d=""){stringstream s;rep(i,sz(v))(i?s<<d:s)<<v[i];return s.str();}
template<typename T>ostream& operator<<(ostream&o,const vc<T>&v){if(sz(v))o<<join(v," ");return o;}
template<typename T1,typename T2>istream& operator>>(istream&i,pair<T1,T2>&v){return i>>v.fi>>v.se;}
template<typename T1,typename T2>ostream& operator<<(ostream&o,const pair<T1,T2>&v){return o<<v.fi<<","<<v.se;}
template<typename T1,typename T2>bool mins(T1& x,const T2&y){if(x>y){x=y;return true;}else return false;}
template<typename T1,typename T2>bool maxs(T1& x,const T2&y){if(x<y){x=y;return true;}else return false;}
template<typename Tx, typename Ty>Tx dup(Tx x, Ty y){return (x+y-1)/y;}
template<typename T>ll suma(const vc<T>&a){ll res(0);for(auto&&x:a)res+=x;return res;}
template<typename T>ll suma(const vv<T>&a){ll res(0);for(auto&&x:a)res+=suma(x);return res;}
template<typename T>void uni(T& a){sort(rng(a));a.erase(unique(rng(a)),a.end());}
template<typename T>void prepend(vc<T>&a,const T&x){a.insert(a.begin(),x);}
const double eps = 1e-10;
const ll LINF = 1001002003004005006ll;
const int INF = 1001001001;
#define dame { puts("IMPOSSIBLE"); return;}
#define yes { puts("Yes"); return;}
#define no { puts("No"); return;}
#define ret(x) { cout<<(x)<<endl; return;}
#define yn {puts("Yes");}else{puts("No");}
const int MX = 200005;

vvi ing(int n, int m=-1, bool bi=true) {
  if (m == -1) m = n-1;
  vvi to(n);
  rep(i,m) {
    int a, b;
    scanf("%d%d",&a,&b);
    --a; --b;
    to[a].pb(b);
    if (bi) to[b].pb(a);
  }
  return to;
}

// Max flow
// !! Be care of double and INF !!
struct Maxflow {
  using TT = int;
  int n;
  vi to, next, head, dist, it;
  vector<TT> lim;
  Maxflow(){}
  Maxflow(int n):n(n),head(n,-1),it(n){}
  void add(int a, int b, TT c=1) {
    next.pb(head[a]); head[a] = sz(to); to.pb(b); lim.pb(c);
    next.pb(head[b]); head[b] = sz(to); to.pb(a); lim.pb(0); 
  }
  void bfs(int sv) {
    dist = vi(n,INF);
    queue<int> q;
    dist[sv] = 0; q.push(sv);
    while (!q.empty()){
      int v = q.front(); q.pop();
      for (int i = head[v]; i != -1; i = next[i]) {
        if (lim[i] && dist[to[i]] == INF) { // double !!
          dist[to[i]] = dist[v]+1; q.push(to[i]);
        }
      }
    }
  }
  TT dfs(int v, int tv, TT nf=INF) { // INF !!
    if (v == tv) return nf;
    for (; it[v] != -1; it[v] = next[it[v]]) {
      int u = to[it[v]]; TT f;
      if (!lim[it[v]] || dist[v] >= dist[u]) continue; // double !!
      if (f = dfs(u, tv, min(nf, lim[it[v]])), f) { // double !!
        lim[it[v]] -= f;
        lim[it[v]^1] += f;
        return f;
      }
    }
    return 0;
  }
  TT solve(int sv, int tv) {
    TT flow = 0, f;
    while (1) {
      bfs(sv);
      if (dist[tv] == INF) return flow;
      rep(i,n) it[i] = head[i];
      while (f = dfs(sv,tv), f) flow += f;
    }
  }
};
//

struct Solver {
  void solve() {
    int n,m;
    scanf("%d%d",&n,&m);
    vvi to = ing(n,m,false);
    int sv = n*2, tv = sv+1;
    Maxflow g(tv+1);

    vi in(n), out(n);
    rep(i,n) {
      for (int j : to[i]) {
        out[i]++;
        in[j]++;
        g.add(i,n+j,INF);
      }
    }
    int tot = 0;
    rep(i,n) {
      g.add(sv,i,m-out[i]);
      g.add(n+i,tv,m-in[i]);
      tot += m-out[i];
    }
    if (g.solve(sv,tv) != tot) dame;
    vvi d(n,vi(n));
    {
      int ei = 1;
      rep(i,n) {
        for (int j : to[i]) {
          d[i][j] = 1+g.lim[ei];
          ei += 2;
        }
      }
    }

    vi ans;
    auto dfs = [&](auto f, int v) -> void {
      rep(u,n) {
        while (d[v][u]) {
          d[v][u]--;
          f(f,u);
        }
      }
      ans.pb(v+1);
    };
    dfs(dfs,0);
    if (sz(ans) != m*n+1) dame;
    reverse(rng(ans));
    cout<<sz(ans)<<endl;
    cout<<ans<<endl;
  }
};

int main() {
  int ts;
  cin>>ts;
  rep1(ti,ts) {
    Solver solver;
    printf("Case #%d: ",ti);
    solver.solve();
  }
  return 0;
}
