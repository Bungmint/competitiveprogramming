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
const int N = 2e3 + 1;
int h, w, mat[N][N], dp[N][N];
string s;

void solve()
{
    cin >> h >> w;
    for (int i = 0; i < h; i++)
    {
        cin >> s;
        for (int j = 0; j < w; j++)
        {
            mat[i][j] = ((s[j] == '+') ? 1 : -1);
        }
    }
    for (int i = h - 1; i >= 0; i--)
    {
        for (int j = w - 1; j >= 0; j--)
        {
            if ((i + j) % 2 == 0)
            {
                if (j < w - 1 && i < h - 1)
                    dp[i][j] = max(dp[i + 1][j] + mat[i + 1][j], dp[i][j + 1] + mat[i][j + 1]);
                else if (i < h - 1)
                    dp[i][j] = dp[i + 1][j] + mat[i + 1][j];
                else if (j < w - 1)
                    dp[i][j] = dp[i][j + 1] + mat[i][j + 1];
            }
            else
            {
                if (j < w - 1 && i < h - 1)
                    dp[i][j] = min(dp[i + 1][j] - mat[i + 1][j], dp[i][j + 1] - mat[i][j + 1]);
                else if (i < h - 1)
                    dp[i][j] = dp[i + 1][j] - mat[i + 1][j];
                else if (j < w - 1)
                    dp[i][j] = dp[i][j + 1] - mat[i][j + 1];
            }
        }
    }
    if (dp[0][0] > 0)
        cout << "Takahashi"
             << "\n";
    else if (dp[0][0] < 0)
        cout << "Aoki"
             << "\n";
    else
        cout << "Draw"
             << "\n";
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