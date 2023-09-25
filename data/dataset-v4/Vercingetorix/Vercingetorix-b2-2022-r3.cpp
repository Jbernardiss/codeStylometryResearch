#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <queue>
#include <cstring>
#include <set>
#include <bitset>
#include <map>
#include <chrono>
#include <random>
#include <unordered_map>
#include <stdio.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<string> vs;
typedef std::vector<double> vd;
typedef std::vector<long long> vll;
typedef std::vector<std::vector<int> > vvi;
typedef vector<vll> vvll;
typedef std::vector<std::pair<int, int> > vpi;
typedef vector<vpi> vvpi;
typedef std::pair<int, int> pi;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

const long long mod = 1000000007;
ll gcd (ll a, ll b) {return b==0 ? a : gcd(b, a%b);}
const unsigned gen_seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937_64 gen(gen_seed);

#define all(c) (c).begin(),(c).end()
#define srt(c) sort(all(c))
#define srtrev(c) sort(all(c)); reverse(all(c))
#define forn(i, a, b) for(int i = a; i < b; i++)
#define read(x) scanf("%d", &x)
#define readv(x, n) vi x(n); forn(i,0,n) scanf("%d", &x[i])

#define pb push_back
#define mp make_pair
const int INF = 1e9;
struct sega {
    int mn, cnt;
    sega(int mn = INF, int cnt = 0) : mn(mn), cnt(cnt) {};
    
    void push(int add) {
        mn += add;
    }
};

sega combine(const sega & a, const sega & b) {
    if(a.mn < b.mn) return a;
    else if(b.mn < a.mn) return b;
    else return sega(a.mn, a.cnt + b.cnt);
}

sega zerosega(INF,0);

class stree {
public:
    vector<sega> t;
    vi pp;
    void build (const vi & a, int v, int tl, int tr) {
        if(v==1) {
            t.resize(a.size() * 4);
            pp = vi(a.size()*4,0);
        }
        if (tl == tr)
            t[v] = sega(a[tl], 1);
        else {
            int tm = (tl + tr) / 2;
            build (a, v*2, tl, tm);
            build (a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }
    
    void push(int v, int tl, int tr) {
        if(pp[v] == 0) return;
        t[v].push(pp[v]);
        if(tl != tr) {
            pp[2*v] += pp[v];
            pp[2*v+1] += pp[v];
        }
        pp[v] = 0;
    }
    
    void update (int v, int tl, int tr, int l, int r, int val) {
        if (l == tl && tr == r) {
            pp[v] += val;
            push(v,tl,tr);
            return;
        }
        if (l > r) {
            push(v, tl, tr);
            return;
        }
        else {
            push(v,tl,tr);
            int tm = (tl + tr) / 2;
            update (v*2, tl, tm, l, min(r,tm), val);
            update (v*2+1, tm+1, tr, max(l,tm+1), r, val);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }
    
    sega get (int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (l>r) return zerosega;
        if (tl ==l && r== tr)
            return t[v];
        int tm = (tl + tr) / 2;
        sega ret =  combine(get(v*2, tl, tm, l, min(r,tm)), get(v*2+1, tm+1, tr, max(l,tm+1), r));
        t[v] = combine(t[v*2], t[v*2+1]);
        return ret;
    }
};

int main()
{
#ifdef LOCAL
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int ta;
    read(ta);
    forn(ifa,0,ta) {
        printf("Case #%d: ", ifa+1);
        int n,m;
        scanf("%d %d", &n, &m);
        vi l(m), r(m);
        forn(i,0,m) {
            scanf("%d %d", &l[i], &r[i]);
        }
        vvi pos(m);
        readv(a,n);
        forn(i,0,n) a[i]--;
        forn(i,0,n) pos[a[i]].pb(i);
        forn(i,0,n) pos[a[i]].pb(i+n);
        stree st;
        st.build(vi(2*n,0), 1, 0, 2*n-1);
        
        forn(i,0,m) {
            if(pos[i].empty()) continue;
            if(l[i] > 1) {
                int bl = pos[i][0];
                int br = 2*n-1;
                if(pos[i].size() >= l[i]) br = pos[i][l[i]-1] - 1;
                st.update(1, 0, 2*n-1, bl, br, 1);
            }
            if(pos[i].size() > r[i]) {
                int bl = pos[i][r[i]];
                st.update(1, 0, 2*n-1, bl, 2*n-1, 1);
            }
        }
        vi pt(m,0);
        ll ans = 0;
        forn(s,0,n) {
            auto cur = st.get(1, 0, 2*n-1, s+1, s+n-2);
            if(cur.mn == 0) ans += cur.cnt;
            int i = a[s];
            if(l[i] > 1 && pt[i] + l[i]-1 < pos[i].size()) {
                int bl = pos[i][pt[i] + l[i]-1];
                int br = 2*n-1;
                if(pt[i] + l[i] < pos[i].size()) br = pos[i][pt[i]+l[i]] - 1;
                st.update(1, 0, 2*n-1, bl, br, 1);
            }
            if(l[i] > 1) {
                int bl = s;
                int br = 2*n-1;
                if(pt[i] + 1 < pos[i].size()) br = pos[i][pt[i] + 1] - 1;
                st.update(1, 0, 2*n-1, bl, br, -1);
            }
            if(pt[i] + r[i] < pos[i].size()) {
                int bl = pos[i][pt[i]+r[i]];
                int br = 2*n-1;
                if(pt[i] + r[i] + 1 < pos[i].size()) br = pos[i][pt[i]+r[i] + 1] - 1;
                st.update(1, 0, 2*n-1, bl, br, -1);
            }
            pt[i]++;
        }
        printf("%lld\n", ans);
    }
    
    
}
