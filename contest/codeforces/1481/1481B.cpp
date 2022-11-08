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

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    while (k)
    {
        int halt = -1;
        for (int i = 0; i < n - 1; i++)
        {
            if (arr[i] < arr[i + 1])
            {
                halt = i;
                break;
            }
        }
        if (halt == -1)
        {
            cout << -1 << "\n";
            return;
        }
        if (halt == 0)
        {
            if (arr[1] - arr[0] >= k)
            {
                cout << 1 << "\n";
                return;
            }
            k -= (arr[1] - arr[0]);
            arr[0] = arr[1];
        }
        else
        {
            int dip = arr[halt - 1] - arr[halt] + 1;
            int wall = arr[halt + 1] - arr[halt];
            if (wall >= dip)
            {
                if (dip >= k)
                {
                    cout << halt + 1 << "\n";
                    return;
                }
                arr[halt] = arr[halt - 1] + 1;
                k -= dip;
            }
            else
            {
                if (wall >= k)
                {
                    cout << halt + 1 << "\n";
                    return;
                }
                k -= wall;
                arr[halt] = arr[halt + 1];
            }
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