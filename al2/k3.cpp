#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	for (int a = 1; a < 5; ++a) {
		for (int b = 1; b < 5; ++b) {
			for (int c = 1; c < 5; ++c) {
				for (int d = 1; d < 5; ++d) {
					for (int e = 1; e < 5; ++e) {
						for (int f = 1; f < 5; ++f) {
							int qtl = 0;
							for (int x = 0; x < 5; ++x) {
								for (int y = 0; y < 5; ++y) {
									for (int z = 0; z < 5; ++z) {
										if (x+y+z == 0) continue;
										int val = x*x*a+y*y*b+z*z*b;
										val += 2 * (x*y*d + x*z*e + y*z*f);
										val %= 5;
										if (val == 0) qtl++;
									}
								}
							}
							if (qtl == 0) {
								// <(x, y, z), (x, y, z)> = ax^2 + by^2 + cz^2 + 2(xyd + xze + yzf)
								// xT A x = 
								// 		   (a d e) (x)   		 (ax+dy+ez)		
								// (x y z) (d b f) (y) = (x y z) (dx+by+fz) = ax2 + dxy + exz + dxy + by2 + yzf + exz + fyz + cz2
								//         (e f c) (z)     		 (ex+fy+cz)
								// ent quero xT A x = 0
								// quero mostrar q esse sistema tem solucao nao nula
								// i can show that a, b, c, d, e, f > 0
								// i must show that no matter what the values of a,b,c,d,e,f are, there will always be a triple (x, y, z) != (0, 0, 0)
								// s.t. <(x, y, z), (x, y, z)> = 0.
								// 124 posicoes
								
								// tenho: cz^2 + 2(xze + yzf) = cz'^2+2(xz'e+yz'f)
								// c(z+z')(z-z') = 2(z'-z)(xe+yf)
								// c(z+z') = 2(xe+yf)
								// z' = 2(xe+yf)/c - z
								// logo, temos q soh um z' pode satisfazer isso! se eu tiver 3 caras dentro do mesmo lugar eh L absurdo
								printf("a = %d, b = %d, c = %d, d = %d, e = %d, f = %d\n", a, b, c, d, e, f);
								exit(0);
							}

						}
					}
				}
			}
		}
	}
	cout << "W" << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
