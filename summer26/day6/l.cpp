#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back
#define PI pair<int,int>

using namespace std;

using ll = long long;

struct Data{
	int cont, val;
	int lef, rig;
	int lp, rp;
};

void solve(int n, vector<int> vals){
	sort(vals.begin(), vals.end());
	vector<Data> vec;

	priority_queue<PI,vector<PI>,greater<PI>> pq;
	for (int i = 0; i < n-1; ++i){
		Data novo;
		novo.cont = novo.val = vals[i+1]-vals[i];
		if (i) novo.lef = i-1;
		else novo.lef = -1;
		if (i < n-2) novo.rig = i+1;
		else novo.rig = -1;
		novo.lp = i, novo.rp = i+1;
		vec.pb(novo);
		pq.push({novo.cont,i});
	}

	int ans = 0;
	vector<int> resp;
	vector<bool> mat(n);

	while (!pq.empty()){
		auto [v,id] = pq.top(); pq.pop();
		if (mat[vec[id].lp] or mat[vec[id].rp]) continue;
		ans += v;
		resp.pb(ans);
		Data cur = vec[id];
		mat[cur.lp] = true, mat[cur.rp] = true;
		if (cur.lef == -1 or cur.rig == -1) continue;

		Data novo;
		int c = (int)(vec.size());
		novo.val = vec[cur.lef].val + vec[cur.rig].val - cur.val + vals[cur.rp] - vals[cur.lp];
		novo.lp = vec[cur.lef].lp, novo.rp = vec[cur.rig].rp;
		/*
		cout << "!" << endl;
		cout << cur.lp << " " << cur.rp << endl;
		cout << vec[cur.lef].lp << " " << vec[cur.lef].rp << endl;
		cout << vec[cur.rig].lp << " " << vec[cur.rig].rp << endl;
		cout << novo.lp << " " << novo.rp << endl;
		*/
		novo.lef = vec[cur.lef].lef, novo.rig = vec[cur.rig].rig;
		if (vec[cur.lef].lef+1) vec[vec[cur.lef].lef].rig = c;
		if (vec[cur.rig].rig+1) vec[vec[cur.rig].rig].lef = c;
		vec[cur.lef].rig = c, vec[cur.rig].lef = c;
		int aux = -(novo.val - vals[novo.rp] + vals[novo.lp]);
		novo.cont = novo.val-aux;

		vec.pb(novo);
		pq.push({novo.cont,c});
	}

	for (auto v : resp) cout << v << " ";
	cout << endl;
}

mt19937 rng(time(0));

int32_t main(){_
	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i) cin >> v[i];
	solve(n,v);
	return 0;
}

