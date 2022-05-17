#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define ar array
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

void solve()
{
    int a, b;
    cin >> a >> b;
    string s;
    cin >> s;
    bool is_pos = true;
    if (a % 2 == 1 && b % 2 == 1)
        is_pos = false;
    int cur_ones = 0, cur_zeros = 0;
    for (int i = 0; i < a + b; i++)
    {
        if (s[i] == '0')
        {
            cur_zeros++;
            if (s[a + b - 1 - i] == '1')
                is_pos = false;
        }
        else if (s[i] == '1')
        {
            cur_ones++;
            if (s[a + b - 1 - i] == '0')
                is_pos = false;
        }
        else
        {
            if (s[a + b - 1 - i] == '0')
            {
                cur_zeros++;
                s[i] = '0';
            }
            else if (s[a + b - 1 - i] == '1')
            {
                cur_ones++;
                s[i] = '1';
            }
        }
    }
    if (a < cur_zeros || b < cur_ones)
        is_pos = false;
    if (abs(a - cur_zeros) % 2 == 1 && abs(b - cur_ones) % 2 == 1)
    {
        is_pos = false;
    }
    if (!is_pos)
        cout << -1 << "\n";
    else
    {
        for (int i = 0; i < a + b; i++)
        {
            if (s[i] == '?')
            {
                if ((a + b) % 2 == 1 && i == (a + b - 1) / 2)
                {
                    if (a % 2 == 1)
                    {
                        s[i] = '0';
                        cur_zeros += 1;
                    }
                    else
                    {
                        s[i] = '1';
                        cur_ones += 1;
                    }
                }
                else
                {
                    if (a - cur_zeros >= 2)
                    {
                        s[i] = '0';
                        s[a + b - 1 - i] = '0';
                        cur_zeros += 2;
                    }
                    else if (b - cur_ones >= 2)
                    {
                        s[i] = '1';
                        s[a + b - 1 - i] = '1';
                        cur_ones += 2;
                    }
                }
            }
        }
        cout << s << "\n";
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
}