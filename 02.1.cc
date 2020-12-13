#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    int lo, hi;
    char meh, ch;
    string s;
    int count[26];
    int valid = 0;
    while (cin >> lo)
    {
        cin >> meh >> hi >> ch >> meh >> s;
        fill(count, count + 26, 0);
        for (char c : s)
            count[c - 'a']++;
        if (lo <= count[ch - 'a'] && count[ch - 'a'] <= hi)
            ++valid;
    }
    cout << valid << '\n';
    return 0;
}
