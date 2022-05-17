// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;
template <typename T, size_t SZ>
using ar = array<T, SZ>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; // 998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out()
{
    cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda
{
    template <typename Fun>
    struct y_combinator_result
    {
        Fun fun_;
        template <typename T>
        explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
        template <typename... Args>
        decltype(auto) operator()(Args &&...args)
        {
            return fun_(ref(*this), forward<Args>(args)...);
        }
    };
    template <typename Fun>
    decltype(auto) y_combinator(Fun &&fun)
    {
        return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
    }
};

void setIO(string s) // USACO
{
#ifndef LOCAL
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
#endif
}

int n, mod;
const int N = 3010;
ll dp[N][N];
ll pref[N][N];

void solve()
{
    cin >> n >> mod;
    FOR(i, 1, n + 1)
    {
        if (i >= 1000)
            dp[i][5]++;
        else if (i >= 100)
            dp[i][4]++;
        else if (i >= 10)
            dp[i][3]++;
        else
            dp[i][2]++;
        FOR(j, 1, n)
        {
            if (i > 1 && j >= 2)
            {
                int lo = max(1, i - 9), hi = i - 1;
                dp[i][j] += 25 * (pref[hi][j - 2] - pref[lo - 1][j - 2]);
            }
            if (i > 10 && j >= 3)
            {
                int lo = max(1, i - 99), hi = i - 10;
                dp[i][j] += 25 * (pref[hi][j - 3] - pref[lo - 1][j - 3]);
            }
            if (i > 100 && j >= 4)
            {
                int lo = max(1, i - 999), hi = i - 100;
                dp[i][j] += 25 * (pref[hi][j - 4] - pref[lo - 1][j - 4]);
            }
            if (i > 1000 && j >= 5)
            {
                int lo = max(1, i - 9999), hi = i - 1000;
                dp[i][j] += 25 * (pref[hi][j - 5] - pref[lo - 1][j - 5]);
            }

            dp[i][j] %= mod;
            dp[i][j] += mod, dp[i][j] %= mod;
            pref[i][j] = pref[i - 1][j] + dp[i][j];
            pref[i][j] %= mod;
        }
    }
    ll ans = 0;
    FOR(i, 1, n)
    {
        ans += dp[n][i];
        ans %= mod;
    }
    cout << ans * 26 % mod << '\n';
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase = 1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}