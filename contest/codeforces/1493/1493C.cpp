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
int arr[26];

void solve()
{
    memset(arr, 0, sizeof(arr));
    ll n, k;
    string s;
    cin >> n >> k >> s;
    if (n % k != 0)
    {
        cout << -1 << "\n";
    }
    else
    {
        unordered_map<char, ll> map1;
        int idx = -1;
        char change = '0';
        map1.reserve(1024);
        map1.max_load_factor(0.25);
        for (ll i = 0; i < n; i++)
        {
            map1[s[i]]++;
            if (s[i] == 'z')
                continue;
            map1[s[i]]--;
            for (int j = 1; j <= 25; j++)
            {
                if (s[i] + j > 'z')
                    break;
                map1[s[i] + j]++;
                ll need = 0;
                for (auto x : map1)
                {
                    if (x.second % k != 0)
                        need += (k - x.second % k);
                }
                if (need <= n - 1 - i)
                {
                    idx = i;
                    change = s[i] + j;
                    map1[s[i] + j]--;
                    break;
                }
                map1[s[i] + j]--;
            }
            map1[s[i]]++;
        }
        bool is_val = true;
        for (auto x : map1)
        {
            if (x.second % k != 0)
                is_val = false;
        }
        if (is_val)
        {
            cout << s << "\n";
            return;
        }
        map1.clear();
        if (idx == -1)
            cout << s << "\n";
        else
        {
            string ans = s;
            for (int i = 0; i < idx; i++)
            {
                map1[s[i]]++;
            }
            map1[change]++;
            ans[idx] = change;
            ll leftovers = n - 1 - idx;
            for (auto x : map1)
            {
                if (x.second % k == 0)
                    continue;
                leftovers -= (k - x.second % k);
                arr[x.first - 'a'] = k - x.second % k;
            }
            for (int i = idx + 1; i <= idx + leftovers; i++)
            {
                ans[i] = 'a';
            }
            int point = idx + leftovers + 1;
            for (int i = 0; i < 26; i++)
            {
                for (int j = 0; j < arr[i]; j++)
                {
                    ans[point] = 'a' + i;
                    point++;
                }
            }
            cout << ans << "\n";
        }
    }
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
