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
mt19937_64 mrand(1);
const ll mod=1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

const int N=110;
bool visa[N],visb[N];
int fa[N],fb[N];
int score[N][N];
//int n=50;
PII v[N*N];
int T,n,W;

int check(VI a,VI b) {
	rep(i,0,2*n) visa[i]=visb[i]=0;
	rep(i,0,2*n) rep(j,0,2*n) score[i][j]=0;
	int msco=0,ans=0;
	auto sett=[&](int pa,int pb) {
		assert(pa>=0&&pa<2*n&&pb>=0&&pb<2*n);
		//printf("gg %d %d\n",pa,pb);
		assert(!visa[pa]&&!visb[pb]);
		msco=0;
		visa[pa]=visb[pb]=1;
		//printf("sett %d %d\n",pa,pb);
		rep(i,0,2*n) rep(j,0,2*n) if (!visa[i]&&!visb[j]) {
			if ((i<pa)!=(j<pb)) {
				score[i][j]+=1;
			}
			msco=max(msco,score[i][j]);
		}
	};
	PII u;
	rep(R,0,n) {
		int pa=-1,pb=-1;
		if (R==0){
			pa=0; pb=0;
		} else {
			if (u.fi==u.se) {
				int rs=-1;
				rep(i,0,2*n) if (!visa[i]&&!visb[i]&&score[i][i]>rs) {
					rs=score[i][i];
					pa=pb=i;
				}
			} else {
				pa=u.se; pb=u.fi;
			}
		}
		ans+=score[pa][pb];
		//printf("%d\n",ans);
		sett(pa,pb);
		int t=0;
		rep(i,0,2*n) rep(j,0,2*n) if (!visa[i]&&!visb[j]&&score[i][j]==msco) {
			v[t++]=mp(i,j);
		}
		u=v[rnd(t)];
		ans-=score[u.fi][u.se];
		sett(u.fi,u.se);
		//printf("%d %d %d\n",R,msco,ans);
	}
	return ans;
}

//int c=0;
void solve() {
	rep(i,0,2*n) visa[i]=visb[i]=0;
	rep(i,0,2*n) rep(j,0,2*n) score[i][j]=0;
	int msco=0,ans=0;
	auto sett=[&](int pa,int pb) {
		assert(pa>=0&&pa<2*n&&pb>=0&&pb<2*n);
		assert(!visa[pa]&&!visb[pb]);
		msco=0;
		visa[pa]=visb[pb]=1;
		rep(i,0,2*n) rep(j,0,2*n) if (!visa[i]&&!visb[j]) {
			if ((i<pa)!=(j<pb)) {
				score[i][j]+=1;
			}
			msco=max(msco,score[i][j]);
		}
	};
	PII u;
	rep(R,0,n) {
		int pa=-1,pb=-1;
		if (R==0){
			pa=0; pb=0;
		} else {
			if (u.fi==u.se) {
				int rs=-1;
				rep(i,0,2*n) if (!visa[i]&&!visb[i]&&score[i][i]>rs) {
					rs=score[i][i];
					pa=pb=i;
				}
			} else {
				pa=u.se; pb=u.fi;
			}
		}
		printf("%d %d\n",pa+1,pb+1);
		fflush(stdout);
		sett(pa,pb);
		scanf("%d%d",&u.fi,&u.se);
		--u.fi; --u.se;
		sett(u.fi,u.se);
	}
	scanf("%*d");
}

int main() {
/*	VI v1,v2;
	rep(i,0,2*n) v1.pb(i),v2.pb(i);
	reverse(all(v2));
	rep(i,0,1000) {
		//printf("%d\n",check(v1,v2));
		c+=check(v1,v2)>0;
	}
	printf("%d\n",c);*/
	scanf("%d%d%d",&T,&n,&W);
	rep(i,0,T) {
		solve();
	}
}