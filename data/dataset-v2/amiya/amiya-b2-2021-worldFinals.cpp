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
mt19937_64 mrand(random_device{}()); 
const ll mod=1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

const int N=301000;
typedef unsigned long long u64;
int n,m,q;
int u[N],v[N],l[N],r[N],o[N],op[N];
VI sq[N];
char e[10];
u64 in[N],out[N],ind[N],outd[N],ins[N],outs[N];

void solve() {
	scanf("%d%d%d",&n,&m,&q);
	u64 tin=0, tout=0;
	rep(i,1,n+1) {
		in[i]=mrand();
		out[i]=mrand();
		tin+=in[i];
		tout+=out[i];
	}
	map<PII,int> hse;
	map<u64,int> inid,outid;
	rep(i,1,n+1) {
		inid[in[i]]=i;
		outid[out[i]]=i;
	}
	rep(i,1,m+1) {
		scanf("%d%d",u+i,v+i);
		hse[mp(u[i],v[i])]=i;
	}
	rep(i,1,m+1) sq[i].clear();
	rep(i,0,q) {
		scanf("%s%d%d%d",e,l+i,r+i,o+i);
		if (e[0]=='E') op[i]=1;
		else op[i]=-1;
		sq[o[i]].pb(i);
	}
	rep(i,1,m+1) {
		ins[0]=outs[0]=0;
		for (int j=i,j_=1;j<=m;j+=i,j_++) {
			ins[j_]=ins[j_-1]+in[u[j]];
			outs[j_]=outs[j_-1]+out[v[j]];
		}
		for (auto x:sq[i]) {
			ind[x]=ins[r[x]/i]-ins[(l[x]-1)/i];
			outd[x]=outs[r[x]/i]-outs[(l[x]-1)/i];
		}
	}
	u64 pin=tin,pout=tout;
	rep(i,0,q) {
		if (op[i]==1) pin-=ind[i],pout-=outd[i];
		else pin+=ind[i],pout+=outd[i];
		///printf("%llu %llu\n",pin,pout);
		if (inid.count(pin)&&outid.count(pout)) {
			int u=inid[pin],v=outid[pout];
			if (hse.count(mp(u,v))) printf("%d ",hse[mp(u,v)]);
			else printf("X ");
		} else {
			printf("X ");
		}
	}
	puts("");
}

int _,__;
int main() {
	for (scanf("%d",&_);_;_--) {
		printf("Case #%d: ",++__);
		solve();
	}
}