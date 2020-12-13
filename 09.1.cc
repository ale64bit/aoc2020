#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    constexpr int window = 25;

    deque<int64_t> q;
    multiset<int64_t> s;
    for (int i = 0; i < window; ++i)
    {
        int64_t x;
        cin >> x;
        q.push_back(x);
        s.insert(x);
    }
    for (int64_t x; cin >> x;)
    {
        bool ok = false;
        for (int64_t a : s)
        {
            int64_t b = x - a;
            if ((a == b && s.count(b) > 1) || (a != b && s.count(b) == 1))
            {
                ok = true;
                break;
            }
        }
        if (!ok)
        {
            cout << x << '\n';
            break;
        }
        q.push_back(x);
        s.insert(x);
        if (q.size() > window)
        {
            s.erase(s.find(q.front()));
            q.pop_front();
        }
    }

    return 0;
}
