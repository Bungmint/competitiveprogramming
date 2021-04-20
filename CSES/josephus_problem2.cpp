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

void solve()
{
    ll n, k;
    cin >> n >> k;
    ordered_set<int> o_set;
    for (int i = 1; i <= n; i++)
    {
        o_set.insert(i);
    }
    ll i = 0;
    while (!o_set.empty())
    {
        ll target = (i + k) % (ll)o_set.size();
        cout << *o_set.find_by_order(target) << " ";
        o_set.erase(o_set.find_by_order(target));
        i = target;
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