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
int fag, meh[2][2] = {1, 0, 0, 1};

struct matrix
{
    int m[2][2];
    matrix()
    {
        m[0][0] = 1;
        m[0][1] = 0;
        m[1][0] = 0;
        m[1][1] = 1;
    }
    matrix operator*(matrix a)
    {
        matrix b = matrix();
        memset(b.m, 0, sizeof(b.m));
        for (int i = 0; i < 2; i++)
        {
            for (int k = 0; k < 2; k++)
            {
                for (int j = 0; j < 2; j++)
                {
                    b.m[i][j] = (b.m[i][j] + m[i][k] * a.m[k][j]) % fag;
                }
            }
        }
        return b;
    }
};

struct segtree
{
    int size;
    matrix NEUTRAL;
    vector<matrix> vals;
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        vals.resize(2 * size);
    }
    matrix merge(matrix a, matrix b)
    {
        return a * b;
    }

    void build(vector<matrix> &vec, int x, int l, int r)
    {
        if (r - l == 1)
        {
            if (l < (int)vec.size())
                vals[x] = vec[l];
            return;
        }
        int mid = (l + r) / 2;
        build(vec, 2 * x + 1, l, mid);
        build(vec, 2 * x + 2, mid, r);
        vals[x] = merge(vals[2 * x + 1], vals[2 * x + 2]);
    }
    void build(vector<matrix> &vec)
    {
        build(vec, 0, 0, size);
    }
    matrix query(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r || rx <= l)
            return NEUTRAL;
        if (lx >= l && rx <= r)
            return vals[x];
        int mid = (lx + rx) / 2;
        matrix a = query(l, r, 2 * x + 1, lx, mid);
        matrix b = query(l, r, 2 * x + 2, mid, rx);
        return merge(a, b);
    }
    matrix query(int l, int r)
    {
        return query(l, r, 0, 0, size);
    }
};

void solve()
{
    int n, m;
    cin >> fag >> n >> m;

    vector<matrix> vec(n);
    for (int i = 0; i < n; i++)
    {
        int a, b, c, d;
        matrix tmp;
        cin >> a >> b >> c >> d;
        tmp.m[0][0] = a;
        tmp.m[0][1] = b;
        tmp.m[1][0] = c;
        tmp.m[1][1] = d;
        vec[i] = tmp;
    }
    segtree st;
    cout << "\n";
    st.init(n);
    st.build(vec);
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        matrix res = st.query(l - 1, r);
        cout << res.m[0][0] << " " << res.m[0][1] << "\n";
        cout << res.m[1][0] << " " << res.m[1][1] << "\n";
        cout << "\n";
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