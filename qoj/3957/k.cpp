#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

const int N = 103, HLF = 50;

char mat[N][N];

int32_t main() {_
      int n;
      cin >> n;
      int x = (int)(ceil(sqrtl(n)));
      fill(mat[0], mat[0]+N*N, '.');
      int rows = (n+x-1)/x, rem = n % x, lx = HLF - rows/2, rx = HLF + rows/2 - !(rows & 1);
      int ly = HLF - x/2, ry = HLF + x/2 - !(x & 1);
      
      auto place = [&](int x, int y, int d){
            mat[x][y] = 'O';
            if(!d){
                  mat[x][y-1] = mat[x-1][y] = '#';
            }
            else if(d == 1){
                  mat[x][y-1] = mat[x+1][y] = '#';
            }
            else if(d == 2){
                  mat[x-1][y] = mat[x][y+1] = '#';
            }
            else if(d == 3){
                  mat[x+1][y] = mat[x][y+1] = '#';
            }
      };

      int xc = lx, yc = ly + rem - 1;

      // Superior
      if(rem){
            place(xc-1, yc+1, 1);
            for(int j = yc-1; j >= ly; j -= 2) place(lx-1, j, 0);
            for(int j = yc+2; j <= ry; j += 2) place(lx, j, 2);
      }
      else{
            for(int j = ry; j >= ly; j -= 2) place(lx-1, j, 0);
      }

      // Esquerda
      for(int i = lx; i <= rx; i += 2) place(i+1, ly-1, 0);
      // Inferior
      for(int j = ly; j <= ry; j += 2) place(rx+1, j, 3);
      
      // Direita
      if(rem){
            for(int i = lx+1; i+1 <= rx; i += 2) place(i, ry+1, 3);
            if((rows-1) & 1) place(rx, ry+2, 0);
      }
      else{
            for(int i = lx; i+1 <= rx; i += 2) place(i, ry+1, 3);
            if(rows & 1) place(rx, ry+2, 0);
      }
      cout << 100 << ' ' << 100 << endl;
      for(int i = 1; i <= 100; ++i){
            for(int j = 1; j <= 100; ++j){
                  cout << mat[i][j];
            }
            cout << endl;
      }

}
