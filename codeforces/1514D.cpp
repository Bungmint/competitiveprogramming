//#pragma GCC optimize("O3")
//#pragma GCC target("sse4")
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
const int MAX = 3e5 + 5;
int freq[MAX], vec[MAX], ans[MAX], counts[MAX];
int block;
int n, qs;

int next_int()
{
    char c;
    do
    {
        c = getchar();
    } while (c != '-' && !isdigit(c));
    bool neg = (c == '-');
    int result = neg ? 0 : c - '0';
    while (isdigit(c = getchar()))
        result = 10 * result + (c - '0');
    return neg ? -result : result;
}

struct Query
{
    int l, r, idx;
} queries[MAX];
bool compare(Query x, Query y)
{
    // Different blocks, sort by block.
    if (x.l / block != y.l / block)
        return x.l / block < y.l / block;

    // Same block, sort by R value
    return x.r < y.r;
}

void fix(int &answer)
{
    while (freq[answer + 1] > 0)
    {
        answer++;
    }
    while (answer > 0 && freq[answer] == 0)
    {
        answer--;
    }
}

void remove(int idx, int &answer)
{
    freq[counts[vec[idx]]]--;
    counts[vec[idx]]--;
    if (counts[vec[idx]] > 0)
        freq[counts[vec[idx]]]++;
    fix(answer);
}
void add(int idx, int &answer)
{
    freq[counts[vec[idx]]]--;
    counts[vec[idx]]++;
    freq[counts[vec[idx]]]++;
    fix(answer);
}

void mo_s_algorithm()
{
    int cur_l = 0;
    int cur_r = -1;
    int answer = 0;
    for (int i = 0; i < qs; i++)
    {
        Query q = queries[i];
        while (cur_l > q.l)
        {
            cur_l--;
            add(cur_l, answer);
        }
        while (cur_r < q.r)
        {
            cur_r++;
            add(cur_r, answer);
        }
        while (cur_l < q.l)
        {
            remove(cur_l, answer);
            cur_l++;
        }
        while (cur_r > q.r)
        {
            remove(cur_r, answer);
            cur_r--;
        }
        if (answer <= (q.r - q.l + 2) / 2)
            ans[q.idx] = 1;
        else
            ans[q.idx] = 2 * answer - (q.r - q.l + 1);
    }
}

void solve()
{

    n = next_int();
    qs = next_int();
    block = (int)sqrt(n);
    for (int i = 0; i < n; i++)
    {
        vec[i] = next_int();
    }
    for (int i = 0; i < qs; i++)
    {
        int l, r;
        l = next_int(), r = next_int();
        queries[i].idx = i;
        queries[i].l = l - 1;
        queries[i].r = r - 1;
    }
    sort(queries, queries + qs, compare);

    mo_s_algorithm();
    for (int i = 0; i < qs; i++)
    {
        cout << ans[i] << "\n";
    }
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