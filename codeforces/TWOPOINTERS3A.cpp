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
    int n;
    ll p;
    cin >> n >> p;
    vector<int> v(n), cir(2 * n);
    ll sum = 0LL;
    for (int i = 0; i < n; i++)
        cin >> v[i], sum += v[i];
    for (int i = 0; i < 2 * n; i++)
        cir[i] = v[i % n];
    ll loop = p / sum, targ = p % sum;
    ll res = LINF;
    ll cursum = 0LL;
    int l = 0, start = -1;
    for (int r = 0; r < 2 * n; r++)
    {
        cursum += cir[r];
        while (l < 2 * n && cursum - cir[l] >= targ)
        {
            cursum -= cir[l];
            l++;
        }
        if (cursum >= targ)
        {
            if (res > r - l + 1)
            {
                res = r - l + 1;
                start = l;
            }
        }
    }
    cout << (start % n) + 1 << " " << res + loop * n << "\n";
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