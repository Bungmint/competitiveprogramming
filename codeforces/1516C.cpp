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
bool dp[200001][101];

bool is_pos(vector<int> &vec, int sum)
{
    int target = sum / 2;
    bool ans = false;
    dp[0][0] = true;
    for (int k = 1; k <= (int)vec.size(); k++)
    {
        for (int x = 0; x <= target; x++)
        {
            if (x - vec[k - 1] >= 0)
                dp[x][k] |= dp[x - vec[k - 1]][k - 1];
            dp[x][k] |= dp[x][k - 1];
        }
    }
    for (int i = 0; i < (int)vec.size(); i++)
        ans |= dp[target][i];
    return ans;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> vec(n);
    vector<int> bits(n);
    int sum = 0, idx = -1, bit = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
        sum += vec[i];
        bits[i] = (vec[i] & -vec[i]);
    }
    for (int i = 0; i < n; i++)
    {
        if (bits[i] < bit)
        {
            idx = i;
            bit = bits[i];
        }
    }
    if (sum % 2)
    {
        cout << 0 << "\n";
        return;
    }
    if (!is_pos(vec, sum))
    {
        cout << 0 << "\n";
        return;
    }
    cout << 1 << "\n";
    cout << idx + 1 << "\n";
    return;
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