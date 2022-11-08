// Problem: E. Earth Wind and Fire
// Contest: Codeforces - Codeforces Global Round 3
// URL: https://codeforces.com/problemset/problem/1148/E
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

void solve()
{
	vpi s, t;
	int n;
	cin >> n;
	ll sSum = 0, tSum = 0;
	for (int i=0;i<n;++i){
		int c;
		cin >> c;
		sSum +=c;
		s.pb({c,i});
	}
	for (int i=0;i<n;++i){
		int c;
		cin >> c;
		tSum +=c;
		t.pb({c,i});
	}
	if (sSum!=tSum){
		cout <<"NO\n";
		return;
	}
	sort(all(s));
	sort(all(t));
	stack<pi> st;
	vector<ar<int,3>> ans;
	for (int i=0;i<n;++i){
		if (t[i].fi-s[i].fi>=0){
			st.push({t[i].fi-s[i].fi, s[i].se});
		}else{
			if (st.empty()){
				cout << "NO\n";
				return;
			}else{
				int v = t[i].fi-s[i].fi;
				int id = s[i].se;
				while(!st.empty()&&v<0){
					pi p = st.top();
					st.pop();
					if (-v<p.fi){
						p.fi+=v;
						ans.pb({p.se, id, -v});
						st.push(p);
						v = 0;
					}else{
						v += p.fi;
						ans.pb({p.se, id, p.fi});
					}
				}
				if (v!=0&&st.empty()){
					cout << "NO\n";
					return;
				}
			}
		}
	}
	
	cout << "YES\n";
	cout << sz(ans)<<"\n";
	for (auto x:ans) cout << x[0]+1<<" "<< x[1]+1<<" "<< x[2]<<"\n";
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