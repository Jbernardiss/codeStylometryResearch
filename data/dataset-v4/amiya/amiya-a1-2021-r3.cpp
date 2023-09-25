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

const int N=50;
char s[N];
int cnt[N];
int _,__,d;
ll ans,pw[40];
bool check() {
	if (d==0) return 1;
	int spr=0;
	for (int i=0;i<=9;i++) spr+=cnt[i]/2;
	if (spr<d) return 0;
	if (spr==cnt[0]/2) return 0;
	return 1;
}

void gao(int dig,ll dif) {
	if (dig==-1) {
		ans=min(ans,dif);
	} else {
		per(j,0,10) {
			for (int i=0;i+j<=9;i++) if (cnt[i]&&cnt[i+j]) {
				cnt[i]--;
				cnt[i+j]--;
				if (check()) {
					gao(dig-1,dif-j*pw[dig]);
					cnt[i]++;
					cnt[i+j]++;
					return;
				}
				cnt[i]++;
				cnt[i+j]++;
			}
		}
	}
}

void solve() {
	scanf("%s",s);
	for (int i=0;i<=9;i++) cnt[i]=0;
	int n=strlen(s);
	for (int i=0;i<n;i++) cnt[s[i]-'0']++;
	if (n%2==1) {
		ll s1=0,s2=0;
		for (int i=n/2;i>=0;i--) {
			rep(j,0,10) if (cnt[j]) {
				if (j==0&&i==n/2) continue;
				cnt[j]--;
				s1+=j*pw[i];
				break;
			}
		}
		for (int i=n/2-1;i>=0;i--) {
			per(j,0,10) if (cnt[j]) {
				if (j==0&&i==n/2-1) continue;
				cnt[j]--;
				s2+=j*pw[i];
				break;
			}
		}
		printf("%lld\n",s1-s2);
	} else {
		ans=1000000000000000000ll;
		bool sm=1;
		for (int i=0;i<10;i++) sm&=cnt[i]%2==0;
		if (sm) ans=0;
		for (int m=0;m<n/2;m++) {
			for (int i=0;i<=9;i++) for (int j=i+1;j<=9;j++) if (cnt[i]&&cnt[j]) {
				if (m==n/2-1&&i==0) continue;
				cnt[i]--;
				cnt[j]--;
				d=n/2-m-1;
				if (check()) gao(m-1,(j-i)*pw[m]);
				cnt[i]++;
				cnt[j]++;
			}
		}
		printf("%lld\n",ans);
	}
}

int main() {
	pw[0]=1;
	for (int i=1;i<=18;i++) pw[i]=pw[i-1]*10;
	for (scanf("%d",&_);_;_--) {
		printf("Case #%d: ",++__);
		solve();
	}
}