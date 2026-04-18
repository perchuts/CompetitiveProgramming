#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
//#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	int p, m, n;
	while (cin >> p >> m >> n) {
		if (p+n+m == 0) break;
		map<char, int> naipe;
		naipe['C'] = 0;
		naipe['D'] = 1;
		naipe['H'] = 2;
		naipe['S'] = 3;
		vector<vector<array<int, 2>>> v(p, vector<array<int, 2>>(m));
		vector<array<int, 2>> deck(n);
		for (int i = 0; i < n; ++i) {
			char c; cin >> deck[i][0] >> c;
			deck[i][1] = naipe[c];
		}
		reverse(begin(deck), end(deck));
		for (int i = 0; i < p; ++i) {
			for (int j = 0; j < m; ++j) { 
				v[i][j] = deck.back();
				deck.pop_back();
			}
		}
		array<int, 2> cur_card = deck.back(); deck.pop_back();
		int order = (cur_card[0] == 12 ? -1 : 1), cur_player = 0;
		auto draw_card = [&] (int i) {
			array<int, 2> add = deck.back(); deck.pop_back();
			v[i].push_back(add);
		};
		auto pass_round = [&] () { 
			cur_player = (p + cur_player + order) % p;
		};
		int last_apply = -1, cur_play = 0;
		auto apply_penalty = [&] () {
			if (last_apply == cur_play) return 0;
			last_apply = cur_play;
			if (cur_card[0] == 7) {
				draw_card(cur_player);
				draw_card(cur_player);
				return 1;
			}
			if (cur_card[0] == 1) {
				draw_card(cur_player);
				return 1;
			}
			if (cur_card[0] == 11) {
				return 1;
			}
			return 0;
		};
		int winner = -1;
		while (true) {
			if (apply_penalty()) {
				pass_round();
				continue;
			}
			auto get_card = [&] () {
				array<int, 2> opt; opt[0] = opt[1] = -1;
				int id = -1;
				for (int i = 0; i < v[cur_player].size(); ++i) {
					if (cur_card[0] == v[cur_player][i][0] or cur_card[1] == v[cur_player][i][1]) {
						if (opt[0] < v[cur_player][i][0] or (opt[0] == v[cur_player][i][0] and opt[1] < v[cur_player][i][1])) {
							id = i;
							opt = v[cur_player][i];
						}
					}
				}
				return id;
			};
			auto play_card = [&] (int id) {
				cur_card = v[cur_player][id];
				if (cur_card[0] == 12) order *= -1;
				cur_play++;
				v[cur_player].erase(begin(v[cur_player]) + id);
			};
			int id = get_card();
			if (id != -1) play_card(id);
			else {
				draw_card(cur_player);
				id = get_card();
				if (id != -1) play_card(id);
			}
			if (v[cur_player].empty()) {
				winner = cur_player;
				break;
			}
			pass_round();
		}
		cout << winner+1 << endl;
	}
}
