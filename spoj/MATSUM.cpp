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
const int N = 1030;
int BIT[N][N], val[N][N];

void upd(int v, int x, int y)
{
    x++;
    y++;
    for (int i = x; i < N; i += i & (-i))
    {
        for (int j = y; j < N; j += j & (-j))
        {
            BIT[i][j] += v;
        }
    }
}

int query(int x, int y)
{
    x++;
    y++;
    int ans = 0;
    for (int i = x; i > 0; i -= i & (-i))
    {
        for (int j = y; j > 0; j -= j & (-j))
        {
            ans += BIT[i][j];
        }
    }
    return ans;
}

void solve()
{
    memset(BIT, 0, sizeof(BIT));
    memset(val, 0, sizeof(val));
    int n;
    cin >> n;
    while (true)
    {
        string s;
        cin >> s;
        if (s == "END")
            return;
        if (s == "SET")
        {
            int x, y, num;
            cin >> x >> y >> num;
            upd(num - val[x][y], x, y);
            val[x][y] = num;
        }
        else
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1) << "\n";
        }
    }
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