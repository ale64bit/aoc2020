#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    constexpr int64_t target = 393911906;

    queue<int64_t> q;
    multiset<int64_t> s;
    for (int64_t x, sum = 0; cin >> x;)
    {
        sum += x;
        q.push(x);
        s.insert(x);
        while (sum > target && !q.empty())
        {
            sum -= q.front();
            s.erase(s.find(q.front()));
            q.pop();
        }
        if (sum == target && s.size() > 1)
        {
            cout << *s.begin() + *s.rbegin() << '\n';
            break;
        }
    }

    return 0;
}
