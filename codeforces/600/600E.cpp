// Problem: E. Lomsat gelral
// Contest: Codeforces - Educational Codeforces Round 2
// URL: https://codeforces.com/problemset/problem/600/E
// Memory Limit: 256 MB
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
const int N = 1e5+1;
vi g[N];
int c[N], st[N], en[N], a[2*N+1], freq[N*2], cnt[2*N];
ll sum[N*2];
int timer = 0, previous=0;
vector<pi> ev;
int res=0, mx=0;


void dfs(int v,int pv){
	st[v] = timer++;
	a[st[v]] = c[v];
	for (int e:g[v]){
		if (e!=pv) dfs(e,v);
	}
	en[v] = timer++;
	a[en[v]] = c[v];
}

void add(int idx){
	int color = a[idx];
	ev.pb({color, freq[color]});
	cnt[freq[color]]--;
	sum[freq[color]]-=color;
	freq[color]++;
	mx = max(mx, freq[color]);
	cnt[freq[color]]++;
	sum[freq[color]]+=color;
}     
ll get_answer(){
	return sum[mx];
}
void snapshot(){
	previous = sz(ev);
	res = mx;
}
void rollback(){
	while(sz(ev)!=previous){
		auto [color, f] = ev.back();
		cnt[f]++;
		cnt[f+1]--;
		sum[f+1]-=color;
		sum[f]+=color;
		freq[color] = f;
		ev.pop_back();
	}
	mx = res;
}

void init(){
	ev.clear();
	previous = res = mx = 0;
	memset(cnt, 0, sizeof(cnt));
	memset(freq,0, sizeof(freq));
	memset(sum, 0, sizeof(sum));
}





const int block=450; //Dont forget to set

struct Query {
    int l, r, idx;
	inline pair<int, int> toPair() const {
		return make_pair(l / block, r);
	}
};
inline bool operator<(const Query &a, const Query &b) {
	return a.toPair() < b.toPair();
}

using vq = vector<Query>;


vl mo(vq queries) {
   	vl answers(queries.size());
    sort(queries.begin(), queries.end());
    init();
    snapshot();
	for (Query q:queries){
		if (q.r-q.l+1<=block){
			for (int i=q.l;i<=q.r;++i){
				add(i);
			}
			answers[q.idx] = get_answer();
			rollback();
		}
	}
	int last_bucket = -1;
	int l,r;
	for (Query q:queries){
		if (q.r-q.l+1<=block) continue;
		int bucket = q.l/block;
		if (last_bucket!=bucket){
			init();
			l = (bucket+1)*block, r = q.r;
			for (int i=l;i<=r;++i) add(i);
		}
		last_bucket = bucket;
		while(r<q.r){
			add(++r);
		}
		snapshot();
		for (int i=l-1;i>=q.l;--i) add(i);
		answers[q.idx] = get_answer();
		rollback();
	}
    
    
    
    
    return answers;
}

void solve()
{
	int n;
	cin >> n;
	for (int i=1;i<=n;++i) cin >> c[i];
	for (int i=0;i<n-1;++i){int u,v;cin >> u >> v; g[u].pb(v), g[v].pb(u);}
	dfs(1,0);
	vq q(n);
	for (int i=0;i<n;++i) q[i] = {st[i+1],en[i+1], i};
	vl ans = mo(q);
	for (ll x:ans) cout << x << " ";
	cout <<endl;
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