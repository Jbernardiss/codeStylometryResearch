#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 32;
const int MAXL = 5;
const int MAXK = (1 << 16);
const int MAXT = 50;
const ll MOD = 1e9 + 7;

int L, N, M;
int D;

int win[MAXL][2][MAXK];

int arr[MAXN];
int cz[MAXN];
vector <int> lh, rh, bh;
int bloc[MAXN];

ll ans[MAXT];

ll cpow (ll b, int e)
{
    if (e == 0) return 1;
    if (e == 1) return b % MOD;

    ll v = cpow (b, e / 2);
    v = (v * v) % MOD;
    if (e & 1) v = (v * b) % MOD;
    return v;
}

ll inv (ll x)
{
    return cpow (x, MOD - 2);
}

int get_val (int c, ll bmask, ll lmask)
{
    int fm = 0;
    for (int i = 0; i < D / 2; i++)
    {
        fm *= 2;
        if (c == 0)
        {
            int x = bloc[arr[i]];
            if (x < MAXN)
            {
                if (bmask & (1 << x))
                    fm++;
            }
            else
            {
                if (lmask & (1 << (x - MAXN)))
                    fm++;
            }
        }
        else
        {
            int x = bloc[arr[i + D / 2]];
            if (x < MAXN)
            {
                if (bmask & (1 << x))
                    fm++;
            }
            else
            {
                if (lmask & (1 << (x - MAXN)))
                    fm++;
            }
        }
    }

    return win[L-1][0][fm];
}

ll figure (ll P)
{
    ll a = 0;
    ll pneg = (1 - P);
    pneg = (pneg % MOD + MOD) % MOD;
    for (int i = 0; i < (1 << bh.size()); i++)
    {
        ll res = 1;
        for (int j = 0; j < bh.size(); j++)
        {
            if (i & (1 << j))
                res = (res * P) % MOD;
            else
                res = (res * pneg) % MOD;
        }

        ll lres = 0, rres = 0;
        for (int j = 0; j < (1 << lh.size()); j++)
        {
            ll cp = 1;
            for (int k = 0; k < lh.size(); k++)
            {
                if (j & (1 << k))
                {
                    cp = (cp * P) % MOD;
                }
                else
                    cp = (cp * pneg) % MOD;
            }

            if (get_val (0, i, j))
                lres = (lres + cp) % MOD;
        }
        for (int j = 0; j < (1 << rh.size()); j++)
        {
            ll cp = 1;
            for (int k = 0; k < rh.size(); k++)
            {
                if (j & (1 << k))
                {
                    cp = (cp * P) % MOD;
                }
                else
                    cp = (cp * pneg) % MOD;
            }

            if (get_val (1, i, j))
                rres = (rres + cp) % MOD;
        }

        //cout << res << " " << lres << " " << rres << "\n";

        ll v = (1 - lres) * (1 - rres);
        v = (v % MOD + MOD) % MOD;
        v = (1 - v);
        v = (v * res) % MOD;
        v = (v % MOD + MOD) % MOD;
        a = (a + v) % MOD;
    }

    //cout << "done " << a << "\n";
    return a;
}

void gogo()
{
    for (int i = 0; i < MAXN; i++)
        arr[i] = cz[i] = 0;
    lh.clear();
    rh.clear();
    bh.clear();

    cin >> N >> M >> L;
    D = (1 << L);
    for (int i = 0; i < D; i++)
    {
        cin >> arr[i];
        arr[i]--;
        if (i < D / 2)
            cz[arr[i]] |= 1;
        else
            cz[arr[i]] |= 2;
    }

    for (int i = 0; i < N; i++)
    {
        if (cz[i] == 1)
            lh.push_back(i);
        else if (cz[i] == 2)
            rh.push_back(i);
        else if (cz[i] == 3)
            bh.push_back(i);
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < bh.size(); j++)
            if (bh[j] == i)
                bloc[i] = j;

        for (int j = 0; j < lh.size(); j++)
            if (lh[j] == i)
                bloc[i] = j + MAXN;
        for (int j = 0; j < rh.size(); j++)
            if (rh[j] == i)
                bloc[i] = j + MAXN;
    }
    /*for (int i = 0; i < N; i++)
        cout << bloc[i] << " ";
    cout << "\n";*/

    for (int i = 0; i < min (MAXT, M); i++)
    {
        ll P = 1 - i * inv (M);
        P = (P % MOD + MOD) % MOD;
        ans[i] = figure (P);
    }

    ll res = 0;
    if (M <= MAXT)
    {
        for (int i = 0; i < M; i++)
        {
            res = (res + ans[i]);
            res %= MOD;
        }
        res = (res % MOD + MOD) % MOD;
    }
    else
    {
        for (int i = 1; i < MAXT; i++)
        {
            ans[i] = (ans[i-1] + ans[i]) % MOD;
        }
        // find M-1 here

        ll G = M - 1;
        for (int i = 0; i < MAXT; i++)
        {
            ll ct = 1;
            for (int j = 0; j < MAXT; j++)
            {
                if (j == i) continue;
                ct = ((ct * (G - j)) % MOD * inv (i - j)) % MOD;
            }
            ct = (ct * ans[i]) % MOD;
            res = (res + ct) % MOD;
        }
        res = (res % MOD + MOD) % MOD;
    }

    for (int i = 0; i < N; i++)
    {
        res = (res * M) % MOD;
    }
    cout << res << "\n";
}

int main()
{
    win[0][0][0] = win[0][1][0] = 0;
    win[0][0][1] = win[0][1][1] = 1;

    for (int i = 1; i < MAXL; i++)
    {
        int ptot = (1 << (1 << i));
        int phalf = (1 << (1 << (i - 1)));
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < ptot; k++)
            {
                int v = win[i-1][1-j][k % phalf];
                int v2 = win[i-1][1-j][k / phalf];

                if (j)
                    win[i][j][k] = max (v, v2);
                else
                    win[i][j][k] = min (v, v2);
            }
        }
    }
    int T; cin >> T;

    for (int t = 0; t < T; t++)
    {
        cout << "Case #" << t + 1 << ": ";
        gogo();
    }
}