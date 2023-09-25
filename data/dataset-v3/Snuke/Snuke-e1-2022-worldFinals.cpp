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
template<typename T>void rot(T& a,int i){rotate(a.begin(),a.begin()+(i),a.end());}
template<typename T>void rot(vv<T>& a){int h=sz(a),w=sz(a[0]);vv<T> p(w,vc<T>(h));swap(a,p);rep(i,h)rep(j,w)a[j][h-1-i]=p[i][j];}
void rot(vc<string>& a){int h=sz(a),w=sz(a[0]);vc<string> p(w,string(h,'?'));swap(a,p);rep(i,h)rep(j,w)a[j][h-1-i]=p[i][j];}

// geom
const double inf = 1e6;
const double PI = acos(-1.0);
inline double toRad(double deg){ return deg * PI / 180.0;}

struct V {
  ll x, y;
  V(ll x=0, ll y=0):x(x),y(y){}
  V operator+(const V& t) const { return V(x+t.x,y+t.y);}
  V operator-(const V& t) const { return V(x-t.x,y-t.y);}
  V operator*(ll t) const { return V(x*t,y*t);}
  V operator/(ll t) const { return V(x/t,y/t);}
  V operator*(const V& t) const { return V(x*t.x-y*t.y,x*t.y+y*t.x);}
  V operator/(const V& t) const { return *this*V(t.x,-t.y)/t.norm2();}
  V& operator+=(const V& t) { x += t.x; y += t.y; return *this;}
  V& operator-=(const V& t) { x -= t.x; y -= t.y; return *this;}
  V& operator*=(ll t) { x *= t; y *= t; return *this;}
  V& operator/=(ll t) { x /= t; y /= t; return *this;}
  V& operator*=(const V& t) { return *this = *this*t;}
  V& operator/=(const V& t) { return *this = *this/t;}
  ll dot(const V& t) const { return x*t.x + y*t.y;}
  ll cross(const V& t) const { return x*t.y - y*t.x;}
  ll norm2() const { return x*x + y*y;}
  V rev() const { return V(-x,-y);}
  bool operator<(const V& a) const { return abs(x - a.x) > eps ? x < a.x : y < a.y;}
  bool operator==(const V& a) const { return abs(x - a.x) < eps && abs(y - a.y) < eps;}
};
istream& operator>>(istream&i,V&a){i>>a.x>>a.y;return i;}
ostream& operator<<(ostream&o,const V&a){o<<a.x<<','<<a.y;return o;}

struct Line {
  V s, t;
  Line(V s=V(0,0), V t=V(0,0)):s(s),t(t){}
  V dir() const { return t-s;}
  /* +1: s-t,s-p : ccw
   * -1: s-t,s-p : cw
   * +2: t-s-p
   * -2: s-t-p
   *  0: s-p-t */
  int ccw(const V& p) const {
    if (dir().cross(p-s) > 0) return +1;
    if (dir().cross(p-s) < 0) return -1;
    if (dir().dot(p-s) < 0) return +2;
    if (dir().norm2() < (p-s).norm2()) return -2;
    return 0;
  }
  bool touch(const Line& l) const {
    int a = ccw(l.s)*ccw(l.t), b = l.ccw(s)*l.ccw(t);
    return !a || !b || (a == -1 && b == -1);
  }
  bool isx(const Line& l) const {
    int a = ccw(l.s)*ccw(l.t), b = l.ccw(s)*l.ccw(t);
    if (a == -1 && b == -1) return true;
    if (!a && !b) return true;
    if (ccw(l.s) == 0 && ccw(l.t) == 0) return true;
    if (l.ccw(s) == 0 && l.ccw(t) == 0) return true;
    return false;
  }
};

struct Solver {
  void solve() {
    int n;
    scanf("%d",&n);
    assert(n <= 12);
    vc<V> ps(n);
    cin>>ps;

    auto tri = [&](const vi& is) {
      if (sz(is) != 3) return false;
      const V& a = ps[is[0]];
      const V& b = ps[is[1]];
      const V& c = ps[is[2]];
      return (b-a).cross(c-a) != 0;
    };

    map<pair<vi,vi>, bool> mp;
    auto check3 = [&](Line& l, vi& is) -> bool {
      const V& a = ps[is[0]];
      const V& b = ps[is[1]];
      const V& c = ps[is[2]];
      if (l.ccw(a) != 0) return false;
      return l.ccw(b) != l.ccw(c);
    };
    auto check2 = [&](vi is, vi js) -> bool {
      rep(ri,3) {
        rep(rj,3) {
          Line li(ps[is[0]], ps[is[1]]);
          Line lj(ps[js[0]], ps[js[1]]);
          if (li.isx(lj)) return false;
          if (check3(li,js)) return false;
          if (check3(lj,is)) return false;
          rot(js,1);
        }
        rot(is,1);
      }
      return true;
    };
    auto check = [&](const vi& is, const vi& js) -> bool {
      pair<vi,vi> p = make_pair(is,js);
      if (mp.count(p)) return mp[p];
      return mp[p] = check2(is,js);
    };

    vi gp;
    rep(i,n) gp.pb(i/3);
    int m = 4;
    vvi ans;
    do {
      vvi is(m);
      rep(i,n) is[gp[i]].pb(i);
      vvi now;
      rep(i,m) {
        if (!tri(is[i])) break;

        bool ok = true;
        rep(j,i) {
          if (!check(is[i],now[j])) { ok = false; break;}
        }
        if (!ok) break;
        now.eb(is[i]);
      }
      if (sz(ans) < sz(now)) {
        ans = now;
      }
    } while (next_permutation(rng(gp)));

    cout<<sz(ans)<<endl;
    for (vi a : ans) {
      rep(i,3) a[i]++;
      cout<<a<<endl;
    }
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
