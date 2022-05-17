#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

int main()
{
    string s, result;
    cin >> s;
    unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'y'};

    for (int i = 0; i < s.length(); i++)
    {
        char lowercase = tolower(s[i]);
        if (vowels.find(lowercase) == vowels.end())
        {
            result.append("." + string(1, lowercase));
        }
    }
    cout << result << "\n";
    return 0;
}