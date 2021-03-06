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
#include <inttypes.h>

using namespace std;

constexpr int kMaxCycles = 7;
constexpr int kMaxSize = 8;
constexpr int kMaxDim = 2 * kMaxCycles + kMaxSize + 1;

char a[kMaxDim][kMaxDim][kMaxDim];
char b[kMaxDim][kMaxDim][kMaxDim];

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    int n = 0;
    for (; scanf("%s", a[kMaxCycles][kMaxCycles + n] + kMaxCycles) == 1; ++n)
    {
        char* ptr = a[kMaxCycles][kMaxCycles + n] + kMaxCycles;
        while (*ptr)
        {
            *ptr = *ptr == '#';
            ++ptr;
        }
    }

    for (int cycle = 1; cycle <= 6; ++cycle)
    {
        for (int i = 1; i < kMaxDim - 2; ++i)
            for (int j = 1; j < kMaxDim - 2; ++j)
                for (int k = 1; k < kMaxDim - 2; ++k)
                {
                    int adj = 0;
                    for (int di = -1; di <= 1; ++di)
                        for (int dj = -1; dj <= 1; ++dj)
                            for (int dk = -1; dk <= 1; ++dk)
                                adj += a[i + di][j + dj][k + dk];
                    b[i][j][k] = (a[i][j][k] && (adj == 3 || adj == 4)) || (!a[i][j][k] && (adj == 3));
                }
        memcpy(a, b, sizeof(a));
    }

    int ans = 0;
    for (int i = 1; i < kMaxDim - 2; ++i)
        for (int j = 1; j < kMaxDim - 2; ++j)
            for (int k = 1; k < kMaxDim - 2; ++k)
                ans += a[i][j][k];
    printf("%d\n", ans);

    return 0;
}
