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
int N, S, L;
int M, K, P;


struct oxc {
    vector<int> conn;
};

vector<oxc> super_nodes;


// N = # groups            [1, 2^5]
// S = # spines per group  [1, 2^5]
// L = # leaves per group  [1, 2^6]
// M = # OXC               [1, 2^8]
// K = # links OXC ~ spine [1, 2^1]
// P = # planes            [1, 2^4]

int foi[32][32][5];
bool mark[32][32];
ii pair_ports[32][32];
// soh ativar quando for necessario!
void solve(int qual_query) {
    int n_queries; cin >> n_queries;
    vector<array<int, 4>> qq(n_queries);
    for (int i = 0; i < n_queries; ++i) {
        for (int j = 0; j < 4; ++j) cin >> qq[i][j];
    }
    // se N, S / P eh impar, entao tem uma carinha de que eu fiz o L supremo
    // corner case: S / P, M / P, N, K impares.
    int ports_per_oxc = S / P * K;
    int oxc_per_plane = M / P;
    auto group_kth_port = [&] (int g, int k) {
        // encontra o indice do k-esimo port do g-esimo grupo dentro de um oxc
        return g * ports_per_oxc + k;
    };
    if (qual_query == 1) {
        vector<ii> ordem;
        for (int i = 1; i <= N/2; ++i) {
            for (int j = 0; j < N; ++j) {
                int other = N - i;
                if (other <= i and (i + j) % N < j) continue;
                ordem.pb({j, (i + j) % N});
            }
        }
        int ptr = 0;
        for (int i = 0; i < P; ++i) {
            for (int cur_oxc = 0; cur_oxc < oxc_per_plane; ++cur_oxc) {
                vector<int> used(N);
                for (int turns = 0; turns < ports_per_oxc * N / 2 and ptr < sz(ordem); ++turns, ++ptr) {
                    auto [u, v] = ordem[ptr];
                    assert(max(used[u], used[v]) < ports_per_oxc);
                    int port_u = group_kth_port(u, used[u]);
                    int port_v = group_kth_port(v, used[v]);
                    // eh o plano i. entao to olhando pro s
                    foi[u][v][0] = foi[v][u][3] = (S / P) * i + (used[u] / K);
                    foi[u][v][3] = foi[v][u][0] = (S / P) * i + (used[v] / K);
                    foi[u][v][1] = foi[v][u][4] = port_u % K;
                    foi[u][v][4] = foi[v][u][1] = port_v % K;
                    foi[u][v][2] = foi[v][u][2] = oxc_per_plane * i + cur_oxc;
                    pair_ports[u][v] = {port_u, port_v};
                    pair_ports[v][u] = {port_v, port_u};
                    used[u]++, used[v]++;
                }
            }
        }
    }

    for (int i = 0; i < n_queries; ++i) {
        int u = qq[i][0], v = qq[i][2];
        if (mark[u][v] == false) {
            mark[u][v] = true;
            auto [port_u, port_v] = pair_ports[u][v];
            super_nodes[foi[u][v][2]].conn[port_u] = port_v;
            super_nodes[foi[u][v][2]].conn[port_v] = port_u;
        }
    }

    for (int i = 0; i < M; ++i) {
        for (auto x : super_nodes[i].conn) cout << x << " ";
        cout << endl;
    }
    for (int i = 0; i < n_queries; ++i) {
        int g_u = qq[i][0], g_v = qq[i][2], id_u = qq[i][1], id_v = qq[i][3];
        for (int j = 0; j < 5; ++j) cout << foi[g_u][g_v][j] << " ";
        cout << endl;
    }
}

void solve_K_equals_1(int qual_query) {
    int n_queries; cin >> n_queries;
    vector<array<int, 4>> qq(n_queries);
    map<ii, vector<ii>> qry;
    for (int i = 0; i < n_queries; ++i) {
        for (int j = 0; j < 4; ++j) cin >> qq[i][j];
        qry[{min(qq[i][0], qq[i][2]), max(qq[i][0], qq[i][2])}].pb({i, (qq[i][0] > qq[i][2])});
    }
    vector<vector<int>> xx(N);
    for (auto [x, y] : qry) {
        xx[x.first].pb(sz(y));
        xx[x.second].pb(sz(y));
    }
    int lim = 1;
    for (int i = 0; i < N; ++i) {
        int l = 1, r = S * L, opt = r;
        while (l <= r) {
            int md = l + (r-l+1)/2, qt = 0;
            for (auto x : xx[i]) qt += (x + md - 1) / md;
            if (qt <= S * (M / P)) opt = md, r = md-1;
            else l = md+1;
        }
        ckmax(lim, opt);
    }
    // uma caixa significa escolher uma tripla (spine_u, oxc, spine_v) tal que (spine_u, oxc) nao aparece em outro lugar, e nem (oxc, spine_v).
    // coisa foda: preciso que spine_u, spine_v vivam no mesmo plano!!
    // pra cada par (u, v), vou precisar de usar X bichos.
    // propriedades desse grafo??
    // soma dos pesos que saem de um vertice eh <= S * (M / P)
    // 1 ~ 0
    // 0 ~ 1
    // P * (S / P) * (M / P)
    // S * M / P 
    vector<array<int, 5>> ans(n_queries);
    for (int i = 0; i < M; ++i) {
        for (auto x : super_nodes[i].conn) cout << x << " ";
        cout << endl;
    }

    for (int i = 0; i < n_queries; ++i) {
        for (int j = 0; j < 5; ++j) cout << ans[i][j] << " ";
        cout << endl;
    }

}

int32_t main() {_
    cin >> N >> S >> L;
    cin >> M >> K >> P;
    super_nodes.resize(M);
    for (int i = 0; i < M; ++i) super_nodes[i].conn = vector<int>(N * S / P * K, -1);
#ifndef gato
    for (int i = 1; i <= 5; ++i) {
        if (K == 2) solve(i);
        else {

        }
    }
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
