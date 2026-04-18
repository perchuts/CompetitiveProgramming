#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back
using namespace std;

using ll = long long;


using pt = array<int,2>;
using line = array<pt,2>;

pt operator - (pt p, pt q){
	return pt{p[0] - q[0], p[1] - q[1]};
}

int area(pt a, pt b, pt c){
	pt v = (a-b);
	pt w = (a-c);
	return v[0]*w[1] - v[1]*w[0];
}

void solve(int n){

	vector<vector<line>> tring(n-2);
	for(int i=0;i<n-2;i++){
		pt A, B, C;
		cin >> A[0] >> A[1] >> B[0] >> B[1] >> C[0] >> C[1];
		line r, s, t;
		r = {A, B};
		s = {B, C};
		t = {C, A};
		tring[i] = {r, s, t};
	}
	for(auto& tr : tring){
		sort(tr.begin(), tr.end());	
		for(auto& l : tr){
			if(l[0] > l[1]) swap(l[0], l[1]);
		}
	}
	map<line,int> mp;
	for(auto& tr : tring){
		for(auto& l : tr){
			mp[l]++;
		}
	}
	vector<line> ans;
	map<pt,vector<line>> coiso;
	for(auto& tr : tring){
		for(auto& l : tr){
			if(mp[l] == 1){
				ans.push_back(l);
				coiso[l[0]].push_back(l);
				coiso[l[1]].push_back(l);
			}
		}
	}

	sort(ans.begin(), ans.end());
	vector<pt> poly;
	line at = ans[0];
	poly.push_back(ans[0][0]);
	for(int i=1;i<n;i++){
		pt prev = poly.back();
		for(auto l : coiso[prev]){
			if(l != at){
				for(auto q : l) if(q != prev) poly.push_back(q);
				at = l;
				break;
			}
		}
	}


	int A = 0;
	for(int i=1;i<n-1;i++){
		A += area(poly[0], poly[i], poly[i+1]);
	}
	if(A>0) reverse(poly.begin()+1, poly.end());

	for(auto p : poly) cout << p[0] << " " << p[1] << " ";
	cout << endl;


}

int32_t main() {_

	while(1){
		int n; cin >> n;
		if(n == -1) return 0;
		solve(n);
	}
}
