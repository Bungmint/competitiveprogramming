//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
int hweight[501][501], vweight[501][501];
int dp[501][501][21];
int n, m, k;

void solve()
{
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m - 1; j++)
        {
            cin >> hweight[i][j];
        }
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> vweight[i][j];
        }
    }
    if (k % 2)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                cout << -1 << " ";
            cout << "\n";
        }
        return;
    }
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            dp[i][j][0] = 0;
        }
    }
    for (int i = 0; i < k / 2; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int l = 0; l < m; l++)
            {
                if (j > 0)
                {
                    if (dp[j - 1][l][i + 1] == -1)
                        dp[j - 1][l][i + 1] = dp[j][l][i] + vweight[j - 1][l];
                    dp[j - 1][l][i + 1] = min(dp[j - 1][l][i + 1], dp[j][l][i] + vweight[j - 1][l]);
                }
                if (j < n - 1)
                {
                    if (dp[j + 1][l][i + 1] == -1)
                        dp[j + 1][l][i + 1] = dp[j][l][i] + vweight[j][l];
                    dp[j + 1][l][i + 1] = min(dp[j + 1][l][i + 1], dp[j][l][i] + vweight[j][l]);
                }
                if (l > 0)
                {
                    if (dp[j][l - 1][i + 1] == -1)
                        dp[j][l - 1][i + 1] = dp[j][l][i] + hweight[j][l - 1];
                    dp[j][l - 1][i + 1] = min(dp[j][l - 1][i + 1], dp[j][l][i] + hweight[j][l - 1]);
                }
                if (l < m - 1)
                {
                    if (dp[j][l + 1][i + 1] == -1)
                        dp[j][l + 1][i + 1] = dp[j][l][i] + hweight[j][l];
                    dp[j][l + 1][i + 1] = min(dp[j][l + 1][i + 1], dp[j][l][i] + hweight[j][l]);
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << dp[i][j][k / 2] * 2 << " ";
        }
        cout << "\n";
    }
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