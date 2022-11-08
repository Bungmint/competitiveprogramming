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
    int l = 1, r = n;
    int lval, rval;
    cout << "? " << 1 << endl;
    cin >> lval;
    cout << "? " << n << endl;
    cin >> rval;
    while (l <= r)
    {
        if (l == r)
            break;
        int m = l + (r - l) / 2;
        int left, right;
        cout << "? " << m << endl;
        cin >> left;
        cout << "? " << m + 1 << endl;
        cin >> right;
        if (left > right)
        {
            l = m + 1;
        }
        else
        {
            r = m;
        }
    }
    cout << "! " << l << endl;
}

int main()
{
    solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}