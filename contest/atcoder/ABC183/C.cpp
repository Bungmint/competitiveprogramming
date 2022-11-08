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
int N = 0, n, k;
vector<int> perm;
vector<vector<int>> vec;
bool chosen[10];
void search()
{
    if ((int)perm.size() == n - 1)
    {
        int ans = 0;
        ans += vec[0][perm[0] - 1];
        ans += vec[perm[n - 2] - 1][0];
        for (int i = 0; i < n - 2; i++)
            ans += vec[perm[i] - 1][perm[i + 1] - 1];
        if (ans == k)
            N++;
    }
    else
    {
        for (int i = 2; i <= n; i++)
        {
            if (chosen[i])
                continue;
            chosen[i] = true;
            perm.PB(i);
            search();
            chosen[i] = false;
            perm.pop_back();
        }
    }
}
void solve()
{
    cin >> n >> k;
    memset(chosen, false, sizeof(chosen));
    vec = vector<vector<int>>(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> vec[i][j];
        }
    }
    search();
    cout << N << "\n";
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