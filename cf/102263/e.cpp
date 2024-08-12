#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define fast_io cin.tie(0)->sync_with_stdio(0);
//#define endl '\n'

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int MAX = 2e5 + 10;

int n;
vector<vector<pair<int, int>>> g(MAX);

using Item = pair<ll, int>;

Item max(Item a, Item b) {
  if (a.first >= b.first) return a;
  return b;
}
vector<Item> h(MAX);

Item operator + (Item a, int w) {
  return {a.first + w, a.second};
}

using Diam = tuple<ll, int, int>;

Diam join(Item a, Item b) {
  return {a.first + b.first, a.second, b.second};
}

Diam max(Diam a, Diam b) {
  if (get<0>(a) >= get<0>(b)) return a;
  return b;
}
vector<Diam> diam(MAX);

vector<Item> sobe(MAX, Item{0, 1});
vector<Diam> ans(MAX);
pair<ll, int> par[MAX][20];
int lvl[MAX];

int lca(int u, int v) {
   if (lvl[u] < lvl[v]) swap(u, v);

   for (int i = 19; i >= 0; --i) {
      if (lvl[par[u][i].second] >= lvl[v]) u = par[u][i].second;
   }
   if (u == v) return v;
   for (int i = 19; i >= 0; --i) {
    if (par[u][i].second != par[v][i].second) {
      u = par[u][i].second, v = par[v][i].second;
    }
   }
   return par[u][0].second;
}

ll center(int u, int v, ll tot) {
  if (u <= 0 || v <= 0) return 0;
  int L = lca(u, v);
  //cout << "query " << u << " " << v << " " << L << endl;
  //cout << "! tot " << tot << endl;
  ll ans = 1e18;
  for (int __ = 0; __ < 2; ++__) {
    int cur = u;
    ll cur_dist = 0;
    //cout << cur << "\n";
    for (int i = 19; i >= 0; --i) {
        if (lvl[par[cur][i].second] >= lvl[L] && 2 *(cur_dist+ par[cur][i].first) <= tot) {
            cur_dist += par[cur][i].first;
            cur = par[cur][i].second;
        }
    }
    ans=min(ans, max(cur_dist, tot-cur_dist));
	if (cur != L) ans = min(ans, max(cur_dist+par[cur][0].first,tot-cur_dist-par[cur][0].first));
    swap(u, v);
  }
  //cout << u << ' ' << v << ' ' << L << endl;
  return ans;
}

void dfs(int u, int p) {
  h[u] = {0, u};
  diam[u] = {0, u, u};
  for (auto [v, w] : g[u]) if (v != p) {
    par[v][0] = {w, u};
    lvl[v] = lvl[u] + 1;
    //cout << "#################  " << u << "->" << v << endl;
    //cout << w << ' ' << u << endl;
    for (int i = 1; i < 19; ++i) {
      par[v][i].first = par[par[v][i-1].second][i-1].first + par[v][i-1].first;
      par[v][i].second = par[par[v][i-1].second][i-1].second;
      //cout << par[v][i].first << ' ' << par[v][i].second << endl;
    }
    dfs(v, u);
    diam[u] = max({diam[u], diam[v], join(h[v] + w, h[u])});
    h[u] = max(h[u], h[v] + w);
  }
}

void dfs2(int u, int p) {
  vector<Item> hs;
  vector<pair<int, int>> ch;

  for (auto [v, w] : g[u]) if (v != p) {
    ch.emplace_back(v, w);
    hs.push_back(h[v] + w);
  }

  auto pref = hs;
  auto suff = hs;
  for (int i = 1; i < ch.size(); i++) {
    pref[i] = max(pref[i], pref[i - 1]);
  }
  for (int i = (int)ch.size() - 2; i >= 0; --i) {
    suff[i] = max(suff[i], suff[i + 1]);
  }

  vector<Diam> diam_pref(ch.size());
  vector<Diam> diam_suff(ch.size());
  for (int i = 0; i < ch.size(); i++) {
    auto [v, w] = ch[i];
    diam_pref[i] = max(diam[v], Diam{h[v].first + w, u, h[v].second});
    if (i) {
      diam_pref[i] = max(diam_pref[i], join(h[v] + w, pref[i - 1]));
      diam_pref[i] = max(diam_pref[i], diam_pref[i - 1]);
    }
  }
  for (int i = (int)ch.size() - 1; i >= 0; --i) {
    auto [v, w] = ch[i];
    diam_suff[i] = max(diam[v], Diam{h[v].first + w, u, h[v].second});
    if (i + 1 < ch.size()) {
      diam_suff[i] = max(diam_suff[i], join(h[v] + w, suff[i + 1]));
      diam_suff[i] = max(diam_suff[i], diam_suff[i + 1]);
    }
  }

  for (int i = 0; i < ch.size(); i++) {
    auto [v, w] = ch[i];

    Item out{0, u};
    if (i) out = max(out, pref[i - 1]);
    if (i + 1 < ch.size()) out = max(out, suff[i + 1]);

    Diam diam_out;
    if (i) diam_out = max(diam_out, diam_pref[i - 1]);
    if (i + 1 < ch.size()) diam_out = max(diam_out, diam_suff[i + 1]);
	if (i && i+1 < ch.size()) diam_out = max(diam_out, Diam{pref[i-1].first+suff[i+1].first, pref[i-1].second, suff[i+1].second});
	

    auto [d, v1, v2] = diam_out;
   // cout << "[diam_out] ";
   // cout << u << " -> " << v << " ";
   // cout << d << " " << v1 << " " << v2 << endl;


    sobe[v] = max(sobe[u], out) + w;
    ans[v] = max(ans[u], diam_out);
    ans[v] = max(ans[v], join(out, sobe[u]));
    auto [d1, v3, v4] = ans[v];
   // cout << "[ans[v]] ";
   // cout << v << ": " << d1 << " " << v3 << " " << v4 << endl;
   // 
   // cout << "[sobe[u]] ";
   // auto [dx, vx] = sobe[u];
   // cout << u << ": " << dx << " " << vx << endl;
    dfs2(v, u);
  }
}

int32_t main() {
  fast_io;

  cin >> n;
  vector<tuple<int, int, ll>> edg;
  for (int i = 1; i < n; i++) {
    int a, b, w;
    cin >> a >> b >> w;

    g[a].emplace_back(b, w);
    g[b].emplace_back(a, w);
    edg.push_back({a, b, w});
  }
  lvl[1] = 1;
  for (int i = 0; i <= 19; ++i) par[1][i] = {0, 1};
  dfs(1, 1);
  dfs2(1, 1);
  for (auto [u, v, w] : edg) {
     if (lvl[u] < lvl[v]) swap(u, v);
     auto [d1, x1, x2] = ans[u];
     auto [d2, y1, y2] = diam[u];
	// cout << u << endl;
    // cout << "d1=" << d1 << " x1=" << x1 << " x2=" << x2 << endl;
    // cout << "d2=" << d2 << " y1=" << y1 << " y2=" << y2 << endl;
     //cout << center(x1, x2, d1) << " " << center(y1, y2, d2) << endl;
     ll ans = max({d1, d2, w + center(x1, x2, d1) + center(y1, y2, d2)});
     cout << ans << endl;
  }
}
