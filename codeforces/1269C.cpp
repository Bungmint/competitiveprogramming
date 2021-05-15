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

void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> xdig(n), first_k(k);
    for (int i = 0; i < n; i++)
    {
        xdig[i] = s[i] - '0';
        if (i < k)
            first_k[i] = xdig[i];
    }
    bool pos = true;
    for (int i = 0; i < n; i++)
    {
        int idx = i % k;
        if (xdig[i] < first_k[idx])
        {
            pos = true;
            break;
        }
        if (xdig[i] == first_k[idx])
            continue;
        if (xdig[i] > first_k[idx])
        {
            pos = false;
            break;
        }
    }
    if (pos)
    {
        cout << n << "\n";
        for (int i = 0; i < n; i++)
        {
            cout << first_k[i % k];
        }
        cout << "\n";
    }
    else if (first_k[k - 1] != 9)
    {
        cout << n << "\n";
        first_k[k - 1]++;
        for (int i = 0; i < n; i++)
        {
            cout << first_k[i % k];
        }
        cout << "\n";
    }
    else
    {
        first_k[k - 1]++;
        for (int i = k - 1; i >= 0; i--)
        {
            if (first_k[i] == 10)
            {
                first_k[i] = 0;
                first_k[i - 1]++;
            }
            else
            {
                break;
            }
        }
        cout << n << "\n";
        for (int i = 0; i < n; i++)
        {
            cout << first_k[i % k];
        }
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