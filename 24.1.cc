#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    set<pair<int, int>> seen;
    for (string s; cin >> s;)
    {
        int x = 0, y = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            switch (s[i])
            {
            case 'e': x += 2; break;
            case 'w': x -= 2; break;
            case 'n':
                x += (s[i + 1] == 'e') ? 1 : -1;
                y += 1;
                ++i;
                break;
            case 's':
                x += (s[i + 1] == 'e') ? 1 : -1;
                y -= 1;
                ++i;
                break;
            }
        }
        auto p = make_pair(x, y);
        if (!seen.insert(p).second)
            seen.erase(p);
    }
    cout << seen.size() << '\n';

    return 0;
}
