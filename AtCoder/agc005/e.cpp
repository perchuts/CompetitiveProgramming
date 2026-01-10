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

void solve() {
    int n, X, Y; cin >> n >> X >> Y; --X, --Y;
    vector<vector<vector<int>>> g(2, vector<vector<int>>(n));
    for (int i = 0; i < 2*(n-1); ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[i/(n-1)][u].pb(v);
        g[i/(n-1)][v].pb(u);
    }
    // se as arvores coincidem, entao o jogo termina e eh trivial determinar a quantidade de rodadas
    // caso contrario, olhe pra arvore azul enraizada em Y.
    // se a alice conseguir chegar em um vertice q "encobre" o bob, entao o jogo acabou! pq o bob vai ter que voltar, ai a alice refaz o movimento,
    // e ai voltamos pro msm lugar. ent o bob tem que impedir esse tipo de estado, i.e., as opcoes imediatas da alice devem satisfazer exatamente um de:
    // estar no mesmo sentido do caminho optimal do bob ate a alice
    // ser vizinho do vertice atual do bob.
    // vamos supor entao que a cond. 2 eh satisfeita e dist(A, B, azul) > 1. fiz o W! o bob vem pra perto, eu vou pra esse vizinho, o bob volta, eu volto.
    //
    //             BOB
    //            /
    //           /
    //           x
    //          /
    //        Alice
    //
    // quero claimar que se a alice tem um vizinho a distancia diferente de 1 de x e fora da subarvore da alice, ela fez o W.
    // a prova eh direta: isso significa que o bob vai ter q desviar da aresta x---alice, e dai a alice pode voltar com seguranca pro vertice anterior.
    // de fato, isso pode ser dito pra todo vertice no caminho de bob ate alice! => se funciona pro vertice mais em cima, funciona pro x tambem. ent
    // so precisamos nos preocupar com o pai de alice (x).
    // quero claimar q o jogo eh finito se e somente se todos os vertices q a alice alcanca antes do bob satisfazem essa prop.
    //
    // ent os movimentos imediatos da alice sao: ir pra um vizinho de x,
    // descer ainda mais na subarvore dela.
    // => se eu conseguir subir, oq acontece? -> ganho. ent so consigo subir ate o meu avo.
    // pinta de preto tds os vertices na subarvore da alice. olha a vizinhanca "branca" agr na arvore vermelha.
    // essa vizinhanca branca precisa ser um subconjunto dos vizinhos de x!
    // -> se existe algum vertice q consegue pular pra fora da subarvore da alice alem do vertice atual dela (e q ela consegue chegar antes do bob),
    // o jogo tambem acabou! entao se a alice adentrar pra essa subarvore, ela garantidamente perde...
    // vms ver se ela ainda tem esperanca de viver infinitamente.... ir pra um filho de x significa repetir o argumento, mas agr com o bob mais proximo.
    // => acabou!
    //
    int T = 0;
    vector<int> tin(n), tout(n), par(n), h(n);
    auto is_anc = [&] (int u, int v) { return (tin[u] <= tin[v] and tout[v] <= tout[u]); };
    auto pre_bob = [&] (auto&& self, int u, int p) -> void {
        tin[u] = ++T, par[u] = p;
        for (auto v : g[1][u]) {
            if (v == p) continue;
            h[v] = 1 + h[u], self(self, v, u);
        }
        tout[u] = T;
    };
    pre_bob(pre_bob, Y, Y);
    // eu faço o W se eu consigo sair da minha subt e da vizinhanca do meu pai
    // eu quero chegar o mais rapido possivel nos lugares? isso pode ser ligeiramente tricky...
    // bem, acredito q sim...
    auto infty = [&] () {
        cout << -1 << endl;
        exit(0);
    };
    vector<int> dist(n, inf);
    auto dfs = [&] (auto&& self, int u) -> void {
        int act_dist = h[u] - dist[u], pos_bob = -1;
        if (act_dist <= 3) {
            pos_bob = u;
            for (int w = 0; w < act_dist; ++w, pos_bob = par[pos_bob]) {}
        }
        for (auto v : g[0][u]) {
            if (dist[v] != inf) continue;
            if ((par[v] != u and par[u] != v) and (par[par[u]] != v and par[par[v]] != u) and par[u] != par[v]) infty();
            // como dizer se posso ir de u -> v?
            // vou executar este movimento no meu passo dist[u] + 1. faço o L se:
            // Bob esta em V. (nesse caso, impossivel ir pra V dado q n caiu no if acima)
            // bob esta em um vizinho de V. => tbm impossivel ir.
            if (act_dist <= 3) {
                if (pos_bob == v or par[v] == pos_bob or par[pos_bob] == v) continue;
            }
            dist[v] = 1 + dist[u];
            self(self, v);
        }
    };
    dist[X] = 0;
    dfs(dfs, X);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (dist[i] != inf) ckmax(ans, 2 * h[i]);
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
