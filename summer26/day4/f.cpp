#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

const int LIM = 1000000000;

int32_t main() {_
	int lo = 0, hi = LIM;

	auto ask = [&](int a1, int a2, int b1, int b2){
		cout << "? " << a1 << " " << b1 << " " << a2 << " " << b2 << endl;
	};

	while (lo+1 < hi){
		int mid = (lo+hi)/2;
		ask(1,mid,1,LIM);
		int x; cin >> x;
		int ex = mid * LIM;
		if (x > ex) hi = mid;
		else lo = mid;
	}
	int v1 = hi;

	lo = 0, hi = LIM;
	while (lo+1 < hi){
		int mid = (lo+hi)/2;
		ask(v1,v1,1,mid);
		int x; cin >> x;
		int ex = mid;
		if (x > ex) hi = mid;
		else lo = mid;
	}
	int v2 = hi;

	lo = 0, hi = LIM;
	while (lo+1 < hi){
		int mid = (lo+hi)/2;
		ask(1,mid,1,LIM);
		int x; cin >> x;
		int ex = mid * LIM;
		if (v1 <= mid) ex++;
		if (x > ex) hi = mid;
		else lo = mid;
	}
	int u1 = hi;

	lo = 0, hi = LIM;
	while (lo+1 < hi){
		int mid = (lo+hi)/2;
		ask(u1,u1,1,mid);
		int x; cin >> x;
		int ex = mid;
		if (u1 == v1 and v2 <= mid) ex++;
		if (x > ex) hi = mid;
		else lo = mid;
	}
	int u2 = hi;

	cout << "! " << v1 << " " << v2 << " " << u1 << " " << u2 << endl;
}
