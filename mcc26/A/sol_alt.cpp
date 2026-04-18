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
    PassengerState state = NOT_APPEARED;
};

struct Train {
    int pos = 0;
    vector<int> onboard;
    int route_id = -1;
    int route_step = -1;
};

struct TaskCandidate {
    int kind = 0;  // 0 deliver, 1 pickup
    int target = -1;
    ll priority = LLONG_MIN / 4;
};

static mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

struct MCMFEdge {
    int to, rev, cap;
    ll cost;
};

static void add_edge(vector<vector<MCMFEdge>>& g, int u, int v, int cap, ll cost) {
    MCMFEdge a{v, (int)g[v].size(), cap, cost};
    MCMFEdge b{u, (int)g[u].size(), 0, -cost};
    g[u].push_back(a);
    g[v].push_back(b);
}

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
        return (it == options.end() ? default_value : stoi(it->second));
    };

    auto get_ll_opt = [&](const string& key, ll default_value) -> ll {
        auto it = options.find(key);
        return (it == options.end() ? default_value : stoll(it->second));
    };

    unsigned seed = (unsigned)get_ll_opt("seed", (ll)chrono::steady_clock::now().time_since_epoch().count());
    rng.seed(seed);

    int NEAR_SCAN_LIMIT = get_int_opt("NEAR_SCAN_LIMIT", 12);
    int GLOBAL_SCAN_LIMIT = get_int_opt("GLOBAL_SCAN_LIMIT", 8);
    ll DELIVERY_COUNT_W = get_ll_opt("DELIVERY_COUNT_W", 4500000LL);
    ll DELIVERY_AGE_W = get_ll_opt("DELIVERY_AGE_W", 5000LL);
    ll DELIVERY_DIST_W = get_ll_opt("DELIVERY_DIST_W", 18000LL);
    ll PICK_COUNT_W = get_ll_opt("PICK_COUNT_W", 2600000LL);
    ll PICK_AGE_W = get_ll_opt("PICK_AGE_W", 4200LL);
    ll PICK_TRAVEL_W = get_ll_opt("PICK_TRAVEL_W", 15000LL);
    ll PICK_TRIP_W = get_ll_opt("PICK_TRIP_W", 1200LL);
    int DOMINANT_PAIR_MODE = get_int_opt("DOMINANT_PAIR_MODE", 0);

    int V, E;
    cin >> V >> E;
    vector<vector<int>> g(V + 1);
    vector<pair<int, int>> edges;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        edges.push_back({u, v});
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
    map<pair<int, int>, int> pair_count;
    map<int, int> spawn_count;
    for (int i = 1; i <= N; ++i) {
        cin >> passengers[i].start >> passengers[i].dest >> passengers[i].spawn;
        max_spawn = max(max_spawn, passengers[i].spawn);
        pair_count[{passengers[i].start, passengers[i].dest}]++;
        spawn_count[passengers[i].spawn]++;
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
                if (dist[src][v] == -1) {
                    dist[src][v] = dist[src][u] + 1;
                    q.push(v);
                }
            }
        }
    }

    vector<vector<int>> first_hop(V + 1, vector<int>(V + 1, -1));
    for (int u = 1; u <= V; ++u) {
        for (int target = 1; target <= V; ++target) {
            if (u == target) continue;
            for (int v : g[u]) {
                if (dist[v][target] == dist[u][target] - 1) {
                    first_hop[u][target] = v;
                    break;
                }
            }
        }
    }

    auto output_answer = [&](const vector<TickPlan>& answer) {
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
    };

    auto run_dominant_pair = [&]() -> bool {
        auto best_pair_it = max_element(pair_count.begin(), pair_count.end(), [&](const auto& a, const auto& b) {
            if (a.second != b.second) return a.second < b.second;
            return a.first < b.first;
        });
        if (best_pair_it == pair_count.end()) return false;

        auto [s, d] = best_pair_it->first;
        int best_pair_count = best_pair_it->second;
        int best_spawn_count = 0;
        int dominant_spawn = -1;
        for (const auto& [tick, cnt] : spawn_count) {
            if (cnt > best_spawn_count) {
                best_spawn_count = cnt;
                dominant_spawn = tick;
            }
        }

        bool all_trains_at_source = true;
        for (int i = 1; i <= T; ++i) {
            if (trains[i].pos != s) {
                all_trains_at_source = false;
                break;
            }
        }

        if (!(best_pair_count == N && best_spawn_count == N && dominant_spawn == 1 && all_trains_at_source && N <= T * C)) {
            return false;
        }

        int units = (N + C - 1) / C;
        int max_out = max(1, (int)g[s].size());
        int horizon = dist[s][d] + units / max_out + 8;

        auto solve_for_horizon = [&](int H, vector<vector<int>>& unit_paths) -> bool {
            int nodes = (H + 1) * V + 2;
            int SRC = 0, SNK = nodes - 1;
            auto id = [&](int city, int time) {
                return 1 + time * V + (city - 1);
            };

            vector<vector<MCMFEdge>> net(nodes);
            const int INF = 1e9;
            for (int t = 0; t < H; ++t) {
                for (int city = 1; city <= V; ++city) {
                    add_edge(net, id(city, t), id(city, t + 1), INF, 0);
                }
                for (auto [u, v] : edges) {
                    if (dist[u][d] == dist[v][d] + 1) {
                        add_edge(net, id(u, t), id(v, t + 1), 1, 0);
                    }
                    if (dist[v][d] == dist[u][d] + 1) {
                        add_edge(net, id(v, t), id(u, t + 1), 1, 0);
                    }
                }
            }
            add_edge(net, SRC, id(s, 0), units, 0);
            for (int t = 0; t <= H; ++t) {
                add_edge(net, id(d, t), SNK, INF, t);
            }

            ll total_cost = 0;
            int flow = 0;
            vector<ll> pot(nodes, 0), distm(nodes);
            vector<int> pv(nodes), pe(nodes);

            while (flow < units) {
                fill(distm.begin(), distm.end(), (ll)4e18);
                priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
                distm[SRC] = 0;
                pq.push({0, SRC});
                while (!pq.empty()) {
                    auto [cur_d, u] = pq.top();
                    pq.pop();
                    if (cur_d != distm[u]) continue;
                    for (int i = 0; i < (int)net[u].size(); ++i) {
                        const auto& e = net[u][i];
                        if (e.cap <= 0) continue;
                        ll nd = cur_d + e.cost + pot[u] - pot[e.to];
                        if (nd < distm[e.to]) {
                            distm[e.to] = nd;
                            pv[e.to] = u;
                            pe[e.to] = i;
                            pq.push({nd, e.to});
                        }
                    }
                }
                if (distm[SNK] > (ll)3e18) {
                    return false;
                }
                for (int v = 0; v < nodes; ++v) {
                    if (distm[v] < (ll)3e18) pot[v] += distm[v];
                }
                int add = units - flow;
                for (int v = SNK; v != SRC; v = pv[v]) {
                    add = min(add, net[pv[v]][pe[v]].cap);
                }
                flow += add;
                total_cost += 1LL * add * pot[SNK];
                for (int v = SNK; v != SRC; v = pv[v]) {
                    auto& e = net[pv[v]][pe[v]];
                    e.cap -= add;
                    net[v][e.rev].cap += add;
                }
            }

            unit_paths.clear();
            for (int unit = 0; unit < units; ++unit) {
                vector<int> path = {s};
                int node = id(s, 0);
                int time = 0;
                while (time <= H) {
                    bool advanced = false;
                    for (auto& e : net[node]) {
                        if (e.to == SRC) continue;
                        if (net[e.to][e.rev].cap <= 0) continue;
                        net[e.to][e.rev].cap--;
                        int nxt = e.to;
                        if (nxt == SNK) {
                            unit_paths.push_back(path);
                            advanced = true;
                            time = H + 1;
                            break;
                        }
                        int idx = nxt - 1;
                        int nxt_time = idx / V;
                        int nxt_city = idx % V + 1;
                        if (nxt_time == time + 1) {
                            path.push_back(nxt_city);
                            node = nxt;
                            time = nxt_time;
                            advanced = true;
                            break;
                        }
                    }
                    if (!advanced) {
                        return false;
                    }
                }
            }
            return (int)unit_paths.size() == units;
        };

        vector<vector<int>> unit_paths;
        while (!solve_for_horizon(horizon, unit_paths)) {
            horizon = horizon * 3 / 2 + 5;
            if (horizon > 200) return false;
        }

        vector<vector<int>> train_passengers(units);
        int next_passenger = 1;
        for (int i = 0; i < units; ++i) {
            for (int k = 0; k < C && next_passenger <= N; ++k) {
                train_passengers[i].push_back(next_passenger++);
            }
        }

        int final_ticks = 1;
        vector<int> arrival_tick(units, 0);
        for (int i = 0; i < units; ++i) {
            const auto& path = unit_paths[i];
            int t = 0;
            while (t + 1 < (int)path.size() && path[t] != d) ++t;
            while (t < (int)path.size() && path[t] != d) ++t;
            if (t == (int)path.size()) return false;
            arrival_tick[i] = t;
            final_ticks = max(final_ticks, t + 1);
        }

        vector<TickPlan> answer(final_ticks);
        for (int i = 0; i < units; ++i) {
            int train_id = i + 1;
            for (int pid : train_passengers[i]) {
                answer[0].actions.push_back({true, train_id, pid});
            }
            const auto& path = unit_paths[i];
            for (int step = 1; step <= arrival_tick[i]; ++step) {
                if (path[step] != path[step - 1]) {
                    answer[step - 1].moves.push_back({train_id, path[step]});
                }
            }
            for (int pid : train_passengers[i]) {
                answer[arrival_tick[i]].actions.push_back({false, train_id, pid});
            }
        }

        output_answer(answer);
        return true;
    };

    if (DOMINANT_PAIR_MODE && run_dominant_pair()) {
        return 0;
    }

    vector<vector<int>> spawn_at(max_spawn + 1);
    for (int i = 1; i <= N; ++i) {
        spawn_at[passengers[i].spawn].push_back(i);
    }

    vector<vector<int>> waiting_at(V + 1);

    auto passenger_age = [&](int passenger_id, int tick) -> int {
        return tick - passengers[passenger_id].spawn;
    };

    auto choose_bundle = [&](int train_id, int city, int tick) -> vector<int> {
        int capacity_left = C - (int)trains[train_id].onboard.size();
        if (capacity_left <= 0 || waiting_at[city].empty()) return {};

        map<int, vector<int>> groups;
        for (int pid : waiting_at[city]) {
            if (passengers[pid].state == WAITING && passengers[pid].current_city == city) {
                groups[passengers[pid].dest].push_back(pid);
            }
        }
        ll best_score = LLONG_MIN / 4;
        vector<int> best_ids;
        for (auto& [dest, ids] : groups) {
            sort(ids.begin(), ids.end(), [&](int a, int b) {
                int age_a = passenger_age(a, tick), age_b = passenger_age(b, tick);
                if (age_a != age_b) return age_a > age_b;
                return a < b;
            });
            ll score = 0;
            int take = min<int>(capacity_left, ids.size());
            for (int i = 0; i < take; ++i) {
                score += 2000LL * passenger_age(ids[i], tick) - 300LL * dist[city][dest];
            }
            if (score > best_score || (score == best_score && dest < passengers[best_ids.empty() ? ids[0] : best_ids[0]].dest)) {
                best_score = score;
                best_ids.assign(ids.begin(), ids.begin() + take);
            }
        }
        return best_ids;
    };

    vector<int> city_count(V + 1, 0);
    vector<ll> city_age(V + 1, 0);

    auto eval_pick_city = [&](int train_id, int city, int tick) -> TaskCandidate {
        vector<int> ids = choose_bundle(train_id, city, tick);
        if (ids.empty()) return {};
        ll age_sum = 0;
        int dest0 = passengers[ids[0]].dest;
        for (int pid : ids) age_sum += passenger_age(pid, tick);
        ll score = PICK_COUNT_W * (ll)ids.size() + PICK_AGE_W * age_sum
                 - PICK_TRAVEL_W * dist[trains[train_id].pos][city]
                 - PICK_TRIP_W * dist[city][dest0];
        return {1, city, score};
    };

    auto build_tasks = [&](int train_id, int tick) -> vector<TaskCandidate> {
        vector<TaskCandidate> tasks;
        if (!trains[train_id].onboard.empty()) {
            map<int, pair<int, ll>> info;
            for (int pid : trains[train_id].onboard) {
                auto& [cnt, age] = info[passengers[pid].dest];
                ++cnt;
                age += passenger_age(pid, tick);
            }
            for (const auto& [dest, data] : info) {
                ll score = DELIVERY_COUNT_W * data.first + DELIVERY_AGE_W * data.second
                         - DELIVERY_DIST_W * dist[trains[train_id].pos][dest];
                tasks.push_back({0, dest, score});
            }
        }

        if ((int)trains[train_id].onboard.size() < C) {
            int seen = 0;
            for (int city = 1; city <= V; ++city) {
                if (city == trains[train_id].pos || city_count[city] == 0) continue;
                if (V > 50 && dist[trains[train_id].pos][city] > 6) continue;
                TaskCandidate cand = eval_pick_city(train_id, city, tick);
                if (cand.target != -1) {
                    tasks.push_back(cand);
                    ++seen;
                }
                if (seen >= NEAR_SCAN_LIMIT) break;
            }

            vector<pair<ll, int>> ranked;
            for (int city = 1; city <= V; ++city) {
                if (city_count[city] == 0) continue;
                ranked.push_back({3000LL * city_count[city] + city_age[city], city});
            }
            sort(ranked.begin(), ranked.end(), [&](const auto& a, const auto& b) {
                if (a.first != b.first) return a.first > b.first;
                return a.second < b.second;
            });
            for (int i = 0; i < min<int>(GLOBAL_SCAN_LIMIT, ranked.size()); ++i) {
                TaskCandidate cand = eval_pick_city(train_id, ranked[i].second, tick);
                if (cand.target != -1) tasks.push_back(cand);
            }
        }

        sort(tasks.begin(), tasks.end(), [&](const TaskCandidate& a, const TaskCandidate& b) {
            if (a.priority != b.priority) return a.priority > b.priority;
            if (a.kind != b.kind) return a.kind < b.kind;
            return a.target < b.target;
        });
        vector<TaskCandidate> dedup;
        for (const auto& t : tasks) {
            if (!dedup.empty() && dedup.back().kind == t.kind && dedup.back().target == t.target) continue;
            dedup.push_back(t);
        }
        return dedup;
    };

    auto choose_next_city = [&](int train_id, int target, const unordered_set<ll>& used_edges) -> int {
        if (target == -1 || target == trains[train_id].pos) return -1;
        int u = trains[train_id].pos;
        vector<int> opts;
        int best = INT_MAX;
        for (int v : g[u]) {
            ll key = 1LL * min(u, v) * (V + 1) + max(u, v);
            if (used_edges.count(key)) continue;
            if (dist[v][target] < best) {
                best = dist[v][target];
                opts.clear();
                opts.push_back(v);
            } else if (dist[v][target] == best) {
                opts.push_back(v);
            }
        }
        if (opts.empty()) return -1;
        return opts[uniform_int_distribution<int>(0, (int)opts.size() - 1)(rng)];
    };

    vector<TickPlan> answer;
    ll total_moves = 0;
    int delivered = 0;

    for (int tick = 1; tick <= 1000000 && delivered < N; ++tick) {
        TickPlan plan;

        if (tick <= max_spawn) {
            for (int pid : spawn_at[tick]) {
                passengers[pid].state = WAITING;
                passengers[pid].current_city = passengers[pid].start;
                waiting_at[passengers[pid].start].push_back(pid);
            }
        }

        for (int train_id = 1; train_id <= T; ++train_id) {
            vector<int> keep;
            for (int pid : trains[train_id].onboard) {
                if (passengers[pid].dest == trains[train_id].pos) {
                    passengers[pid].state = DELIVERED;
                    passengers[pid].current_city = trains[train_id].pos;
                    plan.actions.push_back({false, train_id, pid});
                    ++delivered;
                } else {
                    keep.push_back(pid);
                }
            }
            trains[train_id].onboard.swap(keep);
        }

        for (int train_id = 1; train_id <= T; ++train_id) {
            int city = trains[train_id].pos;
            vector<int> pick_ids = choose_bundle(train_id, city, tick);
            if (pick_ids.empty()) continue;
            sort(pick_ids.begin(), pick_ids.end());
            vector<int> keep;
            for (int pid : waiting_at[city]) {
                if (binary_search(pick_ids.begin(), pick_ids.end(), pid)) {
                    passengers[pid].state = ONBOARD;
                    passengers[pid].current_city = -1;
                    trains[train_id].onboard.push_back(pid);
                    plan.actions.push_back({true, train_id, pid});
                } else {
                    keep.push_back(pid);
                }
            }
            waiting_at[city].swap(keep);
        }

        fill(city_count.begin(), city_count.end(), 0);
        fill(city_age.begin(), city_age.end(), 0);
        vector<int> city_quota(V + 1, 0);
        bool has_waiting = false;
        for (int city = 1; city <= V; ++city) {
            int cnt = 0;
            ll age = 0;
            for (int pid : waiting_at[city]) {
                if (passengers[pid].state == WAITING && passengers[pid].current_city == city) {
                    ++cnt;
                    age += passenger_age(pid, tick);
                }
            }
            city_count[city] = cnt;
            city_age[city] = age;
            if (cnt > 0) {
                has_waiting = true;
                city_quota[city] = (cnt + C - 1) / C;
            }
        }

        vector<vector<TaskCandidate>> tasks_per_train(T + 1);
        vector<pair<ll, int>> active;
        for (int train_id = 1; train_id <= T; ++train_id) {
            if (trains[train_id].onboard.empty() && !has_waiting) continue;
            tasks_per_train[train_id] = build_tasks(train_id, tick);
            if (!tasks_per_train[train_id].empty()) {
                active.push_back({tasks_per_train[train_id][0].priority, train_id});
            }
        }
        sort(active.begin(), active.end(), greater<pair<ll, int>>());

        unordered_set<ll> used_edges;
        vector<int> city_reserved(V + 1, 0);
        for (auto [_, train_id] : active) {
            for (const auto& task : tasks_per_train[train_id]) {
                if (task.kind == 1 && city_reserved[task.target] >= city_quota[task.target]) continue;
                int next_city = choose_next_city(train_id, task.target, used_edges);
                if (next_city == -1) continue;
                ll key = 1LL * min(trains[train_id].pos, next_city) * (V + 1) + max(trains[train_id].pos, next_city);
                used_edges.insert(key);
                plan.moves.push_back({train_id, next_city});
                if (task.kind == 1) ++city_reserved[task.target];
                break;
            }
        }

        total_moves += (ll)plan.moves.size();
        if (total_moves > 2000000) break;
        answer.push_back(move(plan));
        for (auto [train_id, next_city] : answer.back().moves) {
            trains[train_id].pos = next_city;
        }
    }

    output_answer(answer);
    return 0;
}
