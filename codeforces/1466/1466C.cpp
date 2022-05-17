#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    string s;
    cin >> t;
    while (t--)
    {
        unordered_set<int> set1;
        cin >> s;
        char prev = '0', prev_prev = '0';
        int prev_num = -1, prev_prev_num = -2;
        int i = 0;
        while (i < s.length())
        {
            char cur = s[i];
            if (prev == cur && set1.count(prev_num) == 0)
                set1.insert(i);
            if (prev_prev == cur && set1.count(prev_prev_num) == 0)
                set1.insert(i);
            prev_prev = prev;
            prev = s[i];
            prev_prev_num = prev_num;
            prev_num = i;
            i++;
        }
        cout << set1.size() << "\n"; //?????
    }
    return 0;
}