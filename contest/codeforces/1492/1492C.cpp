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
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    vector<int> left(m), right(m);
    int cnt = 0;
    for (int i = 0; i <= n - 1; i++)
    {
        if (cnt > m)
            break;
        if (s[i] == t[cnt])
        {
            left[cnt] = i;
            cnt++;
        }
    }
    cnt = m - 1;
    for (int i = n - 1; i >= 0; i--)
    {
        if (cnt < 0)
            break;
        if (s[i] == t[cnt])
        {
            right[cnt] = i;
            cnt--;
        }
    }
    int ans = 0;
    for (int i = 0; i < m - 1; i++)
    {
        ans = max(ans, right[i + 1] - left[i]);
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