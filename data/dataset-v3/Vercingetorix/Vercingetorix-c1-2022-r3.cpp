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
        int n;
        scanf("%d", &n);
        vvi e(n, vi(2));
        forn(j,0,2) forn(i,0,n) {
            scanf("%d", &e[i][j]);
            e[i][j]--;
        }
        int bad = 0;
        forn(i,0,n) {
            forn(p1,0,2) forn(p2,0,2) {
                if(e[e[i][p1]][p2] == i) bad = 1;
            }
        }
        if(bad) {
            printf("IMPOSSIBLE\n");
            continue;
        }
        vvi g(n);
        forn(u,0,n) {
            forn(p1,0,2) {
                int v = e[u][p1];
                g[u].pb(v);
                g[v].pb(u);
            }
            forn(p1,0,2) forn(p2,0,2) {
                int v = e[e[u][p1]][p2];
                g[u].pb(v);
                g[v].pb(u);
            }
        }
        vi ord;
        vi deg(n,0);
        forn(i,0,n) deg[i] = g[i].size();
        int pt = 0;
        forn(i,0,n) if(deg[i] <= 12) ord.pb(i);
        forn(pt,0,ord.size()) {
            for(auto v : g[ord[pt]]) {
                deg[v]--;
                if(deg[v] == 12) ord.pb(v);
            }
        }
        reverse(all(ord));
        vi taken(n, -1);
        string code = "ACDEHIJKMORST";
        for(auto v : ord) {
            vi ban(13,0);
            for(auto u : g[v]) if(taken[u] != -1) ban[taken[u]] = 1;
            taken[v] = 0;
            while(ban[taken[v]]) taken[v]++;
        }
        string ans;
        forn(i,0,n) ans.pb(code[taken[i]]);
        printf("%s\n", ans.c_str());
        
    }
    
    
}
