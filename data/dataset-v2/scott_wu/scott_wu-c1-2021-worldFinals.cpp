#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 110;

int T, N, W;
bool used[MAXN][2];
int ss[MAXN][MAXN];

void activate (int l, int r)
{
    used[l][0] = used[r][1] = true;
    for (int i = 0; i < 2 * N; i++)
        for (int j = 0; j < 2 * N; j++)
            if ((i < l) != (j < r))
                ss[i][j]++;
}

void answer (int l, int r)
{
    activate (l, r);

    cout << l + 1 << " " << r + 1 << endl;
    cout << flush;

    int x, y;
    cin >> x >> y;
    x--, y--;
    activate (x, y);
}

void gogo()
{
    for (int i = 0; i < MAXN; i++)
    {
        used[i][0] = used[i][1] = false;
        for (int j = 0; j < MAXN; j++)
            ss[i][j] = 0;
    }

    for (int r = 0; r < N; r++)
    {
        int ns = -1, ntie = -1;
        int nl = -1, nr = -1;
        int bval = -1;

        int nv = 0;
        int nleft = 2 * (N - r);
        for (int i = 0; i < 2 * N; i++)
        {
            if (used[i][0]) continue;
            int nt = 0;
            for (int j = 0; j < 2 * N; j++)
            {
                if (used[j][1]) continue;

                int tval = min (nv, nleft - nt - 1) + min (nt, nleft - nv - 1);
                int bv = min (min (nv, nleft - nt - 1), min (nt, nleft - nv - 1));
                bool win = false;
                if (ns < ss[i][j]) win = true;
                if (ns == ss[i][j])
                {
                    if (ntie % 2 > tval % 2) win = true;
                    if ((ntie % 2 == tval % 2) && tval < ntie) win = true;
                    //if (ntie == tval && bv < bval) win = true;
                }
                if (win)
                {
                    ns = ss[i][j];
                    ntie = tval;
                    nl = i;
                    nr = j;
                    bval = bv;
                }
                nt++;
            }

            nv++;
        }

        answer (nl, nr);
    }

    int x; cin >> x;
}

int main()
{
    cin >> T >> N >> W;

    for (int t = 0; t < T; t++)
    {
        gogo();
    }
}