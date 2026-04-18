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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int n, h; cin >> n >> h;
    vector<int> pos(n), pot(n+1, 1);
    for (auto& x : pos) cin >> x;
    if (n == 1) {
        cout << 2 << endl;
        exit(0);
    }
    for (int i = 1; i <= n; ++i) pot[i] = 2 * pot[i-1] % mod;
    vector<int> ord(n); iota(all(ord), 0); sort(all(ord), [&] (int x, int y) { return pos[x] < pos[y]; });
    vector<int> possib(n+1, 1), comp(n+1);
    int sexo = 0;
    auto calc = [&] (vector<int> v) {
        sexo++;
        // pra eu poder matar tudo no v[i]:
        // olha pro menor cara a esq. ele tem q ter ido pra direita. olha pro proximo menor q ele. ele tem q ter ido pra direita. etc.
        // mesma coisa pra quem ta na direita dele.
        // ai vai sobrar um rangezinho neh. v[i] precisa ser uma das pontas!
        // ai dependendo se v[i] ta sozinho, eu multiplico por dois. o total de maneiras vai ser 2^(|v| - caras fixos).
        // dai preciso reportar num vetor global quantas maneiras tem de matar em cada rodada, pq pra TODO mundo morrer aqui, preciso que todos os
        // bichos das outras componentes morram ali ou antes!
        int m = sz(v);
        vector<int> seta_esq(m), seta_dir(m), qnt_e(m), qnt_d(m);
        vector<ii> st;
        st.pb({-1, -1});
        for (int i = 0; i < m; ++i) {
            while (st.back().first > v[i]) st.pop_back();
            seta_esq[i] = st.back().second;
            if (seta_esq[i] != -1) qnt_e[i] = qnt_e[seta_esq[i]] + 1;
            st.pb({v[i], i});
        }
        st = {{-1, m}};
        for (int i = m-1; ~i; --i) {
            while (st.back().first > v[i]) st.pop_back();
            seta_dir[i] = st.back().second;
            if (seta_dir[i] != m) qnt_d[i] = qnt_d[seta_dir[i]] + 1;
            st.pb({v[i], i});
        }
        for (int i = 0; i < m; ++i) {
            int pontas = (seta_esq[i] == i-1) + (seta_dir[i] == i+1);
            if (pontas == 0) continue;
            possib[v[i]] = pot[m-qnt_d[i]-qnt_e[i]+pontas-2]; 
            comp[v[i]] = sexo;
        }
    };
    vector<int> temp = {ord[0]};
    for (int i = 1; i < n; ++i) {
        if (pos[temp.back()] + h < pos[ord[i]]) {
            calc(temp);
            temp = {ord[i]};
        } else temp.pb(ord[i]);
    }
    calc(temp);
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    vector<int> seg(4*sexo);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int y) -> void  {
        if (l == r) {
            seg[i] = y;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, y);
        else self(self, 2*i+1, md+1, r, x, y);
        seg[i] = seg[2*i] * seg[2*i+1] % mod;
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x) -> int {
        if (l == r) return 1;
        int md = (l+r)/2;
        if (x <= md) return seg[2*i+1] * self(self, 2*i, l, md, x) % mod;
        else return seg[2*i] * self(self, 2*i+1, md+1, r, x) % mod;
    };
    vector<int> s_ways(sexo+1);
    for (int i = 0; i < n; ++i) {
        int k = comp[i];
        if (k) {
            s_ways[k] = (s_ways[k] + possib[i]) % mod;
            cout << query(query, 1, 0, sexo-1, k-1) * possib[i] % mod << " ";
            upd(upd, 1, 0, sexo-1, k-1, s_ways[k]);
        } else {
            cout << 0 << ' ';
        }
    }
    cout << endl;
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
