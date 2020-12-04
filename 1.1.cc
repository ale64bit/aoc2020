#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    unordered_map<int, bool> s;
    for (int x; cin >> x;)
    {
        int y = 2020 - x;
        if (s[y])
        {
            cout << x * y << '\n';
            return 0;
        }
        s[x] = true;
    }
    return 0;
}
