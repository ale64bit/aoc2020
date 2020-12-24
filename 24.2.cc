#include <iostream>
#include <string>
#include <array>
#include <set>
#include <algorithm>

using namespace std;

constexpr array<pair<int, int>, 6> moves = { { { 2, 0 }, { 1, -1 }, { -1, -1 }, { -2, 0 }, { -1, 1 }, { 1, 1 } } };

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    set<pair<int, int>> tiles;
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
        const auto p = make_pair(x, y);
        if (!tiles.insert(p).second)
            tiles.erase(p);
    }

    for (int i = 0; i < 100; ++i)
    {
        set<pair<int, int>> add, rm;
        for (const auto& [x, y] : tiles)
        {
            int adj = 0;
            for (const auto& [dx, dy] : moves)
                adj += tiles.count(make_pair(x + dx, y + dy));
            if (adj == 0 || adj > 2)
                rm.insert(make_pair(x, y));
            for (const auto& [dx, dy] : moves)
            {
                const int nx = x + dx;
                const int ny = y + dy;
                if (tiles.count(make_pair(nx, ny)) == 0)
                {
                    int wadj = 0;
                    for (const auto& [dx, dy] : moves)
                        wadj += tiles.count(make_pair(nx + dx, ny + dy));
                    if (wadj == 2)
                        add.insert(make_pair(nx, ny));
                }
            }
        }
        for (const auto p : rm)
            tiles.erase(p);
        tiles.insert(add.begin(), add.end());
    }
    cout << tiles.size() << '\n';

    return 0;
}
