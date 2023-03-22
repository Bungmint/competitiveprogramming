#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int ans = 1;
        for (int i = 1; i <= n; i++) {
            ans *= i;
        }
        cout << ans % 10 << '\n';
    }
}
