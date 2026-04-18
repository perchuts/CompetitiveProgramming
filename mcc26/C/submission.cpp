#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);

static const int INF = 1e9;
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
    comps--;
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

// -1 = confirmed wall, 0 = unknown, 1 = known empty.
vector<int8_t> cell_state;
vector<int> grid_to_vertex;
vector<pair<int, int>> vertex_cell;
vector<vector<int>> graph;
vector<vector<int>> up;
vector<int> depth;
vector<int> landmarks;
vector<vector<int>> landmark_dist;
vector<int> landmark_pos;
vector<int> all_vertices;
vector<uint16_t> all_pair_dist;
int all_pair_vertices = 0;
int lg;
vector<int> in_cand_mark;
vector<int> query_pool_mark;
int query_pool_id = 1;
int fixed_root = -1;
const int fixed_prefix_depth = 2;
const int fixed_second_min_size = 32;
struct PrefixNode {
  int q = -2;
  vector<int> answers;
  vector<int> child;
};
vector<PrefixNode> fixed_prefix;

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
  cout << r << " " << c << '\n' << flush;

  int ans;
  if (!(cin >> ans)) exit(0);
  cell_state[id] = (ans == -1 ? -1 : 1);
  return ans;
}

vector<Corridor> build_corridor_order() {
  vector<Corridor> edges;
  edges.reserve(2 * room_side * (room_side - 1));

  for (int r = 2; r <= n - 1; r += 2) {
    for (int c = 3; c <= n - 2; c += 2) {
      edges.push_back({r, c, room_id_from_cell(r, c - 1),
                       room_id_from_cell(r, c + 1)});
    }
  }
  for (int r = 3; r <= n - 2; r += 2) {
    for (int c = 2; c <= n - 1; c += 2) {
      edges.push_back({r, c, room_id_from_cell(r - 1, c),
                       room_id_from_cell(r + 1, c)});
    }
  }

  // Interior edges tend to be marginally more useful on these generated mazes,
  // and this order also leaves many forced-cycle walls skippable near the end.
  sort(edges.begin(), edges.end(), [](const Corridor& x, const Corridor& y) {
    auto border_dist = [](const Corridor& e) {
      return min(min(e.r - 1, e.c - 1), min(n - e.r, n - e.c));
    };
    int bx = border_dist(x);
    int by = border_dist(y);
    if (bx != by) return bx > by;
    int center = (n + 1) / 2;
    int cx = abs(x.r - center) + abs(x.c - center);
    int cy = abs(y.r - center) + abs(y.c - center);
    if (cx != cy) return cx < cy;
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

  for (const Corridor& e : edges) {
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
      int nr = r + dr[k];
      int nc = c + dc[k];
      if (nr < 1 || nr > n || nc < 1 || nc > n) continue;
      int to = grid_to_vertex[cell_id(nr, nc)];
      if (to != -1) graph[v].push_back(to);
    }
  }

  all_vertices.resize(m);
  iota(all_vertices.begin(), all_vertices.end(), 0);
}

void build_lca() {
  int m = (int)vertex_cell.size();
  lg = 1;
  while ((1 << lg) <= m) lg++;

  up.assign(lg, vector<int>(m, 0));
  depth.assign(m, 0);
  vector<int> parent(m, -1);
  vector<int> order;
  order.reserve(m);

  parent[0] = 0;
  order.push_back(0);
  for (int i = 0; i < (int)order.size(); i++) {
    int v = order[i];
    for (int to : graph[v]) {
      if (to == parent[v]) continue;
      parent[to] = v;
      depth[to] = depth[v] + 1;
      order.push_back(to);
    }
  }

  for (int v = 0; v < m; v++) up[0][v] = parent[v] == -1 ? 0 : parent[v];
  for (int j = 1; j < lg; j++) {
    for (int v = 0; v < m; v++) {
      up[j][v] = up[j - 1][up[j - 1][v]];
    }
  }
}

int lca(int a, int b) {
  if (depth[a] < depth[b]) swap(a, b);
  int diff = depth[a] - depth[b];
  for (int j = 0; j < lg; j++) {
    if (diff & (1 << j)) a = up[j][a];
  }
  if (a == b) return a;
  for (int j = lg - 1; j >= 0; j--) {
    if (up[j][a] != up[j][b]) {
      a = up[j][a];
      b = up[j][b];
    }
  }
  return up[0][a];
}

int tree_dist(int a, int b) {
  if (all_pair_vertices > 0) {
    return (int)all_pair_dist[(size_t)a * all_pair_vertices + b];
  }
  int z = lca(a, b);
  return depth[a] + depth[b] - 2 * depth[z];
}

int farthest_from(int src) {
  int best = src;
  int best_dist = -1;
  for (int v : all_vertices) {
    int d = tree_dist(src, v);
    if (d > best_dist) {
      best_dist = d;
      best = v;
    }
  }
  return best;
}

void choose_landmarks() {
  int m = (int)all_vertices.size();
  int a = farthest_from(0);
  int b = farthest_from(a);

  landmarks.clear();
  landmark_dist.clear();
  landmarks.push_back(a);
  landmarks.push_back(b);
  landmark_pos.assign(m, -1);

  landmark_dist.push_back(vector<int>());
  landmark_dist.back().resize(m);
  landmark_dist.push_back(vector<int>());
  landmark_dist.back().resize(m);

  for (int v : all_vertices) {
    landmark_dist[0][v] = tree_dist(a, v);
    landmark_dist[1][v] = tree_dist(b, v);
  }
  landmark_pos[a] = 0;
  landmark_pos[b] = 1;

  vector<int> nearest(m, INF);
  for (int v : all_vertices) {
    nearest[v] = min(landmark_dist[0][v], landmark_dist[1][v]);
  }

  const int max_landmarks = 24;
  while ((int)landmarks.size() < max_landmarks) {
    int best = -1;
    int best_dist = -1;
    for (int v : all_vertices) {
      if (nearest[v] > best_dist) {
        best_dist = nearest[v];
        best = v;
      }
    }
    if (best == -1 || best_dist == 0) break;
    landmarks.push_back(best);
    landmark_pos[best] = (int)landmarks.size() - 1;
    landmark_dist.push_back(vector<int>());
    landmark_dist.back().resize(m);
    for (int v : all_vertices) {
      int d = tree_dist(best, v);
      landmark_dist.back()[v] = d;
      nearest[v] = min(nearest[v], d);
    }
  }
}

void build_all_pairs_dist() {
  int m = (int)all_vertices.size();
  all_pair_vertices = m;
  if (m == 0) return;

  all_pair_dist.assign((size_t)m * m, 0);
  vector<int> dist(m);
  vector<int> stack;
  stack.reserve(m);

  for (int src = 0; src < m; src++) {
    fill(dist.begin(), dist.end(), -1);
    dist[src] = 0;
    stack.clear();
    stack.push_back(src);
    for (int i = 0; i < (int)stack.size(); i++) {
      int v = stack[i];
      int dv = dist[v];
      all_pair_dist[(size_t)src * m + v] = (uint16_t)dv;
      for (int to : graph[v]) {
        if (dist[to] != -1) continue;
        dist[to] = dv + 1;
        stack.push_back(to);
      }
    }
  }
}

int pick_best_query_for_subset(const vector<int>& cand) {
  if (cand.empty()) return -1;
  if ((int)cand.size() == 1) return cand[0];

  static vector<int> cnt;
  static vector<int> touched;
  if ((int)cnt.size() < all_pair_vertices + 1) cnt.assign(all_pair_vertices + 1, 0);
  int m = all_pair_vertices;

  int best = -1;
  long long best_score = LLONG_MAX;
  int best_worst = INT_MAX;

  for (int q = 0; q < m; q++) {
    touched.clear();
    long long squared_sum = 0;
    int worst = 0;
    for (int v : cand) {
      int d = all_pair_dist[(size_t)q * m + v];
      if (cnt[d] == 0) touched.push_back(d);
      int c = ++cnt[d];
      squared_sum += 2LL * c - 1;
      if (c > worst) worst = c;
    }
    for (int d : touched) cnt[d] = 0;
    if (squared_sum < best_score || (squared_sum == best_score && worst < best_worst)) {
      best_score = squared_sum;
      best_worst = worst;
      best = q;
    }
  }
  return best;
}

int build_fixed_prefix_node(const vector<int>& cand, int depth) {
  int node = (int)fixed_prefix.size();
  fixed_prefix.push_back(PrefixNode());

  if (cand.empty()) {
    fixed_prefix[node].q = -2;
    return node;
  }
  if ((int)cand.size() == 1) {
    fixed_prefix[node].q = -1;
    return node;
  }
  if (depth == 0 || (depth == 1 && (int)cand.size() < fixed_second_min_size)) {
    fixed_prefix[node].q = -2;
    return node;
  }

  int q = pick_best_query_for_subset(cand);
  fixed_prefix[node].q = q;
  if (q == -1) {
    fixed_prefix[node].q = -2;
    return node;
  }

  int m = all_pair_vertices;
  int maxd = 0;
  for (int v : cand) {
    int d = all_pair_dist[(size_t)q * m + v];
    if (d > maxd) maxd = d;
  }
  vector<vector<int>> buckets(maxd + 1);
  for (int v : cand) {
    int d = all_pair_dist[(size_t)q * m + v];
    buckets[d].push_back(v);
  }

  for (int d = 0; d <= maxd; d++) {
    if (buckets[d].empty()) continue;
    int child = build_fixed_prefix_node(buckets[d], depth - 1);
    fixed_prefix[node].answers.push_back(d);
    fixed_prefix[node].child.push_back(child);
  }
  return node;
}

void build_fixed_prefix_plan() {
  int m = (int)all_vertices.size();
  if (m == 0) return;
  vector<int> all_set(m);
  iota(all_set.begin(), all_set.end(), 0);
  fixed_prefix.clear();
  fixed_root = build_fixed_prefix_node(all_set, fixed_prefix_depth);
}

int query_vertex(int v) {
  auto [r, c] = vertex_cell[v];
  return query_cell(r, c);
}

pair<long long, int> bucket_score(int q, const vector<int>& cand, int lm_idx) {
  static vector<int> cnt;
  static vector<int> touched;
  if ((int)cnt.size() < all_pair_vertices + 1) cnt.assign(all_pair_vertices + 1, 0);
  touched.clear();

  long long squared_sum = 0;
  int worst = 0;
  for (int v : cand) {
    int d = (lm_idx == -1 ? tree_dist(q, v) : landmark_dist[lm_idx][v]);
    if (cnt[d] == 0) touched.push_back(d);
    squared_sum += 2LL * cnt[d] + 1;
    cnt[d]++;
    worst = max(worst, cnt[d]);
  }
  for (int d : touched) cnt[d] = 0;
  return {squared_sum, worst};
}

int choose_query_vertex(const vector<int>& cand, const vector<char>& asked, int in_token) {
  const int full_eval_threshold = 512;
  const int max_landmark_eval = 24;
  const int sample_per_large = 12;
  static vector<int> pool;
  if ((int)query_pool_mark.size() < (int)all_vertices.size()) query_pool_mark.assign(all_vertices.size(), 0);
  pool.clear();
  int my_pool_id = query_pool_id++;
  int m = (int)all_vertices.size();

  auto add_candidate = [&](int v) {
    if (v < 0 || v >= m) return;
    if (asked[v]) return;
    if (query_pool_mark[v] == my_pool_id) return;
    query_pool_mark[v] = my_pool_id;
    pool.push_back(v);
  };

  if (cand.size() <= full_eval_threshold) {
    for (int q : cand) add_candidate(q);
  } else {
    for (int i = 0; i < (int)landmarks.size() && i < max_landmark_eval; i++) {
      add_candidate(landmarks[i]);
    }
    if ((int)cand.size() <= 1536) {
      for (int q : cand) {
        if ((int)pool.size() >= 256) break;
        add_candidate(q);
      }
    } else {
      int step = max(1, (int)cand.size() / sample_per_large);
      for (int i = 0; i < (int)cand.size() && (int)pool.size() < sample_per_large; i += step) {
        add_candidate(cand[i]);
      }
      if (cand.size() >= 2 && (int)pool.size() < sample_per_large + 4) {
        int pivot = cand[cand.size() / 2];
        int a = cand[0], b = cand[0];
        int best = -1;
        for (int v : cand) {
          int d = tree_dist(pivot, v);
          if (d > best) {
            best = d;
            b = v;
          }
        }
        a = b;
        best = -1;
        for (int v : cand) {
          int d = tree_dist(a, v);
          if (d > best) {
            best = d;
            b = v;
          }
        }
        add_candidate(a);
        add_candidate(b);
      }
    }
  }

  int best = -1;
  long long best_score = LLONG_MAX;
  int best_worst = INF;
  bool best_inside = false;

  auto consider = [&](int q) {
    if (asked[q]) return;
    bool inside = in_cand_mark[q] == in_token;
    int lm_idx = q < (int)landmark_pos.size() ? landmark_pos[q] : -1;
    auto [score, worst] = bucket_score(q, cand, lm_idx);
    if (score < best_score ||
        (score == best_score && worst < best_worst) ||
        (score == best_score && worst == best_worst && inside && !best_inside)) {
      best_score = score;
      best_worst = worst;
      best_inside = inside;
      best = q;
    }
  };

  for (int q : pool) {
    consider(q);
  }

  if (best != -1) return best;
  for (int v : all_vertices) {
    if (!asked[v]) return v;
  }
  return cand[0];
}

bool find_current_target() {
  vector<int> cand = all_vertices;
  vector<int> nxt;
  vector<char> asked(all_vertices.size(), 0);
  nxt.reserve(cand.size());
  if ((int)in_cand_mark.size() != (int)all_vertices.size()) {
    in_cand_mark.assign(all_vertices.size(), 0);
  }
  int in_token = 1;
  int prefix_node = fixed_root;

  while (used_queries < t) {
    if (cand.empty()) return false;
    if (cand.size() == 1) {
      int ans = query_vertex(cand[0]);
      return ans == 0;
    }

    for (int v : cand) in_cand_mark[v] = in_token;

    int q = -1;
    if (prefix_node >= 0 && prefix_node < (int)fixed_prefix.size()) {
      int forced = fixed_prefix[prefix_node].q;
      if (forced >= 0) q = forced;
    }
    if (q == -1) {
      q = choose_query_vertex(cand, asked, in_token);
    }
    asked[q] = 1;

    int ans = query_vertex(q);
    if (ans == 0) return true;

    int q_landmark_idx = (q < (int)landmark_pos.size() ? landmark_pos[q] : -1);
    nxt.clear();
    if (q_landmark_idx != -1) {
      const vector<int>& drow = landmark_dist[q_landmark_idx];
      for (int v : cand) {
        if (drow[v] == ans) nxt.push_back(v);
      }
    } else {
    for (int v : cand) {
      if (tree_dist(q, v) == ans) nxt.push_back(v);
    }
    }
    cand.swap(nxt);

    if (prefix_node >= 0 && prefix_node < (int)fixed_prefix.size()) {
      const PrefixNode& node = fixed_prefix[prefix_node];
      if (node.q < 0) {
        prefix_node = -1;
      } else {
        auto it = lower_bound(node.answers.begin(), node.answers.end(), ans);
        if (it == node.answers.end() || *it != ans) {
          prefix_node = -1;
        } else {
          prefix_node = node.child[it - node.answers.begin()];
        }
      }
    }

    if (++in_token == INT_MAX) {
      fill(in_cand_mark.begin(), in_cand_mark.end(), 0);
      in_token = 1;
    }
  }

  return false;
}

int main() {_
  cin >> n >> t;

  learn_maze();
  build_tree();
  build_lca();
  choose_landmarks();
  build_all_pairs_dist();
  build_fixed_prefix_plan();

  while (used_queries < t) {
    if (!find_current_target()) break;
  }

  return 0;
}
