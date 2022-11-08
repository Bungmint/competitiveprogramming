#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out()
{
    cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

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

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353

void solve()
{
	int n;
	cin >> n;
	vector<pair<ll,int>> x(n), y(n);
	for (int i=0;i<n;i++){
		cin >> x[i].first >> y[i].first;
		x[i].second = y[i].second = i;
	}
	sort(all(x));sort(all(y));
	map<pair<int,int>, ll> m1;
	m1[{x[n-1].second, x[0].second}] = x[n-1].first-x[0].first;
	m1[{x[n-1].second, x[1].second}] = x[n-1].first - x[1].first;
	m1[{x[n-2].second, x[0].second}] = x[n-2].first -x[0].first;
	dbg(x[n-1], x[n-2], x[1], x[0]);
	dbg(y[n-1], y[n-2], y[1], y[0]);
	if (m1.count({y[n-1].second, y[0].second})){
		m1[{y[n-1].second, y[0].second}] = max(m1[{y[n-1].second, y[0].second}], y[n-1].first-y[0].first);
	}else if (m1.count({y[0].second, y[n-1].second})){
		m1[{y[0].second, y[n-1].second}] = max(m1[{y[0].second, y[n-1].second}], y[n-1].first-y[0].first);
	}else{
		m1[{y[n-1].second, y[0].second}] = y[n-1].first-y[0].first;
	}
	if (m1.count({y[n-1].second, y[1].second})){
		m1[{y[n-1].second, y[1].second}] = max(m1[{y[n-1].second, y[1].second}], y[n-1].first-y[1].first);
	}else if (m1.count({y[1].second, y[n-1].second})){
		m1[{y[1].second, y[n-1].second}] = max(m1[{y[1].second, y[n-1].second}], y[n-1].first-y[1].first);
	}else{
		m1[{y[n-1].second, y[1].second}] = y[n-1].first-y[1].first;
	}
	if (m1.count({y[n-2].second, y[0].second})){
		m1[{y[n-2].second, y[0].second}] = max(m1[{y[n-2].second, y[0].second}], y[n-2].first-y[0].first);
	}else if (m1.count({y[0].second, y[n-2].second})){
		m1[{y[0].second, y[n-2].second}] = max(m1[{y[0].second, y[n-2].second}], y[n-2].first-y[0].first);
	}else{
		m1[{y[n-2].second, y[0].second}] = y[n-2].first-y[0].first;
	}
	multiset<ll> s1;
	dbg(m1);
	for (auto x:m1) s1.insert(x.second);
	auto it = s1.end();
	it--;it--;
	cout << *it << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}