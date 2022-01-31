// Problem: D. Borders
// Contest: Codeforces - ITMO Academy: pilot course - Suffix Array - Step 5
// URL: https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/D
// Memory Limit: 512 MB
// Time Limit: 2000 ms
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
#define ub upper_bound

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
#define dbg(...)
#endif

struct chash
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

struct SuffixArray{
	vi p, c, c_new, p_new, cnt, pos, lcp;
	int n;
	vector<pair<char,int>> a;
	
	void init(int N){
		n = N;
		p.resize(n+1);
		c.resize(n+1);
		c_new.resize(n+1);
		p_new.resize(n+1);
		cnt.resize(n+1);
		pos.resize(n+1);
		lcp.resize(n+1);
		a.resize(n+1);
	}
	
	void count_sort(){
		for (int i=0;i<n;++i) cnt[i] = 0;
		for (int i=0;i<n;++i){
			cnt[c[i]]++;
		}
		pos[0] = 0;
		for (int i=1;i<n;++i) pos[i] = pos[i-1]+cnt[i-1];
		for (int i=0;i<n;++i){
			int x = c[p[i]];
			p_new[pos[x]] = p[i];
			pos[x]++;
		}
		for (int i=0;i<n;++i) p[i] = p_new[i];
	}
	
	void process(string &s)
	{
		s+='$';
		n = sz(s);
		for (int i=0;i<n;++i) a[i] = {s[i], i};
		sort(a.begin(), a.begin()+n);
		for (int i=0;i<n;++i) p[i] = a[i].second;
		c[p[0]] = 0;
		for (int i=1;i<n;++i){
			if (a[i].first==a[i-1].first){
				c[p[i]] = c[p[i-1]];
			}else{
				c[p[i]] = c[p[i-1]] + 1;
			}
		}
		int k=0;
		while((1<<k)<n){
			for (int i=0;i<n;++i) p[i] = (p[i]-(1<<k)+n)%n;
			count_sort();
			c_new[p[0]] = 0;
			for (int i=1;i<n;++i){
				pi prev = {c[p[i-1]], c[(p[i-1]+(1<<k))%n]};
				pi cur = {c[p[i]], c[(p[i]+(1<<k))%n]};
				if (prev==cur){
					c_new[p[i]] = c_new[p[i-1]];
				}else c_new[p[i]] = c_new[p[i-1]]+1;
			}
			
			for (int i=0;i<n;++i) c[i] = c_new[i];
			k++;
		}
		k = 0;
		for (int i=0;i<n-1;++i){
			int posi = c[i];
			int j = p[posi-1];
			while(s[i+k]==s[j+k])k++;
			lcp[posi-1] = k;
			k = max(0, k-1);
		}
	}
};

void solve()
{
	SuffixArray sa;
	string s;
	cin >> s;
	ll n = sz(s);
	sa.init(n);
	sa.process(s);
	ll ans = n*(n+1)/2;
	stack<pi> monoStack;
	for (int i=0;i<=n;++i){
		int pos = i, elem = (i==n? 0:sa.lcp[i]);
		while(sz(monoStack)&&monoStack.top().se>=elem){
			auto [lastpos, lastElem] = monoStack.top();
			monoStack.pop();
			if (lastElem>elem){
				int t = elem;
				ll dif = i - lastpos+1;
				if (sz(monoStack)) ckmax(t, monoStack.top().se);
				ans+=(dif-1)*(dif)/2LL * (lastElem-t);
			}
			pos = lastpos;
		}
		monoStack.push({pos, elem});
	}
	cout << ans << endl;
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