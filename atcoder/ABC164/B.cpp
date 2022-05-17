#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int a, b, c, d;
    int is_ts_turn = 1;
    cin >> a >> b >> c >> d;
    while (a > 0 && c > 0)
    {
        if (is_ts_turn)
        {
            c -= b;
            is_ts_turn = (is_ts_turn + 1) % 2;
        }
        else
        {
            a -= d;
            is_ts_turn = (is_ts_turn + 1) % 2;
        }
    }
    if (a <= 0)
    {
        cout << "No"
             << "\n";
    }
    else
    {
        cout << "Yes"
             << "\n";
    }
    return 0;
}