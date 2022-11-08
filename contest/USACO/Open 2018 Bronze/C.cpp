// Problem: Problem 3. Family Tree
// Contest: USACO - USACO 2018 US Open Contest, Bronze
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=833
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2021 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;
template <typename T, size_t SZ>
using ar = array<T, SZ>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

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
#define dbg(...) 42
#endif

inline namespace RecursiveLambda{
	template <typename Fun>
	struct y_combinator_result{
		Fun fun_;
		template <typename T> 
		explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)){}
		template <typename...Args>
		decltype(auto) operator()(Args &&...args){
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun){
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

void solve()
{
	int n;
	cin >> n;
	int id = 0;
	vector<vi> g(2*n+2);
	vector<bool> vis(2*n+2);
	vi p(2*n+2, -1);
	map<string, int> label;
	string a, b;
	cin >> a >> b;
	label[a] = id++, label[b] = id++;
	int sss = label[a], ttt = label[b];
	REP(n){
		string t, u;
		cin >> t >> u;
		if (!label.count(t)) label[t] = id++;
		if (!label.count(u)) label[u] = id++;
		p[label[u]] = label[t];
		g[label[u]].pb(label[t]);
		g[label[t]].pb(label[u]); 
	}
	auto dfs = y_combinator([&](auto dfs, int u, int pu)->void{
		vis[u] = 1;
		for (auto &v: g[u]){
			if (v != pu){
				dfs(v, u);
			}
		}
	});
	for (auto &[s, u]: label){
		if (p[u]==-1){
			dfs(u, -1);
			if (vis[sss]^vis[ttt]){
				cout << "NOT RELATED";
				return;
			}else if (vis[sss]){
				if (p[sss]==p[ttt]){
					assert(p[sss]!=-1);
					cout << "SIBLINGS";
					return;
				}
				vi parA = {sss}, parB = {ttt};
				while(p[sss]!=-1){
					parA.pb(p[sss]);
					sss = p[sss];
				}
				while(p[ttt]!=-1){
					parB.pb(p[ttt]);
					ttt = p[ttt];
				}
				F0R(i, sz(parA))F0R(j, sz(parB)){
					if (parA[i]==parB[j]){
						dbg(i, j);
						int mi = min(i, j);
						if (mi>=2){
							cout << "COUSINS";
						}else if (mi==1){
							if (i<j){
								cout << a << " is the ";
								REP(j-i-1) cout << "great-";
								cout << "aunt of " << b;
							}else{
								cout << b << " is the ";
								REP(i-j-1) cout << "great-";
								cout << "aunt of " << a;
							}
						}else{
							if (i<j){
								cout << a << " is the ";
								REP(j-i-2) cout << "great-";
								if (j-i-1) cout << "grand-";
								cout << "mother of " << b;
							}else{
								cout << b << " is the ";
								REP(i-j-2) cout << "great-";
								if (i-j-1) cout << "grand-";
								cout << "mother of " << a;
							}
						}
						return;
					}
				}
			}
		}
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    #ifndef LOCAL
    	setIO("family");
    #endif
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}