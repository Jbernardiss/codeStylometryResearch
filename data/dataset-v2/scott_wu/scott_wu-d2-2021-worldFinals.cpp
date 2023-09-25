#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXD = 1000100;
const int MAXN = 100100;
const int P = 20; // nback
const ll MOD = 1e9 + 7;

int N;
string S;
int dig[MAXN];

ll D;
ll p10[MAXN];
ll ps[MAXN];

int pcat[MAXN];
ll ans[MAXN][2];
ll dp[MAXD][2];
ll mtot;

void gogo()
{
    for (int i = 0; i < MAXD; i++)
    {
        dp[i][0] = dp[i][1] = 0;
    }

    cin >> S >> D;
    N = S.length();

    for (int i = 0; i < N; i++)
        dig[i] = (S[i] - '0');

    p10[0] = 1 % D;
    for (int i = 1; i < MAXN; i++)
        p10[i] = (p10[i-1] * 10) % D;

    ps[0] = 0;
    for (int i = 0; i < N; i++)
    {
        ps[i+1] = (ps[i] + p10[N-1-i] * dig[i]) % D;
    }

    ll dmult = 1;
    while (D % (dmult * 2) == 0)
        dmult *= 2;
    while (D % (dmult * 5) == 0)
        dmult *= 5;

    mtot = 0;
    for (int i = 0; i < MAXN; i++)
        ans[i][0] = ans[i][1] = 0;
    ans[0][1] = 1;
    pcat[0] = 0;

    for (int i = 0; i < N; i++)
    {
        if (i >= P)
        {
            int aloc = ps[i-P];
            dp[aloc][0] = (dp[aloc][0] + ans[i-P][0]) % MOD;
            dp[aloc][1] = (dp[aloc][1] + ans[i-P][1]) % MOD;
            mtot = (mtot + ans[i-P][1]) % MOD;
        }

        ll v = 0;
        for (int j = i; j >= 0 && j > i - P; j--)
        {
            v += (dig[j] * p10[i-j]);
            v %= D;

            if (v == 0)
            {
                ans[i+1][1] = (ans[i+1][1] + ans[j][1] + ans[j][0]) % MOD;
            }
            else
            {
                ans[i+1][0] = (ans[i+1][0] + ans[j][1]) % MOD;
            }
        }

        if (v % dmult != 0)
        {
            ans[i+1][0] = (ans[i+1][0] + mtot) % MOD;
        }
        else
        {
            ans[i+1][0] = (ans[i+1][0] + mtot) % MOD;
            ll rloc = ps[i+1];
            ans[i+1][0] = (ans[i+1][0] + MOD - dp[rloc][1]) % MOD;
            ans[i+1][1] = (ans[i+1][1] + dp[rloc][0] + dp[rloc][1]) % MOD;
        }
    }

    ll res = ans[N][0] + ans[N][1];
    res = (res % MOD + MOD) % MOD;
    cout << res << "\n";
}

int main()
{
    int T; cin >> T;

    for (int t = 0; t < T; t++)
    {
        cout << "Case #" << t + 1 << ": ";
        gogo();
    }
}