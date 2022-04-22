#include <bits/stdc++.h>

namespace std{
	template<typename Fun>
	struct y_combinator_result{
		Fun fun_;
		template<typename T>
		explicit y_combinator_result(T &&fun):fun_(std::forward<T>(fun)) {}
		template<typename...Args>
		decltype(auto) operator()(Args&&...args){
			return fun_(std::ref(*this), std::forward<Args>(args)...);
		}
	};
	template<typename Fun>
	decltype(auto) y_combinator(Fun &&fun){
		return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
	}
};

using namespace std;

using vi = vector<int>;

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second

template<typename T, size_t SZ>
using ar = array<T, SZ>;

template<typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U>& P){
	os << "(" << P.fi << ", " << P.se << ")";
	return os;
}
template<typename TContainer, typename T = enable_if_t<!is_same_v<TContainer, string>, typename TContainer::value_type>>
ostream& operator<<(ostream& os, TContainer& C){
	os << "(";
	string sep;
	for (auto &e: C){
		os << sep << e;
		sep = ", ";
	}
	os << ")";
	return os;
}

void dbg_out(){cerr<<endl;}
template<typename Head, typename...Tail>
void dbg_out(Head H, Tail...T){
	cerr << ' ' << H;
	(int[]){(cerr << ' ' << T, 0)...};
	cerr << endl;
}

#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__);
#else
#define dbg(...) 42
#endif



void setIO(){
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
}

void solve(){
	int n;
	cin >> n;
	int cnt = 0;
	vector<vi> adj(n);
	vector<bool> vis(n);
	for (int i=0;i<n;i++){
		int p;
		cin >> p, p--;
		adj[p].pb(i), adj[i].pb(p);
	}
	auto dfs = y_combinator([&](auto dfs, int u)->void{
		vis[u] = 1;
		for (auto&v:adj[u]) if (!vis[v]) dfs(v);
	});
	for (int i=0;i<n;i++){
		if (!vis[i]) cnt++, dfs(i);
	}
	cout << cnt;
}

int main(){
	setIO();
	int tc = 1;
	// cin >> tc;
	while(tc--) solve();
}