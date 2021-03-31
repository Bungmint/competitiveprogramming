#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        int previous = 1;
        cin >> n;
        vector<int> v(n), res(n);
        vector<bool> will_drink(n, true);
        priority_queue<pi, vector<pi>, greater<pi>> pq;
        for (int i = 0; i < n; i++)
        {
            int l, r;
            cin >> l >> r;
            v[i] = l;
            pq.push(make_pair(r, i));
        }
        for (int i = 0; i < n; i++)
        {
            if (will_drink[i])
            {
                res[i] = max(v[i], previous);
                previous = res[i] + 1;
                while (!pq.empty() && previous > pq.top().first)
                {
                    int top_val = pq.top().second;
                    will_drink[top_val] = false;
                    pq.pop();
                }
            }
            else
            {
                res[i] = 0;
            }
        }
        for (auto j : res)
        {
            cout << j << " ";
        }
        cout << "\n";
    }

    return 0;
}