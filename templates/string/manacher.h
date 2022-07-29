/**
 * Description: Finds the length of the longest palindrome centered at i
 * Source: https://cp-algorithms.com/string/manacher.html#working-with-parities
 * Verification: POI 2012 - Prefixuffix
 * Time Complexity: O(|S|)
 */

vi manacher(const string& s) {
    string t = "@";
    for (auto &ch : s)  t += ch, t += '#';
    t.back() = '^';
    vi ret(sz(t) - 1);
    for (int i = 1, l = 1, r = 1; i < sz(t) - 1; i++) {
        ret[i] = max(0, min(r - i, ret[l + (r - i)]));
        while (t[i - ret[i]] == t[i + ret[i]]) ret[i]++;
        if (i + ret[i] > r) l = i - ret[i], r = i + ret[i];
    }
	ret.erase(ret.begin());
	for (int i = 0; i < sz(ret); i++) {
		if (i % 2 == ret[i] % 2) ret[i]--;
	}
	return ret;
}