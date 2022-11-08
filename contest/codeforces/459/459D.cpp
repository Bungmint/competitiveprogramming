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
const int N = 1e6 + 1;
ll v[N], n1, lcnt[N], rcnt[N];
unordered_map<int, int, custom_hash> l, r;

struct item
{
    ll val;
};

struct segtree
{
    int size;
    item NEUTRAL = {0};
    vector<item> vals;
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        vals.resize(2 * size);
    }
    item single(int va)
    {
        return {va};
    }
    item merge(item a, item b)
    {
        return {a.val + b.val};
    }
    void set(int i, int v, int x, int l, int r)
    {
        if (r - l == 1)
        {
            vals[x] = merge(vals[x], single(v));
            return;
        }
        int mid = (l + r) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, l, mid);
        else
            set(i, v, 2 * x + 2, mid, r);
        vals[x] = merge(vals[2 * x + 1], vals[2 * x + 2]);
    }
    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }
    item query(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return NEUTRAL;
        if (lx >= l && rx <= r)
            return vals[x];
        int mid = (lx + rx) / 2;
        item a = query(l, r, 2 * x + 1, lx, mid);
        item b = query(l, r, 2 * x + 2, mid, rx);
        return merge(a, b);
    }
    ll query(int l, int r)
    {
        return query(l, r, 0, 0, size).val;
    }
} st;

// void upd(ll *arr, int i, int val)
// {
//     for (; i <= n; i += (-i) & i)
//         arr[i] += val;
// }
// ll query(ll *arr, int i)
// {
//     ll ans = 0LL;
//     for (; i > 0; i -= (-i) & i)
//         ans += arr[i];
//     return ans;
// }

void solve()
{
    cin >> n1;
    st.init(n1 + 1);
    for (int i = 0; i < n1; i++)
    {
        cin >> v[i];
        l[v[i]]++;
        lcnt[i] = l[v[i]];
    }
    for (int i = n1 - 1; i >= 0; i--)
    {
        r[v[i]]++;
        rcnt[i] = r[v[i]];
    }
    ll ans = 0LL;
    for (int i = 0; i < n1; i++)
    {
        if (i > 0)
            ans += st.query(rcnt[i] + 1, n1 + 1);
        if (i < n1 - 1)
            st.set(lcnt[i], 1);
    }
    cout << ans << "\n";
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