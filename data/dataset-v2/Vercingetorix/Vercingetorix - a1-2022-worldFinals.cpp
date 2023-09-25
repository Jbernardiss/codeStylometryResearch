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
vvi g;
vi vis;
void dfs1(int v) {
    vis[v] = 1;
    for(auto u : g[v]) {
        if(vis[u] == 0) dfs1(u);
    }
}

vi dist;
vi bpar;

void bfs(int p) {
    int n = g.size();
    bpar = vi(n,-1);
    dist = vi(n,-1);
    vi bfs(1,p);
    dist[p] = 0;
    int pt = 0;
    bpar[p] = p;
    while(pt < bfs.size()) {
        int v = bfs[pt++];
        for(auto u : g[v]) if(dist[u] == -1) {
            bpar[u] = v;
            dist[u] = dist[v]+1;
            bfs.pb(u);
        }
    }
}

int dfsf(int v, int p) {
    int ret = 0;
    for(auto u : g[v]) if(u != p) ret = max(ret, 1 + dfsf(u, v));
    return ret;
}

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
        int n,m,a,q;
        scanf("%d %d %d %d", &n, &m, &a, &q);
        --a; --q;
        g = vvi(n);
        forn(i,0,m) {
            int u,v;
            scanf("%d %d", &u, &v);
            --u; --v;
            g[u].pb(v);
            g[v].pb(u);
        }
        vis = vi(n,0);
        dfs1(q);
        if(vis[a] == 0) {
            printf("SAFE\n");
            continue;
        }
        vi ban(n,0);
        vi par(n,-1);
        vi deg;
        forn(i,0,n) deg.pb(g[i].size());
        vi ord;
        forn(i,0,n) {
            if(deg[i] == 0) {
                ban[i] = 1;
            }
            else if(deg[i] == 1) {
                ban[i] = 1;
                ord.pb(i);
            }
        }
        while(!ord.empty()) {
            int v = ord.back();
            ord.pop_back();
            for(auto u : g[v]) {
                if(!ban[u]) {
                    par[v] = u;
                    deg[u]--;
                    if(deg[u] == 1) {
                        ord.pb(u);
                        ban[u] = 1;
                    }
                }
            }
        }
        int p = a;
        while(p != -1 && ban[p]) p = par[p];
        if(p == -1) p = q;
        bfs(p);
        if(dist[a] < dist[q]) {
            printf("SAFE\n");
            continue;
        }
        bfs(q);
        int ans = 0;
        int len = dist[a];
        ans += len - (len-1)/2;
        forn(it,0,(len-1)/2) a = bpar[a];
        printf("%d\n", 2*(ans + dfsf(a, bpar[a])));
        
    }
    
    
}
