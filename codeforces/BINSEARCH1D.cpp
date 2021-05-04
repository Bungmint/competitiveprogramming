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
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(all(arr));
    int k;
    cin >> k;
    while (k--)
    {
        int l, r;
        cin >> l >> r;
        int l1 = 0, r1 = n - 1, id1 = n, l2 = 0, r2 = n - 1, id2 = -1;
        while (l1 <= r1)
        {
            int m = l1 + (r1 - l1) / 2;
            if (arr[m] < l)
            {
                l1 = m + 1;
            }
            else
            {
                id1 = m;
                r1 = m - 1;
            }
        }
        while (l2 <= r2)
        {
            int m = l2 + (r2 - l2) / 2;
            if (arr[m] > r)
            {
                r2 = m - 1;
            }
            else
            {
                l2 = m + 1;
                id2 = m;
            }
        }
        if (id1 == n || id2 == -1)
            cout << 0 << " ";
        else
            cout << id2 - id1 + 1 << " ";
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