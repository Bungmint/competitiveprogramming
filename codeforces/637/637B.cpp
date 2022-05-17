#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    unordered_set<string> friends;
    vector<string> chats(n);
    for (int i = 0; i < n; i++)
    {
        cin >> chats[i];
        friends.insert(chats[i]);
    }
    reverse(chats.begin(), chats.end());
    vector<string> res;
    int distinct = friends.size();
    friends.clear();
    int start = 0;
    while (res.size() < distinct)
    {
        if (friends.count(chats[start]) == 1)
        {
            start++;
            continue;
        }
        friends.insert(chats[start]);
        res.push_back(chats[start]);
        start++;
    }
    for (auto x : res)
    {
        cout << x << "\n";
    }
    return 0;
}