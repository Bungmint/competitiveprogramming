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
        deque<int> deq;
        deq.push_back(n);
        while (deq.size() != n)
        {
            int cur_size = deq.size(), nxt = n - deq.size();
            deq.push_front(nxt);
            for (int i = 0; i < nxt % (cur_size + 1); i++)
            {
                int back = deq.back();
                deq.pop_back();
                deq.push_front(back);
            }
        }
        while (!deq.empty())
        {
            int x = deq.front();
            cout << x << endl;
            deq.pop_front();
        }
    }
}