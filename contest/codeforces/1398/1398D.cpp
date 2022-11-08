//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
const int N = 210;
ll dp[N][N][N], R[N], G[N], B[N];

ll dping(int a, int b, int c)
{
    if (dp[a][b][c] != -1)
        return dp[a][b][c];
    if (a + b + c <= 1)
    {
        dp[a][b][c] = 0LL;
        return dp[a][b][c];
    }
    ll ans = 0LL;
    if (a > 0 && b > 0)
        ans = max(ans, dping(a - 1, b - 1, c) + R[a] * G[b]);
    if (c > 0 && b > 0)
        ans = max(ans, dping(a, b - 1, c - 1) + B[c] * G[b]);
    if (a > 0 && c > 0)
        ans = max(ans, dping(a - 1, b, c - 1) + R[a] * B[c]);
    dp[a][b][c] = ans;
    return ans;
}

void solve()
{
    memset(dp, -1, sizeof(dp));
    int r, g, b;
    cin >> r >> g >> b;
    for (int i = 1; i <= r; i++)
        cin >> R[i];
    for (int i = 1; i <= g; i++)
        cin >> G[i];
    for (int i = 1; i <= b; i++)
        cin >> B[i];
    sort(R, R + r + 1);
    sort(G, G + g + 1);
    sort(B, B + b + 1);
    cout << dping(r, g, b) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}