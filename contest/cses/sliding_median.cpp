#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
#define sz(x) (int)(x).size()

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
const int MOD = 1e9 + 7; //998244353
const int MAXN = 2e5+1;
int n, sz,t[4*MAXN];

inline int single(int val){
	return val;
}

int NEUTRAL = 0; //ALSO HAS TO CHANGE

inline int merge(int a, int b){
	return a+b;
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
        t[x] += single(v);
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
int query(int l, int r, int x, int lx, int rx)
{
    if (lx >= r || rx <= l)
        return NEUTRAL;
    if (lx >= l && rx <= r)
        return t[x];
    int mid = (lx + rx) / 2;
    int a = query(l, r, 2 * x + 1, lx, mid);
    int b = query(l, r, 2 * x + 2, mid, rx);
    return merge(a, b);
}
int query(int l, int r)
{
    return query(l, r, 0, 0, sz);
}

int findk(int k, int x, int lx, int rx){
	if (rx-lx==1){
		dbg(lx,rx);
		return lx;
	}
	int mid = (lx+rx)/2;
	int q = query(lx, mid);
	dbg(k, lx, mid, q);
	if (k<q) return findk(k, 2*x+1, lx, mid);
	return findk(k-q, 2*x+2, mid, rx);
}

int findk(int k){
	return findk(k, 0,0, sz);
}

void solve()
{
	int k;
	cin >> n>>k;
	vi a(n), b;
	init(n);
	unordered_map<int,int, custom_hash> m1, m2;
	for (int &e:a) cin >> e;
	b = a;
	sort(all(b));
	b.resize(unique(all(b))-b.begin());
	for (int i=0;i<sz(b);i++) m1[b[i]] = i, m2[i] = b[i];
	for (int i=0;i<k;i++){
		upd(m1[a[i]],1);
	}
	cout << m2[findk((k-1)/2)]<< " ";
	for (int i=k;i<n;i++){
		upd(m1[a[i]],1);
		upd(m1[a[i-k]], -1);
		cout << m2[findk((k-1)/2)]<<" ";
	}
	cout << "\n";
	
	
	
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase=1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}