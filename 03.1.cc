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

    vector<string> m;
    for (string s; cin >> s; m.push_back(s))
        ;

    int ans = 0;
    int r = 0, c = 0;
    while (r < m.size())
    {
        ans += m[r][c] == '#';
        c = (c + 3) % m[0].size();
        ++r;
    }
    cout << ans << '\n';

    return 0;
}
