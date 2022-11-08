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
const int N = 1e6 + 1;
unordered_map<int, int> dic;
int dp[N][4];

void solve()
{
    string s;
    cin >> s;
    memset(dp, -1, sizeof(dp));
    if (s[0] - '0' == 1)
        dp[0][0] = 1;
    dic[1] = 0, dic[8] = 1, dic[0] = 2, dic[7] = 3;
    for (int i = 1; i < (int)s.length(); i++)
    {
        for (int j = 0; j < 4; j++)
            dp[i][j] = dp[i - 1][j];
        if (dic[s[i] - '0'] == 0)
        {
            if (dp[i - 1][0] != -1)
                dp[i][0] = dp[i - 1][0] + 1;
            else
                dp[i][0] = 1;
        }
        else if (dic[s[i] - '0'] == 1)
        {
            if (dp[i - 1][0] == -1 && dp[i - 1][1] == -1)
                continue;
            if (dp[i - 1][0] != -1)
                dp[i][1] = dp[i - 1][0] + 1;
            if (dp[i - 1][1] != -1)
                dp[i][1] = max(dp[i][1], dp[i - 1][1] + 1);
        }
        else if (dic[s[i] - '0'] == 2)
        {
            if (dp[i - 1][1] == -1 && dp[i - 1][2] == -1)
                continue;
            if (dp[i - 1][1] != -1)
                dp[i][2] = dp[i - 1][1] + 1;
            if (dp[i - 1][2] != -1)
                dp[i][2] = max(dp[i][2], dp[i - 1][2] + 1);
        }
        else
        {
            if (dp[i - 1][2] == -1 && dp[i - 1][3] == -1)
                continue;
            if (dp[i - 1][2] != -1)
                dp[i][3] = dp[i - 1][2] + 1;
            if (dp[i - 1][3] != -1)
                dp[i][3] = max(dp[i][3], dp[i - 1][3] + 1);
        }
    }
    if (dp[(int)s.length() - 1][3] == -1)
        cout << 0 << "\n";
    else
        cout << dp[(int)s.length() - 1][3] << "\n";
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