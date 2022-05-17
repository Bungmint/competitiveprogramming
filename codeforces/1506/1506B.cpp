#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        int last;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '*')
                last = i;
        }
        int counter = 0, prev = -1, i = 0;
        while (i < n)
        {
            if (prev == -1 && s[i] == '*')
            {
                counter++;
                prev = i;
                while (i < last)
                {
                    i = i + k;
                    while (s[i] != '*')
                    {
                        i--;
                    }
                    counter++;
                }
            }
            i++;
        }
        cout << counter << "\n";
    }
}