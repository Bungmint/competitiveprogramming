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
int timer = 0;
int st[200000], en[200000];
vi G[200000];
int a[400010], c[200000], freq[200000], cnt = 0;
vi order;

void dfs(int V, int pV){
	st[V] = timer++;
	a[st[V]] = c[V];
	for (int e:G[V]){
		if (e!=pV) dfs(e,V);
	}
	en[V] = timer++;
	a[en[V]] = c[V];
	dbg(st[V], en[V], V);
}

void remove(int idx){
	freq[a[idx]]--;
	if (!freq[a[idx]])cnt--;
}
void add(int idx){
	freq[a[idx]]++;
	if (freq[a[idx]]==1) cnt++;
}     
int get_answer(){
	return cnt;
}
const int block=450; //Dont forget to set

struct Query {
    int l, r, idx;
	inline pair<int, int> toPair() const {
		return make_pair(l / block, ((l / block) & 1) ? -r : +r);
	}
};
inline bool operator<(const Query &a, const Query &b) {
	return a.toPair() < b.toPair();
}

using vq = vector<Query>;


vi mo(vq queries) {
   	vi answers(queries.size());
    sort(queries.begin(), queries.end());

    int cur_l = 0;
    int cur_r = -1;
    for (Query q : queries) {
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
        answers[q.idx] = get_answer();
    }
    return answers;
}

void solve()
{
	int n;
	cin >> n;
	for (int i=0;i<n;++i) cin >> c[i], order.pb(c[i]);
	for (int i=0;i<n-1;++i){
		int u,v;
		cin >> u >> v;
		u--;v--;
		G[u].pb(v); G[v].pb(u);
	}
	sort(all(order));
	order.resize(unique(all(order))-order.begin());
	for (int i=0;i<n;++i){
		c[i] = lb(all(order), c[i])-order.begin();
	}
	dfs(0,-1);
	vq Q;
	for (int i=0;i<n;++i){
		Q.pb({st[i], en[i], i});
	}
	vi ans = mo(Q);
	for (int x:ans) cout << x << " ";
	cout << "\n";
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