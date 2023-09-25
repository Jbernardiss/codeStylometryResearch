#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <bits/stdc++.h>

using namespace std;

#define POW2(X) (1<<(X))
#define CKBIT(S,X) (((S)&POW2(X))!=0)
const double pi=acos(-1.0);
const double eps=1e-11;
template<class T> inline void ckmin(T &a,T b){ a=min(a,b); }
template<class T> inline void ckmax(T &a,T b){ a=max(a,b); }
template<class T> inline T sqr(T x){ return x*x; }
#define SIZE(A) ((int)A.size())
#define LENGTH(A) ((int)A.length())
#define MP(A,B) make_pair(A,B)
#define PB(X) push_back(X)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,a) for(int i=0;i<(a);++i)
#define ALL(A) A.begin(),A.end()
using uint=unsigned int;
using int64=long long;
using uint64=unsigned long long;
using ipair=pair<int,int>;
using VI=vector<int>;
using VD=vector<double>;

template<typename ModWrapper>
class Modular
{
public:
	using base_type = typename decay<decltype(ModWrapper::value)>::type;

	base_type n;

	constexpr Modular() : n(0) {}

	template<typename U>
	Modular(U m) { 
		if (m >= 0 && m < mod()) { n = static_cast<base_type>(m);
		} else { n = static_cast<base_type>(m % mod()); if (n < 0) n += mod(); }
	}

	constexpr static base_type mod() { return ModWrapper::value; }
	base_type val() const { return n; }

	Modular operator-() const { return build(n == 0 ? 0 : mod() - n); }
	Modular& operator+=(Modular a) { n = (n >= mod() - a.n ? n - mod() + a.n : n + a.n); return *this; }
	Modular& operator-=(Modular a) { n = (n >= a.n) ? n - a.n : n - a.n + mod(); return *this; }
	Modular& operator*=(Modular a) { *this = *this * a; return *this; }
	Modular& operator/=(Modular a) { *this = *this / a; return *this; }
	Modular& operator++() { return *this += 1; }
	Modular& operator--() { return *this -= 1; }
	Modular operator++(int) { Modular result(*this); *this += 1; return result; }
	Modular operator--(int) { Modular result(*this); *this -= 1; return result; }

	static Modular build(base_type n) { Modular r; r.n = n; return r; }

	friend Modular inverse(Modular n) { return build(inverse_internal(n.n)); }
	friend bool operator==(Modular a, Modular b) { return a.n == b.n; }
	friend bool operator!=(Modular a, Modular b) { return !(a.n == b.n); }
	friend Modular operator+(Modular a, Modular b) { return build(a.n >= mod() - b.n ? a.n - mod() + b.n : a.n + b.n); }
	friend Modular operator-(Modular a, Modular b) { return build(a.n >= b.n ? a.n - b.n : a.n - b.n + mod()); }
	friend Modular operator*(Modular a, Modular b) { return build(static_cast<base_type>(static_cast<long long>(a.n)* b.n% mod())); }
	friend Modular operator/(Modular a, Modular b) { return a * inverse(b); }
	friend Modular pow(Modular p, long long e)
	{
		if (e <= 0) return Modular(1);
		Modular r = Modular(1);
		while (1) { if (e & 1) r *= p; e /= 2; if (e) p = p * p; else break; }
		return r;
	}

	friend istream& operator>>(istream& stream, Modular& a) { stream >> a.n; return stream; }
	friend ostream& operator<<(ostream& stream, const Modular& a) { stream << a.n; return stream; }

private:
	static constexpr int INVERSE_CACHE_SIZE = (1 << 18);
	static base_type inverse_cache[INVERSE_CACHE_SIZE];
	static base_type inverse_cache_mod_value;
	static base_type inverse_internal(base_type n)
	{
		if (inverse_cache_mod_value != mod())
		{
			inverse_cache_mod_value = mod();
			inverse_cache[0] = 0;
			inverse_cache[1] = 1;
			for (int n = 2; n < INVERSE_CACHE_SIZE; ++n) inverse_cache[n] = (mod() - (base_type)((long long)inverse_cache[mod() % n] * (mod() / n) % mod()));
		}
		return n < INVERSE_CACHE_SIZE ? inverse_cache[n] : inverse_internal_large(n);
	}
	static base_type inverse_internal_large(base_type n)
	{
		return n < INVERSE_CACHE_SIZE ? inverse_cache[n] : mod() - (base_type)((long long)inverse_internal_large(mod() % n) * (mod() / n) % mod());
	}
};
template<typename ModWrapper> typename decay<decltype(ModWrapper::value)>::type Modular<ModWrapper>::inverse_cache[INVERSE_CACHE_SIZE];
template<typename ModWrapper> typename decay<decltype(ModWrapper::value)>::type Modular<ModWrapper>::inverse_cache_mod_value = -1;

#define MOD (1000000007)

using ModType = int;
struct ModWrapper {
	static ModType value;
};
ModType ModWrapper::value = MOD;
ModType& mod_value = ModWrapper::value;

using Int = Modular<ModWrapper>;

int n;
VI a;
VI p;

int ck(int at,int val)
{
	if (at<0 || at>=n) return val==0;
	return a[at]<0 || a[at]==val;
}
vector<VI> cache;
int dfs(int cur,int mask)
{
	if (cur==n-1)
	{
		return (CKBIT(mask,5) && CKBIT(mask,p[cur]-cur+5))?1:0;
	}
	int& cached_ret=cache[cur][mask];
	if (cached_ret>=0) return cached_ret;
	Int ret=0;
	REP(next_bit,2)
	{
		if (!ck(cur+5,next_bit)) continue;
		int new_mask=(mask|(next_bit<<10));
		if (CKBIT(new_mask,5) && !CKBIT(new_mask,p[cur]-cur+5))
		{
			new_mask^=POW2(5);
			new_mask^=POW2(p[cur]-cur+5);
		}
		ret+=dfs(cur+1,new_mask>>1);
	}
	return cached_ret=ret.n;
}
int solve_one_case()
{
	cin>>n;
	string str;
	cin>>str;
	a=VI(n);
	REP(i,n)
	{
		if (str[i]=='.') a[i]=0;
		if (str[i]=='C') a[i]=1;
		if (str[i]=='?') a[i]=-1;
	}
	p=VI(n);
	REP(i,n) { cin>>p[i]; --p[i]; }
	Int ret=0;
	cache=vector<VI>(n,VI(POW2(10),-1));
	REP(set,POW2(5))
	{
		int ok=1;
		REP(i,5) if (!ck(i,CKBIT(set,i))) ok=0;
		if (!ok) continue;
		ret+=dfs(0,(set<<5));
	}
	return ret.n;
}

int main()
{
#ifdef _MSC_VER
	freopen("input.txt","r",stdin);
#endif
	std::ios::sync_with_stdio(false);
	int testcase;
	cin>>testcase;
	FOR(case_id,1,testcase+1)
	{
		int ret=solve_one_case();
		printf("Case #%d: %d\n",case_id,ret);
	}
	return 0;
}

