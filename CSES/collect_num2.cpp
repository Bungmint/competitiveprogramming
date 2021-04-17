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
bool vis[200001];

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> pos(n + 2);
    vector<int> arr(n);
    int rounds = n;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        arr[i] = tmp;
        vis[tmp] = true;
        if (vis[tmp - 1])
            rounds--;
        pos[tmp] = i + 1;
    }
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        if (a >= b)
            swap(a, b);
        int x = arr[a - 1], y = arr[b - 1];
        if (x == y + 1)
        {
            rounds--;
            if (pos[x + 1] < b && pos[x + 1] > a)
                rounds++;
            if (pos[y - 1] > a && pos[y - 1] < b)
                rounds++;
        }
        else if (x + 1 == y)
        {
            rounds++;
            if (pos[y + 1] > a && pos[y + 1] < b)
            {
                rounds--;
            }
            if (pos[x - 1] > a && pos[x - 1] < b)
                rounds--;
        }
        else if (a == b)
        {
        }
        else
        {
            if (pos[x - 1] > a && pos[x - 1] < b)
                rounds--;
            if (pos[x + 1] < b && pos[x + 1] > a)
                rounds++;
            if (pos[y - 1] > a && pos[y - 1] < b)
                rounds++;
            if (pos[y + 1] > a && pos[y + 1] < b)
                rounds--;
        }
        cout << rounds << "\n";
        swap(arr[a - 1], arr[b - 1]);
        swap(pos[x], pos[y]);
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
