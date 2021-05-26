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
int n;
stack<ll> s1, s2, g1, g2;

void add(ll x)
{
    s2.push(x);
    if (g2.empty())
        g2.push(x);
    else
        g2.push(gcd(g2.top(), x));
}
pair<ll, ll> remove(ll x)
{
    if (s1.empty())
    {
        while (!s2.empty())
        {
            s1.push(s2.top());
            if (g1.empty())
                g1.push(s1.top());
            else
                g1.push(gcd(g1.top(), s1.top()));
            s2.pop();
            g2.pop();
        }
    }
    pair<ll, ll> p1 = {s1.top(), g1.top()};
    s1.pop();
    g1.pop();
    return p1;
}
bool good()
{
    if (s1.empty() && s2.empty())
        return false;
    if (s1.empty())
        return g2.top() == 1;
    if (s2.empty())
        return g1.top() == 1;
    return gcd(g2.top(), g1.top()) == 1;
}

void solve()
{
    cin >> n;
    vector<ll> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    int l = 0;
    ll res = LINF;
    for (int r = 0; r < n; r++)
    {
        add(v[r]);
        while (good() && l < n)
        {
            pair<ll, ll> p1 = remove(v[l]);
            l++;
            if (!good())
            {
                s1.push(p1.first);
                g1.push(p1.second);
                l--;
                break;
            }
        }
        if (good())
            res = min(res, (long long)r - l + 1);
    }
    if (res != LINF)
        cout << res << "\n";
    else
        cout << -1 << "\n";
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