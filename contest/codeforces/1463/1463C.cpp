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
int n;

void solve()
{
    cin >> n;
    vector<pair<ll, ll>> ord(n);
    for (int i = 0; i < n; i++)
        cin >> ord[i].first >> ord[i].second;
    ll success = 0LL, pos = 0;
    ll targ = -1;
    if (n == 1)
    {
        cout << 1 << "\n";
        return;
    }
    for (int i = 0; i <= n - 1; i++)
    {
        if (i == n - 1)
        {
            if ((ord[i].second >= pos && ord[i].second <= targ) || (ord[i].second <= pos && ord[i].second >= targ) || pos == targ)
                success++;
            break;
        }
        if (i == 0)
        {
            targ = ord[i].second;
            if (llabs(targ - pos) <= ord[i + 1].first - ord[i].first)
            {
                success++;
            }
        }
        else
        {
            if (targ == pos)
            {
                targ = ord[i].second;
                if (llabs(targ - pos) <= ord[i + 1].first - ord[i].first)
                {
                    success++;
                }
            }
            else
            {
                if ((pos >= ord[i].second && ord[i].second >= targ) || (pos <= ord[i].second && ord[i].second <= targ))
                {
                    if (llabs(pos - ord[i].second) <= ord[i + 1].first - ord[i].first)
                    {
                        success++;
                    }
                }
            }
        }
        if (pos <= targ)
            pos += min(llabs(targ - pos), ord[i + 1].first - ord[i].first);
        else
            pos -= min(llabs(targ - pos), ord[i + 1].first - ord[i].first);
    }

    cout << success << "\n";
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