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
int ans[501][501], n, cnt;

void dfs1(int x, int y, int num)
{
    if (x < 0 || x >= n || y < 0 || y >= n)
        return;
    if (ans[x][y] != 0)
        return;
    if (cnt == num)
        return;
    ans[x][y] = num;
    cnt++;
    dfs1(x, y - 1, num);
    dfs1(x + 1, y, num);
    //dfs1(x, y - 1, num);
    //dfs1(x - 1, y, num);
}

void dfs2(int x, int y, int num)
{
    if (x < 0 || x >= n || y < 0 || y >= n)
        return;
    if (ans[x][y] != 0)
        return;
    if (cnt == num)
        return;
    ans[x][y] = num;
    cnt++;
    dfs2(x + 1, y, num);
    dfs2(x, y - 1, num);
    //dfs2(x - 1, y, num);
    //dfs2(x, y + 1, num);
}

void solve()
{
    int pos_one;
    cin >> n;
    vector<int> perms(n);
    for (int i = 0; i < n; i++)
    {
        cin >> perms[i];
        ans[i][i] = perms[i];
        if (perms[i] == 1)
            pos_one = i;
    }
    int i = 0;
    while (i < pos_one)
    {
        cnt = 1;
        int x = i + 1, y = i;
        dfs1(x, y, perms[i]);
        if (cnt != perms[i])
        {
            cout << -1 << "\n";
            return;
        }
        i++;
    }
    i = n - 1;
    while (i > pos_one)
    {
        cnt = 1;
        int x = i, y = i - 1;
        dfs2(x, y, perms[i]);
        if (cnt != perms[i])
        {
            cout << -1 << "\n";
            return;
        }
        i--;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
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