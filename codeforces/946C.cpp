#include <iostream>
#include <string>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(NULL);
    string s, alphabet, res;
    cin >> s;
    alphabet = "abcdefghijklmnopqrstuvwxyz";
    res = "";
    if (s.length() < 26)
    {
        cout << "-1"
             << "\n";
    }
    else
    {
        int i = 0;
        string alpha = "a";
        for (char const &c : s)
        {
            if (i < 26)
            {
                int idx = alpha.find(c);
                if (idx != string::npos)
                {
                    res.push_back(alpha[alpha.length() - 1]);
                    alpha.push_back(alphabet[i + 1]);
                    i++;
                }
                else
                {
                    res.push_back(c);
                }
            }
            else
            {
                res.push_back(c);
            }
        }
        if (i < 26)
        {
            cout << -1 << "\n";
        }
        else
        {
            cout << res << "\n";
        }
    }

    return 0;
}