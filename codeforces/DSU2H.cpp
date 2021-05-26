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
const int N = 5e4 + 1, M = 1e5;
int sz[N], p[N], n, m, u, v, w;
ll s;
ar<ll, 4> Edge[M];
bool used[M];
vector<int> ans;

int root(int a) { return p[a] = (a == p[a]) ? a : root(p[a]); }
void unite(int a, int b)
{
    a = root(a);
    b = root(b);
    if (a == b)
        return;
    if (sz[a] < sz[b])
        swap(a, b);
    sz[a] += sz[b];
    p[b] = a;
}

void solve()
{
    cin >> n >> m >> s;
    fill(sz, sz + n + 1, 1);
    iota(p, p + n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        Edge[i] = {w, u, v, i};
    }
    sort(Edge, Edge + m, [](ar<ll, 4> a1, ar<ll, 4> a2) {
        return a1[0] > a2[0];
    });
    for (int i = 0; i < m; i++)
    {
        w = Edge[i][0], u = Edge[i][1], v = Edge[i][2];
        if (root(u) == root(v))
            continue;
        unite(u, v);
        used[i] = true;
    }
    ll sum = 0LL;
    for (int i = m - 1; i >= 0; i--)
    {
        if (used[i])
            continue;
        if (sum + Edge[i][0] <= s)
            sum += Edge[i][0];
        else
            break;
        ans.PB(Edge[i][3] + 1);
    }
    sort(all(ans));
    cout << (int)ans.size() << "\n";
    for (auto &x : ans)
        cout << x << " ";
    cout << "\n";
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