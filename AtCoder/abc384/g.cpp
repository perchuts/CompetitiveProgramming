#include "grader.h"
#include <bits/stdc++.h>

int findEgg(int n, vector<pair<int, int>> edg) {
    vector<vector<int>> g(n+1);
    for (auto [x, y] : edg) g[x].push_back(y), g[y].push_back(x);
    int l = 1, r = n, ans = n;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        vector<int> qq, foi(n+1);
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (qq.size() < md) qq.push_back(u), foi[u] = 1;
            for (auto v : g[u]) {
                if (!foi[v]) continue;
                q.push(v);
            }
        }
        //auto dfs = [&] (auto&& self, int u, int p) -> void {
        //    if (T <= md) qq.push_back(u);
        //    T++;
        //    for (auto v : g[u]) {
        //        if (v == p) continue;
        //        self(self, v, u);
        //    }
        //};
        if (query(qq)) ans = l, l = md+1;
        else r = md-1;
    }
    return ans; 
}
