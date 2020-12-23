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
int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    vector<int> x;
    for (char d; cin >> d; x.push_back(d - '1')) {}

    const int n = x.size();
    for (int r = 0; r < 100; ++r)
    {
        const int cur = x[r % n];
        int pick[3] = {
            x[(r + 1) % n],
            x[(r + 2) % n],
            x[(r + 3) % n],
        };
        int dst = (cur - 1 + n) % n;
        while (dst == pick[0] || dst == pick[1] || dst == pick[2])
            dst = (dst - 1 + n) % n;
        for (int i = 1; i < n; ++i)
        {
            x[(r + i) % n] = x[(r + i + 3) % n];
            if (x[(r + i) % n] == dst)
            {
                for (int j = 0; j < 3; ++j)
                    x[(r + i + j + 1) % n] = pick[j];
                break;
            }
        }
    }

    rotate(x.begin(), find(x.begin(), x.end(), 0), x.end());
    for (int i = 1; i < n; ++i)
        cout << x[i] + 1;
    cout << '\n';

    return 0;
}
