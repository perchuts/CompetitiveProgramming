#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;
#define LINF 1e18

int32_t main() {
	fast_io;
	int n; cin >> n;
	using Pt = array<int,2>;

	vector<Pt> v(n);
	for(auto& [x, y]: v) cin >> x >> y;

	set<Pt> pontos;
	for(auto pt : v) pontos.insert(pt);



	int ymax = -LINF, ymin = LINF;
	for(auto [x, y] : v) ymax = max(ymax, y), ymin = min(ymin, y);
	
	int Q = -1;


	if(ymax == ymin){
		sort(v.begin(), v.end());
		cout << n+1 << endl;
		for(auto [x, y] : v) cout << x << " " << y << endl;
		if(ymax == 1) cout << 1 << " " << 2 << endl;
		else cout << 1 << " " << ymax-1 << endl;
		return 0;
	}

	for(auto [x, y] : v) if(x > -Q+1 && y > ymin && y < ymax){
		pontos.insert({-Q+1, y});
		pontos.insert({-Q+1, y-1});
	}

	pontos.insert({-Q, ymax});
	pontos.insert({-Q+1, ymax-1});
	pontos.insert({-Q+1, ymin+1});
	pontos.insert({-Q, ymin});

	set<Pt> esq;
	for(auto pt : pontos) if(pt[0] == -Q) esq.insert(pt);
	set<Pt> outros;
	for(auto pt : pontos) if(pt[0] != -Q && pt[1] > ymin) {
		outros.insert({-pt[1], pt[0]});
	}
	set<Pt> baixo;
	for(auto pt : pontos) if(pt[0] != -Q && pt[1] == ymin){
		baixo.insert({-pt[0], pt[1]});
	}

	cout << pontos.size() << endl;
	for(auto [x, y] : esq) cout << x << " " << y << endl;
	for(auto [y, x] : outros) cout << x << " " << -y << endl;
	for(auto [x, y] : baixo) cout << -x << " " << y << endl;

}
