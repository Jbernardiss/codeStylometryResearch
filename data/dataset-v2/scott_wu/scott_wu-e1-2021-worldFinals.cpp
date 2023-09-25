#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 110;
const int MAXL = 61;
const ll MV = 1.1e18;

ll A, B;

int N;
int nv[MAXN][2];

ll mat[MAXL][MAXN][MAXN];

ll ccur[MAXN], ncur[MAXN];

void gogo()
{
    cin >> N >> A >> B;
    for (int i = 1; i <= N; i++)
        cin >> nv[i][0];
    for (int i = 1; i <= N; i++)
        cin >> nv[i][1];
    nv[0][0] = nv[0][1] = -1;

    for (int i = 0; i < MAXL; i++)
        for (int j = 0; j < MAXN; j++)
            for (int k = 0; k < MAXN; k++)
                mat[i][j][k] = 0;

    N++;
    for (int i = N; i < 2 * N; i++)
    {
        mat[0][i-N][i] = 1;
        mat[0][i][i] = 1;
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (nv[i][j] == -1) continue;
            mat[0][i][nv[i][j]]++;
        }
    }

    for (int i = 0; i + 1 < MAXL; i++)
    {
        for (int j = 0; j < 2 * N; j++)
            for (int k = 0; k < 2 * N; k++)
            {
                if (!mat[i][j][k]) continue;
                for (int l = 0; l < 2 * N; l++)
                {
                    if (!mat[i][k][l]) continue;

                    if (MV / mat[i][j][k] < mat[i][k][l])
                        mat[i+1][j][l] = MV;
                    else
                    {
                        mat[i+1][j][l] += mat[i][j][k] * mat[i][k][l];
                        if (mat[i+1][j][l] > MV) mat[i+1][j][l] = MV;
                    }
                }
            }
    }

    ll res = 0;
    for (int i = 0; i < MAXN; i++)
        ccur[i] = ncur[i] = 0;
    ccur[1] = 1;

    for (int i = MAXL - 1; i >= 0; i--)
    {
        for (int j = 0; j < MAXN; j++)
            ncur[j] = 0;

        bool bad = false;
        for (int j = 0; j < 2 * N; j++)
        {
            if (!ccur[j]) continue;
            for (int k = 0; k < 2 * N; k++)
            {
                if (MV / ccur[j] < mat[i][j][k]) bad = true;
                else
                {
                    ncur[k] += ccur[j] * mat[i][j][k];
                    if (ncur[k] > MV) ncur[k] = MV;
                }
            }
        }
        ll ctot = 0;
        for (int j = 0; j < 2 * N; j++)
        {
            ctot += ncur[j];
            if (ctot >= B) bad = true;
        }
        if (bad || ctot >= B)
        {
            continue;
        }
        else
        {
            for (int j = 0; j < 2 * N; j++)
                ccur[j] = ncur[j];
            res += (1LL << i);
        }
    }
    res++;
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