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

const int root = 1;
int cur = 1;
int trie[6000000][2];
int cnt[6000000];

void insert(int x){
	int now = 1;
	for (int i=26;i>=0;i--){
		int c = (x>>i)&1;
		if (!trie[now][c]) trie[now][c] = ++cur;
		now = trie[now][c];
		cnt[now]++;
	}
}

void del(int x){
	int now = 1;
	for (int i=26;i>=0;i--){
		int c = (x>>i)&1;
		if (!trie[now][c]) trie[now][c] = ++cur;
		now = trie[now][c];
		cnt[now]--;
	}
}

int query(int p, int l){
	int now = 1;
	int res =0;
	for (int i=26;i>=0;i--){
		if (!now) return res;
		int pc = (p>>i)&1, lc = (l>>i)&1;
		int l = trie[now][0], r = trie[now][1];
		if (pc&&lc){
			now = l;
			res += cnt[r];
		}else if(pc){
			now = r;
			
		}else if (lc){
			now = r;
			res += cnt[l];
		}else{
			now = l;
		}
	}
	return res;
}

void solve()
{
	int q;
	cin >> q;
	while(q--){
		int op;
		cin >> op;
		if (op==1){
			int p;
			cin >> p;
			insert(p);
		}else if (op==2){
			int p;
			cin >> p;
			del(p);
		}else{
			int p, l;
			cin >> p >> l;
			cout << query(p,l)<<"\n";
		}
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}