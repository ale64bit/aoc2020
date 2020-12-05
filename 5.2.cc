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

    unordered_map<int, bool> seen;
    for (string s; cin >> s;)
    {
        int rlo = 0;
        int rhi = 128;
        for (int i = 0; i < 7; ++i)
        {
            int mid = (rlo + rhi) / 2;
            if (s[i] == 'F')
                rhi = mid;
            else
                rlo = mid;
        }
        int clo = 0;
        int chi = 8;
        for (int i = 7; i < 10; ++i)
        {
            int mid = (clo + chi) / 2;
            if (s[i] == 'L')
                chi = mid;
            else
                clo = mid;
        }
        seen[rlo * 8 + clo] = true;
    }
    for (int s = 0; s <= 127 * 8 + 7; ++s)
    {
        if (seen[s - 1] && !seen[s] && seen[s + 1])
        {
            cout << s << '\n';
            break;
        }
    }
    return 0;
}
