#include <iostream>
#include <string>
#include <array>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    constexpr int P = 20201227;

    int a, b;
    cin >> a >> b;

    int x = 0;
    for (int i = 1; i != a; i = (i * 7) % P)
        ++x;

    int64_t ans = 1;
    for (int j = 0; j < x; ++j)
        ans = (ans * b) % P;

    cout << ans << '\n';

    return 0;
}
