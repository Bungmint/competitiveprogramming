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
const int N = 1e5+1;
ll a[N], v[N], l[N], r[N];
int t[N];
ll cnt[N*3];
ll res = 0;
int n, k;

inline void removeleft(int idx){
	cnt[v[idx]]--;
	res -= cnt[r[idx]];
}
inline void removeright(int idx){
	cnt[v[idx]]--;
	res -= cnt[l[idx]];
}
inline void addleft(int idx){
	res += cnt[r[idx]];
	cnt[v[idx]]++;	
}     
inline void addright(int idx){
	res += cnt[l[idx]];
	cnt[v[idx]]++;	
}  
inline ll get_answer(){
	return res;
}
const int block = 320; //Dont forget to set

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


vl mo(vector<Query> queries) {
   	vl answers(queries.size());
    sort(queries.begin(), queries.end());


    int cur_l = 0;
    int cur_r = -1;
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            addleft(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            addright(cur_r);
        }
        while (cur_l < q.l) {
            removeleft(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            removeright(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }
    return answers;
}

void solve()
{
	cin >> n >> k;
	for (int i=1;i<=n;++i) cin >> t[i];
	for (int i=1;i<=n;++i){
		cin >> a[i];
		if (t[i]==2){
			a[i] = -a[i];
		}
		a[i] += a[i-1];
	}
	vl order;
	for (int i=0;i<=n;++i){
		order.pb(a[i]);
		order.pb(a[i]-k);
		order.pb(a[i]+k);
	}
	order.resize(unique(all(order))-order.begin());
	sort(all(order));
	for (int i=0;i<=n;++i){
		int x = lb(all(order), a[i])-order.begin();
		int y = lb(all(order), a[i]-k)-order.begin();
		int z = lb(all(order), a[i]+k)-order.begin();
		v[i] = x, l[i] = y, r[i] = z;
	}
	dbg(order);
	int q;
	cin >> q;
	vq quer(q);
	for (int i=0;i<q;++i){
		int l, r;
		cin >> l >> r;
		l--;
		quer[i] = {l,r,i};
	}
	vl ans = mo(quer);
	for (ll x:ans) cout << x << "\n";
	
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}