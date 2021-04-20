//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

ll inv(ll a, ll b)
{
    if (gcd(a, b) != 1)
        return -1;
    return 1 < a ? b - inv(b % a, a) * b / a : 1;
}

void solve()
{
    ll n;
    cin >> n;
    ll ans = 0, num = 0;
    set<ll> set1;
    vector<ll> vec(n, -1), res;
    vector<pair<ll, ll>> p;
    for (int i = 1; i <= n - 1; i++)
    {
        set1.insert(i);
        vec[i] = inv(i, n);
    }
    res.PB(1);
    ans++;
    for (int i = 2; i <= n - 2; i++)
    {
        if (vec[i] == -1)
            continue;
        if (vec[i] == i)
        {
            if (set1.count(i) == 0)
                continue;
            set1.erase(i);
            set1.erase(n - i);
            p.PB({i, n - i});
            num++;
        }
        else
        {
            if (set1.count(i) == 0)
                continue;
            else
            {
                set1.erase(vec[i]);
                set1.erase(i);
                res.PB(i);
                res.PB(vec[i]);
                ans += 2;
            }
        }
    }
    if (num % 2 == 0)
    {
        ans += 2 * num;
        for (int i = 0; i < num; i++)
        {
            res.PB(p[i].first);
            res.PB(p[i].second);
        }
    }
    else
    {
        ans += 2 * num + 1;
        for (int i = 0; i < num; i++)
        {
            res.PB(p[i].first);
            res.PB(p[i].second);
        }
        res.PB(n - 1);
    }
    sort(all(res));
    cout << ans << "\n";

    for (auto x : res)
        cout << x << " ";
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