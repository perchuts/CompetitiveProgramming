#include <bits/stdc++.h>
//#define stress
using namespace std;
#define endl '\n'
#define int ll
#define INF 100000
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;
//int MAX = 1000000+1;
int MAX = 100+1;
vector<int> solve(int n, vector<int> v) {
	vector<pair<int, int>> sexo(MAX+1);
	vector<int> primos;
	for (int i = 2; i <= MAX; ++i) {
		if (sexo[i].first == 0) {
			sexo[i].first = i;
			primos.push_back(i);
			for (int j = 2*i; j <= MAX; j += i) sexo[j].first = i;	
			sexo[i].second = 1;
		} else {
			int prox = i / sexo[i].first;
			if (sexo[prox].first == sexo[i].first) sexo[i].second = sexo[prox].second;
			else sexo[i].second = prox;
		}
	}
	vector<pair<int, int>> mark(MAX+1, make_pair(-1, -1));
	int idd = 0;
	for (auto& x : v) {
		if (mark[x].first == -1) mark[x].first = idd;
		else if (mark[x].second == -1) mark[x].second = idd;
		idd++;
	}
	vector<vector<pair<int, int>>> dist(MAX+1, vector<pair<int, int>>(2, make_pair(1010, INF)));
	for (int i = 0; i < n; ++i) {
		if (dist[v[i]][0].second == INF) dist[v[i]][0] = {0, i};
		else if (dist[v[i]][1].second == INF) dist[v[i]][1] = {0, i};
	}
	for (int i = MAX; i >= 1; --i) {
		// quero atualizar as dists do i
		// olho para os meus multiplos
		// tem dois casos: sou inicial ou nao

		if(dist[i][0].second != INF){
			// sou bicho inicial
			// quero soh achar o bicho com o melhor dist[outro][0]
			int melhor = INF;
			int id = INF;
			for(auto p : primos){
				if(p * i > MAX) break;
				int outro = p*i;
				if(dist[outro][0].second == INF) continue;
				if(dist[outro][0].first + 1 < melhor){
					melhor = dist[outro][0].first + 1;
					id = dist[outro][0].second;
				}
				else if(dist[outro][0].first + 1 == melhor && dist[outro][0].second < id){
					melhor = dist[outro][0].first + 1;
					id = dist[outro][0].second;
				}


			}
			if(id != INF){
				dist[i][1].first = melhor;
				dist[i][1].second = id;
			}
			continue;
		}
		// quero achar os dois melhores bichos
		// primeiro o melhor
		int melhor = INF;
		int id = INF;
		for(auto p : primos){
			if(p * i > MAX) break;
			int outro = p*i;
			if(dist[outro][0].second == INF) continue;
			if(dist[outro][0].first + 1 < melhor){
				melhor = dist[outro][0].first + 1;
				id = dist[outro][0].second;
			}
			else if(dist[outro][0].first + 1 == melhor && dist[outro][0].second < id){
				melhor = dist[outro][0].first + 1;
				id = dist[outro][0].second;
			}
		}
		if(id != INF){
			dist[i][0].first = melhor;
			dist[i][0].second = id;
		}
		// agora o segundo melhor, so que o id tem que ser diferente (e eu posso usar o [outro][1])
		int smelhor = INF;
		int sid =  INF;
		for(auto p : primos){
			if(p * i > MAX) break;
			int outro = p*i;
			if(dist[outro][0].second == INF || dist[outro][0].second == id) goto prox;
			if(dist[outro][0].first + 1 < smelhor){
				smelhor = dist[outro][0].first + 1;
				sid = dist[outro][0].second;
			}
			else if(dist[outro][0].first + 1 == smelhor && dist[outro][0].second < sid){
				smelhor = dist[outro][0].first + 1;
				sid = dist[outro][0].second;
			}
prox:
			if(dist[outro][1].second == INF || dist[outro][1].second == id)  continue;
			if(dist[outro][1].first + 1 < smelhor){
				smelhor = dist[outro][1].first + 1;
				sid = dist[outro][1].second;
			}
			else if(dist[outro][1].first + 1 == smelhor && dist[outro][1].second < sid){
				smelhor = dist[outro][1].first + 1;
				sid = dist[outro][1].second;
			}
		}
		if(sid != INF){
			dist[i][1].first = smelhor;
			dist[i][1].second = sid;
		}
	}

	//for (int i = 1; i <= 6; ++i) {
	//	cout << dist[i][0].first << ' ' << dist[i][0].second << " +++ " << dist[i][1].first << ' ' << dist[i][1].second << endl;
	//}
	vector<int> factors(MAX+1);
	for (int i = 2; i <= MAX; ++i) {
		factors[i] = 1 + factors[i/sexo[i].first];
	}
	vector<int> respp;
	for (int i = 0; i < n; ++i) {
		int ans = 1010, id_min = -1;
		if (mark[v[i]].second != -1) {
			respp.push_back((mark[v[i]].first == i ? mark[v[i]].second : mark[v[i]].first)+1);
			continue;
		}
		for (int j = 1; j * j <= v[i]; ++j) {
			if (v[i] % j) continue;
			for (int w = 0; w < 2; ++w) {
				auto [x1, y1] = dist[j][0];
				auto [x2, y2] = dist[j][1];
				if (y1 != INF and y1 != i) {
					if (ans > x1+factors[v[i]/j]) ans = x1 + factors[v[i]/j], id_min = y1;
					else if (ans == x1+factors[v[i]/j] and id_min > y1) id_min = y1;
				}
				if (y2 != INF and y2 != i) {
					if (ans > x2+factors[v[i]/j]) ans = x2 + factors[v[i]/j], id_min = y2;
					else if (ans == x2+factors[v[i]/j] and id_min > y2) id_min = y2;
				}
				j = v[i] / j;
			}
		}
			//cout << i << endl;
			//cout.flush();
		assert(ans != 1010);
		respp.push_back(id_min+1);
	}
	return respp;
}
int32_t main() {
	fast_io
#ifdef stress
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
		int n = rand() % 5 + 2;
		vector<int> v(n);
		for (auto& x : v) x = rand() % MAX+1;
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
			int mybest = 100000, idb = 10000;
			for (int j = 0; j < n; ++j) {
				if (i == j) continue;
				if (mybest > calc(i, j)) idb = j, mybest = calc(i, j);
			}
			if (idb+1 != my[i]) {
				cout << "Wrong answer on test " << t << endl;
				for (auto z : my) cout << z << endl;
				cout << "Wrong in answer for i = " << i << endl;
				cout << "best is " << idb+1 << " you printed " << my[i] << endl;
				exit(0);
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
