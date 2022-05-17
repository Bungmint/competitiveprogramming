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
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353

void tog(int &n)
{
    n += 1;
    n %= 2;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    set<pair<int, int>> st;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        st.insert({a[i], i});
    }
    int turn = 0, used = -1;
    while (true)
    {
        if (st.empty())
        {
            tog(turn);
            break;
        }
        auto it1 = --st.end();
        pair<int, int> big = *it1;
        if (big.second == used && st.size() == 1)
        {
            tog(turn);
            break;
        }
        if (big.second == used)
        {
            auto it = st.end();
            it--;
            it--;
            big = *it;
            st.erase(big);
            used = big.second;
            big.first--;
            if (big.first > 0)
                st.insert(big);
        }
        else
        {
            used = big.second;
            st.erase(big);
            big.first--;
            if (big.first > 0)
                st.insert(big);
        }
        tog(turn);
    }
    if (turn == 0)
    {
        cout << "T"
             << "\n";
    }
    else
    {
        cout << "HL"
             << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}