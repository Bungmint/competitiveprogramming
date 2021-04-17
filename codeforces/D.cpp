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
    string s1, s2, s3, ans;
    cin >> s1 >> s2 >> s3;
    int i, j, k;
    i = j = k = 0;
    while (i < 2 * n && j < 2 * n && k < 2 * n)
    {
        if (s1[i] == s2[j])
        {
            ans += s1[i];
            i++;
            j++;
        }
        else if (s1[i] == s3[k])
        {
            ans += s1[i];
            i++;
            k++;
        }
        else if (s2[j] == s3[k])
        {
            ans += s2[j];
            j++;
            k++;
        }
    }
    if (i == 2 * n)
    {
        if (j >= (int)ans.length() - n)
        {
            ans += s2.substr(j);
        }
        else
        {
            ans += s3.substr(k);
        }
    }
    else if (j == 2 * n)
    {
        if (i >= (int)ans.length() - n)
        {
            ans += s1.substr(i);
        }
        else
        {
            ans += s3.substr(k);
        }
    }
    else
    {
        if (j >= (int)ans.length() - n)
        {
            ans += s2.substr(j);
        }
        else
        {
            ans += s1.substr(i);
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}