//~ while (clock()<=69*CLOCKS_PER_SEC)
//~ #pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O3")
//~ #pragma GCC target ("avx2")
//~ #pragma GCC optimize("Ofast")
//~ #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//~ #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

#define shandom_ruffle random_shuffle

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using vi=vector<int>;
using vll=vector<ll>;
const int nax=1000*1007;
using ull=unsigned long long;

void ff()
{
	fflush(stdout);
}

int n;

vi graf[nax];
ll macsom[nax];

int los(int a, int b)
{
	return a+rand()%(b-a+1);
}

map<ll,int> mapa;

int ojf[nax];
int fin(int v)
{
	if (v!=ojf[v])
		ojf[v]=fin(ojf[v]);
	return ojf[v];
}

void uni(int a, int b)
{
	ojf[fin(a)]=fin(b);
}

void wylosuj()
{
	//~ static int ziarno=9;
	//~ ziarno++;
	//~ srand(ziarno);
	//~ debug() << imie(ziarno);
	srand(16);
	for (int i=0; i<n; i++)
	{
		graf[i].clear();
		macsom[i]=1LL<<i;
	}
	for (int i=1; i<n; i++)
	{
		int j=los(0, i-1);
		graf[i].push_back(j);
		graf[j].push_back(i);
		macsom[i]|=(1LL<<j);
		macsom[j]|=(1LL<<i);
	}
	return;
	for (int i=0; i<n; i++)
		ojf[i]=i;
	vector<pii> kra;
	for (int i=0; i<n; i++)
		for (int j=0; j<i; j++)
			kra.push_back({i, j});
	shandom_ruffle(kra.begin(), kra.end());
	//~ vi sto(n);
	for (pii h : kra)
	{
		int i=h.first;
		int j=h.second;
		//~ if (sto[i]>2 || sto[j]>2)
			//~ continue;
		if (fin(i)==fin(j))
			continue;
		//~ sto[i]++;
		//~ sto[j]++;
		uni(i, j);
		graf[i].push_back(j);
		graf[j].push_back(i);
		macsom[i]|=(1LL<<j);
		macsom[j]|=(1LL<<i);
	}
}

static uint64_t splitmix64(uint64_t x) {
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}

ull haszuj(vector<ull> &wek)
{
	//~ sort(wek.begin(), wek.end());
	//~ ull ret=1;
	//~ for (const ull &i : wek)
		//~ ret=splitmix64(ret+i);
	//~ return ret;
	ull s=0;
	for (ull i : wek)
		s+=i;
	return splitmix64(s);
}

ull liczhasz(int v, int oj, ll doz)
{
	vector<ull> wek;
	for (int i : graf[v])
		if (i!=oj && ((doz>>i)&1))
			wek.push_back(liczhasz(i, v, doz));
	return haszuj(wek);
}

int policz(ll v);

int rozbij_i_policz(ll v)
{
	if (!v)
		return 0;
	int x=0;
	while(!((v>>x)&1))
		x++;
	ll mas=1LL<<x;
	while(1)
	{
		ll bylo=mas;
		for (int i=0; i<n; i++)
			if (mas&(1LL<<i))
				mas=(mas|macsom[i])&v;
		if (bylo==mas)
			break;
	}
	return policz(mas)^rozbij_i_policz(v^mas);
	//~ return policz(v);
}

int domex[nax];

int policz(ll v)
{
	if (!v)
		return 0;
	vector<ull> wek;
	for (int i=0; i<n; i++)
		if ((v>>i)&1)
			wek.push_back(liczhasz(i, 0, v));
	ull hasz=haszuj(wek);
	if (mapa.count(hasz))
		return mapa[hasz];
	vi wez;
	for (int i=0; i<n; i++)
	{
		if (!((v>>i)&1))
			continue;
		ll pod=0;
		for (int j : graf[i])
			if ((v>>j)&1)
				pod|=(1LL<<j);
		
		ll ter=pod;
		while(1)
		{
			wez.push_back(rozbij_i_policz(v^(1LL<<i)^ter));
			if (!ter)
				break;
			ter=(ter-1)&pod;
		}
	}
	for (int i=0; i<(int)wez.size()+7; i++)
		domex[i]=0;
	for (int i : wez)
		domex[i]=1;
	int ret=0;
	while(domex[ret])
		ret++;
	return mapa[hasz]=ret;
}

vector<ll> potnij(ll v)
{
	vll ret;
	while(v)
	{
		int x=0;
		while(!((v>>x)&1))
			x++;
		ll mas=1LL<<x;
		while(1)
		{
			ll bylo=mas;
			for (int i=0; i<n; i++)
				if (mas&(1LL<<i))
					mas=(mas|macsom[i])&v;
			if (bylo==mas)
				break;
		}
		ret.push_back(mas);
		v^=mas;
	}
	return ret;
}

void test()
{
	scanf("%d", &n);
	int pro=0;
	while(1)
	{
		wylosuj();
		//~ mapa.clear();
		pro++;
		//~ debug() << imie(pro);
		int wez=policz((1LL<<n)-1);
		if (!wez)
		{
			//~ debug() << imie(pro) << imie(wez);
			break;
			//~ exit(0);
		}
		//~ debug() << imie(mapa.size()) << imie(wez);
	}
	for (int i=0; i<n; i++)
		for (int j : graf[i])
			if (j>i)
				printf("%d %d\n", i+1, j+1);
	ff();
	int gry;
	scanf("%d", &gry);
	//~ debug() << imie(gry);
	while(gry--)
	{
		ll v=(1LL<<n)-1;
		//~ debug() << imie(rozbij_i_policz(v));
		while(v)
		{
			int ile=0;
			scanf("%d", &ile);
			while(ile--)
			{
				int x;
				scanf("%d", &x);
				debug() << "usuwam " << x;
				v^=(1LL<<(x-1));
			}
			
			
			
			vi odp;
			for (int i=0; i<n && odp.empty(); i++)
			{
				if (!((v>>i)&1))
					continue;
				ll pod=0;
				for (int j : graf[i])
					if ((v>>j)&1)
						pod|=(1LL<<j);
				
				ll ter=pod;
				while(1)
				{
					//~ debug() << "probuje " << i << " " << ter;
					if (!rozbij_i_policz(v^(1LL<<i)^ter))
					{
						odp={i};
						for (int j=0; j<n; j++)
							if ((ter>>j)&1)
								odp.push_back(j);
						break;
					}
					if (!ter)
						break;
					ter=(ter-1)&pod;
				}
			}
			//~ debug() << imie(odp);
			printf("%d\n", (int)odp.size());
			for (int i : odp)
				printf("%d ", i+1);
			printf("\n");
			ff();
			for (int i : odp)
				v^=(1LL<<i);
		}
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i=1; i<=t; i++)
	{
		//~ printf("Case #%d: ", i);
		test();
		//~ fflush(stdout);
	}
	return 0;
}
