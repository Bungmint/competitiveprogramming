// Problem: E. Minimax
// Contest: Codeforces - Codeforces Round #733 (Div. 1 + Div. 2, based on VK Cup 2021 - Elimination (Engine))
// URL: https://codeforces.com/contest/1530/problem/E
// Memory Limit: 512 MB
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

void solve()
{
	string s;
	cin >> s;
	int n = sz(s);
	vi cnt(26);
	for (int i=0;i<n;++i) cnt[s[i]-'a']++;
	dbg(cnt);
	int mi = INF;
	int id = -1;
	for (int i=0;i<26;++i){
		if (cnt[i]&&mi>cnt[i]) mi = cnt[i], id = i;
	}
	if (mi==n){
		cout << s << "\n";
		return;
	}
	if (mi==1){
		// Zero
		for (int i=0;i<cnt[id];++i) cout << (char)('a'+id);
		for (int i=0;i<26;++i){
			if (i==id) continue;
			for (int j=0;j<cnt[i];++j){
				cout << (char)('a'+i);
			}
		}
		cout << "\n";
	}else{
		// Juan
		int mi = INF;
		for (int i=0;i<26;++i){
			if (cnt[i]) mi = min(mi, i);
		}
		string tmp = "";
		for (int i=mi+1;i<26;++i){
			for (int j=0;j<cnt[i];++j) tmp+=(char)('a'+i);
		}
		dbg(mi);
		if (cnt[mi]*2<=n+2){
			for (int i=0;i<2;++i) cout << (char)('a'+mi);
			int ptr = 0;
			for (int i=2;i<cnt[mi];++i){
				cout << tmp[ptr++];
				cout << (char)('a'+mi);
			}
			for (int i=ptr;i<sz(tmp);++i) cout << tmp[i];
			cout << "\n";
		}else{
			int avail=0;
			for (int i=0;i<26;++i){
				if (i!=mi&&cnt[i]) avail++;
			}
			if (avail==1){
				int j;
				for (int i=0;i<26;++i){
					if (i!=mi&&cnt[i]) j = i;
				}
		
				cout << (char)('a'+mi);
				for (int i=0;i<cnt[j];++i) cout << (char)('a'+j);
				for (int i=1;i<cnt[mi];++i) cout << (char)('a'+mi);
				cout << "\n";
			}else{
				int j=-1, k=-1;
				string tmp;
				for (int i=0;i<26;++i){
					if (i!=mi&&cnt[i]){
						if (j==-1){
							j=i;
							for (int x=1;x<cnt[i];++x) tmp+=(char)('a'+i);
						}else if (k==-1){
							k=i;
							for (int x=1;x<cnt[i];++x) tmp+=(char)('a'+i);
						}else{
							for (int x=0;x<cnt[i];++x) tmp+=(char)('a'+i);
						}
					}
				}
				cout << (char)('a'+mi);
				cout << (char)('a'+j);
				for (int i=1;i<cnt[mi];++i){
					cout << (char)('a'+mi);
				}
				cout << (char)('a'+k);
				cout << tmp;
				cout << "\n";
			}
		}
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}