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
const int N = 3e4 + 100;
unordered_map<int, int, custom_hash> m1;
int arr[N], BIT[N];
vector<int> ls[N];

void upd(int i)
{
    i++;
    for (int j = i; j < N; j += j & (-j))
        BIT[j]++;
}
int query(int i)
{
    i++;
    int ans = 0;
    while (i > 0)
    {
        ans += BIT[i];
        i -= i & (-i);
    }
    return ans;
}

bool cmp(ar<int, 4> tp1, ar<int, 4> tp2)
{
    return tp1[0] > tp2[0];
}

void solve()
{
    int n;
    cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        vec[i] = arr[i];
    }
    sort(all(vec));
    vec.resize(unique(all(vec)) - vec.begin());
    for (int i = 0; i < (int)vec.size(); i++)
        m1[vec[i]] = i;
    for (int i = 0; i < n; i++)
    {
        ls[m1[arr[i]]].PB(i);
    }
    int q;
    cin >> q;
    vector<ar<int, 4>> quer(q);
    vector<int> ans(q);
    for (int i = 0; i < q; i++)
    {
        int k, j, m;
        cin >> k >> j >> m;
        int idx = upper_bound(all(vec), m) - vec.begin();
        quer[i] = {idx, k - 1, j - 1, i};
    }
    sort(all(quer), cmp);
    int prev = (int)vec.size();
    for (int i = 0; i < q; i++)
    {
        if (quer[i][0] == (int)vec.size())
        {
            ans[quer[i][3]] = 0;
            continue;
        }
        for (int j = prev - 1; j >= quer[i][0]; j--)
        {
            for (auto x : ls[j])
            {
                upd(x);
            }
        }
        prev = quer[i][0];
        ans[quer[i][3]] = query(quer[i][2]) - query(quer[i][1] - 1);
    }
    for (auto x : ans)
        cout << x << "\n";
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