#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using ll = long long;
using namespace std;

int f(char c){
	return c > '9' ? c - 'A' + 10 : c - '0';
}
char g(int x){
	return x > 9 ? x - 10 + 'A' : x + '0';
}

int32_t main() {_

	int n; cin >> n;
		string s; cin >> s;
	while(n--){
		if(s[0] == 'e'){
			vector<int> bits(64);
			for(int i=0;i<16;i++){
				char c; cin >> c;
				int x = f(c);
				for(int j=0;j<4;j++) bits[4*i+j] = (x>>j)&1;
			}

			vector<int> msg(9);
			for(int i=0;i<9;i++){
				for(int j=0;j<7;j++){
					msg[i] |= bits[i*7+j] << j;
				}
			}
			if(bits[63]){
				for(int i=0;i<9;i++) msg[i] ^= (1<<7);
			}


			for(int i=0;i<18;i++){
				if(i % 2 == 0){
					cout << g(msg[i/2] & 15);
				}
				else{
					cout << g((msg[i/2]>>4) & 15);
				}
			}
			cout << endl;
			
		}
		else{

			vector<int> msg(9);
			for(int i=0;i<9;i++){
				char x1, x2; cin >> x1 >> x2;
				msg[i] = f(x1) + (f(x2) << 4);
			}

			int cnt = 0;
			for(int i=0;i<9;i++){
				cnt += (msg[i] >> 7)&1;
			}

			vector<int> bits(64);
			if(cnt > 4){
				//cout << "CNT" << endl;
				bits[63] = 1;
				for(int i=0;i<9;i++) msg[i] ^= (1<<7);
			}

			for(int i=0;i<9;i++){
				for(int j=0;j<7;j++){
					bits[i*7 + j] = ((msg[i]>>j)&1) ^ ((msg[i]>>7)&1);
				}
			}
			
			for(int i=0;i<16;i++){
				int x = 0;
				for(int j=0;j<4;j++) x += bits[i*4+j]<<j;
				cout << g(x);
			}
			cout << endl;


		}

	}
}
