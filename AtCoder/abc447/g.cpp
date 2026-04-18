#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e10+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int n; cin >> n;
    vector<int> k(n), a(n);
    for (int i = 0; i < n; ++i) cin >> k[i] >> a[i], --k[i];
    int ans = -1;
    for (int penis = 0; penis < 2; ++penis) {
        vector<array<int, 8>> pref(n+1), suf(n+2);
        for (int i = 0; i < 4; ++i) pref[0][2*i+1] = suf[n+1][2*i+1] = -1;
        for (int i = 1; i <= n; ++i) {
            pref[i] = pref[i-1];
            bool found = 0;
            for (int j = 0; j < 8; j += 2) {
                if (pref[i][j] == k[i-1]) {
                    found = 1;
                    ckmax(pref[i][j+1], a[i-1]);
                    int t = j;
                    while (t and pref[i][t-1] < pref[i][t+1]) swap(pref[i][t], pref[i][t-2]), swap(pref[i][t+1], pref[i][t-1]), t -= 2;
                    break;
                }
            }
            if (found) continue;
            for (int j = 1; j < 8; j += 2) {
                if (pref[i][j] <= a[i-1]) {
                    for (int t = 7; t > j; t -= 2) pref[i][t] = pref[i][t-2], pref[i][t-1] = pref[i][t-3];
                    pref[i][j] = a[i-1];
                    pref[i][j-1] = k[i-1];
                    break;
                }
            }
        }
        for (int i = n; i >= 1; --i) {
            suf[i] = suf[i+1];
            bool found = 0;
            for (int j = 0; j < 8; j += 2) {
                if (suf[i][j] == k[i-1]) {
                    found = 1;
                    ckmax(suf[i][j+1], a[i-1]);
                    int t = j;
                    while (t and suf[i][t-1] < suf[i][t+1]) swap(suf[i][t], suf[i][t-2]), swap(suf[i][t+1], suf[i][t-1]), t -= 2;
                    break;
                }
            }
            if (found) continue;
            for (int j = 1; j < 8; j += 2) {
                if (suf[i][j] <= a[i-1]) {
                    for (int t = 7; t > j; t -= 2) suf[i][t] = suf[i][t-2], suf[i][t-1] = suf[i][t-3];
                    suf[i][j] = a[i-1];
                    suf[i][j-1] = k[i-1];
                    break;
                }
            }
        }
        // gostaria de saber quem eh o segundo cara...
        vector<int> seg(4*n, -inf);
        vector<multiset<int>> mt(n);
        auto upd = [&] (auto&& self, int i, int l, int r, int x, int y, int k, int type) -> void {
            if (r < x or y < l) return;
            if (x <= l and r <= y) {
                if (type) mt[l].insert(k);
                else mt[l].erase(mt[l].find(k));
                if (mt[l].empty()) seg[i] = -inf;
                else seg[i] = (*prev(end(mt[l])));
                return;
            }
            int md = (l+r)/2;
            if (x <= md) self(self, 2*i, l, md, x, y, k, type);
            else self(self, 2*i+1, md+1, r, x, y, k, type);
        };
        auto query = [&] (auto&& self, int i, int l, int r, int x) -> int {
            if (l == r) return seg[i];
            int md = (l+r)/2;
            if (x <= md) return max(seg[i], self(self, 2*i, l, md, x));
            return max(seg[i], self(self, 2*i+1, md+1, r, x));
        };
        vector<int> seg2(4*n, -inf);
        vector<multiset<int>> mt2(4*n);
        auto upd2 = [&] (auto&& self, int i, int l, int r, int x, int y, int k, int type) -> void {
            if (r < x or y < l) return;
            if (x <= l and r <= y) {
                if (type) mt2[l].insert(k);
                else mt2[l].erase(mt2[l].find(k));
                if (mt2[l].empty()) seg2[i] = -inf;
                else seg2[i] = (*prev(end(mt2[l])));
                return;
            }
            int md = (l+r)/2;
            self(self, 2*i, l, md, x, y, k, type);
            self(self, 2*i+1, md+1, r, x, y, k, type);
        };
        auto query2 = [&] (auto&& self, int i, int l, int r, int x) -> int {
            if (l == r) return seg2[i];
            int md = (l+r)/2;
            if (x <= md) return max(seg2[i], self(self, 2*i, l, md, x));
            return max(seg2[i], self(self, 2*i+1, md+1, r, x));
        };
        map<int, map<int, multiset<int>>> mp;
        for (int i = 4; i <= n-2; ++i) {
            int x = k[i-1];
            for (int j = 0; j < 8; j += 2) {
                if (suf[i+1][j] == -1) break;
                if (suf[i+1][j] == x) continue;
                int y = suf[i+1][j];
                int score = a[i-1], foi = 0;
                for (int w = 0; w < 8; w += 2) {
                    if (suf[i+1][w] != -1 and suf[i+1][w] != x and suf[i+1][w] != y) score += suf[i+1][w+1], foi++;
                }
                if (foi != 2) continue;
                mp[x][y].insert(score);
            }
            int score = a[i-1], foi = 0;
            for (int w = 0; w < 8; w += 2) {
                if (suf[i+1][w] != -1 and suf[i+1][w] != k[i-1] and foi < 2) score += suf[i+1][w+1], foi++;
            }
            vector<int> forb = {k[i-1]};
            for (int w = 0; w < 8; w += 2) {
                if (suf[i+1][w] != -1) forb.pb(suf[i+1][w]);
            }
            forb.pb(-1), forb.pb(n);
            sort(all(forb));
            if (foi == 2) {
                for (int w = 1; w < sz(forb); ++w) {
                    int i1 = forb[w-1]+1, i2 = forb[w]-1;
                    if (i1 <= i2) {
                        upd2(upd2, 1, 0, n-1, i1, i2, score, 1);
                        upd(upd, 1, 0, n-1, i1, i2, score, 1);
                    }
                }
            }
        }
        for (int i = 3; i <= n-3; ++i) {
            if (i >= 4) {
                int x = k[i-1];
                for (int j = 0; j < 8; j += 2) {
                    if (suf[i+1][j] == -1) break;
                    if (suf[i+1][j] == x) continue;
                    int y = suf[i+1][j];
                    int score = a[i-1], foi = 0;
                    for (int w = 0; w < 8; w += 2) {
                        if (suf[i+1][w] != -1 and suf[i+1][w] != x and suf[i+1][w] != y) score += suf[i+1][w+1], foi++;
                    }
                    if (foi != 2) continue;
                    mp[x][y].erase(mp[x][y].find(score));
                }
                int score = a[i-1], foi = 0;
                for (int w = 0; w < 8; w += 2) {
                    if (suf[i+1][w] != -1 and suf[i+1][w] != k[i-1] and foi < 2) score += suf[i+1][w+1], foi++;
                }
                vector<int> forb = {k[i-1]};
                for (int w = 0; w < 8; w += 2) {
                    if (suf[i+1][w] != -1) forb.pb(suf[i+1][w]);
                }
                forb.pb(-1), forb.pb(n);
                sort(all(forb));
                if (foi == 2) {
                    for (int w = 1; w < sz(forb); ++w) {
                        int i1 = forb[w-1]+1, i2 = forb[w]-1;
                        if (i1 <= i2) {
                            upd2(upd2, 1, 0, n-1, i1, i2, score, 0);
                            upd(upd, 1, 0, n-1, i1, i2, score, 0);
                        }
                    }
                }
            }
            vector<int> forb = {k[i-1]};
            forb.pb(-1);
            forb.pb(n);
            for (int j = 0; j < 8; j += 2) {
                if (pref[i-1][j] == -1) break;
                if (pref[i-1][j] == k[i-1]) continue;
                int x = k[i-1], y = pref[i-1][j];
                forb.pb(y);
                int score = a[i-1], foi = 0;
                for (int w = 0; w < 8; w += 2) {
                    if (pref[i-1][w] != -1 and pref[i-1][w] != x and pref[i-1][w] != y) score += pref[i-1][w+1], foi++;
                }
                if (foi != 2) continue;
                // os dois aparecem em ambos os lados
                if (!mp[y][x].empty()) ckmax(ans, score + (*prev(end(mp[y][x]))));
                ckmax(ans, score + query2(query2, 1, 0, n-1, x));
            }
            sort(all(forb));
            int score = a[i-1], foi = 0;
            for (int w = 0; w < 8; w += 2) {
                if (pref[i-1][w] != -1 and pref[i-1][w] != k[i-1] and foi < 2) score += pref[i-1][w+1], foi++;
            }
            if (foi == 2) {
                for (int t = 1; t < sz(forb); ++t) {
                    int i1 = forb[t-1]+1, i2 = forb[t]-1;
                    if (i1 <= i2) {
                        cout << penis << endl;
                        cout << i << " " << i1 << " " << i2 << endl;
                        ckmax(ans, score + query(query, 1, 0, n-1, k[i-1]));
                        if (ans == 34) exit(0);
                    }
                }
            }
            // agora quero o cara a direita que nao eh nenhum desses caras em forb
        }
        reverse(all(k)), reverse(all(a));
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
