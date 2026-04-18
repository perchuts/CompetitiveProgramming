#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define endl '\n'
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

using ll = long long;


int marc[10][10][10][10][10];

int32_t main() {_

	int n; cin >> n;
	int q = n / 10;
	int r = n % 10;
	for(int i1=0;i1<10;i1++){
	for(int i2=0;i2<10;i2++){
	for(int i3=0;i3<10;i3++){
	for(int i4=0;i4<10;i4++){
	for(int i5=0;i5<10;i5++){
		if(q == 0) goto fora;
		if(marc[i1][i2][i3][i4][i5]) continue;
		if((n < 100000) && (i2+10-i1) % 10 == 1 &&
		(i3+10-i2) % 10 == 1 &&
		(i4+10-i3) % 10 == 1 &&
		(i5+10-i4) % 10 == 1) continue;

		for(int k=0;k<10;k++){
			int d1 = (i1+k)%10;
			int d2 = (i2+k)%10;
			int d3 = (i3+k)%10;
			int d4 = (i4+k)%10;
			int d5 = (i5+k)%10;
			marc[d1][d2][d3][d4][d5]  = 1;
			cout << d1 << d2 << d3 << d4 << d5;
			cout << endl;
		}
		q--;
	}
	}
	}
	}
	}
fora:
	for(int i=0;i<r/2;i++){
		for(int x=0;x<5;x++){
			cout << (i+x)%10;
		}
		cout << endl;
		for(int x=0;x<5;x++){
			cout << (i+5+x)%10;
		}
		cout << endl;
	}
	if(r%2){
		cout << 45678 << endl;
	}

}
