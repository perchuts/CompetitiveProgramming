#include "robot.h"
#include <bits/stdc++.h>

using namespace std;

void program_pulibot()
{
    // esq baixo dir cima
    // -2, -1, 0, direcao cardinal, eu mesmo, bloqueio
    // cores a serem usadas: 1 (fazendo trajeto final), 2 (caminho parcial), 3 (bloqueado)
    // entao temos 10^5 estados possivelmente validos. vamos evaluar todos eles!
    array<int, 5> S{};
    string s = "zWSEN";
    auto eval = [&] (auto&& self, int i) -> void {
        if (i == 5) {
            char dir = 'T'; int write_state = 0;
            // what to do??
            if (S[0] == 0) {
                dir = 'H';
                write_state = 2;
            } 
            if (S[0] == 1) { 
                for (int j = 2; j <= 3; ++j) if (S[j] == 3) dir = s[j], write_state = 1;
                if (write_state == 0) {
                    if (S[1] == 2) dir = s[1], write_state = 1;
                    if (S[4] == 2) dir = s[4], write_state = 1;
                }
                if (write_state == 0 and S[1] == -2 and S[4] == -2) {
                    write_state = 1;
                    dir = 'T';
                }
            }
            if (S[0] == 2) {
                if (S[2] == -2 and S[3] == -2) {
                    write_state = 1;
                    dir = 'H';
                } else {
                    for (int j = 2; j <= 3; ++j) if (S[j] == 1) write_state = 1, dir = 'H';
                    if (write_state == 0) {
                        int free_dir = -1;
                        for (int j = 2; j <= 3; ++j) if (S[j] == 0) { free_dir = j; break; }
                        if (free_dir == -1) write_state = 3, dir = 'H';
                        else dir = s[free_dir], write_state = 2;
                    }
                }
            }
            if (S[0] == 3) {
                vector<int> t(4);
				for (int j = 2; j <= 3; ++j) {
					if (S[j] == 3) t[3] = j;
				}
				if (S[1] == 1 or S[1] == 2) t[S[1]] = 1;
				if (S[4] == 1 or S[4] == 2) t[S[4]] = 4;
                if (t[2]) {
                    if (t[3]) write_state = 3, dir = s[t[3]];
                    else write_state = 3, dir = s[t[2]];
                } else if (t[1]) write_state = 0, dir = s[t[1]];
                else if (t[3]) write_state = 0, dir = s[t[3]];
            }
            set_instruction({S[0], S[1], S[2], S[3], S[4]}, write_state, dir);
            return;
        }
        for (int j = (i == 0 ? 0 : -2); j <= 3; ++j) S[i] = j, self(self, i+1);
    };
    eval(eval, 0);
}
