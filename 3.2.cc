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

    int64_t ans = 1;
    for (auto delta : vector<pair<int, int>>{
             { 1, 1 },
             { 3, 1 },
             { 5, 1 },
             { 7, 1 },
             { 1, 2 },
         })
    {
        int count = 0;
        int r = 0, c = 0;
        while (r < m.size())
        {
            count += m[r][c] == '#';
            c = (c + delta.first) % m[0].size();
            r += delta.second;
        }
        ans *= count;
    }
    cout << ans << '\n';

    return 0;
}
