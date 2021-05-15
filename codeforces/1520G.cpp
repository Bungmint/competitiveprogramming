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
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
const int N = 2e3 + 10;
ll n, m, w, sq[N][N], offx[] = {-1, 1, 0, 0}, offy[] = {0, 0, -1, 1};

bool valid(ll x, ll y)
{
    return (x >= 1 && x <= n) && (y >= 1 && y <= m) && (sq[x][y] >= 0);
}

void bfs(vector<vector<ll>> &mat, ll x, ll y)
{
    queue<pair<ll, ll>> q;
    mat[x][y] = 0LL;
    q.push({x, y});
    while (!q.empty())
    {
        ll curx = q.front().first, cury = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            ll tx = curx + offx[i], ty = cury + offy[i];
            if (valid(tx, ty))
            {
                if (mat[tx][ty] > mat[curx][cury] + w)
                {
                    mat[tx][ty] = mat[curx][cury] + w;
                    q.push({tx, ty});
                }
            }
        }
    }
}

void solve()
{
    cin >> n >> m >> w;
    vector<vector<ll>> forsq(N, vector<ll>(N)), backsq(N, vector<ll>(N));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> sq[i][j];
            forsq[i][j] = LINF;
            backsq[i][j] = LINF;
        }
    }
    bfs(forsq, 1, 1);
    bfs(backsq, n, m);
    ll walk = forsq[n][m];
    ll minitele = LINF, dest = LINF;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (sq[i][j] > 0)
            {
                minitele = min(minitele, forsq[i][j] + sq[i][j]);
                dest = min(dest, backsq[i][j] + sq[i][j]);
            }
        }
    }
    if (walk == LINF && (minitele == LINF || dest == LINF))
    {
        puts("-1");
        return;
    }
    cout << min(walk, minitele + dest) << "\n";
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