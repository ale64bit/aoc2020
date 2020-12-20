#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

void fliph(vector<string>& tile)
{
    for (int i = 0; i < tile.size() / 2; ++i)
        swap(tile[i], tile[tile.size() - i - 1]);
}

void flipv(vector<string>& tile)
{
    for (int i = 0; i < tile.size(); ++i)
        reverse(tile[i].begin(), tile[i].end());
}

void trans(vector<string>& tile)
{
    for (int i = 0; i < tile.size(); ++i)
        for (int j = i + 1; j < tile.size(); ++j)
            swap(tile[i][j], tile[j][i]);
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    vector<int> tile_ids;
    vector<vector<string>> tiles;

    for (string s; cin >> s;)
    {
        if (s != "Tile")
            break;
        int id;
        cin >> id;
        getline(cin, s);

        vector<string> tile;
        for (string r; getline(cin, r);)
        {
            if (r.empty())
                break;
            tile.push_back(r);
        }
        tile_ids.push_back(id);
        tiles.push_back(tile);
    }
    const int n = static_cast<int>(sqrt(tiles.size()));
    assert(n * n == tiles.size());

    constexpr int kNumTransforms = 7;
    const vector<vector<void (*)(vector<string>&)>> transforms = {
        {}, { fliph }, { flipv }, { fliph, flipv }, { fliph, trans }, { flipv, trans }, { fliph, flipv, trans },
    };

    unordered_map<string, vector<tuple<int, int, int>>> edges;
    for (size_t i = 0; i < tiles.size(); ++i)
    {
        for (int j = 0; j < kNumTransforms; ++j)
        {
            vector<string> tile = tiles[i];
            for (auto f : transforms[j])
                f(tile);
            edges[*tile.begin()].push_back(make_tuple(tile_ids[i], j, 0));
            edges[*tile.rbegin()].push_back(make_tuple(tile_ids[i], j, 1));
            trans(tile);
            edges[*tile.begin()].push_back(make_tuple(tile_ids[i], j, 2));
            edges[*tile.rbegin()].push_back(make_tuple(tile_ids[i], j, 3));
        }
    }

    unordered_map<int, int> count;
    for (const auto& [edge, configs] : edges)
    {
        set<int> candidates;
        for (const auto t : configs)
        {
            const auto [id, tr, dir] = t;
            candidates.insert(id);
        }
        if (candidates.size() == 1)
            count[*candidates.begin()]++;
    }
    int64_t ans = 1;
    for (const auto& [id, cnt] : count)
        if (cnt == 4)
            ans *= id;
    cout << ans << '\n';

    return 0;
}
