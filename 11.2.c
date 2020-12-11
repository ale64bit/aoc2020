#include <stdio.h>
#include <string.h>

#define MAXN 111

char a[MAXN][MAXN];
char b[MAXN][MAXN];

int main()
{
    int r = 0;
    while (scanf("%s", a[r + 1] + 1) == 1)
        ++r;
    int c = strlen(a[1] + 1);

    for (;;)
    {
        int change = 0;
        for (int i = 1; i <= r; ++i)
        {
            for (int j = 1; j <= c; ++j)
            {
                int adj = 0;
                for (int di = -1; di <= 1; ++di)
                    for (int dj = -1; dj <= 1; ++dj)
                    {
                        if (!di && !dj)
                            continue;
                        int ii = i + di;
                        int jj = j + dj;
                        while (1 <= ii && ii <= r && 1 <= jj && jj <= c && a[ii][jj] == '.')
                        {
                            ii += di;
                            jj += dj;
                        }
                        if (a[ii][jj] == '#')
                            ++adj;
                    }
                if (a[i][j] == 'L' && !adj)
                {
                    b[i][j] = '#';
                    change = 1;
                }
                else if (a[i][j] == '#' && adj >= 5)
                {
                    b[i][j] = 'L';
                    change = 1;
                }
                else
                    b[i][j] = a[i][j];
            }
        }
        if (!change)
            break;
        memcpy(a, b, sizeof(a));
    }

    int ans = 0;
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            ans += a[i][j] == '#';
    printf("%d\n", ans);

    return 0;
}
