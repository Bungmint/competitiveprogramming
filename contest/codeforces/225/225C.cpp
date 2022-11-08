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
int dp[1005][2];

void solve()
{
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    vector<int> col(m), pref(m + 1);
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++)
        {
            if (s[j] == '#')
                col[j]++;
        }
    }
    for (int i = 1; i <= m; i++)
    {
        pref[i] = (i == 1) ? col[0] : col[i - 1] + pref[i - 1];
    }
    memset(dp, -1, sizeof(dp));
    dp[0][0] = dp[0][1] = 0;
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (dp[i][j] == -1)
                continue;
            for (int k = x; k <= y; k++)
            {
                if (i + k > m)
                    break;
                int val = (j == 0) ? dp[i][j] + (pref[i + k] - pref[i]) : dp[i][j] + k * n - (pref[i + k] - pref[i]);
                if (dp[i + k][(j + 1) % 2] == -1)
                    dp[i + k][(j + 1) % 2] = val;
                else
                    dp[i + k][(j + 1) % 2] = min(dp[i + k][(j + 1) % 2], val);
            }
        }
    }
    cout << min(dp[m][0], dp[m][1]) << "\n";
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