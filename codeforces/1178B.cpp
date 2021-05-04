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
const int MOD = 1e9 + 7;

void solve()
{
    string s;
    cin >> s;
    vector<ll> o, w;
    for (int i = 0; i < (int)s.length(); i++)
    {
        if (s[i] == 'o')
            o.PB(i);
    }
    ll n = o.size();
    if (n == 0)
    {
        cout << 0 << "\n";
        return;
    }
    w.resize(n + 1);

    for (int i = 0; i <= n; i++)
    {
        if (i == 0)
        {
            w[0] = max(0LL, o[i] - 1);
        }
        else if (i == n)
        {
            w[n] = max(0LL, (long long)s.length() - 2 - o[n - 1]);
        }
        else
        {
            w[i] = max(0LL, o[i] - o[i - 1] - 2);
        }
    }
    vector<ll> pref(n + 1);
    for (int i = 0; i <= n; i++)
    {
        if (i == 0)
            pref[i] = w[i];
        else
            pref[i] = pref[i - 1] + w[i];
    }
    ll ans = 0LL;
    for (int i = 0; i < n; i++)
    {
        ans += pref[i] * (pref[n] - pref[i]);
    }
    cout << ans << "\n";
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