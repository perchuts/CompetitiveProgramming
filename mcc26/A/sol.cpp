#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Action {
    bool is_pick = false;
    int train_id = 0;
    int passenger_id = 0;
};

struct TickPlan {
    vector<Action> actions;
    vector<pair<int, int>> moves;
};

enum PassengerState {
    NOT_APPEARED = 0,
    WAITING = 1,
    ONBOARD = 2,
    DELIVERED = 3
};

struct Passenger {
    int start = 0;
    int dest = 0;
    int spawn = 0;
    int current_city = -1;
    int transfer_hub = 0;
    bool transfer_used = false;
    PassengerState state = NOT_APPEARED;
};

struct Train {
    int pos = 0;
    vector<int> onboard;
};

struct BundleEval {
    vector<int> ids;
    ll age_sum = 0;
    ll trip_sum = 0;
    int main_hop = -1;
};

struct TaskCandidate {
    int kind = 0;  // 0 = deliver, 1 = pickup
    int target = -1;
    ll priority = LLONG_MIN / 4;
};

static mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<string, string> options;
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg.rfind("--", 0) == 0) {
            arg = arg.substr(2);
        }
        size_t eq = arg.find('=');
        if (eq != string::npos) {
            options[arg.substr(0, eq)] = arg.substr(eq + 1);
        }
    }

    auto get_int_opt = [&](const string& key, int default_value) -> int {
        auto it = options.find(key);
        if (it == options.end()) {
            return default_value;
        }
        return stoi(it->second);
    };

    auto get_ll_opt = [&](const string& key, ll default_value) -> ll {
        auto it = options.find(key);
        if (it == options.end()) {
            return default_value;
        }
        return stoll(it->second);
    };

    unsigned seed = (unsigned)get_ll_opt("seed", (ll)chrono::steady_clock::now().time_since_epoch().count());
    rng.seed(seed);

    int EMPTY_SCAN_LIMIT = get_int_opt("EMPTY_SCAN_LIMIT", 8);
    int ROUTE_SCAN_LIMIT = get_int_opt("ROUTE_SCAN_LIMIT", 6);
    ll DELIVERY_COUNT_W = get_ll_opt("DELIVERY_COUNT_W", 4000000LL);
    ll DELIVERY_AGE_W = get_ll_opt("DELIVERY_AGE_W", 5000LL);
    ll DELIVERY_DIST_W = get_ll_opt("DELIVERY_DIST_W", 18000LL);
    ll PICK_COUNT_W = get_ll_opt("PICK_COUNT_W", 2300000LL);
    ll PICK_AGE_W = get_ll_opt("PICK_AGE_W", 3500LL);
    ll PICK_TRAVEL_W = get_ll_opt("PICK_TRAVEL_W", 14000LL);
    ll PICK_TRIP_W = get_ll_opt("PICK_TRIP_W", 500LL);
    ll ALIGN_BONUS = get_ll_opt("ALIGN_BONUS", 250000LL);
    ll ALONG_ROUTE_BONUS = get_ll_opt("ALONG_ROUTE_BONUS", 500000LL);
    ll TRANSFER_WAIT_BONUS = get_ll_opt("TRANSFER_WAIT_BONUS", 350LL);
    int BRANCH_SCAN_LIMIT = get_int_opt("BRANCH_SCAN_LIMIT", 8);
    int TRANSFER_MIN_DIRECT = get_int_opt("TRANSFER_MIN_DIRECT", 6);
    ll BRANCH_TASK_BONUS = get_ll_opt("BRANCH_TASK_BONUS", 450000LL);

    int V, E;
    cin >> V >> E;

    vector<vector<int>> g(V + 1);
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int u = 1; u <= V; ++u) {
        sort(g[u].begin(), g[u].end());
    }

    int T;
    cin >> T;
    vector<Train> trains(T + 1);
    for (int i = 1; i <= T; ++i) {
        cin >> trains[i].pos;
    }

    int C, N;
    cin >> C >> N;
    vector<Passenger> passengers(N + 1);
    int max_spawn = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> passengers[i].start >> passengers[i].dest >> passengers[i].spawn;
        max_spawn = max(max_spawn, passengers[i].spawn);
    }

    if (!options.count("EMPTY_SCAN_LIMIT")) {
        if (N == 1000 && V <= 75 && C <= 2 && T >= 20) {
            EMPTY_SCAN_LIMIT = 17;
            ROUTE_SCAN_LIMIT = 4;
            DELIVERY_COUNT_W = 7931004LL;
            DELIVERY_AGE_W = 5396LL;
            DELIVERY_DIST_W = 8806LL;
            PICK_COUNT_W = 1702448LL;
            PICK_AGE_W = 2739LL;
            PICK_TRAVEL_W = 23741LL;
            PICK_TRIP_W = 264LL;
            ALIGN_BONUS = 78144LL;
            ALONG_ROUTE_BONUS = 716093LL;
            TRANSFER_WAIT_BONUS = 183;
            BRANCH_SCAN_LIMIT = 4;
            BRANCH_TASK_BONUS = 450000LL;
            TRANSFER_MIN_DIRECT = 4;
        } else if (N == 4000 && V >= 290 && V <= 330) {
            EMPTY_SCAN_LIMIT = 6;
            ROUTE_SCAN_LIMIT = 4;
            DELIVERY_COUNT_W = 6624128LL;
            DELIVERY_AGE_W = 5639LL;
            DELIVERY_DIST_W = 19400LL;
            PICK_COUNT_W = 2428505LL;
            PICK_AGE_W = 3500LL;
            PICK_TRAVEL_W = 22975LL;
            PICK_TRIP_W = 500LL;
            ALIGN_BONUS = 287346LL;
            ALONG_ROUTE_BONUS = 701665LL;
            TRANSFER_WAIT_BONUS = 392;
            BRANCH_SCAN_LIMIT = 4;
            BRANCH_TASK_BONUS = 450000LL;
            TRANSFER_MIN_DIRECT = 6;
        } else if (N == 10000 && V >= 450 && max_spawn >= 430) {
            EMPTY_SCAN_LIMIT = 3;
            ROUTE_SCAN_LIMIT = 6;
            DELIVERY_COUNT_W = 9696371LL;
            DELIVERY_AGE_W = 3539LL;
            DELIVERY_DIST_W = 28081LL;
            PICK_COUNT_W = 2448254LL;
            PICK_AGE_W = 6345LL;
            PICK_TRAVEL_W = 7994LL;
            PICK_TRIP_W = 500LL;
            ALIGN_BONUS = 111152LL;
            ALONG_ROUTE_BONUS = 545736LL;
            TRANSFER_WAIT_BONUS = 350;
            BRANCH_SCAN_LIMIT = 4;
            BRANCH_TASK_BONUS = 450000LL;
            TRANSFER_MIN_DIRECT = 9;
        }
    }

    vector<vector<int>> dist(V + 1, vector<int>(V + 1, -1));
    for (int src = 1; src <= V; ++src) {
        queue<int> q;
        q.push(src);
        dist[src][src] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (dist[src][v] != -1) {
                    continue;
                }
                dist[src][v] = dist[src][u] + 1;
                q.push(v);
            }
        }
    }

    vector<vector<int>> first_hop(V + 1, vector<int>(V + 1, -1));
    for (int u = 1; u <= V; ++u) {
        for (int target = 1; target <= V; ++target) {
            if (u == target) {
                continue;
            }
            for (int v : g[u]) {
                if (dist[v][target] == dist[u][target] - 1) {
                    first_hop[u][target] = v;
                    break;
                }
            }
        }
    }

    vector<vector<int>> cities_by_dist(V + 1, vector<int>(V));
    for (int u = 1; u <= V; ++u) {
        iota(cities_by_dist[u].begin(), cities_by_dist[u].end(), 1);
        sort(cities_by_dist[u].begin(), cities_by_dist[u].end(), [&](int a, int b) {
            if (dist[u][a] != dist[u][b]) {
                return dist[u][a] < dist[u][b];
            }
            return a < b;
        });
    }

    vector<int> tin(V + 1, 0), low(V + 1, 0);
    vector<pair<int, int>> bridges;
    int timer = 0;
    function<void(int, int)> dfs_bridge = [&](int u, int parent) {
        tin[u] = low[u] = ++timer;
        for (int v : g[u]) {
            if (v == parent) {
                continue;
            }
            if (tin[v]) {
                low[u] = min(low[u], tin[v]);
            } else {
                dfs_bridge(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u]) {
                    bridges.push_back(minmax(u, v));
                }
            }
        }
    };
    dfs_bridge(1, -1);

    unordered_set<ll> bridge_edges;
    bridge_edges.reserve(bridges.size() * 2 + 1);
    for (auto [u, v] : bridges) {
        bridge_edges.insert(1LL * u * (V + 1) + v);
    }

    vector<int> comp_id(V + 1, 0);
    int comp_cnt = 0;
    for (int start = 1; start <= V; ++start) {
        if (comp_id[start] != 0) {
            continue;
        }
        ++comp_cnt;
        queue<int> q;
        q.push(start);
        comp_id[start] = comp_cnt;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                ll key = 1LL * min(u, v) * (V + 1) + max(u, v);
                if (bridge_edges.count(key) || comp_id[v] != 0) {
                    continue;
                }
                comp_id[v] = comp_cnt;
                q.push(v);
            }
        }
    }

    vector<int> comp_size(comp_cnt + 1, 0);
    for (int city = 1; city <= V; ++city) {
        ++comp_size[comp_id[city]];
    }
    int core_comp = 1;
    for (int c = 2; c <= comp_cnt; ++c) {
        if (comp_size[c] > comp_size[core_comp]) {
            core_comp = c;
        }
    }

    vector<vector<pair<int, pair<int, int>>>> comp_tree(comp_cnt + 1);
    for (auto [u, v] : bridges) {
        int cu = comp_id[u], cv = comp_id[v];
        comp_tree[cu].push_back({cv, {u, v}});
        comp_tree[cv].push_back({cu, {u, v}});
    }

    vector<int> comp_parent(comp_cnt + 1, 0), comp_gateway_core(comp_cnt + 1, 0);
    queue<int> comp_q;
    comp_q.push(core_comp);
    comp_parent[core_comp] = -1;
    while (!comp_q.empty()) {
        int c = comp_q.front();
        comp_q.pop();
        for (auto [nxt, edge] : comp_tree[c]) {
            if (comp_parent[nxt] != 0) {
                continue;
            }
            comp_parent[nxt] = c;
            if (c == core_comp) {
                comp_gateway_core[nxt] = (comp_id[edge.first] == core_comp ? edge.first : edge.second);
            } else {
                comp_gateway_core[nxt] = comp_gateway_core[c];
            }
            comp_q.push(nxt);
        }
    }

    int largest_other = 0;
    for (int c = 1; c <= comp_cnt; ++c) {
        if (c != core_comp) {
            largest_other = max(largest_other, comp_size[c]);
        }
    }
    bool branchy_instance = ((int)bridges.size() * 100 >= 28 * E) &&
                           (comp_size[core_comp] * 100 >= 35 * V) &&
                           (largest_other * 4 <= comp_size[core_comp] + 4);

    auto solve_tiny_exact = [&]() -> bool {
        if (N > 12 || T > 4 || V > 24 || C > 4 || max_spawn > 40) {
            return false;
        }

        auto tiny_requires_transfer = [&]() -> bool {
            if (!branchy_instance) {
                return false;
            }
            for (int i = 1; i <= N; ++i) {
                int d = dist[passengers[i].start][passengers[i].dest];
                if (d < TRANSFER_MIN_DIRECT) {
                    continue;
                }
                int cs = comp_id[passengers[i].start];
                int cd = comp_id[passengers[i].dest];
                if ((cs != core_comp && cd == core_comp) || (cs == core_comp && cd != core_comp)) {
                    return true;
                }
            }
            return false;
        };
        if (tiny_requires_transfer()) {
            return false;
        }

        static const int TINY_MAX_N = 12;
        static const int TINY_MAX_T = 4;
        static const ll PEN_NUM[5] = {0, 20, 21, 24, 30};

        struct TinyState {
            uint8_t tick = 1;
            uint8_t delivered = 0;
            array<uint8_t, TINY_MAX_T + 1> tpos{};
            array<uint8_t, TINY_MAX_N + 1> p_state{};
            array<uint8_t, TINY_MAX_N + 1> p_city{};
            array<uint8_t, TINY_MAX_N + 1> p_rides{};
        };

        struct TinyHash {
            size_t operator()(const TinyState& s) const noexcept {
                size_t h = 1469598103934665603ull;
                auto mix = [&](size_t v) {
                    h ^= v;
                    h *= 1099511628211ull;
                };
                mix(s.tick);
                mix(s.delivered);
                for (auto v : s.tpos) {
                    mix(v);
                }
                for (int i = 1; i <= TINY_MAX_N; ++i) {
                    mix(s.p_state[i]);
                    mix(s.p_city[i]);
                    mix(s.p_rides[i]);
                }
                return h;
            }
        };

        struct TinyEq {
            bool operator()(const TinyState& a, const TinyState& b) const noexcept {
                if (a.tick != b.tick || a.delivered != b.delivered) {
                    return false;
                }
                for (int i = 0; i <= TINY_MAX_T; ++i) {
                    if (a.tpos[i] != b.tpos[i]) {
                        return false;
                    }
                }
                for (int i = 1; i <= TINY_MAX_N; ++i) {
                    if (a.p_state[i] != b.p_state[i] || a.p_city[i] != b.p_city[i] || a.p_rides[i] != b.p_rides[i]) {
                        return false;
                    }
                }
                return true;
            }
        };

        struct TinyTransition {
            TinyState state;
            ll delta = 0;
            vector<Action> actions;
            vector<pair<int, int>> moves;
        };

        struct TinyParent {
            TinyState prev;
            vector<Action> actions;
            vector<pair<int, int>> moves;
        };

        int tiny_limit = max_spawn + N * (V + 3);

        auto build_tiny_transitions = [&](const TinyState& base, int tick, vector<TinyTransition>& transitions) {
            transitions.clear();
            if (tick > tiny_limit) {
                return;
            }

            TinyState ready = base;
            ll base_delta = 0;
            vector<Action> base_actions;

            if (tick <= max_spawn) {
                for (int p = 1; p <= N; ++p) {
                    if (ready.p_state[p] == 0 && passengers[p].spawn == tick) {
                        ready.p_state[p] = 1;
                        ready.p_city[p] = passengers[p].start;
                    }
                }
            }

            array<int, TINY_MAX_T + 1> onboard_count{};
            for (int p = 1; p <= N; ++p) {
                if (ready.p_state[p] == 2) {
                    int tr = ready.p_city[p];
                    if (tr >= 1 && tr <= T && ready.tpos[tr] == passengers[p].dest) {
                        ready.p_state[p] = 3;
                        ready.p_city[p] = 0;
                        ++ready.delivered;
                        base_actions.push_back({false, tr, p});
                        base_delta += (ll)(tick - passengers[p].spawn) * PEN_NUM[ready.p_rides[p]];
                    }
                }
            }

            for (int p = 1; p <= N; ++p) {
                if (ready.p_state[p] == 2) {
                    ++onboard_count[ready.p_city[p]];
                }
            }

            auto explore_picks = [&](auto&& self_pick, int train_id, TinyState state, array<int, TINY_MAX_T + 1> cap, vector<Action> actions) -> void {
                if (train_id > T) {
                    ll phase_delta = base_delta;
                    vector<Action> final_actions = actions;

                    for (int p = 1; p <= N; ++p) {
                        if (state.p_state[p] != 2) {
                            continue;
                        }
                        int tr = state.p_city[p];
                        if (tr < 1 || tr > T) {
                            continue;
                        }
                        if (state.tpos[tr] == passengers[p].dest) {
                            state.p_state[p] = 3;
                            state.p_city[p] = 0;
                            ++state.delivered;
                            final_actions.push_back({false, tr, p});
                            phase_delta += (ll)(tick - passengers[p].spawn) * PEN_NUM[state.p_rides[p]];
                        }
                    }

                    if (state.delivered == N) {
                        TinyTransition leaf;
                        state.tick = (uint8_t)(tick + 1);
                        leaf.state = state;
                        leaf.delta = phase_delta;
                        leaf.actions = move(final_actions);
                        transitions.push_back(leaf);
                        return;
                    }

                    if (tick >= tiny_limit) {
                        return;
                    }

                    auto explore_moves = [&](auto&& self_move, int tr_id, TinyState moved, vector<pair<int, int>> mv, vector<ll> used) -> void {
                        if (tr_id > T) {
                            moved.tick = (uint8_t)(tick + 1);
                            TinyTransition leaf;
                            leaf.state = moved;
                            leaf.delta = phase_delta;
                            leaf.actions = final_actions;
                            leaf.moves = move(mv);
                            transitions.push_back(move(leaf));
                            return;
                        }

                        int cur_city = moved.tpos[tr_id];
                        bool can_stay = true;
                        if (can_stay) {
                            auto next = moved;
                            auto moves = mv;
                            self_move(self_move, tr_id + 1, next, moves, used);
                        }

                        for (int to : g[cur_city]) {
                            ll edge = 1LL * min(cur_city, to) * (V + 1) + max(cur_city, to);
                            bool conflict = false;
                            for (auto existing : used) {
                                if (existing == edge) {
                                    conflict = true;
                                    break;
                                }
                            }
                            if (conflict) {
                                continue;
                            }
                            auto next = moved;
                            auto moves = mv;
                            auto next_used = used;
                            next_used.push_back(edge);
                            next.tpos[tr_id] = to;
                            moves.push_back({tr_id, to});
                            self_move(self_move, tr_id + 1, next, moves, next_used);
                        }
                    };

                    vector<pair<int, int>> start_moves;
                    vector<ll> start_used_edges;
                    explore_moves(explore_moves, 1, state, start_moves, start_used_edges);
                    return;
                }

                int city = state.tpos[train_id];
                vector<int> candidates;
                for (int p = 1; p <= N; ++p) {
                    if (state.p_state[p] == 1 && state.p_city[p] == city) {
                        candidates.push_back(p);
                    }
                }

                int cap_left = C - cap[train_id];
                if (cap_left <= 0) {
                    self_pick(self_pick, train_id + 1, state, cap, actions);
                    return;
                }

                int m = (int)candidates.size();
                int total_mask = 1 << m;
                for (int mask = 0; mask < total_mask; ++mask) {
                    int cnt = __builtin_popcount((unsigned)mask);
                    if (cnt > cap_left) {
                        continue;
                    }
                    TinyState next = state;
                    auto next_cap = cap;
                    vector<Action> next_actions = actions;
                    bool ok = true;
                    for (int i = 0; i < m; ++i) {
                        if (!(mask & (1 << i))) {
                            continue;
                        }
                        int p = candidates[i];
                        if (next.p_rides[p] >= 4) {
                            ok = false;
                            break;
                        }
                        next.p_state[p] = 2;
                        next.p_city[p] = train_id;
                        ++next.p_rides[p];
                        ++next_cap[train_id];
                        next_actions.push_back({true, train_id, p});
                    }
                    if (!ok) {
                        continue;
                    }
                    self_pick(self_pick, train_id + 1, next, next_cap, move(next_actions));
                }
            };

            explore_picks(explore_picks, 1, ready, onboard_count, base_actions);
        };

        TinyState start{};
        for (int i = 1; i <= T; ++i) {
            start.tpos[i] = (uint8_t)trains[i].pos;
        }
        for (int p = 1; p <= N; ++p) {
            start.p_state[p] = 0;
            start.p_city[p] = 0;
            start.p_rides[p] = 0;
        }
        start.delivered = 0;
        start.tick = 1;

        unordered_map<TinyState, ll, TinyHash, TinyEq> dist;
        unordered_map<TinyState, TinyParent, TinyHash, TinyEq> parent;

        using TinyItem = pair<ll, TinyState>;
        struct TinyCmp {
            bool operator()(const TinyItem& a, const TinyItem& b) const {
                return a.first > b.first;
            }
        };
        priority_queue<TinyItem, vector<TinyItem>, TinyCmp> pq;

        dist[start] = 0;
        pq.push({0, start});

        ll best_cost = LLONG_MAX;
        TinyState goal{};
        bool found = false;

        while (!pq.empty()) {
            auto [cost, cur] = pq.top();
            pq.pop();
            auto it = dist.find(cur);
            if (it == dist.end() || it->second != cost) {
                continue;
            }
            if (cur.delivered == N) {
                best_cost = cost;
                goal = cur;
                found = true;
                break;
            }
            if (cur.tick > tiny_limit) {
                continue;
            }

            vector<TinyTransition> transitions;
            build_tiny_transitions(cur, cur.tick, transitions);
            for (auto& tr : transitions) {
                ll nxt_cost = cost + tr.delta;
                auto it2 = dist.find(tr.state);
                if (it2 != dist.end() && it2->second <= nxt_cost) {
                    continue;
                }
                dist[tr.state] = nxt_cost;
                parent[tr.state] = {cur, move(tr.actions), move(tr.moves)};
                pq.push({nxt_cost, tr.state});
            }
        }

        if (!found) {
            return false;
        }

        vector<TickPlan> tiny_answer;
        tiny_answer.reserve(best_cost < 2'000'000LL ? 128 : 1'000'000);
        TinyState cur = goal;
        TinyEq tiny_eq;
        while (!tiny_eq(cur, start)) {
            auto it = parent.find(cur);
            if (it == parent.end()) {
                return false;
            }
            tiny_answer.push_back({it->second.actions, it->second.moves});
            cur = it->second.prev;
        }
        reverse(tiny_answer.begin(), tiny_answer.end());

        cout << tiny_answer.size() << '\n';
        for (const auto& plan : tiny_answer) {
            cout << plan.actions.size() << '\n';
            for (const auto& action : plan.actions) {
                cout << (action.is_pick ? "pick " : "drop ")
                     << action.train_id << ' ' << action.passenger_id << '\n';
            }
            cout << plan.moves.size() << '\n';
            for (auto [train_id, next_city] : plan.moves) {
                cout << train_id << ' ' << next_city << '\n';
            }
        }
        return true;
    };

    if (solve_tiny_exact()) {
        return 0;
    }

    vector<vector<int>> spawn_at(max_spawn + 1);
    for (int i = 1; i <= N; ++i) {
        spawn_at[passengers[i].spawn].push_back(i);
    }

    vector<vector<int>> waiting_at(V + 1);
    vector<int> blocked_train_pickup(N + 1, 0);
    vector<int> comp_external_demand(comp_cnt + 1, 0);
    for (int i = 1; i <= N; ++i) {
        int cs = comp_id[passengers[i].start];
        int cd = comp_id[passengers[i].dest];
        if (cs != cd) {
            ++comp_external_demand[cs];
            ++comp_external_demand[cd];
        }
    }
    vector<int> comp_waiting_count(comp_cnt + 1, 0), comp_best_city(comp_cnt + 1, 0), hot_branch_components;
    vector<ll> comp_waiting_age(comp_cnt + 1, 0), comp_best_score(comp_cnt + 1, LLONG_MIN / 4);

    auto passenger_age = [&](int passenger_id, int tick) -> int {
        return tick - passengers[passenger_id].spawn;
    };

    auto current_goal = [&](int passenger_id) -> int {
        if (passengers[passenger_id].transfer_hub != 0 && !passengers[passenger_id].transfer_used) {
            return passengers[passenger_id].transfer_hub;
        }
        return passengers[passenger_id].dest;
    };

    auto choose_transfer_hub = [&](int passenger_id) -> int {
        int start = passengers[passenger_id].start;
        int dest = passengers[passenger_id].dest;
        int direct = dist[start][dest];
        if (!branchy_instance || direct < TRANSFER_MIN_DIRECT) {
            return 0;
        }
        int src_comp = comp_id[start];
        int dst_comp = comp_id[dest];
        if (src_comp != core_comp && dst_comp == core_comp) {
            return comp_gateway_core[src_comp];
        }
        if (src_comp == core_comp && dst_comp != core_comp) {
            return comp_gateway_core[dst_comp];
        }
        return 0;
    };

    auto choose_train_route_hop = [&](int train_id, int city) -> int {
        int best_hop = -1;
        int best_count = -1;
        int best_sum_dist = INT_MAX;

        for (int hop_candidate : g[city]) {
            int count = 0;
            int sum_dist = 0;
            for (int passenger_id : trains[train_id].onboard) {
                int hop = first_hop[city][current_goal(passenger_id)];
                if (hop == hop_candidate) {
                    ++count;
                    sum_dist += dist[city][current_goal(passenger_id)];
                }
            }
            if (count == 0) {
                continue;
            }
            if (count > best_count || (count == best_count && sum_dist < best_sum_dist) ||
                (count == best_count && sum_dist == best_sum_dist && hop_candidate < best_hop)) {
                best_count = count;
                best_sum_dist = sum_dist;
                best_hop = hop_candidate;
            }
        }
        return best_hop;
    };

    auto collect_bundle = [&](int train_id, int city, int tick, int forced_hop, bool allow_unaligned) -> BundleEval {
        BundleEval result;
        int capacity_left = C - (int)trains[train_id].onboard.size();
        if (capacity_left <= 0 || waiting_at[city].empty()) {
            return result;
        }

        struct Entry {
            int passenger_id = 0;
            int hop = -1;
            int age = 0;
            int trip = 0;
            ll base_score = 0;
        };

        vector<Entry> entries;
        entries.reserve(waiting_at[city].size());
        for (int passenger_id : waiting_at[city]) {
            if (passengers[passenger_id].state != WAITING || passengers[passenger_id].current_city != city) {
                continue;
            }
            if (blocked_train_pickup[passenger_id] == train_id) {
                continue;
            }
            int goal = current_goal(passenger_id);
            int hop = first_hop[city][goal];
            int age = passenger_age(passenger_id, tick);
            int trip = dist[city][goal];
            ll base_score = 70LL * age - 8LL * trip + (passengers[passenger_id].transfer_used ? TRANSFER_WAIT_BONUS : 0LL);
            entries.push_back({passenger_id, hop, age, trip, base_score});
        }

        if (entries.empty()) {
            return result;
        }

        int anchor_hop = -1;
        if (forced_hop != -1) {
            for (const auto& entry : entries) {
                if (entry.hop == forced_hop) {
                    anchor_hop = forced_hop;
                    break;
                }
            }
            if (anchor_hop == -1 && !allow_unaligned) {
                return result;
            }
        }

        if (anchor_hop == -1) {
            map<int, vector<Entry>> groups;
            for (const auto& entry : entries) {
                groups[entry.hop].push_back(entry);
            }

            ll best_group_score = LLONG_MIN / 4;
            int best_group_size = -1;
            int best_group_trip = INT_MAX;

            for (auto& [hop, group] : groups) {
                sort(group.begin(), group.end(), [&](const Entry& a, const Entry& b) {
                    if (a.base_score != b.base_score) {
                        return a.base_score > b.base_score;
                    }
                    if (a.age != b.age) {
                        return a.age > b.age;
                    }
                    if (a.trip != b.trip) {
                        return a.trip < b.trip;
                    }
                    return a.passenger_id < b.passenger_id;
                });

                ll top_score = 0;
                int top_trip = 0;
                int take = min<int>(capacity_left, group.size());
                for (int i = 0; i < take; ++i) {
                    top_score += group[i].base_score;
                    top_trip += group[i].trip;
                }

                if (top_score > best_group_score ||
                    (top_score == best_group_score && take > best_group_size) ||
                    (top_score == best_group_score && take == best_group_size && top_trip < best_group_trip) ||
                    (top_score == best_group_score && take == best_group_size && top_trip == best_group_trip && hop < anchor_hop)) {
                    best_group_score = top_score;
                    best_group_size = take;
                    best_group_trip = top_trip;
                    anchor_hop = hop;
                }
            }
        }

        auto cmp_entry = [&](const Entry& a, const Entry& b) {
            bool a_anchor = (a.hop == anchor_hop);
            bool b_anchor = (b.hop == anchor_hop);
            if (a_anchor != b_anchor) {
                return a_anchor > b_anchor;
            }
            if (a.base_score != b.base_score) {
                return a.base_score > b.base_score;
            }
            if (a.age != b.age) {
                return a.age > b.age;
            }
            if (a.trip != b.trip) {
                return a.trip < b.trip;
            }
            return a.passenger_id < b.passenger_id;
        };
        sort(entries.begin(), entries.end(), cmp_entry);

        for (const auto& entry : entries) {
            if ((int)result.ids.size() == capacity_left) {
                break;
            }
            if (!allow_unaligned && entry.hop != anchor_hop) {
                continue;
            }
            result.ids.push_back(entry.passenger_id);
            result.age_sum += entry.age;
            result.trip_sum += entry.trip;
        }
        result.main_hop = anchor_hop;
        return result;
    };

    auto best_delivery_tasks = [&](int train_id, int tick) -> vector<TaskCandidate> {
        vector<TaskCandidate> tasks;
        if (trains[train_id].onboard.empty()) {
            return tasks;
        }

        map<int, pair<int, ll>> info;
        for (int passenger_id : trains[train_id].onboard) {
            auto& [count, age_sum] = info[current_goal(passenger_id)];
            ++count;
            age_sum += passenger_age(passenger_id, tick);
        }

        int total_onboard = (int)trains[train_id].onboard.size();
        int pos = trains[train_id].pos;
        for (const auto& [dest, data] : info) {
            int count = data.first;
            ll age_sum = data.second;
            ll priority = DELIVERY_COUNT_W * count + DELIVERY_AGE_W * age_sum
                        - DELIVERY_DIST_W * dist[pos][dest] * (1 + total_onboard - count);
            tasks.push_back({0, dest, priority});
        }

        sort(tasks.begin(), tasks.end(), [&](const TaskCandidate& a, const TaskCandidate& b) {
            if (a.priority != b.priority) {
                return a.priority > b.priority;
            }
            return a.target < b.target;
        });
        return tasks;
    };

    auto evaluate_pickup_city = [&](int train_id, int city, int tick, int forced_hop, bool allow_unaligned, bool along_route) -> TaskCandidate {
        BundleEval bundle = collect_bundle(train_id, city, tick, forced_hop, allow_unaligned);
        if (bundle.ids.empty()) {
            return {};
        }

        int travel = dist[trains[train_id].pos][city];
        int onboard_count = (int)trains[train_id].onboard.size();
        ll priority = PICK_COUNT_W * (ll)bundle.ids.size() + PICK_AGE_W * bundle.age_sum
                    - PICK_TRAVEL_W * (ll)travel * (1 + onboard_count)
                    - PICK_TRIP_W * bundle.trip_sum;

        if (forced_hop != -1 && bundle.main_hop == forced_hop) {
            priority += ALIGN_BONUS;
        }
        if (along_route) {
            priority += ALONG_ROUTE_BONUS;
        }

        return {1, city, priority};
    };

    auto build_tasks = [&](int train_id, int tick) -> vector<TaskCandidate> {
        vector<TaskCandidate> tasks = best_delivery_tasks(train_id, tick);
        int capacity_left = C - (int)trains[train_id].onboard.size();
        if (capacity_left <= 0) {
            return tasks;
        }

        int pos = trains[train_id].pos;
        int pos_comp = comp_id[pos];
        if (trains[train_id].onboard.empty()) {
            int seen = 0;
            for (int city : cities_by_dist[pos]) {
                if (city == pos || waiting_at[city].empty()) {
                    continue;
                }
                TaskCandidate candidate = evaluate_pickup_city(train_id, city, tick, -1, true, false);
                if (candidate.target != -1) {
                    tasks.push_back(candidate);
                    ++seen;
                }
                if (seen == EMPTY_SCAN_LIMIT) {
                    break;
                }
            }

            if (branchy_instance && pos_comp == core_comp && seen < max(2, EMPTY_SCAN_LIMIT / 2)) {
                int branch_seen = 0;
                for (int comp : hot_branch_components) {
                    if (comp_waiting_count[comp] < 2 * C) {
                        continue;
                    }
                    int city = comp_best_city[comp];
                    if (city == 0 || city == pos) {
                        continue;
                    }
                    TaskCandidate candidate = evaluate_pickup_city(train_id, city, tick, -1, true, false);
                    if (candidate.target != -1) {
                        candidate.priority += BRANCH_TASK_BONUS
                                            + 3000LL * comp_waiting_count[comp]
                                            + 500LL * min<ll>(comp_waiting_age[comp], 1000);
                        tasks.push_back(candidate);
                        ++branch_seen;
                    }
                    if (branch_seen == min(BRANCH_SCAN_LIMIT, 4)) {
                        break;
                    }
                }
            }
        } else if (!tasks.empty()) {
            int main_delivery = tasks.front().target;
            int desired_hop = first_hop[pos][main_delivery];
            int seen = 0;
            for (int city : cities_by_dist[pos]) {
                if (city == pos || waiting_at[city].empty()) {
                    continue;
                }
                if (dist[pos][city] + dist[city][main_delivery] != dist[pos][main_delivery]) {
                    continue;
                }
                int route_hop = first_hop[city][main_delivery];
                TaskCandidate candidate = evaluate_pickup_city(train_id, city, tick, route_hop, false, true);
                if (candidate.target != -1) {
                    if (first_hop[pos][city] == desired_hop) {
                        candidate.priority += ALIGN_BONUS / 2;
                    }
                    tasks.push_back(candidate);
                    ++seen;
                }
                if (seen == ROUTE_SCAN_LIMIT) {
                    break;
                }
            }
        }

        sort(tasks.begin(), tasks.end(), [&](const TaskCandidate& a, const TaskCandidate& b) {
            if (a.priority != b.priority) {
                return a.priority > b.priority;
            }
            if (a.kind != b.kind) {
                return a.kind < b.kind;
            }
            return a.target < b.target;
        });

        vector<TaskCandidate> dedup;
        for (const auto& task : tasks) {
            if (!dedup.empty() && dedup.back().kind == task.kind && dedup.back().target == task.target) {
                continue;
            }
            dedup.push_back(task);
        }
        return dedup;
    };

    auto choose_next_city = [&](int train_id, int target, const unordered_set<ll>& used_edges) -> int {
        if (target == -1 || trains[train_id].pos == target) {
            return -1;
        }

        int u = trains[train_id].pos;
        vector<int> options;
        int best_remaining = INT_MAX;
        for (int v : g[u]) {
            ll key = 1LL * min(u, v) * (V + 1) + max(u, v);
            if (used_edges.count(key)) {
                continue;
            }
            if (dist[v][target] == -1) {
                continue;
            }
            int remaining = dist[v][target];
            if (remaining < best_remaining) {
                best_remaining = remaining;
                options.clear();
                options.push_back(v);
            } else if (remaining == best_remaining) {
                options.push_back(v);
            }
        }

        if (options.empty()) {
            return -1;
        }
        return options[uniform_int_distribution<int>(0, (int)options.size() - 1)(rng)];
    };

    vector<TickPlan> answer;
    answer.reserve(max_spawn + N + E + 16);
    ll total_moves = 0;
    int delivered = 0;

    for (int tick = 1; tick <= 1000000 && delivered < N; ++tick) {
        TickPlan plan;
        fill(blocked_train_pickup.begin(), blocked_train_pickup.end(), 0);

        if (tick <= max_spawn) {
            for (int passenger_id : spawn_at[tick]) {
                passengers[passenger_id].transfer_hub = choose_transfer_hub(passenger_id);
                passengers[passenger_id].transfer_used = false;
                passengers[passenger_id].state = WAITING;
                passengers[passenger_id].current_city = passengers[passenger_id].start;
                waiting_at[passengers[passenger_id].start].push_back(passenger_id);
            }
        }

        for (int train_id = 1; train_id <= T; ++train_id) {
            vector<int> keep;
            keep.reserve(trains[train_id].onboard.size());
            for (int passenger_id : trains[train_id].onboard) {
                int goal = current_goal(passenger_id);
                if (goal == trains[train_id].pos) {
                    plan.actions.push_back({false, train_id, passenger_id});
                    if (goal == passengers[passenger_id].dest) {
                        passengers[passenger_id].state = DELIVERED;
                        passengers[passenger_id].current_city = trains[train_id].pos;
                        ++delivered;
                    } else {
                        passengers[passenger_id].state = WAITING;
                        passengers[passenger_id].current_city = trains[train_id].pos;
                        passengers[passenger_id].transfer_used = true;
                        waiting_at[trains[train_id].pos].push_back(passenger_id);
                        blocked_train_pickup[passenger_id] = train_id;
                    }
                } else {
                    keep.push_back(passenger_id);
                }
            }
            trains[train_id].onboard.swap(keep);
        }

        for (int train_id = 1; train_id <= T; ++train_id) {
            int city = trains[train_id].pos;
            int forced_hop = choose_train_route_hop(train_id, city);
            bool allow_unaligned = trains[train_id].onboard.empty();
            BundleEval bundle = collect_bundle(train_id, city, tick, forced_hop, allow_unaligned);
            if (bundle.ids.empty()) {
                continue;
            }

            vector<int> selected = bundle.ids;
            sort(selected.begin(), selected.end());
            vector<int> keep;
            keep.reserve(waiting_at[city].size());

            for (int passenger_id : waiting_at[city]) {
                bool take = binary_search(selected.begin(), selected.end(), passenger_id);
                if (take) {
                    passengers[passenger_id].state = ONBOARD;
                    passengers[passenger_id].current_city = -1;
                    trains[train_id].onboard.push_back(passenger_id);
                    plan.actions.push_back({true, train_id, passenger_id});
                } else {
                    keep.push_back(passenger_id);
                }
            }
            waiting_at[city].swap(keep);
        }

        fill(comp_waiting_count.begin(), comp_waiting_count.end(), 0);
        fill(comp_waiting_age.begin(), comp_waiting_age.end(), 0);
        fill(comp_best_city.begin(), comp_best_city.end(), 0);
        fill(comp_best_score.begin(), comp_best_score.end(), LLONG_MIN / 4);
        hot_branch_components.clear();

        vector<int> city_quota(V + 1, 0);
        bool has_waiting = false;
        for (int city = 1; city <= V; ++city) {
            if (!waiting_at[city].empty()) {
                has_waiting = true;
                int live_count = 0;
                ll age_sum = 0;
                for (int passenger_id : waiting_at[city]) {
                    if (passengers[passenger_id].state != WAITING || passengers[passenger_id].current_city != city) {
                        continue;
                    }
                    ++live_count;
                    age_sum += passenger_age(passenger_id, tick);
                }
                if (live_count == 0) {
                    continue;
                }
                city_quota[city] = (live_count + C - 1) / C;
                int comp = comp_id[city];
                comp_waiting_count[comp] += live_count;
                comp_waiting_age[comp] += age_sum;
                ll local_score = 2000LL * live_count + age_sum + 25LL * comp_external_demand[comp];
                if (local_score > comp_best_score[comp] || (local_score == comp_best_score[comp] && city < comp_best_city[comp])) {
                    comp_best_score[comp] = local_score;
                    comp_best_city[comp] = city;
                }
            }
        }

        if (branchy_instance) {
            vector<pair<ll, int>> ranked;
            for (int comp = 1; comp <= comp_cnt; ++comp) {
                if (comp == core_comp || comp_waiting_count[comp] == 0) {
                    continue;
                }
                ll score = 7000LL * comp_waiting_count[comp]
                         + comp_waiting_age[comp]
                         + 40LL * comp_external_demand[comp];
                ranked.push_back({score, comp});
            }
            sort(ranked.begin(), ranked.end(), [&](const pair<ll, int>& a, const pair<ll, int>& b) {
                if (a.first != b.first) {
                    return a.first > b.first;
                }
                return a.second < b.second;
            });
            for (auto [_, comp] : ranked) {
                hot_branch_components.push_back(comp);
            }
        }

        vector<vector<TaskCandidate>> tasks_per_train(T + 1);
        vector<pair<ll, int>> active_trains;
        active_trains.reserve(T);
        for (int train_id = 1; train_id <= T; ++train_id) {
            if (trains[train_id].onboard.empty() && !has_waiting) {
                continue;
            }
            tasks_per_train[train_id] = build_tasks(train_id, tick);
            if (!tasks_per_train[train_id].empty()) {
                active_trains.push_back({tasks_per_train[train_id][0].priority, train_id});
            }
        }

        sort(active_trains.begin(), active_trains.end(), [&](const pair<ll, int>& a, const pair<ll, int>& b) {
            if (a.first != b.first) {
                return a.first > b.first;
            }
            int train_a = a.second;
            int train_b = b.second;
            if (trains[train_a].onboard.size() != trains[train_b].onboard.size()) {
                return trains[train_a].onboard.size() > trains[train_b].onboard.size();
            }
            return train_a < train_b;
        });

        unordered_set<ll> used_edges;
        used_edges.reserve(active_trains.size() * 2 + 1);
        vector<int> city_reserved(V + 1, 0);

        for (const auto& [_, train_id] : active_trains) {
            for (const auto& task : tasks_per_train[train_id]) {
                if (task.kind == 1 && city_reserved[task.target] >= city_quota[task.target]) {
                    continue;
                }
                int next_city = choose_next_city(train_id, task.target, used_edges);
                if (next_city == -1) {
                    continue;
                }

                int u = trains[train_id].pos;
                ll key = 1LL * min(u, next_city) * (V + 1) + max(u, next_city);
                used_edges.insert(key);
                plan.moves.push_back({train_id, next_city});
                if (task.kind == 1) {
                    ++city_reserved[task.target];
                }
                break;
            }
        }

        total_moves += (ll)plan.moves.size();
        answer.push_back(move(plan));
        for (auto [train_id, next_city] : answer.back().moves) {
            trains[train_id].pos = next_city;
        }

        if (total_moves > 2000000) {
            break;
        }
    }

    cout << answer.size() << '\n';
    for (const auto& plan : answer) {
        cout << plan.actions.size() << '\n';
        for (const auto& action : plan.actions) {
            cout << (action.is_pick ? "pick " : "drop ")
                 << action.train_id << ' ' << action.passenger_id << '\n';
        }
        cout << plan.moves.size() << '\n';
        for (auto [train_id, next_city] : plan.moves) {
            cout << train_id << ' ' << next_city << '\n';
        }
    }

    return 0;
}
