#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll





//#define verbose
//#define assert_checks

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

vector<int> path[7], batch_cost[20];
vector<int> is_last_node[7];

int sp_cost[8], num_cores, c_switch, c_r, mask_cost[256];

int opt_node_cost[20][10001], tr_node_cost[20][10001];

struct packet {
    int id, arrival, type, timeout, cur_node = 0, work = -1, cur_core = -1, working = 0;
    packet() {}
};

void solve() {
    int n; cin >> n;
    vector<packet> pack(n);
    int recieve_cooldown = 0, finished = 0;
    auto recieve = [&] (int t) {
#ifdef assert_checks
        assert(recieve_cooldown <= t);
#endif
        cout << "R " << t << endl;
        int p; cin >> p; 
        vector<packet> v(p);
#ifdef verbose
        cerr << "recieving " << p << " new packets at T = " << t << endl;
#endif
        for (auto& x : v) {
            cin >> x.id >> x.arrival >> x.type >> x.timeout;
            --x.id, --x.type;
#ifdef verbose
            cerr << "id = " << x.id << " arrival = " << x.arrival << " type = " << x.type << " timeout = " << x.timeout << endl;
#endif
        }
        recieve_cooldown = t + c_r;
        return v;
    };
    auto get_work = [&] (int t, int id) {
#ifdef assert_checks
        assert(pack[id].work == -1);
#endif
        cout << "Q " << t << " " << id+1 << endl;
        cin >> pack[id].work;
    };
    vector<vector<int>> assigned_packs(num_cores);
    vector<int> death_time(n), last_cores_cnt(num_cores), is_core_free(num_cores, 1), packets_in_core(num_cores);
    vector<vector<int>> pending_pack(num_cores, vector<int>(20));
    set<ii> working_cores, waiting_packets;
    vector<vector<set<ii>>> packets_in_node(num_cores, vector<set<ii>>(20));
    auto execute = [&] (int t, int core_id, int node_id, vector<int> packs) {
#ifdef verbose
        cerr << "executando " << "T = " << t << " core_id = " << core_id << " node_id = " << node_id << endl;
        cerr << "packs = ";
        for (auto x : packs) cerr << x + 1 << " ";
        cerr << endl;
#endif
#ifdef assert_checks
        assert(0 < sz(packs));
        assert(is_core_free[core_id] == true);
        assert(sz(packs) < sz(batch_cost[node_id]));
        assert(assigned_packs[core_id].empty());
#endif
        cout << "E " << t << " " << core_id + 1 << " " << node_id + 1 << " ";
        cout << sz(packs) << " ";
        for (auto x : packs) cout << x + 1 << " ";
        cout << endl;
        int num_switches = 0;
        for (auto i : packs) {
#ifdef assert_checks
            assert(pack[i].working == false);
#endif
            pack[i].working = true;
            if (pack[i].cur_core != core_id) {
                assert(pack[i].cur_core == -1);
#ifdef verbose
                cerr << "changing core of packet " << i << " from " << pack[i].cur_core << " to " << core_id << endl;
#endif
                num_switches++, pack[i].cur_core = core_id;
            }
            packets_in_node[core_id][node_id].erase({death_time[i], i});
        }
        int ta = batch_cost[node_id][sz(packs)] + num_switches * c_switch;
        if (node_id == 7) for (auto i : packs) {
#ifdef assert_checks
            assert(pack[i].work != -1);
#endif
            ta += mask_cost[pack[i].work];
        }
        working_cores.insert({t + ta, core_id});
        swap(assigned_packs[core_id], packs);
        is_core_free[core_id] = false;
        return ta;
    };
    int T = 1;
    while (finished != n) {
        // everytime we can, we ask!
        if (T >= recieve_cooldown) {
            auto v = recieve(T);
            for (auto x : v) {
                waiting_packets.insert({T + c_r, x.id});
                pack[x.id] = x;
            }
            continue;
        }
        auto assign_packet = [&] (int i) {
            int choice = rnd(0, num_cores-1);
            for (int j = 0; j < sz(path[pack[i].type]); ++j) if (is_last_node[pack[i].type][j]) pending_pack[choice][path[pack[i].type][j]]++;
            packets_in_node[choice][path[pack[i].type][0]].insert({death_time[i], i});
            packets_in_core[choice]++;
#ifdef verbose
            cerr << "assign packet " << i << " to core " << choice << endl;
#endif
        };
        if (!waiting_packets.empty() and (begin(waiting_packets)->first) <= T) {
            auto [a, i] = *begin(waiting_packets);
            waiting_packets.erase(begin(waiting_packets));
            death_time[i] = a + pack[i].timeout;
            if (path[pack[i].type][pack[i].cur_node] == 7) get_work(T, i);
            assign_packet(i);
            continue;
        }
        if (!working_cores.empty() and (begin(working_cores)->first) <= T) {
            // free core
            auto [fodase, idc] = *begin(working_cores);
            working_cores.erase(begin(working_cores));
            for (auto id_p : assigned_packs[idc]) {
                if (is_last_node[pack[id_p].type][pack[id_p].cur_node]) pending_pack[idc][path[pack[id_p].type][pack[id_p].cur_node]]--;
                pack[id_p].cur_node++;
                if (sz(path[pack[id_p].type]) == pack[id_p].cur_node) finished++, packets_in_core[idc]--;
                else {
                    if (path[pack[id_p].type][pack[id_p].cur_node] == 7 and pack[id_p].work == -1) get_work(T, id_p);
                    packets_in_node[idc][path[pack[id_p].type][pack[id_p].cur_node]].insert({death_time[id_p], id_p});
                }
                pack[id_p].working = false;
            }
            assigned_packs[idc].clear();
            is_core_free[idc] = true;
            continue;
        }
        auto goto_next_event = [&] () {
            T = recieve_cooldown;
            if (!working_cores.empty()) ckmin(T, (begin(working_cores)->first));
        };
        int choice = -1;
        for (int i = 0; i < num_cores; ++i) {
            if (is_core_free[i] and packets_in_core[i]) { choice = i; break; }
        }
        if (choice == -1) { goto_next_event(); continue; }
        vector<int> executable;
        int opt_greedy = 1e18;
        int greedy_choice = -1;
        for (int i = 0; i < 20; ++i) {
            int qt = sz(packets_in_node[choice][i]);
            int opt_move = tr_node_cost[i][pending_pack[choice][i]];
            if (qt and ckmin(opt_greedy, (begin(packets_in_node[choice][i])->first))) {
                greedy_choice = i;
            }
            if (1 <= opt_move and opt_move <= qt) executable.pb(i);
        }
        int i, opt_move;
        if (executable.empty()) {
            assert(greedy_choice != -1);
            i = greedy_choice;
            opt_move = min(sz(packets_in_node[choice][i]), sz(batch_cost[i])-1);
        } else {
            int opt = 1e18;
            for (auto x : executable) {
                if (ckmin(opt, (begin(packets_in_node[choice][x])->first))) i = x, opt_move = tr_node_cost[i][pending_pack[choice][i]];
            }
        }
        vector<int> packs;
        for (auto [fodase, id_p] : packets_in_node[choice][i]) {
            packs.pb(id_p);
            if (sz(packs) == opt_move) break;
        }
        execute(T, choice, i, packs);
    }
    cout << "F" << endl;
}

int32_t main() {_
    for (int i = 0; i < 7; ++i) {
        int l; cin >> l;
        path[i].resize(l);
        for (auto& x : path[i]) cin >> x, --x;
        for (int j = 0; j < l; ++j) {
            is_last_node[i].pb(1);
            for (int k = j + 1; k < l; ++k) if (path[i][j] == path[i][k]) is_last_node[i].back() = 0;
        }
    }
    for (int i = 0; i < 20; ++i) {
        int tam; cin >> tam;
        batch_cost[i].resize(tam+1);
        for (int j = 1; j <= tam; ++j) cin >> batch_cost[i][j];
        for (int j = 1; j <= 10000; ++j) {
            opt_node_cost[i][j] = 1e18;
            for (int k = 1; k <= min(j, tam); ++k) {
                if (ckmin(opt_node_cost[i][j], opt_node_cost[i][j-k] + batch_cost[i][k])) tr_node_cost[i][j] = k;
            }
        }
    }
    for (int i = 0; i < 8; ++i) cin >> sp_cost[i];
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 8; ++j) if (i >> j & 1) mask_cost[i] += sp_cost[j];
    }
    cin >> num_cores >> c_switch >> c_r;
    int t = 5;
    while (t--) {
        solve();
    }
}
