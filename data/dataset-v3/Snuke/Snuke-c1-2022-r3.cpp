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

const string S = "ACDEHIJKMORST";

struct Solver {
  void solve() {
    int n;
    scanf("%d",&n);
    vvi lr(n);
    vvi to(n);
    rep(ti,2) {
      rep(i,n) {
        int a;
        scanf("%d",&a);
        --a;
        lr[i].pb(a);
      }
    }
    rep(i,n) {
      vi vs;
      auto dfs = [&](auto f, int v, int k) -> void {
        if (k != 2) vs.pb(v);
        if (!k) return;
        --k;
        for (int u : lr[v]) f(f,u,k);
      };
      dfs(dfs,i,2);
      uni(vs);
      for (int v : vs) {
        if (v == i) dame;
        to[i].pb(v), to[v].pb(i);
      }
    }
    vi deg(n);
    vi vs;
    rep(i,n) deg[i] = sz(to[i]);
    queue<int> q;
    rep(i,n) if (deg[i] <= 12) q.push(i);
    while (sz(q)) {
      int v = q.front(); q.pop();
      vs.pb(v);
      for (int u : to[v]) {
        deg[u]--;
        if (deg[u] == 12) q.push(u);
      }
    }
    reverse(rng(vs));
    vi c(n,-1);
    for (int v : vs) {
      int fl = 0;
      for (int u : to[v]) {
        if (c[u] == -1) continue;
        fl |= 1<<c[u];
      }
      c[v] = 0;
      while (fl>>c[v]&1) c[v]++;
    }
    string ans;
    rep(i,n) ans += S[c[i]];
    cout<<ans<<endl;
  }
};

#define BEGIN_STACK_EXTEND(size) void * stack_extend_memory_ = malloc(size);void * stack_extend_origin_memory_;char * stack_extend_dummy_memory_ = (char*)alloca((1+(int)(((long long)stack_extend_memory_)&127))*16);*stack_extend_dummy_memory_ = 0;asm volatile("mov %%rsp, %%rbx\nmov %%rax, %%rsp":"=b"(stack_extend_origin_memory_):"a"((char*)stack_extend_memory_+(size)-1024));
#define END_STACK_EXTEND asm volatile("mov %%rax, %%rsp"::"a"(stack_extend_origin_memory_));free(stack_extend_memory_);
int main() {
// BEGIN_STACK_EXTEND(128 * (1024*1024));
  int ts;
  cin>>ts;
  rep1(ti,ts) {
    Solver solver;
    printf("Case #%d: ",ti);
    solver.solve();
  }
// END_STACK_EXTEND;
  return 0;
}
