#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 22;

int R, C;
int a[MAXN], b[MAXN];

pair <int, int> pp[MAXN];

int v[MAXN][MAXN];

string poss = "POSSIBLE";
string imp = "IMPOSSIBLE";

bool run()
{
    bool found = false;
    for (int len = 1; len * 2 <= min (R, C); len++)
    {
        for (int i = 0; i <= R - 2 * len; i++)
        {
            for (int j = 0; j <= C - 2 * len; j++)
            {
                bool bad = false;
                for (int k = 0; k < len; k++)
                {
                    if (v[i+k][j+len-1-k] != 1) bad = true;
                    if (v[i+k][j+len+k] != 0) bad = true;
                    if (v[i+len+k][j+k] != 0) bad = true;
                    if (v[i+len+k][j+2*len-1-k] != 1) bad = true;
                    if (bad) break;
                }

                if (!bad)
                {
                    found = true;
                    for (int k = 0; k < len; k++)
                    {
                        v[i+k][j+len-1-k] = 0;
                        v[i+k][j+len+k] = 1;
                        v[i+len+k][j+k] = 1;
                        v[i+len+k][j+2*len-1-k] = 0;
                    }
                }
            }
        }
    }
    return found;
}

void gogo()
{
    cin >> R >> C;
    for (int i = 0; i < R; i++)
        cin >> a[i];
    for (int i = 0; i < C; i++)
        cin >> b[i];

    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            v[i][j] = 0;

    bool bad = false;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
            pp[j] = make_pair (b[j], j);
        sort (pp, pp + C);
        reverse (pp, pp + C);

        for (int j = 0; j < a[i]; j++)
        {
            if (!pp[j].first)
            {
                bad = true;
                break;
            }
            v[i][pp[j].second] = 1;
            b[pp[j].second]--;
        }
    }

    for (int i = 0; i < C; i++)
        if (b[i]) bad = true;

    if (bad)
    {
        cout << imp << "\n";
        return;
    }

    while (true)
    {
        if (!run()) break;
    }

    cout << "POSSIBLE\n";
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (v[i][j]) cout << "/";
            else cout << "\\";
        }
        cout << "\n";
    }
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