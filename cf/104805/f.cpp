#include <bits/stdc++.h>
#define sz(x) (int) x.size()
using namespace std;
#pragma GCC optimize("Ofast")
// Vetorizacao
#pragma GCC target("avx2")
#define _ ios_base::sync_with_stdio(false);cin.tie(0);
#define endl '\n'

using ld = double;

const ld INF = 1e18;
ld fins[10];
int32_t main(){_
    int n; cin >> n;
    vector<ld> d(n);
    for (auto& x : d) cin >> x;
    ld T; cin >> T;
    vector<array<ld, 2>> p(n);
    for (int i = 0; i < n; ++i) p[i][0] = p[i][1] = INF;
    vector<array<int, 2>> ans(n);
    vector<int> P(n); iota(begin(P), end(P), 0);
    int itrs = 0;
    do {
        //itrs++;
        //cout << itrs << endl;
        //cout.flush();
        fins[0] = 0;
        int tf = 1;
        vector<pair<double, double>> tipo(n, make_pair(0, -1));
        auto bt = [&] (auto&& self, int id) -> void {
            if (fins[tf-1] == T) {
                vector<ld> morte(n, INF);
                for (int j = 0; j < n; ++j) {
                    if (tipo[j].second == -1) {
                        morte[j] = d[j]+tipo[j].first;
                        continue;
                    }
                    morte[j] = (d[j] + tipo[j].first + tipo[j].second)/2;
                }
                vector<tuple<ld, int, ld, ld>> resp;
                for (int j = 0; j < n; ++j) {
                    if (morte[j] <= T) resp.push_back({morte[j], j+1, tipo[j].first, tipo[j].second});
                }
                sort(begin(resp), end(resp));
                for (auto& [a, b, c, e] : resp) {
                    if (c > 0) {
                        for (int i = 1; i <= sz(resp); ++i) {
                            if (get<0>(resp[i-1]) >= c) {
                                c = i; break;
                            }
                        }
                    }
                    if (e > 0) {
                        for (int i = 1; i <= sz(resp); ++i) {
                            if (get<0>(resp[i-1]) >= e) {
                                e = i; break;
                            }
                        }
                    }
                }
                cout << resp.size() << endl;
                for (auto [a, b, c, e] : resp) cout << fixed << setprecision(69) << a << ' ' << b << ' ' << int(c) << ' ' << int(e) << endl;
                exit(0);
            }
            if (id == n) return;
            int i = P[id];
            for (int j = 0; j < tf; ++j) {
                ld x = fins[j];
                tipo[i] = {x, -1};
                fins[tf++] = x+d[i];
                if (fins[tf-1] <= T+1e-5) self(self, id+1);
                tf--;
                for (int k = j; k < tf; ++k) {
                    ld y = fins[k];
                    if (x > y) swap(x, y);
                    if (y-x >= d[i]) continue;
                    tipo[i] = {x, y};
                    fins[tf++] = (x+y+d[i])/2;
                    if (fins[tf-1] <= T+1e-5) self(self, id+1);
                    tf--;
                }
            }
        };
        bt(bt, 0);
    } while (next_permutation(begin(P), end(P)));
    cout << -1 << endl;
}

