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

void solve()
{
    int n, m;
    cin >> n >> m;
    int od = 0;
    vector<pair<int, int>> rob(n);
    vector<ar<int, 3>> odd, even;
    vector<bool> used(n);
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
        cin >> rob[i].first;
        if (rob[i].first % 2)
            od++;
    }
    fill(all(used), false);
    odd.resize(od);
    even.resize(n - od);
    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        if (c == 'R')
        {
            rob[i].second = 1;
        }
        else
            rob[i].second = -1;
    }
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (rob[i].first % 2)
        {
            odd[cnt1][0] = rob[i].first;
            odd[cnt1][1] = rob[i].second;
            odd[cnt1][2] = i;
            cnt1++;
        }
        else
        {
            even[cnt2][0] = rob[i].first;
            even[cnt2][1] = rob[i].second;
            even[cnt2][2] = i;
            cnt2++;
        }
    }
    sort(all(even));
    sort(all(odd));
    stack<pair<int, int>> st;
    for (int i = 0; i < od; i++)
    {
        if (odd[i][1] == 1)
        {
            st.push({odd[i][2], odd[i][0]});
        }
        else
        {
            if (st.empty())
                continue;
            int crashcar = st.top().first, crasht = st.top().second;
            st.pop();
            used[crashcar] = true;
            used[odd[i][2]] = true;
            ans[crashcar] = (odd[i][0] - crasht) / 2;
            ans[odd[i][2]] = ans[crashcar];
        }
    }
    st = stack<pair<int, int>>();
    for (int i = 0; i < od; i++)
    {
        if (used[odd[i][2]])
            continue;
        if (odd[i][1] == 1)
            break;
        if (st.empty())
        {
            st.push({odd[i][2], odd[i][0]});
            continue;
        }
        int crashcar = st.top().first, crasht = st.top().second;
        st.pop();
        used[crashcar] = true;
        used[odd[i][2]] = true;
        ans[crashcar] = (odd[i][0] + crasht) / 2;
        ans[odd[i][2]] = ans[crashcar];
    }
    st = stack<pair<int, int>>();
    for (int i = od - 1; i >= 0; i--)
    {
        if (used[odd[i][2]])
            continue;
        if (odd[i][1] == -1)
            break;
        if (st.empty())
        {
            st.push({odd[i][2], odd[i][0]});
            continue;
        }
        int crashcar = st.top().first, crasht = st.top().second;
        st.pop();
        used[crashcar] = true;
        used[odd[i][2]] = true;
        ans[crashcar] = (-odd[i][0] + crasht) / 2 + m - crasht;
        ans[odd[i][2]] = ans[crashcar];
    }
    int unused = 0, prev = -1;
    for (int i = 0; i < od; i++)
    {
        if (!used[odd[i][2]])
        {
            if (prev != -1)
            {
                used[odd[i][2]] = true;
                used[odd[prev][2]] = true;
                ans[odd[i][2]] = m + (odd[prev][0] - odd[i][0]) / 2;
                ans[odd[prev][2]] = ans[odd[i][2]];
            }
            else
            {
                prev = i;
            }
        }
    }
    for (int i = 0; i < od; i++)
    {
        if (!used[odd[i][2]])
        {
            ans[odd[i][2]] = -1;
        }
    }

    st = stack<pair<int, int>>();
    for (int i = 0; i < n - od; i++)
    {
        if (even[i][1] == 1)
        {
            st.push({even[i][2], even[i][0]});
        }
        else
        {
            if (st.empty())
                continue;
            int crashcar = st.top().first, crasht = st.top().second;
            st.pop();
            used[crashcar] = true;
            used[even[i][2]] = true;
            ans[crashcar] = (even[i][0] - crasht) / 2;
            ans[even[i][2]] = ans[crashcar];
        }
    }
    st = stack<pair<int, int>>();
    for (int i = 0; i < n - od; i++)
    {
        if (used[even[i][2]])
            continue;
        if (even[i][1] == 1)
            break;
        if (st.empty())
        {
            st.push({even[i][2], even[i][0]});
            continue;
        }
        int crashcar = st.top().first, crasht = st.top().second;
        st.pop();
        used[crashcar] = true;
        used[even[i][2]] = true;
        ans[crashcar] = (even[i][0] + crasht) / 2;
        ans[even[i][2]] = ans[crashcar];
    }
    st = stack<pair<int, int>>();
    for (int i = n - od - 1; i >= 0; i--)
    {
        if (used[even[i][2]])
            continue;
        if (even[i][1] == -1)
            break;
        if (st.empty())
        {
            st.push({even[i][2], even[i][0]});
            continue;
        }
        int crashcar = st.top().first, crasht = st.top().second;
        st.pop();
        used[crashcar] = true;
        used[even[i][2]] = true;
        ans[crashcar] = (-even[i][0] + crasht) / 2 + m - crasht;
        ans[even[i][2]] = ans[crashcar];
    }
    prev = -1;
    for (int i = 0; i < n - od; i++)
    {
        if (!used[even[i][2]])
        {
            if (prev != -1)
            {
                used[even[i][2]] = true;
                used[even[prev][2]] = true;
                ans[even[i][2]] = m + (even[prev][0] - even[i][0]) / 2;
                ans[even[prev][2]] = ans[even[i][2]];
            }
            else
            {
                prev = i;
            }
        }
    }
    for (int i = 0; i < n - od; i++)
    {
        if (!used[even[i][2]])
        {
            ans[even[i][2]] = -1;
        }
    }
    for (auto x : ans)
        cout << x << " ";
    cout << "\n";
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