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
int n;

int ask(int t, int i, int j, int x)
{
    if (i > n)
        i -= n;
    if (j > n)
        j -= n;
    int res;
    cout << "? " << t << " " << i << " " << j << " " << x << endl;
    cin >> res;
    return res;
}

void solve()
{
    cin >> n;
    vector<int> ans(n);
    set<int> used;
    if (n == 3)
    {
        int res1, res2, idx;
        for (int i = 1; i <= 3; i++)
        {
            res1 = ask(1, i, i + 1, 1);
            if (res1 == 1)
            {
                ans[i % 3] = 1;
                idx = i % 3;
                break;
            }
        }
        int idx2 = (idx + 1) % 3, idx3 = (idx + 2) % 3;
        res2 = ask(2, idx2 + 1, idx3 + 1, 2);
        if (res2 == 3)
        {
            ans[idx2] = 3;
            ans[idx3] = 2;
        }
        else
        {
            ans[idx2] = 2;
            ans[idx3] = 3;
        }
        cout << "! ";
        cout.flush();
        for (auto x : ans)
        {
            cout << x << " ";
            cout.flush();
        }
        cout << endl;
        return;
    }
    for (int i = 1; i <= n / 2; i++)
    {
        int j = n - i + 1;
        int res1 = ask(1, i, j, n - 1), res2 = ask(2, i, j, 1);
        if (res1 == n)
        {
            ans[j - 1] = n;
            ans[i - 1] = res2;
            continue;
        }
        else if (res2 == 1)
        {
            ans[i - 1] = 1;
            ans[j - 1] = res1;
            continue;
        }
        if (res1 == n - 1)
        {
            int res3 = ask(1, j, i, n - 1);
            int res4 = ask(2, j, i, 1);
            if (res3 == n)
            {
                ans[i - 1] = n;
                ans[j - 1] = res4;
            }
            else if (res4 == 1)
            {
                ans[j - 1] = 1;
                ans[i - 1] = n - 1;
            }
            else
            {
                int res5 = ask(2, i, j, n - 2);
                if (res5 == n - 2)
                {
                    ans[i - 1] = res4;
                    ans[j - 1] = n - 1;
                }
                else
                {
                    ans[j - 1] = res4;
                    ans[i - 1] = n - 1;
                }
            }
            continue;
        }
        if (res2 == 2)
        {
            int res3 = ask(2, j, i, 1);
            if (res3 == 1)
            {
                ans[i - 1] = res1;
                ans[j - 1] = 1;
            }
            else
            {
                int res5 = ask(1, i, j, 2);
                if (res5 == 2)
                {
                    ans[i - 1] = res1;
                    ans[j - 1] = 2;
                }
                else
                {
                    ans[j - 1] = res1;
                    ans[i - 1] = 2;
                }
            }
            continue;
        }
        int res3 = ask(2, i, j, res2);
        if (res3 == res2)
        {
            ans[i - 1] = res2;
            ans[j - 1] = res1;
        }
        else
        {
            ans[i - 1] = res1;
            ans[j - 1] = res2;
        }
    }
    if (n % 2)
    {
        int i = n / 2 + 1;
        int j = i + 1, val = ans[j - 1];
        int res1 = ask(1, i, j, n - 1), res2 = ask(2, i, j, 1);
        if (val == n)
        {
            ans[i - 1] = res2;
        }
        else if (val == n - 1)
        {
            if (res2 == n - 1)
            {
                ans[i - 1] = n;
            }
            else
            {
                ans[i - 1] = res2;
            }
        }
        else if (val == 1)
        {
            if (res1 == n - 1)
            {
                int res3 = ask(2, i, j, n - 1);
                if (res3 == n)
                    ans[i - 1] = n;
                else
                    ans[i - 1] = n - 1;
            }
            else
            {
                ans[i - 1] = res1;
            }
        }
        else if (val == 2)
        {
            if (res2 == 1)
                ans[i - 1] = 1;
            else
            {
                if (res1 == n - 1)
                {
                    int res3 = ask(2, i, j, n - 1);
                    if (res3 == n)
                        ans[i - 1] = n;
                    else
                        ans[i - 1] = n - 1;
                }
                else
                {
                    ans[i - 1] = res1;
                }
            }
        }
        else
        {
            if (res1 == n - 1)
            {
                int res3 = ask(2, i, j, n - 1);
                if (res3 == n)
                    ans[i - 1] = n;
                else
                    ans[i - 1] = n - 1;
            }
            else
            {
                ans[i - 1] = (res1 == val) ? res2 : res1;
            }
        }
    }
    cout << "! ";
    cout.flush();
    for (auto x : ans)
    {
        cout << x << " ";
        cout.flush();
    }
    cout << endl;
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