#include <bits/stdc++.h>
#include "jngen.h"
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

// Esse gerador cria queries com resposta pelo menos 1.1 * N/10 

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 1e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

pair<Graph, vector<pair<int, int>>> genRandom3(int n, int maxM) {
      Graph g = Graph::empty(n);
      // crio linha de tamanho N / 2
      for (int i = 0; i < n / 2 - 1; ++i) g.addEdge(i, i + 1);
      TArray<int> tams, pod;
      int sobra = n - n / 2, edg = n / 2 - 1;
      // sorteio o tamanho das componentes de cada vertice da linha
      for (int i = 0; i < n / 2; ++i) {
            tams.pb(rnd.next(0, min(100, sobra)));
            sobra -= tams.back(), edg += tams.back();
      }
      tams.shuffle();
      int curNode = n / 2;
      // // agora adicionando as componentes perifericas no grafo principal
      int sq = sqrt(n/2);
      for (int i = 0; i < n/2; ++i) pod.pb(i<sq);
      pod.shuffle();
      const int perif_dst = 5, max_conn = 5;
      for (int i = 0; i < n / 2; ++i) {
            if (tams[i] == 0) continue;
            // ja reservei la em cima tams[i] arestas pra essa componente (arvore + conectar na linha)
            int qt_edg = rnd.next(tams[i] - 1, tams[i] - 1 + min(maxM - edg, (perif_dst-1) * tams[i] + 1));
            ckmin(qt_edg, ((tams[i] - 1) * tams[i]) / 2);
            edg += qt_edg - (tams[i] - 1);
            auto peq = Graph::random(tams[i], qt_edg).connected().g();
            for (int j = 0; j < tams[i]; ++j) {
                  for (auto x : peq.edges(j)) {
                        // adicionando no grafo original
                        if (x < j) g.addEdge(curNode + j, curNode + x);
                  }
            }
            // conexoes com o grafo principal
            int qntConn = rnd.next(1, 1 + min(max_conn - 1, maxM - edg));
            TArray<int> possible;
            // soh sqrt(n/2) caras podem ter vizinhos "distantes" na linha (distantes = 5)
            if (pod[i] == 1) for (int j = i; j < min(i + 5, n / 2); ++j) possible.pb(j);
            else possible.pb(i);
            // garantir que sempre vou conseguir gerar as conexoes sem repeticao
            ckmin(qntConn, sz(possible) * tams[i]);
            map<ii, bool> used;
            for (int j = 0; j < qntConn; ++j) {
                  while (true) {
                        int k = rnd.next(0, sz(possible) - 1);
                        int w = rnd.next(0, tams[i] - 1);
                        if (used[{w, k}]) continue;
                        used[{w, k}] = 1;
                        g.addEdge(possible[k], curNode + w);
                        break;
                  }
            }
            edg += qntConn - 1, curNode += tams[i];
      }
      int q = rnd.next(2 * n, min(200000, 5 * n));
      vector<pair<int, int>> queries;
      // onde comeca os labels de cada componente
      vector<int> st; st.pb(n/2);
      for (int i = 1; i < n / 2; ++i) st.pb(st.back() + tams[i-1]);
      for (int i = 0; i < q; ++i) {
            while(true) {
                  int a = rnd.next(0, n / 2 - 1), b = rnd.next(0, n / 2 - 1);
                  // garantindo que o caminho minimo vai ser > n / 10
                  if (abs(a - b) <= n/10 + sq * 5) continue;
                  int u = rnd.next(0, tams[a]), v = rnd.next(0, tams[b]);
                  // escolhe aleatorio alguem na componente, tambem pode escolher o cara correspondente na linha
                  u = (u == tams[a] ? a : st[a] + u), v = (v == tams[b] ? b : st[b] + v);
                  queries.pb(make_pair(v, u));
                  break;
            }
      }
      return make_pair(g, queries);
}

const int MAXN = 100000;
const int MAXM = 200000;
const int MAXQ = 200000;

vector<int> gg[MAXN + 100];

void checker(int n, vector<pair<int, int>> queries, int cs) {
      mt19937 rng(6969420);
    
      int k = min(n, 200); 

      vector<int>p(n);
      iota(all(p), 1);
      shuffle(all(p), rng);

      queue<int>q;

      vector<vector<int>> dist(k, vector<int>(n+1, inf));

      for(int i=0;i<k;++i){
            int cur = p[i];
            dist[i][cur] = 0;
            q.push(cur); 
            while(!q.empty()){
                  auto x = q.front();q.pop();
                  for(auto y : gg[x]){
                        if(dist[i][y] == inf){
                              dist[i][y] = dist[i][x] + 1;
                              q.push(y);
                        }
                  }
            }
      }

      int md = n;
      int a, b;
      double tot = 0, ruin = 0;
      for (auto [u, v] : queries){
            int mn = inf; 
            for(int i=0;i<k;++i)ckmin(mn, dist[i][u]+dist[i][v]);
            if (10 * mn < n) ++ruin;
            tot++;
            md = min(md, mn);
      }
      cout << "Caso #" << cs << " gerado!" << endl;
      cout << "Menor distanca eh " << fixed << setprecision(6) << md / (double)(n/10) << " do minimo permitido" << endl;
      cout << md << ' ' << (n/10) << endl;
      if (10 * md < n) {
            cout << "Caso #" << cs << "ta errado" << endl;
            cout << "Fracao de queries ruins: " << ruin / tot << endl;
            cout << ruin << ' ' << tot << endl;
            exit(0);
      }
}


int32_t main(int argc, char *argv[]){
      // vertexbylabel: quem eh o i dentro do jngen
      // vertexlabel: qual o label do i (i de dentro do jngen)
      for (int i = 1; i <= 99; ++i) {
            string s = to_string(i) + ".txt";
            ofstream fl(s);

            int n;
            if (i <= 14) n = rnd.next(1000, 10000);
            else if (i <= 30) n = rnd.next(10000, 50000);
            else if (i <= 95) n = rnd.next(50000, 100000);
            else n = 100000;

            auto [g, queries] = genRandom3(n, min(4 * n, 200000));

            g.shuffle();

            for (auto& [x, y] : queries) x = g.vertexLabel(x) + 1, y = g.vertexLabel(y) + 1;

            for (int i = 1; i <= n; ++i) {
                  gg[i].clear();
                  for (auto x : g.edges(i-1)) gg[i].pb(x+1);
            }

            checker(n, queries, i);

            fl << g.n() << ' ' << g.m() << ' ' << sz(queries) << '\n';
            fl << g.add1() << endl;
            for (auto [x, y] : queries) fl << x << ' ' << y << endl;
            fl.close();
            cout << "Caso #" << i << " salvo com sucesso!" << endl; 
      }
      cout << "TODOS OS CASOS GERADOS COM SUCESSO :)" << endl;
} 

