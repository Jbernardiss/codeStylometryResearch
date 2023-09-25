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

const int N=1010000;
char S[N];
int d;
ll pw[50],dp[N][2],s[N],sm[N][2];
int _,__;

void solve() {
	scanf("%s%d",S+1,&d);
	int n=strlen(S+1);
	int p=1;
	while (d%2==0) p*=2,d/=2;
	while (d%5==0) p*=5,d/=5;
	ll pw_=1%d;
	s[n+1]=0;
	per(i,1,n+1) {
		s[i]=(s[i+1]+(S[i]-'0')*pw_)%d;
		pw_=pw_*10%d;
	}
	rep(i,0,d) sm[i][0]=sm[i][1]=0;
	int pos=0;
	dp[0][1]=1;
	dp[0][0]=0;
	ll t0=0,t1=0;
	pw[0]=1%p;
	rep(i,1,30) pw[i]=pw[i-1]*10%p;
	rep(i,1,n+1) {
		int z=0;
		dp[i][0]=dp[i][1]=0;
		per(j,0,i) {
			if (i-j<30) {
				z=(z+pw[i-1-j]*(S[j+1]-'0'))%p;
				if (s[j+1]==s[i+1]&&z%p==0) {
					//printf("zz %d %d\n",i,j);
					dp[i][1]=(dp[i][1]+dp[j][0]+dp[j][1])%mod;
				} else {
					dp[i][0]=(dp[i][0]+dp[j][1])%mod;
				}
			} else {
				while (pos<=j) {
					sm[s[pos+1]][0]=(sm[s[pos+1]][0]+dp[pos][0])%mod;
					sm[s[pos+1]][1]=(sm[s[pos+1]][1]+dp[pos][1])%mod;
					t0=(t0+dp[pos][0])%mod;
					t1=(t1+dp[pos][1])%mod;
					pos++;
				}
				if (z%p==0) {
					dp[i][1]=(dp[i][1]+sm[s[i+1]][0]+sm[s[i+1]][1])%mod;
					dp[i][0]=(dp[i][0]+t1+mod-sm[s[i+1]][1])%mod;
				} else {
					dp[i][0]=(dp[i][0]+t1)%mod;
				}
				break;
			}
		}
	}
	printf("%lld\n",(dp[n][0]+dp[n][1])%mod);
}

int main() {
	for (scanf("%d",&_);_;_--) {
		printf("Case #%d: ",++__);
		solve();
	}
}
