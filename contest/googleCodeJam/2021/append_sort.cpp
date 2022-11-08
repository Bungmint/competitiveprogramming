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

void solve(int t)
{
    int n;
    cin >> n;
    vector<string> vec(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    int ans = 0;
    for (int i = 1; i < n; i++)
    {
        string prev = vec[i - 1], cur = vec[i];
        if (prev.length() < cur.length())
            continue;
        else if (prev.length() == cur.length())
        {
            if (prev < cur)
                continue;
            cur += '0';
            ans++;
            vec[i] = cur;
        }
        else
        {
            if (prev.substr(0, cur.length()) < cur)
            {
                while (cur.length() < prev.length())
                {
                    cur += '0';
                    ans++;
                }
                vec[i] = cur;
            }
            else if (prev.substr(0, cur.length()) == cur)
            {
                string prev_plus = prev;
                int numNine = 0, j = prev.length() - 1;
                while (prev[j] == '9' && j >= 0)
                {
                    j--;
                    numNine++;
                }
                if (numNine == (int)prev.length())
                {
                    prev_plus += '0';
                    for (int k = 1; k < (int)prev_plus.length(); k++)
                    {
                        prev_plus[i] = '0';
                    }
                }
                else
                {
                    for (int k = 0; k < numNine; k++)
                    {
                        prev_plus[prev.length() - 1 - k] = '0';
                    }
                    prev_plus[prev.length() - 1 - numNine]++;
                }
                if (prev_plus.substr(0, cur.length()) == cur && prev_plus.length() == prev.length())
                {
                    ans += prev_plus.length() - cur.length();
                    cur = prev_plus;
                }
                else if (prev_plus.substr(0, cur.length()) < cur && prev_plus.length() == prev.length())
                {
                    while (cur.length() < prev.length())
                    {
                        cur += '0';
                        ans++;
                    }
                }
                else
                {
                    while (cur.length() <= prev.length())
                    {
                        cur += '0';
                        ans++;
                    }
                }
                vec[i] = cur;
            }
            else
            {
                while (cur.length() <= prev.length())
                {
                    cur += '0';
                    ans++;
                }
                vec[i] = cur;
            }
        }
    }
    cout << "Case #" << t << ": " << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        solve(i);
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}