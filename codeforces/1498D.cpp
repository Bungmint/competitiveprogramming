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
const int DIV = 1e5;

ll ceil(ll a, ll b)
{
    return (a + b - 1) / b;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<bool> vis(m + 1, false);
    vis[0] = true;
    vector<ll> ans(m + 1, -1);
    ans[0] = 0;
    for (int i = 0; i < n; i++)
    {
        auto new_vis = vis;
        ll t, x, y;
        cin >> t >> x >> y;
        auto operation = [&](long long &curr) {
            if (t == 1)
            {
                curr = curr + ceil(x, DIV);
            }
            else
                curr = ceil(curr * x, DIV);
        };
        for (int k = 0; k <= m; k++)
        {
            if (vis[k])
            {
                ll curr = k;
                operation(curr);
                for (int a = 1; a <= y;)
                {
                    if (curr > m)
                        break;
                    if (vis[curr])
                        break;
                    new_vis[curr] = true;
                    ans[curr] = i + 1;
                    a++;
                    operation(curr);
                }
            }
        }
        vis = new_vis;
    }
    for (int i = 1; i <= m; i++)
        cout << ans[i] << " ";
    cout << "\n";
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