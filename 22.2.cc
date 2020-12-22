#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <algorithm>

using namespace std;

struct ConfigHash
{
    size_t operator()(const pair<deque<int>, deque<int>>& p) const
    {
        constexpr size_t P = 1234567891;
        size_t h = 0;
        for (const auto& i : p.first)
            h = h * P + i;
        h = h * P + 99999;
        for (const auto& i : p.second)
            h = h * P + i;
        return h;
    }
};

int play(deque<int>& p1, deque<int>& p2, bool root = true)
{
    if (!root)
    {
        int max1 = 0, max2 = 0;
        int min1 = 1e9, min2 = 1e9;
        for (int i : p1)
        {
            min1 = min(min1, i);
            max1 = max(max1, i);
        }
        for (int i : p2)
        {
            min2 = min(min2, i);
            max2 = max(max2, i);
        }
        if ((min1 > p1.size() || min2 > p2.size()) && max1 > max2)
            return 0;
    }

    unordered_set<pair<deque<int>, deque<int>>, ConfigHash> m;
    while (p1.size() && p2.size())
    {
        const auto key = make_pair(p1, p2);
        if (m.find(key) != m.end())
            return 0;
        m.insert(key);

        int c1 = p1.front();
        int c2 = p2.front();
        p1.pop_front();
        p2.pop_front();

        int winner = 0;
        if (c1 <= p1.size() && c2 <= p2.size())
        {
            deque<int> p1_copy(p1.begin(), p1.begin() + c1), p2_copy(p2.begin(), p2.begin() + c2);
            winner = play(p1_copy, p2_copy, false);
        }
        else
            winner = c1 > c2 ? 0 : 1;
        if (winner == 0)
        {
            p1.push_back(c1);
            p1.push_back(c2);
        }
        else
        {
            p2.push_back(c2);
            p2.push_back(c1);
        }
    }
    return p1.size() ? 0 : 1;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    deque<int> cards[2];
    for (int i = 0; i < 2; ++i)
    {
        for (string s; getline(cin, s);)
            if (s.substr(0, 6) == "Player")
                break;
        for (string s; getline(cin, s);)
        {
            if (s == "")
                break;
            cards[i].push_back(stoi(s.c_str()));
        }
    }

    int winner = play(cards[0], cards[1]);
    int ans = 0;
    for (int j = cards[winner].size(); !cards[winner].empty(); cards[winner].pop_front(), --j)
        ans += cards[winner].front() * j;
    cout << ans << '\n';

    return 0;
}
