#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
//#define endl '\n'
#define int long long
const int INF = 1e18;

mt19937_64 rng(98723);

int32_t main(){

	//while(1){

		//int y = rng() % 100000000;
		//cout << y << ": ";
		//cout.flush();
		int y, l;
		cin >> y >> l;
		int fct = 1;
		int ans = 1;
		while(1){
			if(y == 1){

				// x eh 0
				ans += fct * l;
				break;
			}
			int menor_div = -1;
			for(int i=2;i*i<=y;i++){
				if(y % i == 0){
					menor_div = i;
					break;
				}
			}
			if(menor_div == -1) menor_div = y;
			if(menor_div - 1 < l){
				// ele nao acaba
				l -= (menor_div - 1);
				ans += fct * (menor_div - 1);
				fct *= menor_div;
				y /= menor_div;
			}
			else{
				// acaba agora!
				ans += fct * l;
				break;
			}
		}


		cout << ans << endl;

	//}

}
