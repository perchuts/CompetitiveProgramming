#include "robot.h"
#include <bits/stdc++.h>

using namespace std;

void program_pulibot()
{
    // esq baixo dir cima
    // -2, -1, 0, direcao cardinal, eu mesmo, bloqueio
    // cores a serem usadas: 1 (fazendo trajeto final), 2 (bloqueado)
    // entao temos 10^5 estados possivelmente validos. vamos evaluar todos eles!
    array<int, 5> S{};
    string s = "zWSEN";
    auto eval = [&] (auto&& self, int i) -> void {
        if (i == 5) {
            char dir = 'T';
            int write_state = 0;
            if (S[1] == S[3] and S[1] == -2) return;
            if (S[2] == S[4] and S[2] == -2) return;
            int free_dir = -1;
            for (int i = 1; i <= 4; ++i) {
                if (S[i] == 0) { free_dir = i; break; }
            }
            if (S[0] == 7) {
                for (int j = 1; j <= 4; ++j) if (S[j] == 7) dir = s[j], write_state = 0;
                if (dir == 'T') {
                    for (int j = 1; j <= 4; ++j) if (3 <= S[j] and S[j] <= 6) dir = s[j], write_state = 7;
                }
                goto finish;
            } 
            if (S[0] == 0) {
                if (S[2] == S[3] and S[2] == -2) {
                    dir = 'H';
                    write_state = 2;
                    goto finish;
                } 
                for (int j = 1; j <= 4; ++j) if (S[j] > 0) dir = s[j], write_state = 2 + j;
                if (dir == 'T') {
                    dir = 'H';
                    write_state = 3;
                }
                goto finish;
            }
            if (3 <= S[0] and S[0] <= 6) {
                if (free_dir == -1) {
                    dir = 'H';
                    write_state = 7;
                } else {
                    write_state = S[0];
                    dir = s[free_dir];
                }
                goto finish;
            }
finish:
            set_instruction({S[0], S[1], S[2], S[3], S[4]}, write_state, dir);
            return;
        }
        for (int j = (i == 0 ? 0 : -2); j <= 7; ++j) S[i] = j, self(self, i+1);
    };
    eval(eval, 0);
}
