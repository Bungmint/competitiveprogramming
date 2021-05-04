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
int n, k;

bool check(vector<ld> &vec, ld v)
{
    int ans = 0;
    for (auto x : vec)
        ans += x / v;
    return ans >= k;
}

void solve()
{

    cin >> n >> k;
    vector<ld> vec(n);
    for (int i = 0; i < n; i++)
        cin >> vec[i];
    ld l = 0;   // Good value
    ld r = 1e8; //Bad value
    for (int i = 0; i < 100; i++)
    {
        ld m = (l + r) / 2;
        if (check(vec, m))
        {
            l = m;
        }
        else
        {
            r = m;
        }
    }
    cout << setprecision(20) << l << "\n";
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