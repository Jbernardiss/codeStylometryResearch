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
int n,k;
vi ask(vi col) {
    forn(i,0,n) printf("%d ", col[i]+1);
    printf("\n");
    fflush(stdout);
    int ret;
    scanf("%d", &ret);
    if(ret == -1) exit(0);
    if(ret == 1) {
        vi res;
        forn(i,0,n) res.pb(i);
        return res;
    }
    else {
        readv(res,n);
        forn(i,0,n) res[i]--;
        return res;
    }
    return vi();
}

int main()
{
    int ta;
    read(ta);
    
    scanf("%d %d", &n, &k);
    vi good;
    forn(i,0,n) good.pb(i);
    forn(ifa,0,ta) {
        readv(a,n);
        forn(i,0,n) a[i]--;
        while(1) {
            vi vis(n,0);
            int need = 0;
            vi col(n,0);
            int pt = 0;
            forn(i,0,n) {
                if(a[i] != i) need = 1;
                if(vis[i] == 0) {
                    int cur =  i;
                    vi c;
                    do {
                        c.pb(cur);
                        vis[cur] = 1;
                        col[cur] = pt;
                        cur = a[cur];
                    } while(cur != i);
                    if(c.size() > 20) {
                        for(int j = 0; j < c.size(); j+=10) {
                            forn(k,0,10) {
                                if(j + k < c.size()) col[c[j+k]] = pt;
                            }
                            pt++;
                        }
                    }
                    else pt++;
                }
            }
            a = ask(col);
            if(a == good)  break;
        }
    }
    
    
}
