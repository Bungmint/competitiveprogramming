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
int ansi, ansj, ansk, ansl;

void mi(int a, int b, int c, int d, int &res)
{
    int t1 = abs(a - b);
    int t2 = abs(a - c);
    int t3 = abs(a - d);
    int t4 = abs(d - b);
    int t5 = abs(c - b);
    int t6 = abs(d - c);
    if (res > max({t1, t2, t3, t4, t5, t6}))
    {
        ansi = a, ansj = b, ansk = c, ansl = d;
        res = max({t1, t2, t3, t4, t5, t6});
    }
}

void solve()
{
    int a, b, c, d;
    vector<int> v1, v2, v3, v4;
    cin >> a;
    v1.resize(a);
    for (int i = 0; i < a; i++)
        cin >> v1[i];
    cin >> b;
    v2.resize(b);
    for (int i = 0; i < b; i++)
        cin >> v2[i];
    cin >> c;
    v3.resize(c);
    for (int i = 0; i < c; i++)
        cin >> v3[i];
    cin >> d;
    v4.resize(d);
    for (int i = 0; i < d; i++)
        cin >> v4[i];
    sort(all(v1));
    sort(all(v2));
    sort(all(v3));
    sort(all(v4));
    int i = 0, j = 0, k = 0, l = 0;
    int res = INF;
    while (i < a || j < b || k < c || l < d)
    {
        if (i == a && j == b && k == c)
        {
            mi(v1[i - 1], v2[j - 1], v3[k - 1], v4[l], res);
            l++;
            continue;
        }
        if (i == a && j == b && l == d)
        {
            mi(v1[i - 1], v2[j - 1], v3[k], v4[l - 1], res);
            k++;
            continue;
        }
        if (i == a && l == d && k == c)
        {
            mi(v1[i - 1], v2[j], v3[k - 1], v4[l - 1], res);
            j++;
            continue;
        }
        if (l == d && j == b && k == c)
        {
            mi(v1[i], v2[j - 1], v3[k - 1], v4[l - 1], res);
            i++;
            continue;
        }
        if (i == a && j == b)
        {
            if (v3[k] <= v4[l])
            {
                mi(v1[a - 1], v2[b - 1], v3[k], v4[l], res);
                k++;
            }
            else
            {
                mi(v1[a - 1], v2[b - 1], v3[k], v4[l], res);
                l++;
            }
            continue;
        }
        if (i == a && k == c)
        {
            if (v2[j] <= v4[l])
            {
                mi(v1[a - 1], v2[j], v3[c - 1], v4[l], res);
                j++;
            }
            else
            {
                mi(v1[a - 1], v2[j], v3[c - 1], v4[l], res);
                l++;
            }
            continue;
        }
        if (i == a && l == d)
        {
            if (v2[j] <= v3[k])
            {
                mi(v1[a - 1], v2[j], v3[k], v4[l - 1], res);
                j++;
            }
            else
            {
                mi(v1[a - 1], v2[j], v3[k], v4[l - 1], res);
                k++;
            }
            continue;
        }
        if (k == c && j == b)
        {
            if (v1[i] <= v4[l])
            {
                mi(v1[i], v2[b - 1], v3[k - 1], v4[l], res);
                i++;
            }
            else
            {
                mi(v1[i], v2[b - 1], v3[k - 1], v4[l], res);
                l++;
            }
            continue;
        }
        if (l == d && j == b)
        {
            if (v1[i] <= v3[k])
            {
                mi(v1[i], v2[b - 1], v3[k], v4[l - 1], res);
                i++;
            }
            else
            {
                mi(v1[i], v2[b - 1], v3[k], v4[l - 1], res);
                k++;
            }
            continue;
        }
        if (k == c && l == d)
        {
            if (v1[i] <= v2[j])
            {
                mi(v1[i], v2[j], v3[k - 1], v4[l - 1], res);
                i++;
            }
            else
            {
                mi(v1[i], v2[j], v3[k - 1], v4[l - 1], res);
                j++;
            }
            continue;
        }
        if (l == d)
        {
            if (v1[i] <= v2[j] && v1[i] <= v3[k])
            {
                mi(v1[i], v2[j], v3[k], v4[l - 1], res);
                i++;
            }
            else if (v2[j] <= v1[i] && v2[j] <= v3[k])
            {
                mi(v1[i], v2[j], v3[k], v4[l - 1], res);
                j++;
            }
            else
            {
                mi(v1[i], v2[j], v3[k], v4[l - 1], res);
                k++;
            }
            continue;
        }
        if (k == c)
        {
            if (v1[i] <= v2[j] && v1[i] <= v4[l])
            {
                mi(v1[i], v2[j], v3[k - 1], v4[l], res);
                i++;
            }
            else if (v2[j] <= v1[i] && v2[j] <= v4[l])
            {
                mi(v1[i], v2[j], v3[k - 1], v4[l], res);
                j++;
            }
            else
            {
                mi(v1[i], v2[j], v3[k - 1], v4[l], res);
                l++;
            }
            continue;
        }
        if (i == a)
        {
            if (v4[l] <= v2[j] && v4[l] <= v3[k])
            {
                mi(v1[i - 1], v2[j], v3[k], v4[l], res);
                l++;
            }
            else if (v2[j] <= v4[l] && v2[j] <= v3[k])
            {
                mi(v1[i - 1], v2[j], v3[k], v4[l], res);
                j++;
            }
            else
            {
                mi(v1[i - 1], v2[j], v3[k], v4[l], res);
                k++;
            }
            continue;
        }
        if (j == b)
        {
            if (v1[i] <= v4[l] && v1[i] <= v3[k])
            {
                mi(v1[i], v2[j - 1], v3[k], v4[l], res);
                i++;
            }
            else if (v4[l] <= v1[i] && v4[l] <= v3[k])
            {
                mi(v1[i], v2[j - 1], v3[k], v4[l], res);
                l++;
            }
            else
            {
                mi(v1[i], v2[j - 1], v3[k], v4[l], res);
                k++;
            }
            continue;
        }
        if (v1[i] <= v2[j] && v1[i] <= v3[k] && v1[i] <= v4[l])
        {
            mi(v1[i], v2[j], v3[k], v4[l], res);
            i++;
        }
        else if (v2[j] <= v1[i] && v2[j] <= v3[k] && v2[j] <= v4[l])
        {
            mi(v1[i], v2[j], v3[k], v4[l], res);
            j++;
        }
        else if (v3[k] <= v2[j] && v3[k] <= v1[i] && v3[k] <= v4[l])
        {
            mi(v1[i], v2[j], v3[k], v4[l], res);
            k++;
        }
        else
        {
            mi(v1[i], v2[j], v3[k], v4[l], res);
            l++;
        }
    }
    cout << ansi << " " << ansj << " " << ansk << " " << ansl << "\n";
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