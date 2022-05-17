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
int dp[2 * N][N];

void solve()
{
    memset(dp, -1, sizeof(dp));
    int n;
    cin >> n;
    vector<int> dish(n);
    for (int i = 0; i < n; i++)
        cin >> dish[i];
    sort(all(dish));
    for (int i = 1; i <= 2 * n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 1)
            {
                if (j == 0)
                    dp[i][j] = abs(i - dish[j]);
                continue;
            }
            if (j == 0)
                dp[i][j] = min(dp[i - 1][j], abs(i - dish[j]));
            else
            {
                if (dp[i - 1][j - 1] != -1 && dp[i - 1][j] != -1)
                    dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1] + abs(i - dish[j]));
                else if (dp[i - 1][j] != -1)
                    dp[i][j] = dp[i - 1][j];
                else if (dp[i - 1][j - 1] != -1)
                    dp[i][j] = dp[i - 1][j - 1] + abs(i - dish[j]);
            }
        }
    }
    int mini = INF;
    for (int i = 1; i <= 2 * n; i++)
    {
        if (dp[i][n - 1] != -1)
            mini = min(mini, dp[i][n - 1]);
    }
    cout << mini << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}