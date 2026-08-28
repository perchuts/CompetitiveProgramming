#include "longesttrip.h"
#include <bits/stdc++.h>
#define pb push_back
#define all(x) begin(x), end(x)

using namespace std;

std::vector<int> longest_trip(int n, int d)
{
    if (d == 2) {

        deque<int> dq = {0};
        if (are_connected({0}, {1})) {
            for (int i = 1; i < n; ++i) {
                if (are_connected({dq.back()}, {i})) dq.push_back(i);
                else dq.push_front(i);
            }
        } else {
            dq = {1};
            for (int i = 2; i <= n; ++i) {
                if (are_connected({dq.back()}, {i%n})) dq.push_back(i%n);
                else dq.push_front(i%n);
            }
        }
        vector<int> ans;
        for (auto x : dq) ans.push_back(x);
        return ans;
    };
    if (d == 3) {
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) ans[i] = i;
        return ans;
    }
    auto solve = [&] (auto&& self, int l, int r) -> array<vector<int>, 2> {
        if (r == l) {
            array<vector<int>, 2> ans;
            ans[0] = {l};
            return ans;
        }
        if (r == l+1) {
            array<vector<int>, 2> ans;
            if (are_connected({l}, {r})) ans[0] = {l, r};
            else ans[0] = {l}, ans[1] = {r};
            return ans;
        }
        int md = (l+r)/2;
        auto p = self(self, l, md);
        auto q = self(self, md+1, r);
        if (p[1].empty() and !q[1].empty()) swap(p, q);
        vector<int> P, Q;
        if (!p[1].empty() and !q[1].empty()) {
            int choice = are_connected({p[0][0]}, {q[0][0]}) ^ 1;
            for (auto x : q[choice]) P.pb(x);
            reverse(all(P));
            for (auto x : p[0]) P.pb(x);
            // q[choice] p[0], q[choice^1], p[1]
            auto aux = p[1];
            reverse(all(aux));
            if (are_connected({p[1][0]}, {P[0]})) {
                for (auto x : P) aux.pb(x);
                P = aux;
                Q = q[choice^1];
            } else {
                for (auto x : q[choice^1]) aux.pb(x);
                Q = aux;
            }
        } else if (!p[1].empty()) {
            int choice = are_connected({p[0][0]}, {q[0][0]}) ^ 1;
            for (auto x : p[choice]) P.pb(x);
            reverse(all(P));
            for (auto x : q[0]) P.pb(x);
            Q = p[choice^1];
        } else P = p[0], Q = q[0];

        if (!are_connected(P, Q)) return {P, Q};
        for (int aa = 0; aa < 2; ++aa) {
            for (int bb = 0; bb < 2; ++bb) {
                if (are_connected({P.back()}, {Q[0]})) {
                    vector<int> opt = P;
                    for (auto x : Q) opt.pb(x);
                    return {opt, {}};
                }
                if (Q.size() == 1) break;
                reverse(all(Q));
            }
            if (P.size() == 1) break;
            reverse(all(P));
        }
        
        // no connection between edges!
        if (P.size() > Q.size()) swap(P, Q);

        int lp = 0, rp = P.size()-1, i = -1;
        int calls = 0;
        while (lp <= rp) { 
            calls++;
            int m = lp + (rp-lp+1)/2;
            vector<int> pp;
            for (int k = 0; k <= m; ++k) pp.pb(P[k]);
            if (are_connected(Q, pp)) i = m, rp = m-1;
            else lp = m+1;
        }
        lp = 0, rp = Q.size()-1; int j = -1;
        while (lp <= rp) { 
            int m = lp + (rp-lp+1)/2;
            vector<int> pp;
            for (int k = 0; k <= m; ++k) pp.pb(Q[k]);
            if (are_connected({P[i]}, pp)) j = m, rp = m-1;
            else lp = m+1;
        }
        vector<int> h;
        for (int k = 0; k < P.size(); ++k) h.pb(P[(i+1+k)%P.size()]);
        for (int k = 0; k < Q.size(); ++k) h.pb(Q[(j+k)%Q.size()]);
        return {h, {}};
    };
    auto [p1, p2] = solve(solve, 0, n-1);
    if (p1.size() < p2.size()) swap(p1, p2);
    return p1;
}
