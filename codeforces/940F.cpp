// Problem: F. Machine Learning
// Contest: Codeforces - Codeforces Round #466 (Div. 2)
// URL: https://codeforces.com/problemset/problem/940/F
// Memory Limit: 512 MB
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


const int block=1750; //Dont forget to set
int B[200011], ans[200011], last[200011];
int a[200011], Q1=0, Q2=-1, freq[200011], SZ[200011];

void remove(int idx){
	SZ[freq[a[idx]]]--;
	freq[a[idx]]--;
	SZ[freq[a[idx]]]++;
}
void add(int idx){
	SZ[freq[a[idx]]]--;
	freq[a[idx]]++;
	SZ[freq[a[idx]]]++;
}     
ll get_answer(){
	F0R(i, 1000){
		if (SZ[i]==0) return i;
	}
}
void change(int id, int val,int l,int r){
	if (id>=l&&id<=r){
		dbg(a[id], SZ[freq[a[id]]],freq[a[id]]);
		SZ[freq[a[id]]]--;
		freq[a[id]]--;
		SZ[freq[a[id]]]++;
		a[id] = val;
		dbg(SZ[freq[a[id]]],freq[a[id]]);
		dbg(a[id]);
		SZ[freq[a[id]]]--;
		freq[a[id]]++;
		SZ[freq[a[id]]]++;
		dbg(SZ[freq[a[id]]],freq[a[id]]);
	}else{
		a[id] = val;
	}
}


struct Query {
    int l, r,time, idx;
};
inline bool operator<(const Query &a, const Query &b) {
	return B[a.l]<B[b.l] || (B[a.l]==B[b.l]&&B[a.r]<B[b.r]) || (B[a.l]==B[b.l]&&B[a.r]==B[b.r]&&a.time<b.time);
}
struct Update{
	int id,pre, cur;
}updates[100001];

using vq = vector<Query>;


void mo(vq queries) {
    sort(queries.begin(), queries.end());

    int cur_l = 0;
    int cur_r = -1;
    int cur_t = -1;
    for (Query q : queries) {
    	dbg(q.l,q.r, q.time, q.idx);
    	while(cur_t<q.time){
    		cur_t++;
    		change(updates[cur_t].id, updates[cur_t].cur, cur_l, cur_r);
    		dbg();
    	}
    	while(cur_t>q.time){
    		change(updates[cur_t].id, updates[cur_t].pre, cur_l, cur_r);
    		cur_t--;
    	}
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        ans[q.idx] = get_answer();
    }
}

void solve()
{
	int n, q;
	cin >> n >> q;
	F0R(i, 100001){
		B[i] = i/block;
	}
	vi order;
	F0R(i,n) cin >> a[i], order.pb(a[i]);
	SZ[0] = INF;
	vq Queries;
	F0R(i, q){
		int t, x, y;
		cin >> t >> x >> y;
		if(t==1){
			x--,y--;
			Queries.pb({x, y, Q2, sz(Queries)});
		}else{
			x--;
			updates[++Q2] = {x, last[x],y};
			order.pb(y);
		}
	}
	sort(all(order)), order.resize(unique(all(order))-order.begin());
	F0R(i, n) a[i] = lb(all(order), a[i])-order.begin(), last[i] = a[i];
	F0R(i, Q2+1){
		updates[i].pre = last[updates[i].id];
		updates[i].cur = lb(all(order), updates[i].cur)-order.begin();
		last[updates[i].id] = updates[i].cur;
	}
	mo(Queries);
	F0R(i, sz(Queries))cout << ans[i]<<"\n";
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