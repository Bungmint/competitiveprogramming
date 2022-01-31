#include <iostream>

using namespace std;

int16_t lcp[10000 + 5][10000 + 5];

int dp[10000 + 5];

bool is_greater(const string& s, int x, int y) {
    if (lcp[x][y] == static_cast<int>(s.size()) - x) {
        return false;
    }
    return s[x + lcp[x][y]] > s[y + lcp[x][y]];
}

int get_score(const string& s, int x, int y) {
    if (is_greater(s, x, y)) {
        return dp[y] + static_cast<int>(s.size()) - x - lcp[x][y];
    }
    return 0;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        if (s.size() != n) return 42;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                lcp[i][j] = 0;
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i == j) {
                    lcp[i][j] = n - i;
                } else
                if (s[i] != s[j]) {
                    lcp[i][j] = 0;
                } else {
                    lcp[i][j] = lcp[i + 1][j + 1] + 1;
                }
            }
        }
        int ans = n;
        dp[0] = n;
        for (int i = 1; i < n; i++) {
            dp[i] = n - i;
            for (int j = 0; j < i; j++) {
                dp[i] = max (dp[i], get_score(s, i, j));
            }
            ans = max(ans, dp[i]);
        }
        cout << ans << '\n';
    }
}