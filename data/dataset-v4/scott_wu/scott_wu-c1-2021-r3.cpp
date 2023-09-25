#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXD = 10;
const int MAXN = 19;

int N;
string s;
int D[MAXD];
ll p10[MAXN];

ll figure_odd()
{
    ll ans = 0;
    for (int i = 1; i <= 9; i++)
    {
        if (D[i])
        {
            ans += i * p10[N/2];
            D[i]--;
            break;
        }
    }

    for (int i = N / 2 - 1; i >= 0; i--)
    {
        for (int j = 0; j <= 9; j++)
        {
            if (D[j])
            {
                ans += j * p10[i];
                D[j]--;
                break;
            }
        }
        for (int j = 9; j >= 0; j--)
        {
            if (D[j])
            {
                ans -= j * p10[i];
                D[j]--;
                break;
            }
        }
    }
    return ans;
}

ll res;

int d2[MAXD];

void clutchbox (int v)
{
    int nd = 0;
    for (int i = 0; i < 10; i++)
        nd += D[i];

    if (nd == 0)
    {
        res = 0;
        return;
    }

    ll ctot = 0;
    for (int i = 1 - v; i <= 9; i++)
        for (int j = i + 1; j <= 9; j++)
        {
            if (D[i] > 0 && D[j] > 0)
            {
                for (int k = 0; k < 10; k++)
                {
                    d2[k] = D[k];
                }

                d2[i]--;
                d2[j]--;
                ctot = (j - i) * p10[nd/2 - 1];
                if ((j - i - 1) * p10[nd/2 - 1] > res) continue;
                for (int k = nd / 2 - 2; k >= 0; k--)
                {
                    for (int l = 0; l < 10; l++)
                        if (d2[l])
                        {
                            ctot += l * p10[k];
                            d2[l]--;
                            break;
                        }
                    for (int l = 9; l >= 0; l--)
                        if (d2[l])
                        {
                            ctot -= l * p10[k];
                            d2[l]--;
                            break;
                        }
                }
                //cout << ctot << " " << i << " " << j << " " << nd << "\n";
                res = min (res, ctot);
            }
        }
}

void figure (int cdig, int v)
{
    if (cdig == -1)
    {
        clutchbox(v);
        return;
    }

    int dstart = D[cdig];
    figure (cdig - 1, v);
    if (cdig > 0 || v > 0)
    {
        while (D[cdig] >= 2)
        {
            D[cdig] -= 2;
            figure (cdig - 1, 1);
        }
    }
    D[cdig] = dstart;
}

void gogo()
{
    cin >> s;
    N = s.length();

    for (int i = 0; i < MAXD; i++)
        D[i] = 0;
    for (int i = 0; i < N; i++)
        D[s[i] - '0']++;

    if (N % 2 == 1)
    {
        cout << figure_odd() << "\n";
        return;
    }

    res = 2e18;
    figure (9, 0);
    cout << res << "\n";
}

int main()
{
    p10[0] = 1;
    for (int i = 1; i < MAXN; i++)
        p10[i] = 10 * p10[i-1];

    int T; cin >> T;

    for (int t = 0; t < T; t++)
    {
        cout << "Case #" << t + 1 << ": ";
        gogo();
    }
}