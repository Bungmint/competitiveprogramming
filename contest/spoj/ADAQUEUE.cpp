#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    const string msg = "No job for Ada?";
    int q;
    cin >> q;
    deque<int> deq_normal, deq_reverse;
    for (auto i = 0; i <= q; i++)
    {
        string s;
        int x;
        getline(cin, s);
        switch (s[0])
        {
        case 'b':
            if (deq_normal.empty())
            {
                cout << msg << "\n";
            }
            else
            {
                x = deq_normal.back();
                deq_normal.pop_back();
                deq_reverse.pop_front();
                cout << x << "\n";
            }
            break;
        case 'f':
            if (deq_normal.empty())
            {
                cout << msg << "\n";
            }
            else
            {
                x = deq_normal.front();
                deq_normal.pop_front();
                deq_reverse.pop_back();
                cout << x << "\n";
            }
            break;
        case 'r':
            swap(deq_normal, deq_reverse);
            break;
        case 'p':
            x = stoi(s.substr(10));
            deq_normal.push_back(x);
            deq_reverse.push_front(x);
            break;
        case 't':
            x = stoi(s.substr(8));
            deq_normal.push_front(x);
            deq_reverse.push_back(x);
            break;
        }
    }
    return 0;
}