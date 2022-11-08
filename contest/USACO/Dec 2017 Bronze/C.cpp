#include <iostream>
#include <cmath>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;

int milk[3], N;
array<int, 3> logs[111];
map<char, int> conv = {{'B', 0}, {'E', 1}, {'M', 2}};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	freopen("measurement.in", "r", stdin);
	freopen("measurement.out", "w", stdout);

	for (int i = 0; i < 3; i++) milk[i] = 7;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> logs[i][0];
		string name; 
		cin >> name;
		logs[i][1] = conv[name[0]];
		cin >> logs[i][2];
	}
	sort(logs, logs + N);
	
	int result = 0;
	for (int i = 0; i < N; i++) {
		int pmax = max({milk[0], milk[1], milk[2]}), pmask = 0;
		for (int j = 0; j < 3; j++)
			if (pmax == milk[j]) pmask ^= 1 << j;
		milk[logs[i][1]] += logs[i][2];
		int curmax = max({milk[0], milk[1], milk[2]}), curmask = 0;
		for (int j = 0; j < 3; j++)
			if (curmax == milk[j]) curmask ^= 1 << j;
		
		result += pmask != curmask;
	}
	cout << result << '\n';
}