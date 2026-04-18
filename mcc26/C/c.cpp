#include <bits/stdc++.h>

using namespace std;

static const int dr[4] = {1, -1, 0, 0};
static const int dc[4] = {0, 0, 1, -1};

struct DSU {
  vector<int> p, sz;
  int comps;

  explicit DSU(int n = 0) { init(n); }

  void init(int n) {
    p.resize(n);
    sz.assign(n, 1);
    iota(p.begin(), p.end(), 0);
    comps = n;
  }

  int find(int x) {
    while (p[x] != x) {
      p[x] = p[p[x]];
      x = p[x];
    }
    return x;
  }

  bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    --comps;
    return true;
  }
};

struct Corridor {
  int r, c;
  int a, b;
};

int n, t;
int used_queries = 0;
int room_side;

vector<int8_t> cell_state;
vector<int> grid_to_vertex;
vector<pair<int, int>> vertex_cell;
vector<vector<int>> graph;
vector<int> all_vertices;
vector<uint16_t> all_pair_dist;
int all_pair_n = 0;

vector<int> landmarks;
vector<int> landmark_pos;

vector<int> in_cand_mark;
vector<int> query_pool_mark;
int query_pool_id = 1;

int cell_id(int r, int c) {
  return (r - 1) * n + (c - 1);
}

int room_id_from_cell(int r, int c) {
  return ((r - 2) / 2) * room_side + ((c - 2) / 2);
}

int query_cell(int r, int c) {
  int id = cell_id(r, c);
  if (cell_state[id] == -1) return -1;
  if (used_queries >= t) exit(0);

  used_queries++;
  cout << r << ' ' << c << '\n' << flush;

  int ans;
  if (!(cin >> ans)) exit(0);

  cell_state[id] = (ans == -1 ? -1 : 1);
  return ans;
}

int query_vertex(int v) {
  auto [r, c] = vertex_cell[v];
  return query_cell(r, c);
}

vector<Corridor> build_corridor_order() {
  vector<Corridor> edges;
  edges.reserve(2 * room_side * (room_side - 1));

  for (int r = 2; r <= n - 1; r += 2) {
    for (int c = 3; c <= n - 2; c += 2) {
      edges.push_back({r, c, room_id_from_cell(r, c - 1), room_id_from_cell(r, c + 1)});
    }
  }

  for (int r = 3; r <= n - 2; r += 2) {
    for (int c = 2; c <= n - 1; c += 2) {
      edges.push_back({r, c, room_id_from_cell(r - 1, c), room_id_from_cell(r + 1, c)});
    }
  }

  // A practical ordering that finds spanning edges earlier on random mazes.
  sort(edges.begin(), edges.end(), [&](const Corridor &x, const Corridor &y) {
    auto score = [&](const Corridor &e) {
      int border = min({e.r - 1, e.c - 1, n - e.r, n - e.c});
      int cx = abs(e.r - (n + 1) / 2);
      int cy = abs(e.c - (n + 1) / 2);
      return pair<int, int>{-border, cx + cy};
    };
    auto sx = score(x);
    auto sy = score(y);
    if (sx.first != sy.first) return sx.first > sy.first;
    if (sx.second != sy.second) return sx.second < sy.second;
    if (x.r != y.r) return x.r < y.r;
    return x.c < y.c;
  });

  return edges;
}

void learn_maze() {
  cell_state.assign(n * n, 0);
  room_side = n / 2;

  for (int r = 2; r <= n - 1; r += 2) {
    for (int c = 2; c <= n - 1; c += 2) {
      cell_state[cell_id(r, c)] = 1;
    }
  }

  DSU dsu(room_side * room_side);
  vector<Corridor> edges = build_corridor_order();

  for (const Corridor &e : edges) {
    if (used_queries >= t) break;
    if (dsu.find(e.a) == dsu.find(e.b)) continue;

    int ans = query_cell(e.r, e.c);
    if (ans != -1) {
      dsu.unite(e.a, e.b);
      if (dsu.comps == 1) break;
    }
  }
}

void build_tree() {
  grid_to_vertex.assign(n * n, -1);
  vertex_cell.clear();

  for (int r = 1; r <= n; r++) {
    for (int c = 1; c <= n; c++) {
      if (cell_state[cell_id(r, c)] != 1) continue;
      int v = (int)vertex_cell.size();
      grid_to_vertex[cell_id(r, c)] = v;
      vertex_cell.push_back({r, c});
    }
  }

  int m = (int)vertex_cell.size();
  graph.assign(m, {});

  for (int v = 0; v < m; v++) {
    auto [r, c] = vertex_cell[v];
    for (int k = 0; k < 4; k++) {
      int nr = r + dr[k], nc = c + dc[k];
      if (nr < 1 || nr > n || nc < 1 || nc > n) continue;
      int to = grid_to_vertex[cell_id(nr, nc)];
      if (to != -1 && to > v) {
        graph[v].push_back(to);
        graph[to].push_back(v);
      }
    }
  }

  all_vertices.resize(m);
  iota(all_vertices.begin(), all_vertices.end(), 0);
}

inline int dist_between(int a, int b) {
  return all_pair_dist[(size_t)a * all_pair_n + b];
}

void build_all_pairs_dist() {
  int m = (int)all_vertices.size();
  all_pair_n = m;
  if (m == 0) return;

  all_pair_dist.assign((size_t)m * m, 0);

  vector<int> dist(m);
  vector<int> q;
  q.reserve(m);

  for (int src = 0; src < m; src++) {
    fill(dist.begin(), dist.end(), -1);
    dist[src] = 0;
    q.clear();
    q.push_back(src);

    for (int i = 0; i < (int)q.size(); i++) {
      int v = q[i];
      int dv = dist[v];
      all_pair_dist[(size_t)src * m + v] = (uint16_t)dv;

      for (int to : graph[v]) {
        if (dist[to] != -1) continue;
        dist[to] = dv + 1;
        q.push_back(to);
      }
    }
  }
}

int farthest_from(int src) {
  int best = src;
  int best_d = -1;
  int m = all_pair_n;
  for (int v = 0; v < m; v++) {
    int d = dist_between(src, v);
    if (d > best_d) {
      best_d = d;
      best = v;
    }
  }
  return best;
}

void choose_landmarks() {
  int m = all_pair_n;
  if (m == 0) return;

  landmarks.clear();
  landmark_pos.assign(m, -1);

  int a = farthest_from(0);
  int b = farthest_from(a);

  if (landmark_pos[a] == -1) {
    landmark_pos[a] = (int)landmarks.size();
    landmarks.push_back(a);
  }
  if (b != a && landmark_pos[b] == -1) {
    landmark_pos[b] = (int)landmarks.size();
    landmarks.push_back(b);
  }

  vector<int> nearest(m, INT_MAX);
  for (int v = 0; v < m; v++) {
    int d = dist_between(a, v);
    int d2 = dist_between(b, v);
    nearest[v] = min(d, d2);
  }

  const int max_landmarks = 20;
  while ((int)landmarks.size() < max_landmarks) {
    int best = -1;
    int best_d = -1;
    for (int v = 0; v < m; v++) {
      if (nearest[v] > best_d) {
        best_d = nearest[v];
        best = v;
      }
    }
    if (best == -1 || best_d == 0) break;

    if (landmark_pos[best] == -1) {
      landmark_pos[best] = (int)landmarks.size();
      landmarks.push_back(best);
    }

    for (int v = 0; v < m; v++) {
      nearest[v] = min(nearest[v], dist_between(best, v));
    }
  }
}

pair<long long, int> bucket_score(int q, const vector<int> &cand) {
  static vector<int> cnt;
  static vector<int> touched;

  if ((int)cnt.size() < all_pair_n + 1) cnt.assign(all_pair_n + 1, 0);
  touched.clear();

  long long score = 0;
  int worst = 0;
  for (int v : cand) {
    int d = dist_between(q, v);
    if (cnt[d] == 0) touched.push_back(d);
    int c = ++cnt[d];
    score += 1LL * c * c;
    if (c > worst) worst = c;
  }

  for (int d : touched) cnt[d] = 0;
  return {score, worst};
}

int choose_query_vertex(const vector<int> &cand, const vector<char> &asked, int in_token) {
  const int full_eval_threshold = 640;
  const int landmark_pool = 20;
  const int sample_pool = 16;

  static vector<int> pool;
  pool.clear();

  if ((int)query_pool_mark.size() < all_pair_n) query_pool_mark.assign(all_pair_n, 0);
  int my_pool_id = query_pool_id++;

  auto add_to_pool = [&](int v) {
    if (v < 0 || v >= all_pair_n) return;
    if (asked[v]) return;
    if (query_pool_mark[v] == my_pool_id) return;
    query_pool_mark[v] = my_pool_id;
    pool.push_back(v);
  };

  if ((int)cand.size() <= full_eval_threshold) {
    for (int v : cand) add_to_pool(v);
  } else {
    for (int i = 0; i < (int)landmarks.size() && i < landmark_pool; i++) {
      add_to_pool(landmarks[i]);
    }

    int k = sample_pool;
    int step = max(1, (int)cand.size() / k);
    for (int i = 0; i < (int)cand.size() && (int)pool.size() < k + landmark_pool; i += step) {
      add_to_pool(cand[i]);
    }

    // Diameter-like spread points: inexpensive and usually stable.
    if (!cand.empty()) {
      int a = cand[0];
      int b = cand[0];
      int best = -1;
      for (int v : cand) {
        int d = dist_between(a, v);
        if (d > best) {
          best = d;
          b = v;
        }
      }
      int c = b;
      best = -1;
      for (int v : cand) {
        int d = dist_between(c, v);
        if (d > best) {
          best = d;
          b = v;
        }
      }
      add_to_pool(c);
      add_to_pool(b);
    }
  }

  int best = -1;
  long long best_score = LLONG_MAX;
  int best_worst = INT_MAX;
  bool best_inside = false;

  for (int q : pool) {
    bool inside = in_cand_mark[q] == in_token;
    auto sc = bucket_score(q, cand);
    if (sc.first < best_score || (sc.first == best_score && sc.second < best_worst) ||
        (sc.first == best_score && sc.second == best_worst && inside && !best_inside)) {
      best = q;
      best_score = sc.first;
      best_worst = sc.second;
      best_inside = inside;
    }
  }

  if (best != -1) return best;

  for (int v : cand) {
    if (!asked[v]) return v;
  }

  return cand.empty() ? -1 : cand[0];
}

bool find_current_target() {
  vector<int> cand = all_vertices;
  vector<int> nxt;
  nxt.reserve(cand.size());

  if ((int)in_cand_mark.size() != (int)all_vertices.size()) {
    in_cand_mark.assign(all_vertices.size(), 0);
  }

  vector<char> asked(all_vertices.size(), 0);
  int token = 1;

  while (used_queries < t) {
    if (cand.empty()) return false;

    if (cand.size() == 1) {
      int ans = query_vertex(cand[0]);
      return ans == 0;
    }

    for (int v : cand) in_cand_mark[v] = token;

    int q = choose_query_vertex(cand, asked, token);
    if (q < 0 || q >= (int)all_vertices.size()) return false;
    asked[q] = 1;

    int ans = query_vertex(q);
    if (ans == 0) return true;

    nxt.clear();
    for (int v : cand) {
      if (dist_between(q, v) == ans) nxt.push_back(v);
    }

    if (nxt.empty()) return false;
    cand.swap(nxt);

    if (++token == INT_MAX) {
      fill(in_cand_mark.begin(), in_cand_mark.end(), 0);
      token = 1;
    }
  }

  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> t;
  if (!cin) return 0;

  learn_maze();
  build_tree();
  if (all_vertices.empty()) return 0;

  build_all_pairs_dist();
  choose_landmarks();

  while (used_queries < t) {
    if (!find_current_target()) break;
  }
  return 0;
}
