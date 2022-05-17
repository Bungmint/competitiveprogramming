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
const ll LINF = 1e15;
const int MOD = 1e9 + 7; //998244353

void solve()
{
    int n;
    cin >> n;
    vector<vector<ll>> vec(n, vector<ll>(n));
    vector<ll> up(2 * n - 1), down(2 * n - 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int tmp;
            cin >> tmp;
            vec[i][j] = tmp;
            up[i + j] += tmp;
            down[i - j + (n - 1)] += tmp;
        }
    }
    ll maxi = -1, maxj = -1, sum = -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (sum < up[i + j] + down[i - j + n - 1] - vec[i][j])
            {
                maxi = i;
                maxj = j;
                sum = up[i + j] + down[i - j + n - 1] - vec[i][j];
            }
        }
    }
    int maxup = maxi + maxj, maxdown = maxi - maxj + n - 1;
    ll sec = -1;
    int maxsecondi = -1, maxsecondj = -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == maxi && j == maxj)
                continue;

            if ((maxup + i - j) % 2 == 0 && (maxup + i - j) / 2 >= 0 && (maxup - i + j) % 2 == 0 && (maxup - i + j) / 2 >= 0)
                continue;
            if ((maxdown + i + j) % 2 == 0 && (maxdown + i + j) / 2 >= 0 && (i + j - maxdown + n - 1) % 2 == 0 && (i + j - maxdown + n - 1) >= 0)
                continue;

            if (sec < up[i + j] + down[i - j + n - 1] - vec[i][j])
            {
                sec = up[i + j] + down[i - j + n - 1] - vec[i][j];
                maxsecondi = i + 1;
                maxsecondj = j + 1;
            }
        }
    }
    cout << sum + sec << "\n";
    cout << maxi + 1 << " " << maxj + 1 << " " << maxsecondi << " " << maxsecondj << "\n";
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