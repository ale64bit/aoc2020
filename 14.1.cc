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

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    const uint64_t kMaskSize = 36;

    unordered_map<uint64_t, uint64_t> mem;
    uint64_t mask0, mask1;
    char line[128];
    char s[kMaskSize + 1];
    uint64_t addr, val;

    while (fgets(line, 127, stdin))
    {
        if (sscanf(line, "mask = %s", s) == 1)
        {
            mask0 = 0;
            mask1 = 0;
            for (int i = 0; i < kMaskSize; ++i)
            {
                const auto bit = 1ULL << (kMaskSize - i - 1);
                switch (s[i])
                {
                case '0': break;
                case '1':
                    mask0 ^= bit;
                    mask1 ^= bit;
                    break;
                case 'X': mask1 ^= bit; break;
                default: assert(false);
                }
            }
        }
        else if (sscanf(line, "mem[%" SCNu64 "] = %" SCNu64 "", &addr, &val) == 2)
            mem[addr] = (val | mask0) & mask1;
        else
            break;
    }

    uint64_t ans = 0;
    for (auto p : mem)
        ans += p.second;
    printf("%" PRIu64 "\n", ans);

    return 0;
}
