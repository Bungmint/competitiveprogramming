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
const int N = 1e7;       // Only advised to use it under 1e7 (More Memory)
int lp[N + 1];
vector<int> pr;
void linsieve()
{
    for (int i = 2; i <= N; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
}

struct segtree
{
    int size;
    vector<int> vals;
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        vals.resize(2 * size);
    }
    void set(int i, int x, int l, int r)
    {
        if (r - l == 1)
        {
            vals[x]++;
            return;
        }
        int mid = (l + r) / 2;
        if (i < mid)
            set(i, 2 * x + 1, l, mid);
        else
            set(i, 2 * x + 2, mid, r);
        vals[x] = vals[2 * x + 1] + vals[2 * x + 2];
    }
    void set(int i)
    {
        set(i, 0, 0, size);
    }
    int query(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return 0;
        if (lx >= l && rx <= r)
            return vals[x];
        int mid = (lx + rx) / 2;
        int a = query(l, r, 2 * x + 1, lx, mid);
        int b = query(l, r, 2 * x + 2, mid, rx);
        return a + b;
    }
    int query(int l, int r)
    {
        return query(l, r, 0, 0, size);
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> vec(n);
    segtree st;
    st.init(10000001);
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        while (tmp > 1)
        {
            int prim = lp[tmp];
            while (tmp % prim == 0)
                tmp /= prim;
            st.set(prim);
        }
    }
    int m;
    cin >> m;
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, min(10000001, r + 1)) << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    linsieve();
    solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}