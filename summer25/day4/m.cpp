#include <bits/stdc++.h>
//#define stress
using namespace std;
#define endl '\n'
#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;
vector<int> solve(int n, vector<int> v) {
	int MAX = 1000000+69;
	vector<pair<int, int>> sexo(MAX+1);
	for (int i = 2; i <= MAX; ++i) {
		if (sexo[i].first == 0) {
			sexo[i].first = i;
			for (int j = 2*i; j <= MAX; j += i) sexo[j].first = i;	
			sexo[i].second = 1;
		} else {
			int prox = i / sexo[i].first;
			if (sexo[prox].first == sexo[i].first) sexo[i].second = sexo[prox].second;
			else sexo[i].second = prox;
		}
	}
	vector<vector<pair<int, int>>> dist(MAX+1, vector<pair<int, int>>(2, make_pair(1010, -1)));
	for (int i = 0; i < n; ++i) {
		if (dist[v[i]][0].second == -1) dist[v[i]][0] = {0, i};
		else dist[v[i]][1] = {0, i};
	}
	for (int i = MAX; i >= 2; --i) {
		auto [d1, id1] = dist[i][0];
		auto [d2, id2] = dist[i][1];
		if (id1 == -1) { assert(id2 == -1); continue; }
		assert(id1 != id2);
		int cur = i;
		while (cur != 1) {
			auto [p, prox] = sexo[cur];
			int j = i / p;
			for (int w = 0; w < 2; ++w) {
				if (id1 != -1) {
					if (d1+1 < dist[j][1].first) {
						if (d1+1 <= dist[j][0].first) {
							if (dist[j][0].second == id1) {
								dist[j][0].first = d1+1; 
							} else {
								dist[j][1] = dist[j][0];
								dist[j][0] = {d1+1, id1};
							}
						} else if (dist[j][0].second != id1) dist[j][1] = {d1+1, id1};
					}
				}
				swap(d1, d2), swap(id1, id2);
			}
			cur = prox;
		}
	}
	vector<int> factors(MAX+1);
	for (int i = 2; i <= MAX; ++i) {
		factors[i] = 1 + factors[i/sexo[i].first];
	}
	vector<int> respp;
	for (int i = 0; i < n; ++i) {
		int ans = 1010, id_min = -1;
		for (int j = 1; j * j <= v[i]; ++j) {
			if (v[i] % j) continue;
			for (int w = 0; w < 2; ++w) {
				auto [x1, y1] = dist[j][0];
				auto [x2, y2] = dist[j][1];
				if (y1 != -1 and y1 != i) {
					if (ans > x1+factors[v[i]/j]) ans = x1 + factors[v[i]/j], id_min = y1;
				}
				if (y2 != -1 and y2 != i) {
					if (ans > x2+factors[v[i]/j]) ans = x2 + factors[v[i]/j], id_min = y2;
				}
				j = v[i] / j;
			}
		}
		assert(ans != 1010);
		respp.push_back(id_min+1);
	}
	return respp;
}
int32_t main() {
	fast_io
#ifdef stress
	int MAX = 1000000+69;
	int t = 1;
	while (true) {
	vector<pair<int, int>> mark(MAX+1, make_pair(-1LL, -1LL)); 
	vector<pair<int, int>> sexo(MAX+1);
	for (int i = 2; i <= MAX; ++i) {
		if (sexo[i].first == 0) {
			sexo[i].first = i;
			for (int j = 2*i; j <= MAX; j += i) sexo[j].first = i;	
			sexo[i].second = 1;
		} else {
			int prox = i / sexo[i].first;
			if (sexo[prox].first == sexo[i].first) sexo[i].second = sexo[prox].second;
			else sexo[i].second = prox;
		}
	}
		vector<int> factors(MAX+1);
	for (int i = 2; i <= MAX; ++i) {
		factors[i] = 1 + factors[i/sexo[i].first];
	}
		int n = rand() % 200 + 2;
		vector<int> v(n);
		for (auto& x : v) x = rand() % 1000000+1;
		cout << n << endl;
		for (auto z : v) cout << z << ' ';
		cout << endl;
		cout.flush();
		auto my = solve(n, v);
		auto calc = [&] (int i, int j) {
			assert(max(i, j) < n);
			int g = gcd(v[i], v[j]);
			return factors[v[i]/g] + factors[v[j]/g];
		};
		for (int i = 0; i < n; ++i) {
			int resp = calc(i, my[i]-1); 
			for (int j = 0; j < n; ++j) {
				if (i == j) continue;
				if (calc(i, j) < resp) {
					cout << "Wrong answer on test " << t << endl;
					for (auto z : my) cout << z << endl;
					cout << "Wrong in answer for i = " << i << endl;
					cout << "found dist = " << calc(i, j) << " for j = " << j+1 << endl;
					exit(0);
				}
			}
		}
		cout << "Accepted on test " << t++ << endl;
		cout.flush();
	}
#else
		int n; cin >> n;
		vector<int> v(n);
		for (auto& x : v) cin >> x;
		auto ans = solve(n, v);
		for (auto x : ans) cout << x << endl;
#endif
}
