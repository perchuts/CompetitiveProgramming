#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int n, m;
vector<string> a;
int C;

vector<string> solve1(){
	int pref = 0;
	for(int i=n-1; i>=0; i--){
		vector<int> pos;
		for(int j=0; j<m; j++) if(a[i][j] == 'C') pos.push_back(j);
		int cnt = pos.size();
 
		if(pref + cnt == C/2){
			auto b = a;
			for(int k=n-1; k>=i; k--) for(int l=0; l<m; l++) if(a[k][l] != '#') b[k][l] = 'A';
			for(int k=i-1; k>=0; k--) for(int l=0; l<m; l++) if(a[k][l] != '#') b[k][l] = 'B';
 
			return b;
		}
		if(pref + cnt > C/2){
			int v = C/2 - pref;
			assert(cnt >= v+1);
 
			if(i == n-1){
				if(1 < v and v == cnt-1 and a[n-1][0] == 'C' and a[n-1][m-1] == 'C'){
					return {};
				}
 
				auto b = a;
 
				if(pos[v-1]+2 < m){
					for(int l=0; l<=pos[v-1]; l++) if(a[i][l] != '#') b[i][l] = 'A';
					for(int l=pos[v-1]+1; l<m; l++) if(a[i][l] != '#') b[i][l] = 'B';
				}
				else{
					assert(pos[cnt-v]-2 >= 0);
					for(int l=0; l<pos[cnt-v]; l++) if(a[i][l] != '#') b[i][l] = 'B';
					for(int l=pos[cnt-v]; l<m; l++) if(a[i][l] != '#') b[i][l] = 'A';
				}
 
				for(int k=i-1; k>=0; k--) for(int l=0; l<m; l++) if(a[k][l] != '#') b[k][l] = 'B';
 
				return b;
			}
 
			if(v >= 2){
				auto b = a;
				for(int k=n-1; k>=i+1; k--) for(int l=0; l<m; l++) if(a[k][l] != '#') b[k][l] = 'A';
 
				for(int l=0; l<=pos[v-2]; l++) if(a[i][l] != '#') b[i][l] = 'A';
				for(int l=pos[v-2]+1; l<pos.back(); l++) if(a[i][l] != '#') b[i][l] = 'B';
				for(int l=pos.back(); l<m; l++) if(a[i][l] != '#') b[i][l] = 'A';
 
				for(int k=i-1; k>=0; k--) for(int l=0; l<m; l++) if(a[k][l] != '#') b[k][l] = 'B';
 
				return b;
			}
			else{
				assert(v == 1);
 
				auto b = a;
				for(int k=n-1; k>=i+1; k--) for(int l=0; l<m; l++) if(a[k][l] != '#') b[k][l] = 'A';
 
				if(pos[0]+2 < m and a[i][pos[0]+2] != '#'){
					for(int l=0; l<=pos[0]; l++) if(a[i][l] != '#') b[i][l] = 'A';
					for(int l=pos[0]+1; l<m; l++) if(a[i][l] != '#') b[i][l] = 'B';
				}
				else{
					for(int l=0; l<=pos[0]; l++) if(a[i][l] != '#') b[i][l] = 'B';
					for(int l=pos[0]+1; l<m; l++) if(a[i][l] != '#') b[i][l] = 'A';
				}
 
				for(int k=i-1; k>=0; k--) for(int l=0; l<m; l++) if(a[k][l] != '#') b[k][l] = 'B';
				return b;
			}
		}
 
		pref += cnt;
	}
	assert(false);
}

vector<string> solve2(){
	int pref = 0;
	for(int j=0; j<m; j++){
		vector<int> pos;
		for(int i=0; i<n; i++) if(a[i][j] == 'C') pos.push_back(i);

		if(pref + pos.size() == C/2){
			auto b = a;
			for(int k=0; k<=j; k++) for(int i=0; i<n; i++) if(a[i][k] != '#') b[i][k] = 'A';
			for(int k=j+1; k<m; k++) for(int i=0; i<n; i++) if(a[i][k] != '#') b[i][k] = 'B';
			return b;
		}
		if(pref + pos.size() > C/2){
			int v = C/2 - pref;
			assert(v >= 1);
			assert(v < pos.size());

			if(j < n-1){ 
				// bottom
				auto b = a;
				for(int k=0; k<j; k++) for(int i=0; i<n; i++) if(a[i][k] != '#') b[i][k] = 'A';

				for(int i=0; i<pos[pos.size()-v]; i++) if(a[i][j] != '#') b[i][j] = 'B';
				for(int i=pos[pos.size()-v]; i<n; i++) if(a[i][j] != '#') b[i][j] = 'A';

				for(int k=j+1; k<m; k++) for(int i=0; i<n; i++) if(a[i][k] != '#') b[i][k] = 'B';
				return b;
			}
			if(j == n-1){
				if(pos.size() == 2 and pos[0] == 0 and pos[1] == 1){
					if(C == 2){
						auto b = a;
						for(int i=0; i<n; i++) for(int k=0; k<m; k++) if(a[i][k] != '#') b[i][k] = 'B';
						b[0][n-1] = 'A';
						return b;
					}

					return {};
				}
				if(v >= 2){
					// top
					auto b = a;
					for(int k=0; k<j; k++) for(int i=0; i<n; i++) if(a[i][k] != '#') b[i][k] = 'A';

					for(int i=0; i<=pos[v-1]; i++) if(a[i][j] != '#') b[i][j] = 'A';
					for(int i=pos[v-1]+1; i<n; i++) if(a[i][j] != '#') b[i][j] = 'B';

					for(int k=j+1; k<m; k++) for(int i=0; i<n; i++) if(a[i][k] != '#') b[i][k] = 'B';
					return b;
				}
				if(v == 1){
					// bottom
					auto b = a;
					for(int k=0; k<j; k++) for(int i=0; i<n; i++) if(a[i][k] != '#') b[i][k] = 'A';

					for(int i=0; i<pos[pos.size()-v]; i++) if(a[i][j] != '#') b[i][j] = 'B';
					for(int i=pos[pos.size()-v]; i<n; i++) if(a[i][j] != '#') b[i][j] = 'A';

					for(int k=j+1; k<m; k++) for(int i=0; i<n; i++) if(a[i][k] != '#') b[i][k] = 'B';
					return b;
				}
			}
			if(j > n-1){
				// top
				auto b = a;
				for(int k=0; k<j; k++) for(int i=0; i<n; i++) if(a[i][k] != '#') b[i][k] = 'A';

				for(int i=0; i<=pos[v-1]; i++) if(a[i][j] != '#') b[i][j] = 'A';
				for(int i=pos[v-1]+1; i<n; i++) if(a[i][j] != '#') b[i][j] = 'B';

				for(int k=j+1; k<m; k++) for(int i=0; i<n; i++) if(a[i][k] != '#') b[i][k] = 'B';
				return b;
			}

			assert(false);
		}

		pref += pos.size();
	}

	assert(false);
}

int main() { _
	cin >> n;
	m = 2*n-1;
	a = vector<string>(n);
	for(int i=0; i<n; i++) cin >> a[i];

	C = 0;
	for(int i=0; i<n; i++) 
		for(int j=0; j<m; j++) 
			if(a[i][j] == 'C') C++;

	if(C&1){
		cout << "impossible" << endl;
		exit(0);
	}

	auto b1 = solve1();
	if(b1.size() != 0){
		for(auto s : b1) cout << s << endl;
		exit(0);
	}

	auto b2 = solve2();
	if(b2.size() != 0){
		for(auto s : b2) cout << s << endl;
		exit(0);
	}
	cout << "impossible" << endl;

	exit(0);
}

