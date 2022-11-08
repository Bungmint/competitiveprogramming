#include <bits/stdc++.h>
using ll = long long;
const ll MAX = 1e5 + 5;
ll arr[MAX];
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    ll n, temp;
    cin >> n;
    set<int> ls;
    vector<int> vec;
    while (n--)
    {
        cin >> temp;
        arr[temp] += temp;
        ls.insert(temp);
    }
    for (auto x : ls)
    {
        vec.push_back(x);
    }
    ll leng = vec.size();
    ll arr_takes[leng + 1], arr_nottake[leng + 1];
    arr_takes[leng] = arr[vec[leng - 1]];
    arr_nottake[leng] = 0ll;
    int cur;
    int prev = vec[leng - 1];
    for (ll i = leng - 1; i > 0; i--)
    {
        cur = vec[i - 1];
        if (llabs(cur - prev) > 1)
        {
            arr_takes[i] = arr[vec[i - 1]] + max(arr_takes[i + 1], arr_nottake[i + 1]);
            arr_nottake[i] = max(arr_takes[i + 1], arr_nottake[i + 1]);
        }
        else
        {
            arr_takes[i] = arr[vec[i - 1]] + arr_nottake[i + 1];
            arr_nottake[i] = max(arr_takes[i + 1], arr_nottake[i + 1]);
        }
        prev = cur;
    }
    cout << max(arr_nottake[1], arr_takes[1]) << "\n";

    return 0;
}