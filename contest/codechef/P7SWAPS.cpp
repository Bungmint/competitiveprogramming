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
const int LOG = 20;
int n, q;

void solve()
{
    cin >> n;
    vector<int> a(n), p(n + 1);
    vector<vector<int>> down(n + 1, vector<int>(LOG));
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
        down[p[i]][0] = i;
    }
    for (int i = 1; i < LOG; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            down[p[j]][i] = down[down[p[j]][i - 1]][i - 1];
        }
    }
    cin >> q;
    vector<int> pos(n + 1);
    iota(all(pos), 0);
    int cnt = 0;
    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            cnt++;
        }
        else if (op == 2)
        {
            int x, y;
            cin >> x >> y;
            for (int i = LOG - 1; i >= 0; i--)
            {
                if (cnt & (1 << i))
                {
                    x = down[x][i];
                    y = down[y][i];
                }
            }
            swap(pos[x], pos[y]);
        }
        else
        {
            int x;
            cin >> x;
            for (int i = LOG - 1; i >= 0; i--)
            {
                if (cnt & (1 << i))
                {
                    x = down[x][i];
                }
            }
            cout << a[pos[x] - 1] << "\n";
        }
    }
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