#include <bits/stdc++.h>

using namespace std;

struct Passenger {
    int start = 0;
    int dest = 0;
    int spawn = 0;
    int state = 0;  // 0 not appeared, 1 waiting, 2 onboard, 3 delivered
    int city = -1;
    int train = -1;
    int rides = 0;
    int arrival_tick = -1;
};

struct Verdict {
    bool ok = false;
    string message;
    long double points = 0;
};

static const array<long double, 5> PENALTY = {0.0L, 1.0L, 1.05L, 1.2L, 1.5L};

Verdict check_test(const string& test_path, const string& out_path) {
    ifstream tin(test_path);
    if (!tin) {
        return {false, "cannot open input file", 0};
    }

    int V, E;
    tin >> V >> E;
    vector<vector<int>> g(V + 1);
    for (int i = 0; i < E; ++i) {
        int u, v;
        tin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int T;
    tin >> T;
    vector<int> train_pos(T + 1), train_load(T + 1, 0);
    for (int i = 1; i <= T; ++i) {
        tin >> train_pos[i];
    }

    int C, N;
    tin >> C >> N;
    vector<Passenger> p(N + 1);
    vector<vector<int>> appear;
    int max_spawn = 0;
    for (int i = 1; i <= N; ++i) {
        tin >> p[i].start >> p[i].dest >> p[i].spawn;
        max_spawn = max(max_spawn, p[i].spawn);
    }
    appear.assign(max_spawn + 1, {});
    for (int i = 1; i <= N; ++i) {
        appear[p[i].spawn].push_back(i);
    }

    ifstream fout(out_path);
    if (!fout) {
        return {false, "missing output file", 0};
    }

    auto fail = [&](const string& msg) -> Verdict {
        return {false, msg, 0};
    };

    long long S;
    if (!(fout >> S)) {
        return fail("wrong format: missing S");
    }
    if (S < 0 || S > 1000000) {
        return fail("wrong format: S out of range");
    }

    long long total_moves = 0;
    int delivered = 0;

    for (int tick = 1; tick <= S; ++tick) {
        if (tick <= max_spawn) {
            for (int id : appear[tick]) {
                p[id].state = 1;
                p[id].city = p[id].start;
            }
        }

        long long K;
        if (!(fout >> K)) {
            return fail("wrong format at tick " + to_string(tick) + ": missing K");
        }
        if (K < 0) {
            return fail("wrong format at tick " + to_string(tick) + ": negative K");
        }

        for (long long i = 0; i < K; ++i) {
            string cmd;
            int train_id, pass_id;
            if (!(fout >> cmd >> train_id >> pass_id)) {
                return fail("wrong format at tick " + to_string(tick) + ": malformed action");
            }
            if (train_id < 1 || train_id > T || pass_id < 1 || pass_id > N) {
                return fail("wrong format at tick " + to_string(tick) + ": invalid action id");
            }

            if (cmd == "pick") {
                if (p[pass_id].state == 3) {
                    return fail("tick " + to_string(tick) + ": trying to pick delivered tradesman");
                }
                if (p[pass_id].state != 1) {
                    return fail("tick " + to_string(tick) + ": trying to pick non-waiting tradesman");
                }
                if (p[pass_id].city != train_pos[train_id]) {
                    return fail("tick " + to_string(tick) + ": pick in different city");
                }
                if (train_load[train_id] >= C) {
                    return fail("tick " + to_string(tick) + ": train capacity exceeded");
                }
                ++train_load[train_id];
                ++p[pass_id].rides;
                if (p[pass_id].rides > 4) {
                    return fail("tick " + to_string(tick) + ": tradesman used more than four rides");
                }
                p[pass_id].state = 2;
                p[pass_id].train = train_id;
                p[pass_id].city = -1;
            } else if (cmd == "drop") {
                if (p[pass_id].state != 2 || p[pass_id].train != train_id) {
                    return fail("tick " + to_string(tick) + ": trying to drop tradesman not on this train");
                }
                --train_load[train_id];
                p[pass_id].train = -1;
                if (train_pos[train_id] == p[pass_id].dest) {
                    p[pass_id].state = 3;
                    p[pass_id].arrival_tick = tick;
                    ++delivered;
                } else {
                    p[pass_id].state = 1;
                    p[pass_id].city = train_pos[train_id];
                }
            } else {
                return fail("wrong format at tick " + to_string(tick) + ": unknown action");
            }
        }

        long long M;
        if (!(fout >> M)) {
            return fail("wrong format at tick " + to_string(tick) + ": missing M");
        }
        if (M < 0) {
            return fail("wrong format at tick " + to_string(tick) + ": negative M");
        }

        total_moves += M;
        if (total_moves > 2000000) {
            return fail("tick " + to_string(tick) + ": total move limit exceeded");
        }

        vector<int> next_pos = train_pos;
        vector<int> seen(T + 1, 0);
        set<pair<int, int>> used_edges;
        for (long long i = 0; i < M; ++i) {
            int train_id, city_id;
            if (!(fout >> train_id >> city_id)) {
                return fail("wrong format at tick " + to_string(tick) + ": malformed move");
            }
            if (train_id < 1 || train_id > T || city_id < 1 || city_id > V) {
                return fail("wrong format at tick " + to_string(tick) + ": invalid move id");
            }
            if (seen[train_id]) {
                return fail("tick " + to_string(tick) + ": duplicate train move");
            }
            seen[train_id] = 1;

            bool ok_edge = false;
            for (int to : g[train_pos[train_id]]) {
                if (to == city_id) {
                    ok_edge = true;
                    break;
                }
            }
            if (!ok_edge) {
                return fail("tick " + to_string(tick) + ": move uses nonexistent rail track");
            }

            auto edge = minmax(train_pos[train_id], city_id);
            if (used_edges.count(edge)) {
                return fail("tick " + to_string(tick) + ": rail track reused in same movement phase");
            }
            used_edges.insert(edge);
            next_pos[train_id] = city_id;
        }
        train_pos.swap(next_pos);
    }

    string extra;
    if (fout >> extra) {
        return fail("wrong format: trailing tokens after declared plan");
    }

    if (delivered != N) {
        return fail("incomplete plan: some tradesmen never reached destination");
    }

    long double points = 0;
    for (int i = 1; i <= N; ++i) {
        if (p[i].arrival_tick == -1) {
            return fail("internal error: missing arrival tick");
        }
        points += (long double)(p[i].arrival_tick - p[i].spawn) * PENALTY[p[i].rides];
    }

    long double rooted_points = sqrtl(points);
    ostringstream out;
    out << fixed << setprecision(2) << rooted_points;
    return {true, out.str(), rooted_points};
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc >= 4 && string(argv[1]) == "--single") {
        bool quiet = false;
        for (int i = 4; i < argc; ++i) {
            if (string(argv[i]) == "--quiet") {
                quiet = true;
            }
        }

        Verdict verdict = check_test(argv[2], argv[3]);
        if (!verdict.ok) {
            if (quiet) {
                cerr << verdict.message << '\n';
            } else {
                cout << verdict.message << '\n';
            }
            return 2;
        }

        ostringstream out;
        out << fixed << setprecision(2) << verdict.points;
        if (quiet) {
            cout << out.str() << '\n';
        } else {
            cout << filesystem::path(argv[2]).filename().string() << ": OK " << out.str() << '\n';
        }
        return 0;
    }

    string tests_dir = "tests";
    string out_dir = "out";
    if (argc >= 2) {
        tests_dir = argv[1];
    }
    if (argc >= 3) {
        out_dir = argv[2];
    }

    vector<string> tests;
    for (const auto& entry : filesystem::directory_iterator(tests_dir)) {
        if (!entry.is_regular_file()) {
            continue;
        }
        tests.push_back(entry.path().filename().string());
    }
    sort(tests.begin(), tests.end());

    for (const string& name : tests) {
        string test_path = tests_dir + "/" + name;
        string out_path = out_dir + "/" + name + ".out";
        Verdict verdict = check_test(test_path, out_path);
        if (verdict.ok) {
            cout << name << ": OK " << verdict.message << '\n';
        } else {
            cout << name << ": " << verdict.message << '\n';
        }
    }

    return 0;
}
