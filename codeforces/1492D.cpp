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
int s1[200000], s2[200000];

void solve()
{
    memset(s1, 0, sizeof(s1));
    memset(s2, 0, sizeof(s2));
    int a, b, k;
    cin >> a >> b >> k;
    if (a == 0)
    {
        if (k != 0)
            cout << "No"
                 << "\n";
        else
        {
            cout << "Yes"
                 << "\n";
            for (int i = 0; i < a + b; i++)
            {
                cout << 1;
            }
            cout << "\n";
            for (int i = 0; i < a + b; i++)
            {
                cout << 1;
            }
            cout << "\n";
        }
        return;
    }
    if (b == 1)
    {
        if (k != 0)
            cout << "No"
                 << "\n";
        else
        {
            cout << "Yes"
                 << "\n";
            s1[0] = 1;
            s2[0] = 1;
            for (int i = 0; i < a + b; i++)
            {
                cout << s1[i];
            }
            cout << "\n";
            for (int i = 0; i < a + b; i++)
            {
                cout << s2[i];
            }
            cout << "\n";
        }
        return;
    }
    if (k >= a + b - 1)
    {
        cout << "No"
             << "\n";
        return;
    }
    s1[0] = s2[0] = 1;
    int diff = a + b - k - 1, cnt = 2;
    s1[diff] = 1;
    s2[a + b - 1] = 1;
    for (int i = 1; i < a + b; i++)
    {
        if (i == diff)
            continue;
        if (cnt == b)
            break;
        s1[i] = 1;
        cnt++;
    }
    cnt = 2;
    for (int i = 1; i < a + b; i++)
    {
        if (i == diff)
            continue;
        if (cnt == b)
            break;
        s2[i] = 1;
        cnt++;
    }
    cout << "Yes"
         << "\n";
    for (int i = 0; i < a + b; i++)
    {
        cout << s1[i];
    }
    cout << "\n";
    for (int i = 0; i < a + b; i++)
    {
        cout << s2[i];
    }
    cout << "\n";
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