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
#define bn(x) ((1ll<<(x))-1)
random_device _rd;
struct xrand {
  static const uint64_t _x = 88172645463325252ull;
  uint64_t x;
  xrand(): x(_x ^ (_rd()+time(0))) {}
  xrand(uint64_t seed): x(_x ^ seed) {}
  uint64_t get() {
    x = x ^ (x << 7);
    return x = x ^ (x >> 9);
  }
  int operator()(int n) { return get()%n;}
  int operator()(int l, int r) { return get()%(r-l+1) + l;}
} rnd;
void bins(ll x) {
  vi vs;
  while (x) {
    ll b = x&-x;
    vs.pb(pcnt(b-1)+1);
    x ^= b;
  }
  cerr<<vs<<endl;
}

const vvp edges = {
  {{0,1},{1,2},{2,3},{3,4},{4,5},{4,26},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15},{15,16},{15,27},{16,17},{17,18},{18,19},{19,20},{20,21},{21,22},{22,23},{22,28},{23,24},{24,25},{26,29}},
{{0,1},{1,2},{2,3},{3,4},{4,5},{4,27},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{12,30},{13,14},{14,15},{15,16},{16,17},{17,18},{18,19},{18,29},{19,20},{20,21},{21,22},{22,23},{23,24},{24,25},{25,26},{25,28}},
{{0,1},{1,2},{1,29},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{10,30},{11,12},{12,13},{13,14},{14,15},{15,16},{15,28},{16,17},{17,18},{18,19},{19,20},{20,21},{21,22},{22,23},{23,24},{24,25},{24,31},{25,26},{26,27}},
{{0,1},{1,2},{2,3},{2,32},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15},{14,29},{15,16},{15,30},{16,17},{17,18},{17,31},{18,19},{19,20},{20,21},{21,22},{22,23},{23,24},{24,25},{25,26},{26,27},{27,28}},
{{0,1},{1,2},{1,30},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{11,33},{12,13},{12,31},{13,14},{14,15},{15,16},{16,17},{17,18},{18,19},{19,20},{20,21},{21,22},{21,32},{22,23},{23,24},{24,25},{25,26},{26,27},{27,28},{28,29}},
{{0,1},{0,32},{1,2},{1,34},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15},{15,16},{16,17},{17,18},{18,19},{19,20},{20,21},{21,22},{22,23},{23,24},{24,25},{25,26},{26,27},{27,28},{28,29},{29,30},{30,31},{31,33}},
{{0,1},{1,2},{2,3},{3,4},{3,34},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{12,32},{13,14},{14,15},{14,33},{15,16},{16,17},{16,35},{17,18},{18,19},{19,20},{20,21},{21,22},{22,23},{23,24},{24,25},{25,26},{26,27},{27,28},{28,29},{29,30},{30,31}},
{{0,1},{1,2},{2,3},{2,34},{3,4},{3,33},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15},{15,16},{16,17},{17,18},{18,19},{18,36},{19,20},{20,21},{21,22},{22,23},{23,24},{24,25},{25,26},{26,27},{27,28},{28,29},{29,30},{30,31},{30,35},{31,32}},
{{0,1},{1,2},{2,3},{2,37},{3,4},{3,35},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15},{15,16},{16,17},{17,18},{18,19},{19,20},{20,21},{21,22},{22,23},{23,24},{24,25},{25,26},{26,27},{27,28},{28,29},{29,30},{29,36},{30,31},{31,32},{31,34},{32,33}},
{{0,1},{0,38},{1,2},{2,3},{3,4},{3,36},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{11,37},{12,13},{13,14},{14,15},{15,16},{16,17},{17,18},{18,19},{19,20},{20,21},{21,22},{22,23},{23,24},{24,25},{25,26},{26,27},{27,28},{28,29},{29,30},{30,31},{31,32},{32,33},{33,34},{33,35}},
{{0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{9,36},{10,11},{11,12},{11,38},{12,13},{13,14},{14,15},{15,16},{15,39},{16,17},{17,18},{18,19},{19,20},{20,21},{21,22},{22,23},{23,24},{24,25},{25,26},{26,27},{27,28},{28,29},{29,30},{30,31},{31,32},{32,33},{33,34},{34,35},{36,37}},

};

struct Solver {
  int n;
  vvi to;
  vl g;
  map<ll,int> dp;
  ll tfs(ll s, int v, int p) {
    ll res = 1ll<<v;
    for (int u : to[v]) if (u != p) {
      if (s>>u&1) res |= tfs(s,u,v);
    }
    return res;
  }
  int f2(ll s, int v) {
    int res = 0;
    for (int u : to[v]) if (s>>u&1) {
      res ^= f(tfs(s,u,v));
    }
    return res;
  }
  int f(ll s) {
    if (!s) return 0;
    auto it = dp.find(s);
    if (it != dp.end()) return it->se;
    vi xs;
    rep(v,n) if (s>>v&1) {
      vi d(1);
      for (int u : to[v]) if (s>>u&1) {
        ll t = tfs(s,u,v);
        int x = f(t), y = f2(t^1ll<<u,u);
        vi p; swap(d,p);
        for (int a : p) d.pb(a^x), d.pb(a^y);
      }
      xs.insert(xs.end(),rng(d));
    }
    uni(xs);
    int res = 0;
    while (res < sz(xs) && xs[res] == res) ++res;
    return dp[s] = res;
  }
  // int gen() {
  //   dp = map<ll,int>();
  //   to = vvi(n);
  //   auto add = [&](int a, int b) {
  //     to[a].pb(b);
  //     to[b].pb(a);
  //   };
  //   rep1(i,n-1) {
  //     if (n-i >= 5) add(i,i-1);
  //     else add(i,rnd(i));
  //   }
  //   int res = f(bn(n));
  //   cerr<<res<<endl;
  //   cerr<<sz(dp)<<endl;
  //   return res;
  // }

  //*
  void gen() {
    to = vvi(n);
    g = vl(n);
    rep(i,n) g[i] |= 1ll<<i;
    for (auto [a,b] : edges[n-30]) {
      to[a].pb(b);
      to[b].pb(a);
      g[a] |= 1ll<<b;
      g[b] |= 1ll<<a;
      cout<<a+1<<" "<<b+1<<endl;
    }
    assert(f(bn(n)) == 0);
  }
  //*/

  ll tox(ll s, int X) {
    X ^= f(s);
    rep(v,n) if (s>>v&1) {
      vi d(1);
      int b = 0;
      for (int u : to[v]) if (s>>u&1) {
        ll t = tfs(s,u,v);
        int x = f(t), y = f2(t^1ll<<u,u);
        vi p; swap(d,p);
        for (int a : p) d.pb(a^x), d.pb(a^y);
        ++b;
      }
      int di = 0;
      while (di < sz(d) && d[di] != X) di++;
      if (di == sz(d)) continue;
      ll res = 1ll<<v;
      int nx = 0;
      for (int u : to[v]) if (s>>u&1) {
        ll t = tfs(s,u,v);
        --b;
        if (di>>b&1) {
          res |= 1ll<<u;
          nx ^= f2(t^1ll<<u,u);
          // bins(t^1ll<<u); cerr<<f(t^1ll<<u)<<endl;
        } else {
          nx ^= f(t);
          // bins(t); cerr<<f(t)<<endl;
        }
      }
      // bins(s);
      // cerr<<s<<' '<<X<<endl;
      assert(nx == X);
      return res;
    }
    return 0;
  }

  ll get(ll s) {
    vl ss;
    int x = 0;
    rep(i,n) if (s>>i&1) {
      ll t = tfs(s,i,-1);
      s ^= t;
      ss.pb(t);
      x ^= f(t);
      // cerr<<t<<" "<<f(t)<<endl;
    }
    assert(x);
    // cerr<<"x:"<<x<<endl;
    for (ll t : ss) {
      ll u = tox(t,x);
      if (u) return u;
    }
    assert(false);
  }

  void check(ll s) {
    vl ss;
    int x = 0;
    rep(i,n) if (s>>i&1) {
      ll t = tfs(s,i,-1);
      s ^= t;
      ss.pb(t);
      x ^= f(t);
      // cerr<<t<<" "<<f(t)<<endl;
    }
    assert(x == 0);
  }

  void solve() {
    cin>>n;
    // while (gen());
    // char c = '{';
    // rep(i,n) for (int j : to[i]) if (i < j) printf("%c{%d,%d}", c, i, j), c = ',';
    // puts("},");
    // return;

    gen();

    int games;
    cin>>games;
    rep(gi,games) {
      ll s = bn(n);
      while (s) {
        int m;
        cin>>m;
        rep(i,m) {
          int v;
          cin>>v;
          --v;
          s ^= 1ll<<v;
        }
        ll t = get(s);
        s ^= t;
        vi vs;
        rep(i,n) if (t>>i&1) {
          if ((t&g[i]) == t) {
            vs.pb(i+1);
            t ^= 1ll<<i;
            break;
          }
        }
        rep(i,n) if (t>>i&1) vs.pb(i+1);
        cout<<sz(vs)<<endl;
        cout<<vs<<endl;
        // cerr<<"rem: "<<pcnt(s)<<endl;
        // check(s);
      }
    }
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
    // printf("Case #%d: ",ti);
    solver.solve();
  }
// END_STACK_EXTEND;
  return 0;
}
