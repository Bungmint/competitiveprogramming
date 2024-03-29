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
vector<pair<double, double>> peeps;
int n;
bool good(double t)
{
    double left = -LINF, right = LINF;
    for (int i = 0; i < n; i++)
    {
        left = max(left, peeps[i].first - t * peeps[i].second);
        right = min(right, peeps[i].first + peeps[i].second * t);
    }
    return left < right || ((right - left) < 1e-9 && (right - left) > 0) || ((left - right) < 1e-9 && (left - right) > 0);
}

void solve()
{
    cin >> n;
    peeps.resize(n);
    for (int i = 0; i < n; i++)
        cin >> peeps[i].first >> peeps[i].second;
    double l = 0, r = 1e10, ans;
    while (l + 1e-6 < r)
    {
        double m = (r + l) / 2;
        if (good(m))
        {
            ans = m;
            r = m;
        }
        else
            l = m;
    }
    cout << setprecision(20) << ans << "\n";
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