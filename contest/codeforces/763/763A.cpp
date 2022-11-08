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
typedef vector<int> vi;
typedef pair<int, int> pi;

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out()
{
    cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

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

using ll = long long;
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
const int N = 1e5 + 1;
bool subcol[N];
int col[N], ans = -1;
vi adj[N];

void subdfs(int V, int pV)
{
    int pre = col[V];
    subcol[V] = true;
    for (auto &e : adj[V])
    {
        if (e == pV)
            continue;
        subdfs(e, V);
        subcol[V] &= subcol[e];
        if (pre != col[e])
            subcol[V] = false;
    }
}
void dfs(int V, int pV)
{
    int f = 0, child = -1;
    if (subcol[V])
    {
        ans = V;
        return;
    }
    for (auto &e : adj[V])
    {
        if (e == pV)
            continue;
        if (!subcol[e])
        {
            f++;
            child = e;
        }
    }
    if (f >= 2)
        return;
    if (f == 1)
    {
        unordered_set<int, custom_hash> s1;
        for (int &e : adj[V])
        {
            if (e != child && e != pV)
            {
                s1.insert(col[e]);
            }
        }
        if ((int)s1.size() >= 2 || (col[V] != col[pV] && pV != 0))
            return;
        dfs(child, V);
    }
    if (f == 0)
        ans = V;
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].PB(v);
        adj[v].PB(u);
    }
    for (int i = 1; i <= n; i++)
        cin >> col[i];
    subdfs(1, 0);
    dfs(1, 0);
    if (ans == -1)
        cout << "NO\n";
    else
    {
        cout << "YES\n";
        cout << ans << "\n";
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