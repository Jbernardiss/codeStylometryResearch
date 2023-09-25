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
int ncur;
vi ban;
void go(const vi & x) {
    ncur -= x.size();
    for(auto y : x) ban[y] = 1;
    printf("%d\n", (int)x.size());
    for(auto y : x) printf("%d ", y+1);
    printf("\n");
    fflush(stdout);
}

vi get() {
    int k;
    read(k);
    if(k == -1) exit(0);
    readv(a,k);
    forn(i,0,k) a[i]--;
    for(auto x : a) ban[x] = 1;
    ncur -= a.size();
    return a;
}

int main()
{
//#ifdef LOCAL
//    freopen("input.txt", "rt", stdin);
//    freopen("output.txt", "wt", stdout);
//#endif
    int ta;
    read(ta);
    forn(ifa,0,ta) {
        int n;
        scanf("%d", &n);
        if(n%2 == 0) {
            printf("1 2\n");
            printf("2 3\n");
            printf("3 4\n");
            forn(i,5,n+1) printf("4 %d\n", i);
            fflush(stdout);
            int q;
            read(q);
            while(q--) {
                ban = vi(n,0);
                ncur = n;
                while(1) {
                    vi a = get();
                    if(ban[3]) {
                        int fr = 0;
                        forn(i,4,n) fr += 1-ban[i];
                        if(ban[1]) {
                            int pt = 0;
                            while(ban[pt]) pt++;
                            go(vi(1,pt));
                        }
                        else {
                            vi my(1,1);
                            if(ban[0] == 0) fr++;
                            if(ban[2] == 0) fr++;
                            if(fr%2) {
                                if(ban[0] == 0) my.pb(0);
                                else my.pb(2);
                            }
                            go(my);
                        }
                    }
                    else {
                        if(ban[1] + ban[2] == 0) {
                            go({2,1,3});
                        }
                        else if(ban[2] == 0) {
                            if(ban[0] == 0) go({3});
                            else go({2,3});
                        }
                        else {
                            if(ban[0] + ban[1] > 0) {
                                vi my;
                                forn(i,3,n) if(ban[i] == 0) my.pb(i);
                                if(ban[0] + ban[1] == 1) my.pop_back();
                                go(my);
                            }
                            else {
                                int pt = 4;
                                while(pt < n && ban[pt]) pt++;
                                if(pt == n) go({0});
                                else go({pt});
                            }
                        }
                    }
                    if(ncur == 0) break;
                }
            }
        }
    }
    
    
}
