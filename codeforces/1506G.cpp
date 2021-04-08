#include <bits/stdc++.h>
using namespace std;

int distinct(string s)
{
    sort(s.begin(), s.end());
    return unique(s.begin(), s.end()) - s.begin();
}

string filter(const string &s, char c)
{
    string t;
    bool foundFirst = false;
    for (char a : s)
    {
        if (a != c && foundFirst)
        {
            t += a;
        }
        else if (a == c)
        {
            foundFirst = true;
        }
    }
    return t;
}

void solve()
{
    string s;
    cin >> s;
    int m = distinct(s);
    unordered_set<char> used(s.begin(), s.end());
    string t;
    while (m > 0)
    {
        char maxC = -1;
        for (char c : used)
        {
            if (distinct(filter(s, c)) == m - 1)
            {
                maxC = max(maxC, c);
            }
        }
        t += maxC;
        s = filter(s, maxC);
        used.erase(maxC);
        m--;
    }
    cout << t << "\n";
}

int main()
{
    int tests;
    cin >> tests;
    while (tests-- > 0)
    {
        solve();
    }
    return 0;
}