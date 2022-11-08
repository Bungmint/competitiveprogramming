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
unordered_map<int, int> assigned;
ll tmp[1000000], BIT[1000001], num_pairs[1000000], n;
void update(int x, int v)
{
    x++;
    for (int j = x; j <= n; j += (j & -j))
    {
        BIT[j] += v;
    }
}
ll query(int x)
{
    x++;
    ll ans = 0;
    while (x > 0)
    {
        ans += BIT[x];
        x -= (x & -x);
    }
    return ans;
}

void solve()
{
    cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
        tmp[i] = vec[i];
    }
    sort(tmp, tmp + n);
    for (int i = 0; i < n; i++)
        assigned[tmp[i]] = i;
    for (int i = 0; i < n; i++)
    {
        update(assigned[vec[i]], 1);
        num_pairs[assigned[vec[i]]] = query(n - 1) - query(assigned[vec[i]]);
    }
    ll ans = 0;
    memset(BIT, 0, sizeof(BIT));
    for (int i = 0; i < n; i++)
    {
        update(assigned[vec[i]], num_pairs[assigned[vec[i]]]);
        ans += query(n - 1) - query(assigned[vec[i]]);
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