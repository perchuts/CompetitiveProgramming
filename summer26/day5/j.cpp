#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back
using namespace std;

using ll = long long;

int32_t main() {_

	vector<string> rom(4000);
	
	vector<string> un = {".", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
	vector<string> de = {".", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
	vector<string> ce = {".", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
	vector<string> mi = {".", "M", "MM", "MMM"};

	for(int ii=1;ii<4000;ii++){
		int i =ii;
		int d0 = i%10;
		i/=10;
		int d1 = i%10;
		i/=10;
		int d2 = i%10;
		i/=10;
		int d3 = i%10;
		string s;
		if(d3 > 0) s += mi[d3];
		if(d2 > 0) s += ce[d2];
		if(d1 > 0) s += de[d1];
		if(d0 > 0) s += un[d0];
		
		rom[ii] = s;
	}
	
	vector<vector<vector<int>>> td(7, vector<vector<int>>(4, vector<int>(4000)));
	vector<vector<vector<int>>> pr(7, vector<vector<int>>(4, vector<int>(4000)));
	vector<vector<vector<int>>> su(7, vector<vector<int>>(4, vector<int>(4000)));
	vector<vector<vector<int>>> in(7, vector<vector<int>>(4, vector<int>(4000)));
	vector<vector<vector<int>>> co(7, vector<vector<int>>(4, vector<int>(4000)));

	vector<char> v = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

	for(int c=0;c<7;c++){
		for(int i=1;i<4000;i++){
			string x = rom[i];		
			int m = x.size();
			int ok = 1;
			for(int j=0;j<m;j++){
				if(x[j] != v[c]) ok = 0;
			}
			if(ok){
				assert(m <= 3);
				td[c][m][i]++;
				continue;
			}
			for(int j=0;j<m;j++){
				if(x[j] != v[c]){
					if(j >= 1){
						pr[c][j][i]++;
					}
					break;
				}
			}
			for(int j=0;j<m;j++){
				if(x[m-1-j] != v[c]){
					if(j >= 1){
						su[c][j][i]++;
					}
					break;
				}
			}
			if(pr[c][1][i] && su[c][1][i]) co[c][1][i] = 1;
			if(pr[c][2][i] && su[c][1][i]) co[c][2][i] = 1;
			if(pr[c][3][i] && su[c][1][i]) co[c][3][i] = 1;

			int infix = 0;
			int mxinfix = 0;
			for(int j=0;j<m;j++){
				if(x[j] == v[c]) infix++;
				else infix = 0;
				mxinfix = max(mxinfix, infix);
			}
			if(mxinfix > 0){
				in[c][mxinfix][i]++;
			}
		}
	}

	for(int c=0;c<7;c++){
		for(int m=0;m<4;m++){
			for(int i=1;i<4000;i++){
				td[c][m][i] += td[c][m][i-1];
				pr[c][m][i] += pr[c][m][i-1];
				su[c][m][i] += su[c][m][i-1];
				in[c][m][i] += in[c][m][i-1];
				co[c][m][i] += co[c][m][i-1];
			}
		}
	}

	int t; cin >> t;
	while(t--){
		int l, r; cin >> l >> r;
		int ans = 0;
		for(int c=0;c<7;c++){

			int ansc = 0;
			int td1 = td[c][1][r] - td[c][1][l-1];
			int td2 = td[c][2][r] - td[c][2][l-1];
			int td3 = td[c][3][r] - td[c][3][l-1];
			
			ansc += td1 + 2*td2 + 3*td3;

			int pr1 = pr[c][1][r] - pr[c][1][l-1];
			int pr2 = pr[c][2][r] - pr[c][2][l-1];
			int pr3 = pr[c][3][r] - pr[c][3][l-1];

			if(pr3) ansc += 3;
			else if(pr2) ansc += 2;
			else if(pr1) ansc += 1;

			int su1 = su[c][1][r] - su[c][1][l-1];
			int su2 = su[c][2][r] - su[c][2][l-1];
			int su3 = su[c][3][r] - su[c][3][l-1];

			if(su3) ansc += 3;
			else if(su2) ansc += 2;
			else if(su1) ansc += 1;

			int co1 = co[c][1][r] - co[c][1][l-1];
			int co2 = co[c][2][r] - co[c][2][l-1];
			int co3 = co[c][3][r] - co[c][3][l-1];

			int in1 = in[c][1][r] - in[c][1][l-1];
			int in2 = in[c][2][r] - in[c][2][l-1];
			int in3 = in[c][3][r] - in[c][3][l-1];

			//cout << td3 << " " << td2 << " " << td1 << endl;
			//cout << su3 << " " << su2 << " " << su1 << endl;
			//cout << pr3 << " " << pr2 << " " << pr1 << endl;
			//cout << co3 << " " << co2 << " " << co1 << endl;
			//cout << in3 << " " << in2 << " " << in1 << endl;

			if(su3 == 0 && su2 == 0 && su1 == 1){
				if(pr3 == 1 && co3 == 1) ansc--;
				else if(pr3 == 0 && pr2 == 1 && co2 == 1) ansc--;
				else if(pr3 == 0 && pr2 == 0 && pr1 == 1 && co1 == 1) ansc--;
			}
			
			if(in3) ansc = max(ansc, 3ll);
			if(in2) ansc = max(ansc, 2ll);
			if(in1) ansc = max(ansc, 1ll);

			ans = max(ans, ansc);
		}
		cout << ans << endl;
	}


}
