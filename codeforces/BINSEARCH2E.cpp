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
using ld = long double;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;
ld c;

bool is_equal(ld x, ld y)
{
    return ((x - y) < 1e-9 && (x - y) > 0) || ((y - x) > 0 && (y - x) < 1e-9);
}
bool good(ld x)
{
    return is_equal(x * x + sqrt(x), c);
}

void solve()
{
    cin >> c;
    ld l = 0, r = 1e11;
    while (l <= r)
    {
        ld m = (l + r) / 2;
        if (good(m))
        {
            cout << setprecision(20) << m << "\n";
            return;
        }
        else if (m * m + sqrt(m) > c)
        {
            r = m;
        }
        else
        {
            l = m;
        }
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