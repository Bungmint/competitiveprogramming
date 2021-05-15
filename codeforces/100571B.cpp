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
ll troy[100009];

void solve()
{
    ll n, q, f1, f2, a, b;
    cin >> n >> q >> f1 >> f2 >> a >> b;
    for (int i = 0; i <= 1e5; i++)
    {
        if (i == 0)
            troy[i] = f1;
        else if (i == 1)
            troy[i] = f2;
        else
            troy[i] = ((troy[i - 2] * a) % MOD + (troy[i - 1] * b) % MOD) % MOD;
    }
    vector<ll> p(n), ans(n);
    for (int i = 0; i < n; i++)
        cin >> p[i];
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        if (l == r)
        {
            ans[l] = (ans[l] + troy[0]) % MOD;
            if (l < n - 1)
                ans[l + 1] = ((1LL * ans[l + 1] + MOD - 1LL * (1LL * b * troy[0]) % MOD)) % MOD;
            if (l < n - 2)
                ans[l + 2] = ((1LL * ans[l + 2] + MOD - 1LL * (1LL * a * troy[0]) % MOD)) % MOD;
        }
        else
        {
            ans[l] = (ans[l] + troy[0]) % MOD;
            ans[l + 1] = (ans[l + 1] + troy[1]) % MOD;
            ans[l + 1] = (((ans[l + 1] - 1LL * (b * troy[0]) % MOD) % MOD) + MOD) % MOD;
            if (r < n - 1)
                ans[r + 1] = (ans[r + 1] - troy[r - l + 1] + MOD) % MOD;
            if (r < n - 2)
                ans[r + 2] = ((ans[r + 2] + MOD - 1LL * ((a * troy[r - l]) % MOD))) % MOD;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (i > 0)
            ans[i] = (ans[i] + ans[i - 1] * b) % MOD;
        if (i > 1)
            ans[i] = (ans[i] + ans[i - 2] * a) % MOD;
        p[i] = (p[i] + ans[i]) % MOD;
        cout << p[i] << " ";
    }
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