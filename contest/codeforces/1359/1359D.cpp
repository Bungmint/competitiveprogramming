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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;

const int MAXN = 1e5+1;
int n, sz;

struct Node{
	int mi, mx;
}t[4*MAXN];

Node single(int val){
	return {val, val};
}

Node NEUTRAL = {INF, -INF}; //ALSO HAS TO CHANGE

Node merge(Node a, Node b){
	return {min(a.mi, b.mi), max(a.mx, b.mx)};
}

void init(int n){
	sz = 1;
	while(sz<n) sz*=2;
}

void build(vector<int> &vec, int x, int l, int r)
{
    if (r - l == 1)
    {
        if (l < (int)vec.size())
            t[x] = single(vec[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(vec, 2 * x + 1, l, mid);
    build(vec, 2 * x + 2, mid, r);
    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
}
void build(vector<int> &vec)
{
    build(vec, 0, 0, sz);
}
void upd(int i, int v, int x, int l, int r)
{
    if (r - l == 1)
    {
        t[x] = single(v);
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

void solve()
{
	int n;
	cin >> n;
	vi a(n+1), pref(n+1),L(n+1), R(n+1);
	
	for (int i=1;i<=n;++i) cin >> a[i], pref[i]=pref[i-1]+a[i];
	dbg(pref);
	init(n+1);
	build(pref);
	stack<int> st, ts;
	for (int i=1;i<=n;++i){
		while(!st.empty()&&a[st.top()]<=a[i]){
			st.pop();
		}
		if (st.empty()){
			L[i] = 0;
		}else{
			L[i] = st.top();
		}
		st.push(i);
	}
	while(!st.empty()) st.pop();
	for (int i=n;i>=1;--i){
		while(!st.empty()&&a[st.top()]<=a[i]){
			st.pop();
		}
		if (st.empty()){
			R[i] = n+1;
		}else{
			R[i] = st.top();
		}
		st.push(i);
	}
	int ans = 0;
	for (int i=1;i<=n;++i){
		int l = L[i]+1, r = R[i]-1;
		Node ri = query(i, r+1);
		Node le = query(l-1, i);
		dbg(l,i);
		dbg(i, r,ri.mx, ri.mi, le.mx, le.mi);
		ans = max(ans, ri.mx-le.mi-a[i]);
		dbg(a[i], ans);
	}
	cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}