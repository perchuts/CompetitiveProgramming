#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

typedef array<array<int,9>,9> tab;

using T = __int128;
set<T> sol;
void g(tab t){

	for(auto& x : t) for(auto& y : x) if(y != 1) y = 0;
	//for(int i=0;i<9;i++){
	//	for(int j=0;j<9;j++) cout << t[i][j];
	//	cout << endl;
	//}
	//cout << endl;
	T ans = 1;
	for(int i=0;i<100;i++) ans *= 2;
	for(int r=0;r<2;r++){
		for(int s=0;s<4;s++){
			T p2 = 1;
			T x = 0;
			for(int i=0;i<9;i++) for(int j=0;j<9;j++){
				x += p2 * t[i][j];
				p2 *= 2;
			}
			ans = min(ans, x);
			tab nx;
			for(int i=0;i<9;i++){
				for(int j=0;j<9;j++){
					nx[i][j] = t[8-j][i];
				}
			}
			t = nx;
		}
		for(int i=0;i<4;i++) for(int j=0;j<9;j++) swap(t[i][j], t[8-i][j]);
	}
	sol.insert(ans);
}

void f(int i, int j, int k, tab t){

	if(k == 9){
		g(t);
		return;
	}
	if(i==9) return;

	int ni = i, nj = j+1;
	if(nj == 9) nj=0, ni++;

	f(ni, nj, k, t);
	if(t[i][j] == 2) return;

	for(int a=0;a<9;a++) t[i][a] = 2;
	for(int b=0;b<9;b++) t[b][j] = 2;
	for(int c=-9;c<9;c++){
		int pi = i+c, pj = j+c;
		if(min(pi, pj)>=0 && max(pi, pj) < 9) t[pi][pj] = 2;
	}
	for(int c=-9;c<9;c++){
		int pi = i+c, pj = j-c;
		if(min(pi, pj)>=0 && max(pi, pj) < 9) t[pi][pj] = 2;
	}

	t[i][j] = 1;
	f(ni, nj, k+1, t);
}

void pr(T x){
	vector<int> ans;
	while(x){
		ans.push_back(x%10);
		x /= 10;
	}
	reverse(ans.begin(), ans.end());
	cout << "\"";
	for(auto x : ans) cout << x;
	cout << "\"," << endl;
}

int32_t main() {_
	tab t;
	for(int i=0;i<9;i++) for(int j=0;j<9;j++) t[i][j] = 0;
	f(0, 0, 0, t);
	for(auto x : sol) pr(x);
}
