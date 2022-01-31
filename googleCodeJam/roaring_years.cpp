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
ll mini[] = {-1, 0, 123, 0, 12345, 0, 1234567, 0, 100101102, 0, 12345678910, 0, 1234567891011, 0, 100001000110002, 0, 12345678910111213, 0, 1234567891011121314};

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

ll pow(ll base, ll exp)
{
    if (exp == 0)
        return 0LL;
    if (exp == 1)
        return base;
    ll m = pow(base, exp / 2);
    if (exp % 2 == 0)
    {
        return m * m;
    }
    else
        return m * m * base;
}

void solve()
{
    string y;
    cin >> y;
    ll len = y.length();
    if (len == 1)
    {
        cout << 12 << "\n";
        return;
    }
    if (len == 19)
    {
        cout << mini[18] << "\n";
    }
    ll max_pos = 0;
    if (len % 2 == 0)
        max_pos = (pow(10LL, len / 2) - 2) * pow(10LL, len / 2) + pow(10LL, len / 2) - 1;
    else
        max_pos = (pow(10LL, len / 2) - 1) * pow(10LL, len - len / 2) + pow(10LL, len / 2);
    if (stoll(y) >= max_pos)
    {
        if (len % 2 == 0)
        {
            cout << mini[len] << "\n";
            return;
        }
        else
        {
            cout << pow(10LL, len) + pow(10LL, (len) / 2) + 1LL << "\n";
            return;
        }
        return;
    }
    ll ans = LLONG_MAX;
    for (int k = 0; k < len; k++)
    {
        char tmp = y[k];

        for (int i = (y[k] - '0'); i <= 9; i++)
        {
            y[k] = '0' + i;
            ll local = LLONG_MAX;
            for (int j = 1; j < len; j++)
            {
                if (j > len / 2)
                    break;
                string m = y.substr(0, j);
                ll val = stoll(m);
                while ((int)m.length() < len)
                {
                    val++;
                    m += to_string(val);
                }
                if ((int)m.length() > len)
                    continue;
                if (stoll(m) <= stoll(y))
                    continue;
                local = min(local, stoll(m));
            }
            ans = min(ans, local);
        }
        y[k] = tmp;
    }

    if (ans == LLONG_MAX)
    {
        cout << mini[len] << "\n";
    }
    else
        cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        cout << "CASE #" << i << ": ";
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}