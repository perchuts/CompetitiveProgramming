#include "soccer.h"
#include <bits/stdc++.h>
#define pb push_back

using namespace std;

using ll = long long;
using ii = pair<int, int>;

int biggest_stadium(int n, std::vector<std::vector<int>> grid)
{
    vector<vector<int>> ps(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            ps[i][j] = ps[i-1][j] + ps[i][j-1] - ps[i-1][j-1] + grid[i-1][j-1];
        }
    }
    auto rect = [&] (int x1, int y1, int x2, int y2) { return ps[x2][y2] - ps[x2][y1-1] - ps[x1-1][y2] + ps[x1-1][y1-1]; };
    // posso aumentar o comprimento, diminuir a altura. o ganho sera oq esta na diferenca de ambos!
    int h = 0;
    vector id(n+1, vector(n+1, vector(n+1, vector(n+1, -1))));
    for (int x1 = 1; x1 <= n; ++x1) {
        for (int y1 = 1; y1 <= n; ++y1) {
            for (int x2 = x1; x2 <= n; ++x2) {
                for (int y2 = y1; y2 <= n; ++y2) {
                    if (rect(x1, y1, x2, y2) == 0) id[x1][y1][x2][y2] = h++;
                }
            }
        }
    }
    vector<int> dp(h);
	int ans = 0;
	for (int sr = n; sr >= 1; --sr) {
		for (int sc = 1; sc <= n; ++sc) {
			for (int x1 = 1; x1 + sr <= n+1; ++x1) {
				for (int y1 = 1; y1 + sc <= n+1; ++y1) {
					int x2 = x1+sr-1, y2 = y1+sc-1;
					int eu = id[x1][y1][x2][y2];
					if (eu == -1) continue;
					dp[eu] = max(dp[eu], sr*sc);
					ans = max(ans, dp[eu]);
                    for (int x3 = x1; x3 <= x2; ++x3) {
                        for (int x4 = x3; x4 <= x2; ++x4) {
                            for (int y3 = 1; y3 <= y1; ++y3) {
                                for (int y4 = y2; y4 <= n; ++y4) {
									int outro = id[x3][y3][x4][y4];
									if (outro != -1) dp[outro] = max(dp[outro], dp[eu] + (x4-x3+1) * (y1-y3 + y4 - y2));
								}
							}
						}
					}
				}
			}
		}
	}
    return ans;
}
