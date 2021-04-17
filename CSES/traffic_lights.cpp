#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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
    int x, n;
    cin >> x >> n;
    set<int> traffic;
    multiset<int> leng;
    for (int i = 0; i < n; i++)
    {
        int traf;
        cin >> traf;
        if (traffic.empty())
        {
            leng.insert(x - traf);
            leng.insert(traf);
        }
        else
        {
            auto lo = traffic.lower_bound(traf);
            if (lo == traffic.begin())
            {
                int seg = *lo;
                leng.insert(seg - traf);
                leng.insert(traf);
                auto it = leng.find(seg);
                leng.erase(it);
            }
            else if (lo == traffic.end())
            {
                lo--;
                int seg = *lo;
                leng.insert(x - traf);
                leng.insert(traf - seg);
                auto it = leng.find(x - seg);
                leng.erase(it);
            }
            else
            {
                int above = *lo;
                lo--;
                int below = *lo;
                leng.insert(above - traf);
                leng.insert(traf - below);
                auto it = leng.find(above - below);
                leng.erase(it);
            }
        }
        cout << *leng.rbegin() << " ";
        traffic.insert(traf);
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