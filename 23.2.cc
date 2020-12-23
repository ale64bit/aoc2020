#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    constexpr int N = 1'000'000;
    constexpr int R = 10'000'000;

    list<int> x;
    for (char d; cin >> d; x.push_back(d - '1')) {}
    const int n = x.size();
    for (int i = n; i < N; ++i)
        x.push_back(i);
    list<int>::iterator its[N];
    for (auto it = x.begin(); it != x.end(); ++it)
        its[*it] = it;

    auto cur = x.begin();
    for (int r = 0; r < R; ++r)
    {
        auto it = cur;
        ++it;
        if (it == x.end())
            it = x.begin();

        int pick[3];
        for (int j = 0; j < 3; ++j)
        {
            pick[j] = *it;
            if ((it = x.erase(it)) == x.end())
                it = x.begin();
        }
        int dst = (*cur - 1 + N) % N;
        while (dst == pick[0] || dst == pick[1] || dst == pick[2])
            dst = (dst - 1 + N) % N;

        it = its[dst];
        ++it;
        it = x.insert(it, pick, pick + 3);
        for (int i = 0; i < 3; ++i, ++it)
            its[*it] = it;

        ++cur;
        if (cur == x.end())
            cur = x.begin();
    }

    int64_t ans = 1;
    auto it = its[0];
    for (int i = 0; i < 2; ++i)
    {
        ++it;
        if (it == x.end())
            it = x.begin();
        ans *= *it + 1;
    }
    cout << ans << '\n';

    return 0;
}
