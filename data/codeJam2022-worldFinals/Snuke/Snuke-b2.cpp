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
#define dame { puts("-1"); return;}
#define yes { puts("Yes"); return;}
#define no { puts("No"); return;}
#define ret(x) { cout<<(x)<<endl; return;}
#define yn {puts("Yes");}else{puts("No");}
const int MX = 200005;

// SCC
// upstream is smaller id
struct scc {
  int n, k;
  vvi to, ot, d, gt; // to, rev_to, groups, group_to
  vi g, used, kv; // group, gomi, topo_ord
  scc(int n=0):n(n),to(n),ot(n){}
  int inc() { to.pb(vi()); ot.pb(vi()); return n++;}
  void add(int a, int b) { to[a].pb(b); ot[b].pb(a);}
  void dfs(int v) {
    if (used[v]) return;
    used[v] = 1;
    rep(i,sz(to[v])) dfs(to[v][i]);
    kv[--k] = v;
  }
  void rfs(int v) {
    if (g[v] != -1) return;
    g[v] = k; d[k].pb(v);
    rep(i,sz(ot[v])) rfs(ot[v][i]);
  }
  void init() {
    k = n;
    used = kv = vi(n);
    g = vi(n,-1);
    rep(i,n) dfs(i);
    rep(i,n) if (g[kv[i]] == -1)  {
      d.pb(vi());
      rfs(kv[i]);
      k++;
    }
    gt = vvi(k);
    rep(i,n)rep(j,sz(ot[i])) {
      int v = g[ot[i][j]], u = g[i];
      if (v != u) gt[v].pb(u);
    }
    rep(i,k) {
      sort(rng(gt[i]));
      gt[i].erase(unique(rng(gt[i])),gt[i].end());
    }
  }
};
//
struct D {
  ll x, y, t;
  D(ll x=0, ll y=0, ll t=0):x(x),y(y),t(t) {}
  bool operator<(const D& _) const { return t<_.t;}
  bool can(const D& a) const {
    ll dx = x-a.x, dy = y-a.y, dt = t-a.t;
    return dx*dx+dy*dy <= dt*dt;
  }
};
istream& operator>>(istream&i,D&a){return i>>a.x>>a.y>>a.t;}
ostream& operator<<(ostream&o,const D&a){return o<<a.x<<" "<<a.y<<" "<<a.t;}

struct E {
  D d;
  int a, b;
  E(D d=D(), int a=0, int b=0):d(d),a(a),b(b) {}
  bool operator<(const E& _) const { return d<_.d;}
};
istream& operator>>(istream&i,E&a){return i>>a.a>>a.b;}
ostream& operator<<(ostream&o,const E&a){return o<<a.a<<" "<<a.b;}

struct Solver {
  void solve() {
    int n,w,m;
    scanf("%d%d%d",&n,&w,&m);
    vi ans(n,0);

    vc<D> ws(w);
    cin>>ws;

    vc<E> ms(m);
    rep(i,m) {
      int a, b;
      cin>>a>>b>>ms[i].d;
      --a; --b;
      ms[i].a = a;
      ms[i].b = b;
    }

    vvi isa(n);
    {
      int mi = 0;
      for (auto [d,a,b] : ms) {
        isa[a].pb(mi);
        isa[b].pb(mi);
        mi++;
      }
    }
    rep(ai,n) {
      vi& is = isa[ai];
      int s = sz(is);
      set<P> st;
      auto check = [&](int i, int j) {
        return ms[i].d.can(ms[j].d);
      };
      auto ng = [&](int i) {
        ans[ms[i].a] = 1;
      };
      for (int i : is) {
        auto d = ms[i].d;
        P p(d.t,i);
        auto it = st.lower_bound(p);
        while (it != st.end()) {
          if (check(i,it->se)) break;
          ng(it->se);
          st.erase(it++);
        }
        while (it != st.begin()) {
          --it;
          if (check(i,it->se)) break;
          ng(it->se);
          it = st.erase(it);
        }
        st.insert(p);
      }
      // rep(nj,s)rep(ni,nj) {
      //   int i = is[ni], j = is[nj];
      //   if (ms[i].d.can(ms[j].d)) continue;
      //   ans[ms[i].a] = 1;
      // }
    }

    scc g(n);
    {
      sort(rng(ms));
      int wi = 0;
      for (auto [d,a,b] : ms) {
        while (wi < w && ws[wi].t < d.t) ++wi;
        auto check = [&](int i) -> bool {
          if (i < 0 || i >= w) return false;
          if (!ws[i].can(d)) return true;
          return false;
        };
        if (check(wi-1) || check(wi)) {
          g.add(b,a);
        }
      }
    }
    g.init();
    rep(i,g.k) {
      vi& vs = g.d[i];
      int duck = 0;
      for (int v : vs) duck |= ans[v];
      if (duck) {
        for (int v : vs) ans[v] = 1;
        for (int j : g.gt[i]) ans[g.d[j][0]] = 1;
      }
    }

    int num = suma(ans);
    if (!num) {
      num = n;
      rep(i,g.k) {
        if (sz(g.gt[i])) continue;
        mins(num, sz(g.d[i]));
      }
    }
    cout<<num<<endl;
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
