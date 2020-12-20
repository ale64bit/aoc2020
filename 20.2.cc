#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

constexpr int kMaxN = 12;
constexpr int kMaxTiles = kMaxN * kMaxN;
constexpr int kNumTransforms = 8;

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

const vector<vector<void (*)(vector<string>&)>> transforms = {
    {}, { fliph }, { flipv }, { trans }, { fliph, flipv }, { fliph, trans }, { flipv, trans }, { fliph, flipv, trans },
};

int n;
int m;
vector<vector<string>> tiles;
vector<bool> used;
int img[kMaxN][kMaxN][2];
bool match[kMaxTiles][kNumTransforms][4][kMaxTiles][kNumTransforms][4];

inline bool compat(int r, int c, int i, int j)
{
    bool ret = true;
    if (r > 0 && img[r - 1][c][0] != -1)
        ret &= match[i][j][0][img[r - 1][c][0]][img[r - 1][c][1]][1];
    if (r < m - 1 && img[r + 1][c][0] != -1)
        ret &= match[i][j][1][img[r + 1][c][0]][img[r + 1][c][1]][0];
    if (c < m - 1 && img[r][c + 1][0] != -1)
        ret &= match[i][j][2][img[r][c + 1][0]][img[r][c + 1][1]][3];
    if (c > 0 && img[r][c - 1][0] != -1)
        ret &= match[i][j][3][img[r][c - 1][0]][img[r][c - 1][1]][2];
    return ret;
}

bool solve(int r, int c)
{
    if (r < 0 || r >= m || c < 0 || c >= m)
        return true;
    if (img[r][c][0] != -1)
        return true;

    for (int i = 0; i < tiles.size(); ++i)
    {
        if (used[i])
            continue;
        for (int j = 0; j < kNumTransforms; ++j)
        {
            if (compat(r, c, i, j))
            {
                used[i] = true;
                img[r][c][0] = i;
                img[r][c][1] = j;
                if (solve(r + 1, c) && solve(r, c + 1))
                    return true;
                img[r][c][0] = -1;
                used[i] = false;
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    vector<int> tile_ids;

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
    n = tiles[0].size();
    m = static_cast<int>(sqrt(tiles.size()));

    for (size_t i = 0; i < tiles.size(); ++i)
    {
        for (int j = 0; j < kNumTransforms; ++j)
        {
            vector<string> tile1 = tiles[i];
            for (auto f : transforms[j])
                f(tile1);
            for (size_t ii = 0; ii < tiles.size(); ++ii)
            {
                for (int jj = 0; jj < kNumTransforms; ++jj)
                {
                    if (i == ii)
                        continue;
                    vector<string> tile2 = tiles[ii];
                    for (auto f : transforms[jj])
                        f(tile2);

                    match[i][j][1][ii][jj][0] = tile1[n - 1] == tile2[0];
                    match[i][j][0][ii][jj][1] = tile1[0] == tile2[n - 1];
                    match[i][j][3][ii][jj][2] = true;
                    match[i][j][2][ii][jj][3] = true;
                    for (int r = 0; r < n; ++r)
                    {
                        match[i][j][3][ii][jj][2] &= tile1[r][0] == tile2[r][n - 1];
                        match[i][j][2][ii][jj][3] &= tile1[r][n - 1] == tile2[r][0];
                    }
                }
            }
        }
    }

    used.resize(tiles.size());
    fill(used.begin(), used.end(), false);
    memset(img, -1, sizeof(img));

    assert(solve(0, 0));
    vector<string> full_img(m * (n - 2));
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            auto tile = tiles[img[i][j][0]];
            for (auto f : transforms[img[i][j][1]])
                f(tile);
            for (int k = 1; k < n - 1; ++k)
                full_img[i * (n - 2) + k - 1].append(tile[k].substr(1, n - 2));
        }
    }

    const vector<string> kSeaMonster = {
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   ",
    };
    for (auto t : transforms)
    {
        vector<pair<int, int>> loc;
        auto tmp = full_img;
        for (auto f : t)
            f(tmp);
        for (int i = 0; i < tmp.size() - kSeaMonster.size(); ++i)
            for (int j = 0; j < tmp[i].size() - kSeaMonster[0].size(); ++j)
            {
                bool ok = true;
                for (int ii = 0; ii < kSeaMonster.size(); ++ii)
                    for (int jj = 0; jj < kSeaMonster[ii].size(); ++jj)
                        ok &= (kSeaMonster[ii][jj] != '#') || (tmp[i + ii][j + jj] == '#');
                if (ok)
                    loc.push_back(make_pair(i, j));
            }
        if (loc.size())
        {
            for (const auto& [i, j] : loc)
            {
                for (int ii = 0; ii < kSeaMonster.size(); ++ii)
                    for (int jj = 0; jj < kSeaMonster[ii].size(); ++jj)
                        if (kSeaMonster[ii][jj] == '#')
                            tmp[i + ii][j + jj] = 'O';
            }
            int ans = 0;
            for (int i = 0; i < tmp.size(); ++i)
                for (int j = 0; j < tmp[i].size(); ++j)
                    if (tmp[i][j] == '#')
                        ++ans;
            cout << ans << '\n';
            break;
        }
    }

    return 0;
}
