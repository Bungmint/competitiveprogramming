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
    int n, k;
    cin >> n >> k;
    if (2 * k >= n)
    {
        int a = 2 * k - n, b = n - k;
        while (a--)
            cout << 1 << " ";
        while (b--)
            cout << 2 << " ";
        cout << "\n";
    }
    else
    {
        if (k % 2 == 0)
        {
            if (n % 2 == 0)
            {
                int off = (k - 4) / 2 + 1;
                cout << n / 2 - off << " " << n / 2 - off << " ";
                for (int i = 0; i < off * 2; i++)
                    cout << 1 << " ";
                cout << "\n";
            }
            else
            {
                if (n % 4 == 3)
                {
                    cout << n / 2 - 1 - (k - 4) << " " << n / 2 - 1 - (k - 4) << " ";
                    cout << 1 << " ";
                    for (int i = 0; i < k - 3; i++)
                        cout << 2 << " ";
                    cout << "\n";
                }
                else
                {
                    cout << n / 2 - (k - 4) << " " << n / 4 - (k - 4) / 2 << " " << n / 4 - (k - 4) / 2 << " " << 1 << " ";
                    for (int i = 0; i < k - 4; i++)
                        cout << 2 << " ";
                    cout << "\n";
                }
            }
        }
        else
        {
            if (n % 4 == 2)
            {
                cout << (n - 2) / 2 - (k - 3) << " " << (n - 2) / 2 - (k - 3) << " ";
                for (int i = 0; i < k - 2; i++)
                    cout << 2 << " ";
                cout << "\n";
            }
            else if (n % 4 == 0)
            {
                cout << n / 2 - (k - 3) << " " << n / 4 - (k - 3) / 2 << " " << n / 4 - (k - 3) / 2 << " ";
                for (int i = 0; i < k - 3; i++)
                    cout << 2 << " ";
                cout << "\n";
            }
            else
            {
                cout << n / 2 - (k - 3) / 2 << " " << n / 2 - (k - 3) / 2 << " ";
                for (int i = 0; i < k - 2; i++)
                    cout << 1 << " ";
                cout << "\n";
            }
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