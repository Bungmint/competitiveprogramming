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
    string s;
    cin >> s;
    int digits[3] = {0, 0, 0};
    int digits_sum = 0;
    for (int i = 0; i < (int)s.length(); i++)
    {
        digits[(s[i] - '0') % 3]++;
        digits_sum += (s[i] - '0');
        digits_sum %= 3;
    }
    if (digits_sum % 3 == 0)
    {
        cout << 0 << "\n";
        return;
    }
    if (s.length() == 1)
    {
        cout << -1 << "\n";
        return;
    }
    if (digits[digits_sum] > 0)
    {
        cout << 1 << "\n";
        return;
    }
    if (s.length() == 2)
    {
        cout << -1 << "\n";
        return;
    }
    cout << 2 << "\n";
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