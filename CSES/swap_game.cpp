#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;
using pl = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pl>;
using ld = long double;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound

template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
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

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
int powers[10];

int move(int grid, int i, int j)
{
	int a = grid % powers[i + 1] / powers[i];
	int b = grid % powers[j + 1] / powers[j];
	return grid - a * powers[i] - b * powers[j] + b * powers[i] + a * powers[j];
}

void solve()
{
	powers[0] = 1;
	for (int i=1;i<10;++i) powers[i] = powers[i-1]*9;
	vector<bool> vis(powers[9], false);
	int target = 0;
	for (int i=0;i<9;++i){
		target += (8-i)*powers[i];
	}
	int st = 0;
	for (int i=8;i>=0;--i){
		int t;
		cin>> t;
		st += (t-1)*powers[i];
	}
	queue<pi> q;
	q.push({st,0});
	while(!q.empty()){
		auto [g,dist] = q.front();
		if (g==target){
			cout <<dist << endl;
			return;
		}
		q.pop();
		for (int i = 0; i < 8; i++)
		{
			if (i % 3 == 2)
			{
				continue;
			}
			int swapped = move(g, 8 - i, 8 - (i + 1));
			if (!vis[swapped])
			{
				q.push({swapped, dist + 1});
				vis[swapped] = true;
			}
		}
		// swap two vertically adjacent pieces
		for (int i = 0; i < 6; i++)
		{
			int swapped = move(g, 8 - i, 8 - (i + 3));
			if (!vis[swapped])
			{
				q.push({swapped, dist + 1});
				vis[swapped] = true;
			}
		}
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}