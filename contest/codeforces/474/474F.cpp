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
int a[100010],freq[200101];
int spar[100000][20];

void remove(int idx){
	freq[a[idx]]--;
}
void add(int idx){
	freq[a[idx]]++;
}     
const int block=320; //Dont forget to set

struct Query {
    int l, r, idx, g;
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
        answers[q.idx] = q.r-q.l+1 - freq[q.g];
    }
    return answers;
}

void solve()
{
	int n;
	cin >> n;
	vi order;
	for (int i=0;i<n;++i) cin >> a[i], order.pb(a[i]);
	for (int i=0;i<n;++i) spar[i][0] = a[i];
	for(int j=1;j<20;++j){
		for (int i=0;i+(1<<j)<=n;++i) spar[i][j] = gcd(spar[i][j-1], spar[i+(1<<(j-1))][j-1]);
	}
	int m;
	cin >> m;
	vq q(m);
	for (int i=0;i<m;++i){
		int l, r;
		cin >> l >> r;
		l--;r--;
		int lg = log2(r-l+1);
		int g = gcd(spar[l][lg], spar[r-(1<<lg)+1][lg]);
		order.pb(g);
		q[i] = {l,r,i, g};
	}
	sort(all(order));
	order.resize(unique(all(order))-order.begin());
	for (int i=0;i<n;++i) a[i] = lb(all(order), a[i])-order.begin();
	for (int i=0;i<m;++i) q[i].g = lb(all(order), q[i].g)-order.begin();
	vi ans = mo(q);
	for (int x:ans)cout <<x << "\n";
	
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