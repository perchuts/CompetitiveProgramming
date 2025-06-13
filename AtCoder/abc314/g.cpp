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

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(){
    int n, m, h; cin >> n >> m >> h;
    vector<int> a(n), b(n), ss(m), tipo(m);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i], --b[i];
    int ans = 0, L = 0;
    set<ii> sexo, sem_sexo;
    for (int i = 0; i < m; ++i) sem_sexo.insert({0, i});
    for (int can = 0; can <= m; ++can) {
        if (sz(sexo) < can and !sem_sexo.empty()) {
            auto [x, y] = *begin(sem_sexo);
            L += x, tipo[y] = 1;
            sem_sexo.erase({x, y}), sexo.insert({x, y});
        }
        auto update = [&] (int sgn) {
            if (tipo[b[ans]] == 1) {
                sexo.erase({-ss[b[ans]], b[ans]});
                ss[b[ans]] += sgn*a[ans];
                sexo.insert({-ss[b[ans]], b[ans]});
            } else {
                sem_sexo.erase({-ss[b[ans]], b[ans]});
                ss[b[ans]] += sgn*a[ans], L += sgn*a[ans];
                sem_sexo.insert({-ss[b[ans]], b[ans]});
            }
        };
        while (ans != n) {
            update(1);
            if (min(sz(sexo), sz(sem_sexo))) {
                auto [x1, y1] = *begin(sem_sexo);
                auto [x2, y2] = *prev(end(sexo));
                int go = 0;
                if (-x1 > -x2) L += x1 - x2, go = 1;
                if (L >= h) { L -= go*(x1 - x2); update(-1); break; }
                if (go) {
                    sem_sexo.erase({x1, y1}), sexo.erase({x2, y2});
                    sexo.insert({x1, y1}), sem_sexo.insert({x2, y2});
                    swap(tipo[y1], tipo[y2]);
                }
            } else if (L >= h) { update(-1); break; }
            ans++;
        }
        cout << ans << ' ';
    }
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
