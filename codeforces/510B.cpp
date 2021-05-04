//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7; //998244353
char mat[50][50];
bool vis[50][50], cycle = false;
int offx[4] = {0, 0, -1, 1}, offy[4] = {-1, 1, 0, 0};
int n, m;

void dfs(int x, int y, int px, int py)
{
    if (vis[x][y])
    {
        cycle = true;
        return;
    }
    vis[x][y] = true;
    for (int i = 0; i < 4; i++)
    {
        int nxtx = x + offx[i], nxty = y + offy[i];
        if (nxtx >= n || nxtx < 0 || nxty >= m || nxty < 0)
            continue;
        if (nxtx == px && nxty == py)
            continue;
        if (mat[nxtx][nxty] != mat[x][y])
            continue;
        dfs(nxtx, nxty, x, y);
    }
}

void solve()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++)
        {
            mat[i][j] = s[j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (vis[i][j])
                continue;
            dfs(i, j, -1, -1);
        }
    }
    if (cycle)
        cout << "Yes"
             << "\n";
    else
        cout << "No\n";
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