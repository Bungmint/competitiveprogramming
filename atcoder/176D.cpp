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
const int N = 1001;
char maze[N][N];
int offx[] = {-1, 1, 0, 0}, offy[] = {0, 0, -1, 1}, cost[N][N], h, w;
int magicx[] = {2, 2, -2, -2, 1, 1, -1, -1, 2, 2, -2, -2, 1, 1, -1, -1, 2, -2, 0, 0}, magicy[] = {1, -1, 1, -1, 2, -2, 2, -2, 2, -2, 2, -2, 1, -1, 1, -1, 0, 0, 2, -2};

bool ok(int x, int y)
{
    return (x < h && x >= 0 && y < w && y >= 0 && maze[x][y] == '.');
}
void bfs(int x, int y)
{
    cost[x][y] = 0;
    deque<pair<int, int>> q;
    q.push_front({x, y});
    while (!q.empty())
    {
        int x1 = q.front().first, y1 = q.front().second;
        q.pop_front();
        for (int i = 0; i < 4; i++)
        {
            int nxtx = x1 + offx[i], nxty = y1 + offy[i];
            if (ok(nxtx, nxty) && cost[nxtx][nxty] > cost[x1][y1])
            {
                cost[nxtx][nxty] = cost[x1][y1];
                q.push_front({nxtx, nxty});
            }
        }
        for (int i = 0; i < 20; i++)
        {
            int nxtx = x1 + magicx[i], nxty = y1 + magicy[i];
            if (ok(nxtx, nxty) && (cost[nxtx][nxty] > cost[x1][y1] + 1))
            {
                cost[nxtx][nxty] = cost[x1][y1] + 1;
                q.push_back({nxtx, nxty});
            }
        }
    }
}

void solve()
{
    cin >> h >> w;
    int c1, c2, d1, d2;
    cin >> c1 >> c2 >> d1 >> d2;
    c1--;
    c2--;
    d1--;
    d2--;
    for (int i = 0; i < h; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < w; j++)
        {
            maze[i][j] = s[j];
            cost[i][j] = INF;
        }
    }
    bfs(c1, c2);
    if (cost[d1][d2] == INF)
        cout << -1 << "\n";
    else
        cout << cost[d1][d2] << "\n";
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