#include "beechtree.h"
#include <bits/stdc++.h>

using namespace std;

vector<int> beechtree(int N, int M, std::vector<int> P, std::vector<int> C)
{
    int n = N, m = M;
    vector<int> p = P, c = C, ans(n);
    vector<vector<int>> g(n), subt(n);
    for (int i = 1; i < n; ++i) g[p[i]].push_back(i);
    for (int i = 0; i < n; ++i) {
        int cur = i;
        while (cur != -1) subt[cur].push_back(i), cur = p[cur];
    }
    vector<int> idc(m+1), dont_rep(n, 1);
    vector<int> mark(max(n, m)+1);
    auto dfs = [&] (auto&& self, int u) -> void {
        for (auto v : g[u]) self(self, v), dont_rep[u] &= dont_rep[v];
        for (auto v : g[u]) {
            dont_rep[u] &= (mark[c[v]] == 0);
            mark[c[v]] = 1;
        }
        for (auto v : g[u]) {
            mark[c[v]] = 0;
        }
    };
    for (int r = 0; r < n; ++r) { 
        if (dont_rep[r] == 0) {
            ans[r] = 0;
            continue;
        }
        vector<int> colors;
        for (auto x : subt[r]) if (x != r) colors.push_back(c[x]);
        sort(begin(colors), end(colors));
        colors.erase(unique(begin(colors), end(colors)), end(colors));
        int nc = 0;
        for (auto x : colors) idc[x] = nc++;
        vector<vector<int>> choices(nc);
        for (auto x : subt[r]) if (x != r) choices[idc[c[x]]].push_back(p[x]);
        vector<int> ord(nc); iota(begin(ord), end(ord), [&] (int x, int y) {
            return choices[x].size() > choices[y].size();
        });
        bool ok = 1;
        for (int i = 1; i < nc; ++i) {
            for (auto u : choices[i-1]) mark[u] = 1;
            for (auto v : choices[i]) ok &= (mark[v] == 1);
            for (auto u : choices[i-1]) mark[u] = 0;
        }
        if (ok == 0) { 
            ans[r] = 0;
            continue;
        }

    }
    return ans;
}
