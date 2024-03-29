#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
const int N = 1e6+1;
int trie[N][26], cnt[N][26], n, q, nxt = 1;

void build(string &s, int i =0, int v = 0){
	while(i<(int)s.size()){
		dbg(v,s[i]);
		cnt[v][s[i]-'a']++;
		if (trie[v][s[i]-'a'] == -1){
			v = trie[v][s[i++]-'a'] = nxt++;
		}else{
			v = trie[v][s[i++]-'a'];
		}
	}
}

int query(string &s, int i=0, int v=0){
	while(i<(int)s.size()-1){
		dbg(v, s[i]);
		if (trie[v][s[i]-'a']==-1) return 0;
		else{
			v = trie[v][s[i]-'a'];
			i++;
		}
	}
	return cnt[v][s[i]-'a'];
}

void solve()
{
	memset(trie, -1, sizeof(trie));
	cin >> n >> q;
	while(n--){
		string s;
		cin >> s;
		build(s);
		dbg(nxt);
	}
	while(q--){
		string s;
		cin >> s;
		cout << query(s)<<"\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}