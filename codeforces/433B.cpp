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
    vector<ll> pref(n), pref_cheap(n), vec(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
        if (i == 0)
            pref[i] = vec[i];
        else
            pref[i] = pref[i - 1] + vec[i];
    }
    sort(all(vec));
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
            pref_cheap[i] = vec[i];
        else
            pref_cheap[i] = pref_cheap[i - 1] + vec[i];
    }
    int m;
    cin >> m;
    while (m-- > 0)
    {
        int op, l, r;
        cin >> op >> l >> r;
        l--;
        r--;
        if (op == 1)
        {
            if (l == 0)
                cout << pref[r] << "\n";
            else
                cout << pref[r] - pref[l - 1] << "\n";
        }
        else
        {
            if (l == 0)
                cout << pref_cheap[r] << "\n";
            else
                cout << pref_cheap[r] - pref_cheap[l - 1] << "\n";
        }
    }
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