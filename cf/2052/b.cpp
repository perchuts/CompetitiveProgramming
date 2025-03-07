#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

array<int, 4> pos = { 5*128, 6*128, 7*128, 8*128 };
array<int, 4> stage = { 0, 100, 200, 300 };
array<int, 4000> mem{};

const int Zero = 2024;
const int One = 2025;

int onde(int x, int i) {
	return (x<<4) + i;
}

void halt(int i) {
	mem[i + 0] = onde(Zero, 0);
	mem[i + 1] = onde((1<<12) - 1, 0);
	mem[i + 2] = (1<<12) - 1;
}

void next(int i, int t) {
	if (t == 3) {
		mem[i + 0] = onde(One, 0);
		mem[i + 1] = onde((1<<12) - 1, 0);
		mem[i + 2] = (1<<12) - 1;
	} else {
		mem[i + 0] = onde(Zero, 0);
		mem[i + 1] = onde(Zero, 0);
		mem[i + 2] = stage[t+1];
	}
}

void do_stage(int i) {
	int off = stage[i];
	
	for (int it = 0; it < 4; it++) {
		mem[off + it*3 + 0] = onde((1<<12) - 1, i*4+it); 
		mem[off + it*3 + 1] = onde(off+12 +2, it+2);
		mem[off + it*3 + 2] = off + it*3 + 3;
	}
	mem[off + 12 + 0] = 0;
	mem[off + 12 + 1] = 0;
	mem[off + 12 + 2] |= pos[i];
}

void do_table(int t, int x) {
	int off = pos[t];
	for (int i = 0; i < 16; i++) {
		if (i == x) {
			next(off + 4*i, t);
		} else {
			halt(off + 4*i);
		}
	}
}

int simula(int op) {
	mem[(1<<12) - 1] = op;
	int pt = 0;
	while (pt+2 < (1<<12)) {
		cout << "pt=" << setw(4) << setfill('0') << pt << endl; cout.flush();

		int a = mem[pt], b = mem[pt+1];

		int offa = (a >> 4), bita = (a & 15);
		int offb = (b >> 4), bitb = (b & 15);

		int va = mem[offa] >> bita & 1;
		if (va) mem[offb] |= (1 << bitb);
		else mem[offb] &= ~(1 << bitb);

		int c = mem[pt+2]; 
		pt = c;
	}

	return mem[(1<<12) - 1] >> 0 & 1;
}

//string ele = "fff0 0026 0003 fff1 0056 0006 fff2 0086 0009 fff3 00b6 000c fff4 00e6 000f fff5 0116 0012 fff6 0146 0015 fff7 0176 0018 fff8 01a6 001b fff9 01d6 001e fffa 0206 0021 fffb 0236 0024 fffc 0266 0027 fffd 0296 002a fffe 02c6 002d ffff 02f6 0030 0004 fff0 0fff 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff 0000 fff0 0fff";
//
//void le() {
//	stringstream ss(ele);
//
//}

int32_t main() {
	fast_io;
	int x; cin >> x;

	array<int, 4> parts = {0, 0, 0, 0};
	int cp = x;
	for (int i = 0; i < 4; i++) {
		parts[i] = cp&15;
		cp >>= 4;
	}

	mem[One] = 0b1111111111111111;
	
	for (int i = 0; i < 4; i++) {
		do_table(i, parts[i]);
		do_stage(i);
	}

	for (int i = 0; i < One + 1; i++) {
		cout << setw(4) << setfill('0') << hex << mem[i] << " \n"[i == One];
	}

	//auto prog = mem;
	//for (int i = 0; i < (1<<16); i++) {
	//	cout << i << endl; cout.flush();
	//	mem = prog;
	//	assert(simula(i) == (i == x));
	//}

}
