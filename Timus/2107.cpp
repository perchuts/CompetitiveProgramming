#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 40;
const int maxX = 12;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

vector<int> achievable = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 38, 39, 40, 42, 44, 45, 46, 48, 50, 51, 52, 54, 55, 56, 57, 58, 60, 62, 63, 65, 66, 68, 69, 70, 72, 75, 76, 77, 78, 80, 84, 85, 87, 88, 90, 91, 92, 93, 95, 96, 99, 100, 102, 104, 105, 108, 110, 112, 114, 115, 116, 117, 119, 120, 124, 126, 130, 132, 133, 135, 136, 138, 140, 143, 144, 145, 150, 152, 153, 154, 156, 161, 165, 168, 170, 171, 174, 175, 176, 180, 182, 184, 187, 189, 190, 195, 198, 200, 204, 207, 208, 209, 210, 216, 220, 221, 225, 228, 230, 231, 234, 238, 240, 247, 252, 253, 255, 260, 264, 266, 270, 272, 273, 276, 280, 285, 286, 300, 304, 306, 308, 312, 315, 322, 330, 336, 340, 342, 345, 350, 357, 360, 364, 374, 380, 385, 390, 396, 399, 408, 414, 418, 420, 429, 440, 442, 455, 456, 460, 462, 468, 476, 483, 494, 495, 504, 510, 520, 525, 528, 532, 546, 552, 560, 561, 570, 572, 585, 595, 612, 616, 624, 627, 630, 644, 660, 663, 665, 680, 684, 690, 693, 714, 715, 720, 728, 741, 748, 760, 765, 770, 780, 792, 798, 805, 819, 836, 840, 855, 858, 880, 884, 910, 924, 935, 936, 952, 966, 990, 1001, 1008, 1020, 1040, 1045, 1064, 1071, 1092, 1105, 1122, 1140, 1144, 1155, 1170, 1190, 1197, 1224, 1232, 1254, 1260, 1287, 1309, 1320, 1326, 1330, 1365, 1380, 1386, 1428, 1430, 1530, 1540, 1560, 1596, 1638, 1680, 1710, 1716, 1785, 1820, 1848, 1870, 1980, 1995, 2002, 2040, 2142, 2145, 2184, 2244, 2280, 2310, 2340, 2380, 2520, 2574, 2640, 2660, 2730, 2772, 2856, 2860, 3003, 3060, 3080, 3276, 3432, 3465, 3570, 3640, 3960, 4004, 4095, 4290, 4620, 4680, 5460, 5544, 6930, 9240};
vector<ii> head[36]; // head.first -> ... -> head.second
vector<ii> g[1 << maxX]; 

int tot[1 << maxX], achievable2[10000], lcm_pre[36][400];

bitset<330> dp[1 << maxX][36];

int32_t main(){_
      int n, K; cin >> n >> K;
      vector<int> f(n+1), cnt(n+1), inv(n + 1);
      for (int i = 1; i <= n; ++i) cin >> f[i], cnt[f[i]]++, inv[f[i]] = i;

      for (int i = 1; i <= n; ++i) {
            if (cnt[i] > 1) {
                  cout << "No" << endl;
                  return 0;
            }
      }
      
      vector<int> vals, used, vis(n + 1), amount(n + 1);
      
      for (int i = 1; i <= n; ++i) {
            if (inv[i] == 0) {
                  vis[i] = 1;
                  int count = 1, cur = i;
                  while (f[cur]) cur = f[cur], count++, vis[cur] = 1;
                  vals.pb(count);
                  head[count].pb({i, cur});
                  amount[count]++;
            }
      }

      for (int i = 1; i <= n; ++i) {
            if (vis[i]) continue;
            int count = 0, cur = i;
            while (vis[cur] == 0) vis[cur] = 1, cur = inv[cur], count++;
            used.pb(count);
      }

      int lcm = 1;
      for (auto x : used) lcm = (x * lcm) / __gcd(x, lcm);

      // precomputa mascaras dos estados
      int t = sz(achievable);
      assert(t < 330);

      for (int i = 0; i < t; ++i) achievable2[achievable[i]] = i;

      vector<ii> real_amount, ranges;

      for (int i = 1; i <= n; ++i) 
            if (amount[i]) real_amount.pb({i, amount[i]});
      
      int x = 0, m = sz(real_amount);

      for (auto [val, qnt] : real_amount) {
            int need = ceil(log2(qnt+1));
            int mask = ((1 << (x + need)) - 1) - ((1 << x) - 1);
            ranges.pb({mask, x}), x += need;
      }

      assert(x <= maxX);

      for (int k = 1; k <= n; ++k) {
            for (int z = 0; z < t; ++z) {
                  lcm_pre[k][z] = k * achievable[z] / __gcd(k, achievable[z]);
            }
      }

      int todos = 0;

      // constroi o grafo
      for (int i = 1; i < (1 << x); ++i) {
            bool ok = 1;
            for (int j = 0; j < m; ++j) {
                  // what if we removed one from here?
                  auto [mask, shift] = ranges[j];
                  auto [valor, qnt] = real_amount[j];
                  int qnt_act = (i & mask), temp = i - qnt_act; qnt_act >>= shift;
                  tot[i] += qnt_act * valor;
                  ok &= (qnt_act <= qnt);
                  if (qnt_act == 0) continue;
                  qnt_act--, qnt_act <<= shift, temp += qnt_act;
                  g[i].pb({temp, valor});
            }
            if (ok == 0) g[i].clear();
            else todos = i;
      }
      
      // DP!
      dp[0][0][0] = 1;
      for (int i = 0; i < (1 << x); ++i) {
            for (int k = 0; k <= n - tot[i]; ++k) {
                  for (auto [j, valor] : g[i]) dp[i][k] |= dp[j][k + valor];
                  if (k) {
                        for (int z = 0; z < t; ++z) {
                              if (!dp[i][0][z]) continue;
                              int lcm_ = lcm_pre[k][z], ind = achievable2[lcm_];
                              dp[i][k][ind] = 1;
                        }
                  }
            }
      }

      int id = -1;
      for (int i = 0; i < t; ++i) {
            if (dp[todos][0][i]) {
                  int z = achievable[i];
                  int lcm_ = z * lcm / __gcd(z, lcm);
                  if (K % lcm_ == 0) {
                        id = i;
                        break;
                  }
            }
      }

      if (id == -1) {
            cout << "No" << endl;
            return 0;
      }

      cout << "Yes" << endl;
      // recover answer - trickiest part
      ii state = {todos, 0};
      lcm = achievable[id];      
      vector<int> selected;
      while (state.first + state.second) {
            // bora colocar alguem na solucao
            bool ok = 0;
            for (auto [j, valor] : g[state.first]) {
                  if (dp[j][state.second + valor][achievable2[lcm]]) {
                        ok = 1; 
                        selected.pb(valor);
                        state = {j, state.second + valor}; break;
                  }
            }
            if (ok) continue;
            // fechei um ciclo
            assert(state.second);
            for (int z = 0; z < t; ++z) {
                  if (dp[state.first][0][z] == 0) continue;
                  int k = achievable[z], lcm_ = state.second * k / __gcd(state.second, k);
                  if (lcm_ == lcm) {
                        ok = 1;
                        state = {state.first, 0}, lcm = k;
                        break;
                  }
                  // quero ver se o lcm dos dois da o lcm
            }
            assert(ok);
            // agora temos que fechar um ciclo com o que acabamos de encontrar
            // assert(!head[selected[0]].empty());
            assert(!head[selected[0]].empty());
            int ponta = head[selected[0]].back().first;
            for (int i = 0; i < sz(selected); ++i) {
                  assert(!head[selected[i]].empty());
                  int x = selected[i], y = head[x].back().second;
                  head[x].pop_back();
                  if (i == sz(selected) - 1) f[y] = ponta;
                  else {
                        assert(!head[selected[i+1]].empty());
                        f[y] = head[selected[i+1]].back().first;
                  }
            }
            selected.clear();
      }
      for (int i = 1; i <= n; ++i) cout << f[i] << " \n"[i==n];
} 
