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
    vector<pair<int, int>> point(n);
    for (int i = 0; i < n; i++)
        cin >> point[i].first >> point[i].second;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                pair<int, int> p1, p2, p3;
                p1 = point[i], p2 = point[j], p3 = point[k];
                int x1 = p2.first - p1.first, x2 = p3.first - p2.first;
                int y1 = p2.second - p1.second, y2 = p3.second - p2.second;
                if ((x1 == y2 && y2 == 0) || (x2 == y1 && y1 == 0))
                {
                    continue;
                }
                if (x1 * y2 == x2 * y1)
                {
                    cout << "Yes"
                         << "\n";
                    return;
                }
            }
        }
    }
    cout << "No"
         << "\n";
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