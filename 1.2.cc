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

int64_t a[111];

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    int n = 0;
    while (cin >> a[n++])
        ;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            for (int k = j + 1; k < n; ++k)
            {
                if (a[i] + a[j] + a[k] == 2020)
                {
                    cout << a[i] * a[j] * a[k] << '\n';
                    return 0;
                }
            }
        }
    }

    return 0;
}
