#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;
    int ans = 0;
    vector<int> vec(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    set<int> set1;
    queue<int> play;
    int i = 0;
    int j = 0;
    while (i < n)
    {
        for (; j < n; j++)
        {
            if (set1.count(vec[j]))
            {
                play.push(vec[j]);
                break;
            }
            set1.insert(vec[j]);
            play.push(vec[j]);
        }
        ans = max(ans, j - i);
        while (!play.empty() && play.front() != play.back())
        {
            auto it = set1.find(play.front());
            set1.erase(it);
            play.pop();
            i++;
        }
        play.pop();
        i++;
        j++;
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}