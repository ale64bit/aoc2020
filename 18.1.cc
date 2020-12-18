#include <cstdio>
#include <cctype>
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

constexpr int64_t kMaxLen = 1024;

char line[kMaxLen + 1];
int cur;

/*
 * expr := term mterms
 * mterms := op term mterms | eps
 * term := int | ( expr )
 */

void SkipWs()
{
    while (line[cur] == ' ')
        ++cur;
}

char Peek()
{
    SkipWs();
    return line[cur];
}

char Eat()
{
    SkipWs();
    return line[cur++];
}

int64_t expr();

int64_t term()
{
    int64_t res = 0;
    if (isdigit(Peek()))
        res = Eat() - '0';
    else if (Peek() == '(')
    {
        assert(Eat() == '(');
        res = expr();
        assert(Eat() == ')');
    }
    return res;
}

int64_t mterms(int64_t acc)
{
    if (Peek() == '+')
    {
        assert(Eat() == '+');
        acc += term();
        return mterms(acc);
    }
    else if (Peek() == '*')
    {
        assert(Eat() == '*');
        acc *= term();
        return mterms(acc);
    }
    return acc;
}

int64_t expr()
{
    return mterms(term());
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    int64_t ans = 0;
    for (; fgets(line, kMaxLen, stdin);)
    {
        cur = 0;
        ans += expr();
    }
    cout << ans << '\n';

    return 0;
}
