//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
using ll = long long;
const int INF = 1e9;
const ll LINF = 1e15;
const int MOD = 1e9 + 7; //998244353
const int N = 3e4;
int p[N], nodes[N];

void solve()
{
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> doges(n, vector<pair<int, int>>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            cin >> doges[i][j].first;
            doges[i][j].second = j + 1;
        }
    }
    for (int i = 0; i < n; i++)
        sort(all(doges[i]));
    map<pair<int, int>, int> track;
    int cur_total = n;
    for (int i = 0; i < n; i++)
    {
        int prev_val = 0LL, prev_node = -1LL;
        for (int j = 0; j < n; j++)
        {
            auto &[sal, num] = doges[i][j];
            if (j == 0)
            {
                prev_val = sal;
                nodes[num] = prev_val;
                prev_node = num;
                continue;
            }
            if (prev_val != sal)
            {
                if (track.count({i + 1, num}) == 0 && track.count({num, i + 1}) == 0)
                {
                    cur_total++;
                    nodes[cur_total] = sal;
                    p[prev_node] = cur_total;
                    prev_node = cur_total;
                    prev_val = sal;
                    track[{i + 1, num}] = cur_total;
                    track[{num, i + 1}] = cur_total;
                    int k = j;
                    while (k < n - 1 && doges[i][k + 1].first == sal)
                    {
                        k++;
                    }
                    for (int l = j; l <= k; l++)
                    {
                        track[{i + 1, doges[i][l].second}] = cur_total;
                        track[{doges[i][l].second, i + 1}] = cur_total;
                    }
                }
                else
                {
                    p[prev_node] = track[{i + 1, num}];
                    break;
                }
            }
        }
    }
    int head = -1;
    for (int i = 1; i <= cur_total; i++)
    {
        if (p[i] == 0)
        {
            head = i;
            continue;
        }
    }
    cout << cur_total << "\n";
    for (int i = 1; i <= cur_total; i++)
    {
        cout << nodes[i] << " ";
    }
    cout << "\n";
    cout << head << "\n";
    for (int i = 1; i <= cur_total; i++)
    {
        if (i == head)
            continue;
        cout << i << " " << p[i] << "\n";
    }
    cout << "\n";
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