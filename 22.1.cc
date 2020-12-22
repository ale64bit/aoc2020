#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    queue<int> cards[2];
    for (int i = 0; i < 2; ++i)
    {
        for (string s; getline(cin, s);)
            if (s.substr(0, 6) == "Player")
                break;
        for (string s; getline(cin, s);)
        {
            if (s == "")
                break;
            cards[i].push(stoi(s.c_str()));
        }
    }
    assert(cards[0].size() == cards[1].size());

    const int n = cards[0].size();
    while (cards[0].size() && cards[1].size())
    {
        if (cards[0].front() < cards[1].front())
        {
            cards[1].push(cards[1].front());
            cards[1].push(cards[0].front());
        }
        else
        {
            assert(cards[0].front() > cards[1].front());
            cards[0].push(cards[0].front());
            cards[0].push(cards[1].front());
        }
        cards[0].pop();
        cards[1].pop();
    }
    int ans = 0;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = n + n; !cards[i].empty(); cards[i].pop(), --j)
            ans += cards[i].front() * j;
    }
    cout << ans << '\n';

    return 0;
}
