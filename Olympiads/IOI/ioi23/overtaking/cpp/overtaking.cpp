#include "overtaking.h"
#include <bits/stdc++.h>

using namespace std;
#define int long long

int l, n, m, x;
vector<int> t, w, s;
vector<vector<int>> e, ar, ps, ar_ord;

void init(int32_t L, int32_t N, std::vector<long long> T, std::vector<int32_t> W, int32_t X, int32_t M, std::vector<int32_t> S)
{
    l = L, n = N, m = M, x = X;
    for (auto z : W) w.push_back(z);
    for (auto z : S) s.push_back(z);
    for (auto z : T) t.push_back(z);
    //w.push_back(X);
    //t.push_back(-1);
    vector<int> ord(n);
    iota(begin(ord), end(ord), 0);
    ar = vector<vector<int>>(m, vector<int>(n));
    e  = vector<vector<int>>(m, vector<int>(n));
    ps  = vector<vector<int>>(m, vector<int>(n+1));
    ar[0] = t;
    for (int turn = 1; turn < m; ++turn) {
        int dd = s[turn] - s[turn-1];
        for (int i = 0; i < n; ++i) e[turn][i] = ar[turn-1][i] + dd * w[i];
        sort(begin(ord), end(ord), [&] (int x, int y) { return ar[turn-1][x] < ar[turn-1][y]; });
        int prv = 0;
        for (int l = 0, r = 0; l != n; l = r) {
            while (r != n and ar[turn-1][ord[l]] == ar[turn-1][ord[r]]) r++;
            int nxt = prv;
            for (int i = l; i < r; ++i) {
                ps[turn-1][i] = prv;
                nxt = max(nxt, e[turn][ord[i]]);
                ar[turn][ord[i]] = max(prv, e[turn][ord[i]]);
            }
            prv = nxt;
        }
        ps[turn-1][n] = prv;
    }
    for (int i = 0; i < m; ++i) {
        ar_ord.push_back({});
        for (int j = 0; j < n; ++j) ar_ord.back().push_back(ar[i][j]);
        sort(begin(ar_ord.back()), end(ar_ord.back()));
    }
}

long long arrival_time(long long Y)
{
    int tempo = Y;
    for (int turn = 1; turn < m; ++turn) {
        int dd = s[turn] - s[turn-1];
        int exp = tempo + dd * x;
        if (tempo <= ar_ord[turn-1][0]) {
            tempo = exp;
            continue;
        }
        if (ar_ord[turn-1].back() < tempo) {
            tempo = max(exp, ps[turn-1].back());
            continue;
        }
        int l = 0, r = n-1, pos = -1;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (ar_ord[turn-1][md] >= tempo) pos = md, r = md-1;
            else l = md+1;
        }
        assert(pos != -1);
        tempo = max(exp, ps[turn-1][pos]);
    }
    return tempo;
}
