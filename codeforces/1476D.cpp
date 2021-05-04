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
string s;
int n;

void solve()
{
    cin >> n;
    cin >> s;
    vector<int> chain(n);
    vector<bool> used(n);
    int j = 0;
    char cur, prev = 'a';
    for (int i = 0; i < n; i++)
    {
        cur = s[i];
        if (cur == prev)
        {
            j++;
        }
        prev = cur;
        if (used[j])
            continue;
        chain[j] = i;
        used[j] = true;
    }
    chain.resize(j + 1);
    for (int i = 0; i <= n; i++)
    {
        int val = 1;
        if (i > 0 && s[i - 1] == 'L')
        {
            auto idx = lower_bound(all(chain), i) - chain.begin();
            if (idx == 0)
            {
                val += i;
            }
            else
            {
                idx--;
                val += i - chain[idx];
            }
        }
        if (i < n && s[i] == 'R')
        {
            auto idx = lower_bound(all(chain), i) - chain.begin();
            if (idx != (int)chain.size() && chain[idx] == i)
            {
                idx++;
            }
            if (idx == (int)chain.size())
                val += n - i;
            else
                val += chain[idx] - i;
        }
        cout << val << " ";
    }
    cout << "\n";
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