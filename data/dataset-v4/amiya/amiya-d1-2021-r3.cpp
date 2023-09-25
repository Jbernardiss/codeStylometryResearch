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

int dp[17][(1<<16)+10][2];
ll cc[50][2],cL[50][2],cR[50][2],ret[50][2],z[55];
int ap[50],val[50],a[50];
int _,__,n,m,l,mid;
void dfs2(int u,int st,int cnt1) {
	if (u==n+1) {
		if (st==1) {
			int s=0;
			rep(i,0,mid) s|=(val[a[i]]<<i);
			//printf("zz %d %d\n",mid,s);
			cc[cnt1][dp[mid][s][1]]++;
		} else {
			int s=0;
			rep(i,0,mid) s|=(val[a[i+mid]]<<i);
			cc[cnt1][dp[mid][s][1]]++;
		}
	} else {
		if (ap[u]==st) {
			val[u]=0;
			dfs2(u+1,st,cnt1);
			val[u]=1;
			dfs2(u+1,st,cnt1+1);
		} else {
			dfs2(u+1,st,cnt1);
		}
	}
}

void dfs(int u,int cnt1) {
	if (u==n+1) {
		rep(i,0,n+1) rep(j,0,2) cc[i][j]=0;
		dfs2(1,1,0);
		rep(i,0,n+1) rep(j,0,2) cL[i][j]=cc[i][j],cc[i][j]=0;
		dfs2(1,2,0);
		rep(i,0,n+1) rep(j,0,2) cR[i][j]=cc[i][j];
		rep(vl,0,n+1) rep(rl,0,2) rep(vr,0,n+1) rep(rr,0,2) if (cL[vl][rl]&&cR[vr][rr]) {
			assert(vl+vr+cnt1<=n);
			(ret[vl+vr+cnt1][max(rl,rr)]+=cL[vl][rl]*cR[vr][rr])%=mod;
		}
	} else {
		if (ap[u]==3) {
			val[u]=0;
			dfs(u+1,cnt1);
			val[u]=1;
			dfs(u+1,cnt1+1);
		} else {
			dfs(u+1,cnt1);
		}
	}
}

void precalc(int m,int ty) {
	// bob 最小
	if (m==1) {
		rep(i,0,2) dp[m][i][ty]=i;
		return;
	}
	precalc(m/2,ty^1);
	rep(i,0,(1<<m)) {
		int L=i>>(m/2),R=i-(L<<(m/2));
		assert(R<1<<(m/2));
		if (ty==1) {
			dp[m][i][ty]=min(dp[m/2][L][ty^1],dp[m/2][R][ty^1]);
		} else {
			dp[m][i][ty]=max(dp[m/2][L][ty^1],dp[m/2][R][ty^1]);
		}
	}
	/*if (m==4) {
		rep(i,0,(1<<m)) printf("%d %d %d %d\n",m,i,ty,dp[m][i][ty]);
	}*/
}


namespace polysum {
	const int D=101000;
	ll a[D],f[D],g[D],p[D],p1[D],p2[D],b[D],h[D][2],C[D];
	ll calcn(int d,ll *a,ll n) {
		if (n<=d) return a[n];
		p1[0]=p2[0]=1;
		rep(i,0,d+1) {
			ll t=(n-i+mod)%mod;
			p1[i+1]=p1[i]*t%mod;
		}
		rep(i,0,d+1) {
			ll t=(n-d+i+mod)%mod;
			p2[i+1]=p2[i]*t%mod;
		}
		ll ans=0;
		rep(i,0,d+1) {
			ll t=g[i]*g[d-i]%mod*p1[i]%mod*p2[d-i]%mod*a[i]%mod;
			if ((d-i)&1) ans=(ans-t+mod)%mod;
			else ans=(ans+t)%mod;
		}
		return ans;
	}
	void init(int M) {
		f[0]=f[1]=g[0]=g[1]=1;
		rep(i,2,M+5) f[i]=f[i-1]*i%mod;
		g[M+4]=powmod(f[M+4],mod-2);
		per(i,1,M+4) g[i]=g[i+1]*(i+1)%mod;
	}
	ll polysum(ll n,ll *a,ll m) { // a[0].. a[m] \sum_{i=0}^{n-1} a[i]
		a[m+1]=calcn(m,a,m+1);
		rep(i,1,m+2) a[i]=(a[i-1]+a[i])%mod;
		return calcn(m+1,a,n-1);
	}
	ll qpolysum(ll R,ll n,ll *a,ll m) { // a[0].. a[m] \sum_{i=0}^{n-1} a[i]*R^i
		if (R==1) return polysum(n,a,m);
		a[m+1]=calcn(m,a,m+1);
		ll r=powmod(R,mod-2),p3=0,p4=0,c,ans;
		h[0][0]=0;h[0][1]=1;
		rep(i,1,m+2) {
			h[i][0]=(h[i-1][0]+a[i-1])*r%mod;
			h[i][1]=h[i-1][1]*r%mod;
		}
		rep(i,0,m+2) {
			ll t=g[i]*g[m+1-i]%mod;
			if (i&1) p3=((p3-h[i][0]*t)%mod+mod)%mod,p4=((p4-h[i][1]*t)%mod+mod)%mod;
			else p3=(p3+h[i][0]*t)%mod,p4=(p4+h[i][1]*t)%mod;
		}
		c=powmod(p4,mod-2)*(mod-p3)%mod;
		rep(i,0,m+2) h[i][0]=(h[i][0]+h[i][1]*c)%mod;
		rep(i,0,m+2) C[i]=h[i][0];
		ans=(calcn(m,C,n)*powmod(R,n)-c)%mod;
		if (ans<0) ans+=mod;
		return ans;
	}
}


void solve() {
	scanf("%d%d%d",&n,&m,&l);
	rep(i,0,(1<<l)) scanf("%d",a+i);
	mid=(1<<l)/2;
	rep(i,1,n+1) ap[i]=0;
	rep(i,0,(1<<l)) {
		if (i<mid) ap[a[i]]|=1;
		if (i>=mid) ap[a[i]]|=2;
	}
	rep(i,0,n+1) rep(j,0,2) ret[i][j]=0;
	dfs(1,0);
	int o=0;
	rep(i,0,n+1) if (ap[i]!=0) o++;
	//rep(i,0,n+1) rep(j,0,2) printf("%d %d %lld\n",i,j,ret[i][j]);
	for (int i=0;i<=n+1;i++) {
		z[i]=0;
		rep(k,0,o+1) z[i]=(z[i]+powmod(m-i,k)*powmod(i,o-k)%mod*ret[k][1])%mod;
		//printf("zz %d %lld\n",i,z[i]);
	}
	printf("%lld\n",polysum::polysum(m,z,o)*powmod(m,n-o)%mod);
}

int main() {
	precalc(16,0);
	precalc(16,1);
	polysum::init(100);
	for (scanf("%d",&_);_;_--) {
		printf("Case #%d: ",++__);
		solve();
	}
}