#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
typedef double db;
mt19937 mrand(random_device{}()); 
const ll mod=1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

typedef vector<ll> VL;
typedef vector<VL> matrix;
const ll inf=1ll<<60;
typedef __int128 i128;
matrix mul(const matrix &a,const matrix &b) {
	int n=SZ(a),m=SZ(a[0]),k=SZ(b[0]);
	matrix c(n,VL(k,0));
	rep(i,0,n) rep(j,0,k) rep(k,0,m) {
		c[i][j]=min((i128)inf,c[i][j]+(i128)a[i][k]*b[k][j]);
	}
	return c;
}
void multo(matrix &a,const matrix &b) {
	int n=SZ(a);
	assert(SZ(a[0])==n&&SZ(b)==n&&SZ(b[0])==n);
	matrix c(n,VL(n,0));
	rep(i,0,n) rep(j,0,n) rep(k,0,n) {
		c[i][j]=min((i128)inf,c[i][j]+(i128)a[i][k]*b[k][j]);
	}
	rep(i,0,n) rep(j,0,n) a[i][j]=c[i][j];
}
matrix add(const matrix &a,const matrix &b) {
	int n=SZ(a);
	matrix c(n,VL(n,0));
	rep(i,0,n) rep(j,0,n) {
		c[i][j]=min(a[i][j]+b[i][j],inf);
		//if (c[i][j]>=mod) c[i][j]-=mod;
	}
	return c;
}
matrix unit(int n,int w=1) {
	matrix c(n,VL(n,0));
	rep(i,0,n) c[i][i]=w;
	return c; 
}
matrix powmod(matrix a,ll b) {
	int n=SZ(a);
	matrix res=unit(n);
	for (;b;b>>=1) { if(b&1) multo(res,a);multo(a,a);}
	return res;
}
void print(const matrix &a) {
	int n=SZ(a);
	rep(i,0,n) {rep(j,0,n) cout<<a[i][j]<<" ";puts("");}
	puts("");
}

const int N=70;
int n,l[N],r[N],_,__;
ll A,B;
matrix base[N];

ll getlev(ll B) {
	matrix o(1,VL(n+2,0));
	o[0][1]=1;
	ll ans=0;
	per(i,0,60) {
		auto d=mul(o,base[i]);
		if (d[0][n+1]<B) o=d,ans+=(1ll<<i);
	}
	return ans;
}

void solve() {
	scanf("%d%lld%lld",&n,&A,&B);
	rep(i,1,n+1) scanf("%d",l+i);
	rep(i,1,n+1) scanf("%d",r+i);
	matrix f=unit(n+2,0);
	rep(i,1,n+1) {
		f[i][l[i]]++;
		f[i][r[i]]++;
		f[i][n+1]=1;
	}
	f[0][n+1]=1;
	f[n+1][n+1]=1;
	base[0]=f;
	rep(i,0,60) {
		base[i+1]=mul(base[i],base[i]);
		//printf("%d\n",i);
		//print(base[i]);
	}
	ll d=getlev(B);
	printf("%lld\n",d);
}

int main() {
	for (scanf("%d",&_);_;_--) {
		printf("Case #%d: ",++__);
		solve();
	}
}