#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int k = 0; k < t; k++)
    {
        string s;
        cin >> s;
        if (s[0] != 'a' && s[s.length() - 1] != 'a')
        {
            s.push_back('a');
            cout << "YES"
                 << "\n";
            cout << s << "\n";
        }
        else if (s[0] == 'a' && (s[s.length() - 1] != 'a'))
        {
            cout << "YES"
                 << "\n";
            cout << 'a' + s << "\n";
        }
        else if (s[0] != 'a' && s[s.length() - 1] == 'a')
        {
            s.push_back('a');
            cout << "YES"
                 << "\n";
            cout << s << "\n";
        }
        else
        {
            bool is_impos = true;
            for (int i = 0; i < s.length() / 2; i++)
            {
                if (s[s.length() - 1 - i] != 'a' && s[i] != 'a')
                {
                    is_impos = false;
                    s += 'a';
                    break;
                }
                else if (s[i] == 'a' && s[s.length() - 1 - i] != 'a')
                {
                    is_impos = false;
                    s = 'a' + s;
                    break;
                }
                else if (s[i] != 'a' && s[s.length() - 1 - i] == 'a')
                {
                    is_impos = false;
                    s = s + 'a';
                    break;
                }
            }
            if (is_impos)
            {
                if (s.length() % 2 == 1)
                {
                    if (s[s.length() / 2] != 'a')
                    {
                        cout << "YES"
                             << "\n";
                        cout << s + 'a' << "\n";
                    }
                    else
                    {
                        cout << "NO"
                             << "\n";
                    }
                }
                else
                {
                    cout << "NO"
                         << "\n";
                }
            }
            else
            {
                cout << "YES"
                     << "\n";
                cout << s << "\n";
            }
        }
    }
    return 0;
}