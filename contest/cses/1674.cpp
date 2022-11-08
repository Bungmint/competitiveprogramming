#include <bits/stdc++.h>

namespace std{
	template<typename Fun>
	struct y_combinator_result {
		Fun fun_;
		template<typename T>
		explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)){}
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

// using namespace std;

using vi = std::vector<int>;
template<typename T, size_t SZ>
using ar = std::array<T, SZ>;

#define sz(x) (int)(x).size()
#define pb push_back

void setIO(const std::string& str){
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin.exceptions(std::cin.failbit);
	if (sz(str)){
		freopen((str+".in").c_str(), "r", stdin);
		freopen((str+".out").c_str(), "w", stdout);
	}
}

void solve(){
	int n;
	std::cin >> n;
	std::vector<vi> g(n);
	vi subtree(n);
	for (int i=1;i<n;i++){
		int p; std::cin >> p;
		p--;
		g[i].pb(p), g[p].pb(i);
	}
	auto dfs = std::y_combinator([&](auto dfs, int u, int pu)->void{
		subtree[u] = 1;
		for (auto&v:g[u]){
			if (v!=pu){
				dfs(v, u);
				subtree[u] += subtree[v];
			}
		}
	});
	dfs(0, -1);
	for (auto&e:subtree) std::cout << e-1 << " ";
}


int main(){
	setIO("");
	int tc = 1;
	// cin >> tc;
	while(tc--) solve();
}
