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
stack<ll> s1, s2, mi1, ma1, mi2, ma2;
ll k;

void add(ll x)
{
    s2.push(x);
    if (ma2.empty())
    {
        ma2.push(x);
        mi2.push(x);
    }
    else
    {
        ma2.push(max(ma2.top(), x));
        mi2.push(min(mi2.top(), x));
    }
}
void remove(ll x)
{
    if (s1.empty())
    {
        while (!s2.empty())
        {
            s1.push(s2.top());
            if (ma1.empty())
            {
                ma1.push(s1.top());
                mi1.push(s1.top());
            }
            else
            {
                ma1.push(max(ma1.top(), s1.top()));
                mi1.push(min(mi1.top(), s1.top()));
            }

            s2.pop();
            ma2.pop();
            mi2.pop();
        }
    }
    s1.pop();
    mi1.pop();
    ma1.pop();
}
bool good()
{
    ll mi = LINF, ma = -LINF;
    if (!s1.empty())
    {
        mi = min(mi, mi1.top()), ma = max(ma, ma1.top());
    }
    if (!s2.empty())
    {
        mi = min(mi, mi2.top()), ma = max(ma, ma2.top());
    }
    if (mi == LINF && ma == -LINF)
        return true;
    return ma - mi <= k;
}

void solve()
{
    cin >> n >> k;
    vector<ll> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    int l = 0;
    ll res = 0;
    for (int r = 0; r < n; r++)
    {
        add(v[r]);
        while (!good() && l < n)
        {
            remove(v[l]);
            l++;
        }
        res += r - l + 1;
    }
    cout << res << "\n";
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