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

void solve()
{
    string s;
    cin >> s;
    int digits[10];
    memset(digits, 0, sizeof(digits));
    for (int i = 0; i < (int)s.length(); i++)
        digits[s[i] - '0']++;
    if ((int)s.length() == 1)
    {
        if ((s[0] - '0') % 8 == 0)
        {
            cout << "Yes"
                 << "\n";
            return;
        }
        cout << "No"
             << "\n";
        return;
    }
    else if ((int)s.length() == 2)
    {
        int a = s[0] - '0', b = s[1] - '0';
        if ((a * 10 + b) % 8 == 0 || (a + 10 * b) % 8 == 0)
        {
            cout << "Yes"
                 << "\n";
            return;
        }
        cout << "No"
             << "\n";
        return;
    }
    if (digits[8] > 2)
    {
        cout << "Yes"
             << "\n";
        return;
    }
    for (int i = 1; i < 10; i++)
    {
        if (digits[i] >= 2)
        {
            for (int j = 1; j < 10; j++)
            {
                if (digits[j] >= 1 && j != i)
                {
                    int n1 = 100 * (i) + 10 * (i) + j, n2 = 100 * (i) + 10 * (j) + i, n3 = 100 * (j) + 10 * (i) + i;
                    if ((n1 % 8 == 0) || (n2 % 8 == 0) || (n3 % 8 == 0))
                    {
                        cout << "Yes"
                             << "\n";
                        return;
                    }
                }
            }
        }
        if (digits[i] == 1)
        {
            for (int j = 1; j < 10; j++)
            {
                if (digits[j] > 0 && j != i)
                {
                    for (int k = 1; k < 10; k++)
                    {
                        if (digits[k] > 0 && k != i && k != j)
                        {
                            if ((100 * (i) + 10 * (j) + k) % 8 == 0)
                            {
                                cout << "Yes"
                                     << "\n";
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "No"
         << "\n";
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