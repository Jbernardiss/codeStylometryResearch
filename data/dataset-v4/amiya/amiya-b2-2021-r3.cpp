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

const int inf=0x20202020;
typedef int flowt;
namespace flow {
	const int M=100000,N=1000;
	int y[M],nxt[M],gap[N],fst[N],c[N],pre[N],q[N],dis[N];
	flowt f[M];
	int S,T,tot,Tn;
	void init(int s,int t,int tn) {
		tot=1; assert(tn<N);
		rep(i,0,tn) fst[i]=0;
		S=s;T=t;Tn=tn;
	}
	void add(int u,int v,flowt c1,flowt c2=0) {
		tot++;y[tot]=v;f[tot]=c1;nxt[tot]=fst[u];fst[u]=tot;
		tot++;y[tot]=u;f[tot]=c2;nxt[tot]=fst[v];fst[v]=tot;
	}
	flowt sap() {
		int u=S,t=1;flowt flow=0;
		rep(i,0,Tn) c[i]=fst[i],dis[i]=Tn,gap[i]=0;
		q[0]=T;dis[T]=0;pre[S]=0;
		rep(i,0,t) {
			int u=q[i];
			for (int j=fst[u];j;j=nxt[j]) if (dis[y[j]]>dis[u]+1&&f[j^1]) 
				q[t++]=y[j],dis[y[j]]=dis[u]+1;
		}
		rep(i,0,Tn) gap[dis[i]]++;
		while (dis[S]<=Tn) {
			while (c[u]&&(!f[c[u]]||dis[y[c[u]]]+1!=dis[u])) c[u]=nxt[c[u]];
			if (c[u]) {
				pre[y[c[u]]]=c[u]^1;
				u=y[c[u]];
				if (u==T) {
					flowt minf=inf;
					for (int p=pre[T];p;p=pre[y[p]]) minf=min(minf,f[p^1]);
					for (int p=pre[T];p;p=pre[y[p]]) f[p^1]-=minf,f[p]+=minf;
					flow+=minf;u=S;
				}
			} else {
				if (!(--gap[dis[u]])) break;
				int mind=Tn;
				c[u]=fst[u];
				for (int j=fst[u];j;j=nxt[j]) if (f[j]&&dis[y[j]]<mind) 
					mind=dis[y[j]],c[u]=j;
				dis[u]=mind+1;
				gap[dis[u]]++;
				if (u!=S) u=y[pre[u]];
			}
		}
		return flow;
	}
};

const int N=50;
int n,m,r[N],c[N],g[N][N],_,__;
char t[N][N];
void solve() {
	scanf("%d%d",&n,&m);
	rep(i,0,n) scanf("%d",r+i);
	rep(i,0,m) scanf("%d",c+i);
	flow::init(n+m,n+m+1,n+m+2);
	int s=0,tt=0;
	rep(i,0,n) flow::add(n+m,i,r[i]),s+=r[i];
	rep(i,0,m) flow::add(i+n,n+m+1,c[i]),tt+=c[i];
	if (s!=tt) {
		puts("IMPOSSIBLE");
		return;
	}
	rep(i,0,n) rep(j,0,m) {
		g[i][j]=flow::tot+1;
		flow::add(i,j+n,1);
	}
	int z=flow::sap();
	if (s!=z) {
		puts("IMPOSSIBLE");
		return;
	}
	rep(i,0,n) rep(j,0,m) {
		t[i][j]=flow::f[g[i][j]]?'\\':'/';
	}
	while (1) {
		bool alive=0;
		rep(i,0,n-1) {
			vector<PII> adj;
			VI pos;
			int c1=0,c2=0;
			rep(j,0,m) {
				if (t[i][j]==t[i+1][j]) continue;
				pos.pb(j);
				if (t[i][j]=='/'&&t[i+1][j]=='\\') {
					c1++;
					adj.pb({1,j});
				} else {
					c2++;
					adj.pb({0,j});
				}
			}
			auto dd=adj;
			sort(all(adj));
			sort(all(pos));
			if (adj!=dd) {
				alive=1;
				rep(j,0,c2) {
					int x=pos[j];
					t[i][x]='\\'; t[i+1][x]='/';
				}
				rep(j,c2,c1+c2) {
					int x=pos[j];
					t[i][x]='/'; t[i+1][x]='\\';
				}
			}
		}
		if (!alive) break;
	}
	puts("POSSIBLE");
	rep(i,0,n) {
		rep(j,0,m) printf("%c",t[i][j]);
		puts("");
	}
}

int main() {
	for (scanf("%d",&_);_;_--) {
		printf("Case #%d: ",++__);
		solve();
	}
}
