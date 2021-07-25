// Problem: D. Cut
// Contest: Codeforces - Codeforces Round #717 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1516/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
const int N = 1e5, LOG=20;
int lp[N + 1];
int a[N+1], nxt[N+1];
vi factors[N];
int up[N+1][LOG];
vector<int> pr;
void linsieve()
{
    for (int i = 2; i <= N; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
}

struct SegTree{

	int sz;
	struct Node{
		int val;
	};
	vector<Node> t;
	
	
	Node single(int val){
		return {val};
	}
	Node NEUTRAL = {0}; //ALSO HAS TO CHANGE
	Node merge(Node a, Node b){
		return {max(a.val, b.val)};
	}
	
	void init(int n){
		sz = 1;
		while(sz<n) sz*=2;
		t.resize(sz*2);
	}
	void upd(int i, int v, int x, int l, int r)
	{
	    if (r - l == 1)
	    {
	        t[x] = {t[x].val+v};
	        return;
	    }
	    int mid = (l + r) / 2;
	    if (i < mid)
	        upd(i, v, 2 * x + 1, l, mid);
	    else
	        upd(i, v, 2 * x + 2, mid, r);
	    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
	}
	void upd(int i, int v)
	{
	    upd(i, v, 0, 0, sz);
	}
	Node query(int l, int r, int x, int lx, int rx)
	{
	    if (lx >= r || rx <= l)
	        return NEUTRAL;
	    if (lx >= l && rx <= r)
	        return t[x];
	    int mid = (lx + rx) / 2;
	    Node a = query(l, r, 2 * x + 1, lx, mid);
	    Node b = query(l, r, 2 * x + 2, mid, rx);
	    return merge(a, b);
	}
	Node query(int l, int r)
	{
	    return query(l, r, 0, 0, sz);
	}
};




void solve()
{
	int n, q;
	cin >> n >> q;
	SegTree st;
	st.init(N+10);
	for (int i=0;i<n;++i) cin >> a[i];
	for (int i=0;i<n;++i){
		int x = a[i];
		while(x>1){
			int p = lp[x], cnt = 0;
			while(x%p==0){
				cnt++;
				x/=p;
			}
			factors[i].pb(p);
		}
	}
	int r = n-1;
	nxt[n] = n;
	for (int i=0;i<LOG;++i) up[n][i] = n;
	for (int l=n-1;l>=0;l--){
		for (int x:factors[l]){
			st.upd(x, 1);
		}
		while(st.t[0].val>1){
			for (int x:factors[r]){
				st.upd(x,-1);
			}
			r--;
		}
		nxt[l] = r+1;
		up[l][0] = r+1;
		for (int i=1;i<LOG;++i){
			up[l][i] = up[up[l][i-1]][i-1];
		}
	}
	int l;
	while(q--){
		cin >> l >> r;
		l--;r--;
		dbg(l,r);
		int cnt = 1;
		for (int i=LOG-1;i>=0;i--){
			if (up[l][i]<r+1) l = up[l][i], cnt += (1<<i);
		}
		dbg(cnt);
		cout << cnt << "\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    linsieve();
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}