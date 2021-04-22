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
int arr[5] = {0, 1, 2, 5, 8};

void solve()
{
    int h, m;
    cin >> h >> m;
    string s;
    cin >> s;
    int time = 1000 * (s[0] - '0') + 100 * (s[1] - '0') + 10 * (s[3] - '0') + (s[4] - '0');
    vector<int> vec;
    int tmp = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                for (int l = 0; l < 5; l++)
                {
                    tmp = arr[i] * 1000 + arr[j] * 100 + arr[k] * 10 + arr[l];
                    vec.PB(tmp);
                }
            }
        }
    }
    sort(all(vec));
    int ans = -1;
    for (int i = 0; i < (int)vec.size(); i++)
    {
        if (vec[i] < time)
            continue;
        if (vec[i] / 100 >= (h))
            continue;
        if (vec[i] % 100 >= m)
            continue;
        int val = vec[i];
        int h1 = val / 1000;
        val -= h1 * 1000;
        int h2 = val / 100;
        val -= h2 * 100;
        int m1 = val / 10;
        val -= m1 * 10;
        int m2 = val;
        int reversed = 0;
        if (h1 == 2)
        {
            reversed += 5;
        }
        else if (h1 == 5)
        {
            reversed += 2;
        }
        else
        {
            reversed += h1;
        }
        if (h2 == 2)
        {
            reversed += 50;
        }
        else if (h2 == 5)
        {
            reversed += 20;
        }
        else
        {
            reversed += h2 * 10;
        }
        if (m1 == 2)
        {
            reversed += 500;
        }
        else if (m1 == 5)
        {
            reversed += 200;
        }
        else
        {
            reversed += m1 * 100;
        }
        if (m2 == 2)
        {
            reversed += 5000;
        }
        else if (m2 == 5)
        {
            reversed += 2000;
        }
        else
        {
            reversed += m2 * 1000;
        }
        if (reversed / 100 >= h)
            continue;
        if (reversed % 100 >= m)
            continue;
        if (ans != -1)
            continue;
        ans = vec[i];
    }
    if (ans == -1)
    {
        cout << "00:00"
             << "\n";
    }
    else
    {
        int h1 = ans / 1000;
        ans -= h1 * 1000;
        int h2 = ans / 100;
        ans -= h2 * 100;
        int m1 = ans / 10;
        ans -= m1 * 10;
        int m2 = ans;
        cout << h1 << h2 << ":" << m1 << m2 << "\n";
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