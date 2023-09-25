#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXB = 60000;
const int MAXN = 300100;
const int P = 30;
const int MAXT = 1010;
const int BUCK = 300;

int B, S, N;
int X[MAXN], Y[MAXN];

bitset<MAXB> ps[P][MAXT];

map <pair <int, int>, int> mm;

void gogo()
{
    mm.clear();
    cin >> B >> S >> N;
    X[0] = Y[0] = 0;
    for (int i = 1; i <= S; i++)
    {
        cin >> X[i] >> Y[i];
        X[i]--, Y[i]--;
        Y[i] += B;

        mm[make_pair (X[i], Y[i])] = i;
    }

    // stuff
    for (int i = 1; i < P; i++)
    {
        bitset<MAXB> pcur;
        pcur.reset();
        ps[i][0].reset();
        for (int j = 0; j * i <= S; j++)
        {
            pcur.flip(X[j*i]);
            pcur.flip(Y[j*i]);
            if (j % BUCK == (BUCK - 1))
                ps[i][j/BUCK+1] = pcur;
        }
    }


    int ctot = 0;
    bitset<MAXB> pcur;
    for (int i = 0; i < N; i++)
    {
        char c;
        int l, r, m;
        cin >> c >> l >> r >> m;

        int nc = (r / m) - ((l - 1) / m);
        if (c == 'E') ctot += nc;
        else ctot -= nc;

        // stuff
        l = (l - 1) / m;
        r /= m;
        l++, r++;
        if (m >= P)
        {
            for (int x = l; x < r; x++)
            {
                pcur.flip(X[x*m]);
                pcur.flip(Y[x*m]);
            }
        }
        else
        {
            int v = (l / BUCK);
            pcur ^= ps[m][v];
            //cout << m << " " << v << endl;
            int v2 = (r / BUCK);
            pcur ^= ps[m][v2];
            //cout << m << " " << v2 << endl;

            for (int x = v * BUCK; x < l; x++)
            {
                pcur.flip(X[x*m]);
                pcur.flip(Y[x*m]);
            }
            for (int x = v2 * BUCK; x < r; x++)
            {
                pcur.flip(X[x*m]);
                pcur.flip(Y[x*m]);
            }
        }

        if (i) cout << " ";
        bool found = false;
        if (ctot == B - 1)
        {
            // stuff
            if (pcur.count() == 2 * (B - 1))
            {
                bitset<MAXB> bb = pcur;
                bb.flip();

                int x = bb._Find_first();
                bb.flip(x);
                int y = bb._Find_first();

                if (mm.find (make_pair (x, y)) != mm.end())
                {
                    found = true;
                    int res = mm[make_pair (x, y)];
                    cout << res;
                }
            }
        }
        if (!found) cout << "X";
    }
    cout << "\n";
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