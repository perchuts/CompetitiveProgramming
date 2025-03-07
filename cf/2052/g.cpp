#include <bits/stdc++.h>
using namespace std;

#define int __int128
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

using T = array<int,2>;
using Pt = array<T,2>;
using Seg = array<Pt,2>;

T operator + (T a, T b){
	return T({a[0]+b[0], a[1]+b[1]});
}
Pt operator + (Pt a, Pt b){
	return Pt({a[0]+b[0], a[1]+b[1]});
}
T operator - (T a, T b){
	return T({a[0]-b[0], a[1]-b[1]});
}
Pt operator - (Pt a, Pt b){
	return Pt({a[0]-b[0], a[1]-b[1]});
}

T operator * (int c, T a){
	return T{a[0]*c, a[1]*c};
}


Pt operator * (int c, Pt p) {
	return Pt{c*p[0], c*p[1]};
}

map<int, Pt> unit;

Pt rot45(Pt p) {
	Pt ret;
	int a, b, c, d;
	tie(a, b, c, d) = make_tuple(p[0][0], p[0][1], p[1][0], p[1][1]);

	ret[0][0] = (b - d) / 2;
	ret[0][1] = (a - c);
	ret[1][0] = (b + d) / 2;
	ret[1][1] = (a + c);

	return ret;
}

Seg rot45(Seg p) {
	return {rot45(p[0]), rot45(p[1])};
}

Pt rot90(Pt p) {
    return rot45(rot45(p));
}

Seg rot90(Seg p) {
	return {rot90(p[0]), rot90(p[1])};
}

Pt rot180(Pt p) {
    return rot90(rot90(p));
}

Seg rot180(Seg p) {
	return {rot180(p[0]), rot180(p[1])};
}

T operator * (T a, T b){
	return T{2*a[0]*b[0]+a[1]*b[1], a[0]*b[1]*2+a[1]*b[0]*2};
}

bool collinear(Pt a, Pt b, Pt c) {
    a = rot90(a - b);
    c = c - b;
    T x = a[0]*c[0];
    T y = a[1]*c[1];
    return (x[0]+y[0] == 0 and x[1]+y[1] == 0);
}

int32_t main() {
	fast_io;
	int32_t n; cin >> n;

	unit[0] = Pt{T{1, 0}, T{0, 0}};
	for (int i = 1; i < 8; i++) {
		unit[i] = rot45(unit[i - 1]);
	}

	vector<Seg> seg;
	Pt atual = Pt{T{0, 0}, T{0, 0}};
	int ang = 0;
	for(int i=0;i<n;i++){
		string s; cin >> s;
		if(s[0]=='d'){
			int64_t d; cin >> d;
			Pt off = d * unit[ang];
			seg.push_back({atual, atual+off});
			atual = atual+off;
		} else if(s[0] == 'm'){
			int64_t d; cin >> d;
			Pt off = d * unit[ang];
			atual = atual+off;
		} else {
			int32_t x; cin >> x; x /= 45;
			ang = (ang + x) % 8;
		}	
	}

    for (int i = 0; i < seg.size(); ++i) {
        auto [x1, y1] = seg[i];
        for (int j = i+1; j < seg.size(); ++j) {
            auto [x2, y2] = seg[j];
            if (y1 == x2 and collinear(x1, y1, y2)) {
                seg.erase(begin(seg)+j);
                seg[i][1] = y2;
                --i; break;
            }
            if (y1 == y2 and collinear(x1, y1, x2)) {
                seg.erase(begin(seg)+j);
                seg[i][1] = x2;
                --i; break;
            }
            if (x1 == x2 and collinear(y1, x1, y2)) {
                seg.erase(begin(seg)+j);
                seg[i][0] = y2;
                --i; break;
            }
            if (x1 == y2 and collinear(y1, x1, x2)) {
                seg.erase(begin(seg)+j);
                seg[i][0] = x2;
                --i; break;
            }
        }
    }


	int N = seg.size() * 2;

	Pt cm = Pt{T{0, 0}, T{0, 0}};

	for (auto &[a, b] : seg) cm = cm + a + b, a = N * a, b = N * b;

	for (auto &[a, b] : seg) a = a - cm, b = b - cm;

	
	set<Seg> st(seg.begin(), seg.end());
	bool ok = true;
	for (auto x : seg) {
		x = rot45(x);
		auto y = x; swap(y[0], y[1]);
		ok &= (st.count(x) || st.count(y));
	}

	if (ok) {
		cout << 45 << endl;
		return 0;
	}

	ok = true;
	for (auto x : seg) {
		x = rot90(x);
		auto y = x; swap(y[0], y[1]);
		ok &= (st.count(x) || st.count(y));
	}

	if (ok) {
		cout << 90 << endl;
		return 0;
	}

	ok = true;
	for (auto x : seg) {
		x = rot180(x);
		auto y = x; swap(y[0], y[1]);
		ok &= (st.count(x) || st.count(y));
	}

	if (ok) {
		cout << 180 << endl;
		return 0;
	}

	cout << 360 << endl;
}

