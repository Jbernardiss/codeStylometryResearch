//#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

/*** START OF TEMPLATE CODE ***/

typedef vector<string> vs;
typedef long long ll;
typedef complex<double> pnt;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define RA(x) begin(x), end(x)
#define FE(i, x) for (auto i = begin(x); i != end(x); ++i)
#define SZ(x) ((ll) (x).size())

template<class T>
vector<T> splitstr(const string &s)
{
    istringstream in(s);
    vector<T> out;
    copy(istream_iterator<T>(in), istream_iterator<T>(), back_inserter(out));
    return out;
}

static void solve_case(int cas);

int main(int argc, char * const *argv)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    struct rlimit stack_limit;
    getrlimit(RLIMIT_STACK, &stack_limit);
    stack_limit.rlim_cur = 1024 * 1024 * 1024;
    setrlimit(RLIMIT_STACK, &stack_limit);

    if (argc >= 2)
    {
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) { perror(argv[1]); exit(1); }
        if (-1 == dup2(fd, 0)) { perror(argv[1]); exit(1); }
        if (-1 == close(fd)) { perror(argv[1]); exit(1); }
    }
    if (argc >= 3)
    {
        int fd = open(argv[2], O_WRONLY | O_CREAT, 0666);
        if (fd == -1) { perror(argv[2]); exit(1); }
        if (-1 == dup2(fd, 1)) { perror(argv[2]); exit(1); }
        if (-1 == close(fd)) { perror(argv[2]); exit(1); }
    }
    cin.exceptions(ios::failbit | ios::badbit);

    int cases;
    cin >> cases;
    for (int cas = 1; cas <= cases; cas++)
        solve_case(cas);
    return 0;
}

/*** END OF TEMPLATE CODE ***/


// Undefined sign for negative inputs
template<typename T> static constexpr T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }
template<typename T> static constexpr T wrap_pos(T a, T m) { return a < 0 ? a + m : a; }
template<typename T> static constexpr T sqr(T a) { return a * a; }
// m must be positive
template<typename T> static constexpr T mod(T a, T m) { return wrap_pos(a % m, m); }

template<typename T>
static constexpr T inverse2(T a, T m) { return a <= 1 ? a : mod((1 - inverse2(m % a, a) * m) / a, m); }

// a must be relatively prime to m, m > 0
template<typename T>
static constexpr T inverse(T a, T m) { return inverse2(mod(a, m), m); }

template<typename T, typename P>
static constexpr T power(T a, P b) { return b == 0 ? T(1) : (b % 2) ? power(a, b - 1) * a : sqr(power(a, b / 2)); }

template<typename T, typename C, T Modulus>
class MR
{
private:
    struct tag_plus {}; // indicates value is in range [0, 2 * Modulus)
    struct tag_minus {}; // indicates value is in range (-Modulus, Modulus)
    struct tag_good {}; // indicates value is in range

    T value;

    static_assert(std::numeric_limits<C>::max() / Modulus / Modulus > 0, "compute type is too small");
    static_assert(Modulus < std::numeric_limits<T>::max() / 2, "storage type is too small");

    static constexpr T reduce(T value, tag_plus)
    {
        return value >= Modulus ? value - Modulus : value;
    }

    static constexpr T reduce(T value, tag_minus)
    {
        return value < 0 ? value + Modulus : value;
    }

    static constexpr T reduce(T value, tag_good) { return value; }

    static constexpr T multiply(T a, T b)
    {
        using UC = typename std::make_unsigned<C>::type;
        return UC(a) * UC(b) % Modulus;
    }

public:
    typedef T value_type;
    typedef C compute_type;
    static constexpr T modulus = Modulus;

    constexpr MR() : value(0) {}
    constexpr MR(C value) : value(reduce(value % Modulus, tag_minus())) {}
    template<typename tag_t>
    constexpr MR(T value, tag_t tag) : value(reduce(value, tag)) {}

    MR &operator=(C value) { this->value = reduce(value % Modulus, tag_minus()); return *this; }

    constexpr MR operator +(MR b) const { return MR(value + b.value, tag_plus()); }
    constexpr MR operator -(MR b) const { return MR(value - b.value, tag_minus()); }
    constexpr MR operator *(MR b) const { return MR(multiply(value, b.value), tag_good()); }
    constexpr MR operator -() const { return MR(-value, tag_minus()); }

    MR &operator +=(MR b) { value = reduce(value + b.value, tag_plus()); return *this; }
    MR &operator -=(MR b) { value = reduce(value - b.value, tag_minus()); return *this; }
    MR &operator *=(MR b) { value = multiply(value, b.value); return *this; }

    constexpr bool operator==(MR b) const { return value == b.value; }
    constexpr bool operator!=(MR b) const { return value != b.value; }

    constexpr T get() const { return value; }

    // These are only valid if the dividend is relatively prime to the modulus
    constexpr MR inverse() const
    {
        return MR(::inverse(C(value), C(Modulus)), tag_good());
    }
    constexpr MR operator /(MR b) const { return *this * b.inverse(); }
    MR &operator /=(MR b) { return *this *= b.inverse(); }
};

template<typename T, typename C, T Modulus>
static inline std::ostream &operator<<(std::ostream &o, MR<T, C, Modulus> mr)
{
    return o << mr.get();
}

typedef MR<int, ll, 1000000007> mr;


static void solve_case(int cas)
{
    string S;
    int D;
    cin >> S >> D;
    int N = SZ(S);
    mr ans;
    if (D == 1)
    {
        ans = power(mr(2), N - 1);
    }
    else
    {
        int Dz = D;
        int D25 = 1;
        while (Dz % 2 == 0)
        {
            Dz /= 2;
            D25 *= 2;
        }
        while (Dz % 5 == 0)
        {
            Dz /= 5;
            D25 *= 5;
        }
        vector<int> lastD(Dz, -1);

        vi cmod(N + 1);
        cmod[N] = 0;
        int p10 = 1;
        for (int i = N - 1; i >= 0; i--)
        {
            cmod[i] = (cmod[i + 1] + p10 * (S[i] - '0')) % Dz;
            p10 = p10 * 10 % Dz;
        }

        constexpr int window = 22;

        auto check25 = [&](int p) -> bool
        {
            int cur = 0;
            for (int i = max(0, p - window); i < p; i++)
                cur = (cur * 10 + (S[i] - '0')) % D25;
            return cur == 0;
        };

        vector<mr> dpg(N + 1), dpb(N + 1);
        dpg[N] = dpb[N] = 1;
        vector<mr> dpgs(N + 1), dpgbs(N + 1);
        dpgs[N] = 1;
        mr dpb_tot = 1;
        for (int i = N - 1; i >= 0; i--)
        {
            dpg[i] += dpb_tot;

            int j = i + 1;
            int v = (S[i] - '0') % D;
            while (j - i <= window && j < N && v != 0)
            {
                v = (v * 10 + (S[j] - '0')) % D;
                j++;
            }
            if (v != 0)
            {
                j = lastD[cmod[i]];
                if (j != -1)
                    v = 0;
            }

            if (i + window <= N && check25(i + window))
                lastD[cmod[i + window]] = i + window;

            if (v == 0)
            {
                dpg[i] += dpgbs[j];
                dpb[i] += dpgs[j];
                dpgs[i] = dpgs[j];
                dpgbs[i] = dpgbs[j];
            }
            dpgs[i] += dpg[i];
            dpgbs[i] += dpg[i] - dpb[i];
            dpb_tot += dpb[i];
        }
        ans = dpg[0];
    }
    cout << "Case #" << cas << ": " << ans << "\n";
}
