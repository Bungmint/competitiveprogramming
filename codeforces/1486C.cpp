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
    int n;
    cin >> n;
    cout << "? " << 1 << " " << n << "\n";
    cout.flush();
    int second, idx, ans;
    cin >> second;
    if (second != 1 && second != n)
    {
        cout << "? " << 1 << " " << second << "\n";
        cout.flush();
        cin >> idx;
        if (idx == second)
        {
            int l = 1, r = second - 1, tmp;
            while (l <= r)
            {
                int mid = l + (r - l) / 2;
                if (r == l)
                {
                    ans = l;
                    break;
                }
                if (r - l == 1)
                {
                    cout << "? " << r << " " << second << "\n";
                    cout.flush();
                    cin >> tmp;
                    if (tmp == second)
                        ans = r;
                    else
                        ans = l;
                    break;
                }
                cout << "? " << mid << " " << second << "\n";
                cout.flush();
                cin >> tmp;
                if (tmp == second)
                {
                    l = mid;
                }
                else
                {
                    r = mid - 1;
                }
            }
        }
        else
        {
            int l = second + 1, r = n, tmp;
            while (l <= r)
            {
                int mid = l + (r - l) / 2;
                if (r == l)
                {
                    ans = r;
                    break;
                }
                if (r - l == 1)
                {
                    cout << "? " << second << " " << l << "\n";
                    cout.flush();
                    cin >> tmp;
                    if (tmp == second)
                        ans = l;
                    else
                        ans = r;
                    break;
                }
                cout << "? " << second << " " << mid << "\n";
                cout.flush();
                cin >> tmp;
                if (tmp == second)
                {
                    r = mid;
                }
                else
                {
                    l = mid + 1;
                }
            }
        }
    }
    else if (second == 1)
    {
        int l = 2, r = n, tmp;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (r == l)
            {
                ans = r;
                break;
            }
            if (r - l == 1)
            {
                cout << "? " << second << " " << l << "\n";
                cout.flush();
                cin >> tmp;
                if (tmp == second)
                    ans = l;
                else
                    ans = r;
                break;
            }
            cout << "? " << second << " " << mid << "\n";
            cout.flush();
            cin >> tmp;
            if (tmp == second)
            {
                r = mid;
            }
            else
            {
                l = mid + 1;
            }
        }
    }
    else
    {
        int l = 1, r = n - 1, tmp;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (r == l)
            {
                ans = r;
                break;
            }
            if (r - l == 1)
            {
                cout << "? " << r << " " << second << "\n";
                cout.flush();
                cin >> tmp;
                if (tmp == second)
                    ans = r;
                else
                    ans = l;
                break;
            }
            cout << "? " << mid << " " << second << "\n";
            cout.flush();
            cin >> tmp;
            if (tmp == second)
            {
                l = mid;
            }
            else
            {
                r = mid - 1;
            }
        }
    }
    cout << "! " << ans << "\n";
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