#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        if (s[0] != '1' || s[s.length() - 1] != '1')
        {
            cout << "NO"
                 << "\n";
        }
        else
        {
            int zero_count = 0, one_count = 0;
            string a, b;
            int tog = 0;
            for (int i = 0; i < n; i++)
            {
                if (s[i] == '0')
                    zero_count++;
                if (s[i] == '1')
                    one_count++;
            }
            if (zero_count % 2 != 0)
            {
                cout << "NO"
                     << "\n";
            }
            else
            {
                int half = one_count / 2;
                one_count = 0;
                for (int i = 0; i < n; i++)
                {
                    if (s[i] == '0')
                    {
                        if (tog)
                        {
                            a.push_back('(');
                            b.push_back(')');
                        }
                        else
                        {
                            a.push_back(')');
                            b.push_back('(');
                        }
                        tog = (tog + 1) % 2;
                    }
                    else
                    {
                        if (one_count < half)
                        {
                            a.push_back('(');
                            b.push_back('(');
                        }
                        else
                        {
                            a.push_back(')');
                            b.push_back(')');
                        }
                        one_count++;
                    }
                }
                cout << "YES"
                     << "\n";
                cout << a << "\n";
                cout << b << "\n";
            }
        }
    }
    return 0;
}