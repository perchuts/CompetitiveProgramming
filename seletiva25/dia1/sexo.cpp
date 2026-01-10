#include<bits/stdc++.h>
#include"arrays.h"
using namespace std;
 
vector<vector<int>> arrays_secretos(int n, int k){
    // ok, nao sei fazer direto. vou sair fazendo subtasks pra ganhar intuicao (e testar elas)
    // vou fazer n/2 perguntas
    vector<vector<int>> ans(n);
    int i = 0;
    for (; i + 2 < n; i += 3) {
        vector<int> sexo(k, i);
        sexo[1] = i+1;
        auto v1 = concatenar(sexo);
        sexo = vector<int>(k, i+1);
        sexo[1] = i+2;
        auto v2 = concatenar(sexo);
        sexo = vector<int>(k, i+2);
        sexo[1] = i;
        auto v3 = concatenar(sexo);
        int a1 = v1.size(), a2 = v2.size(), a3 = v3.size();
        int y = (a2 + (a1 - a2) / (k-1)) / k;
        int x = (a1 - y) / (k - 1);
        int z = a2 - y * (k - 1);
        for (int j = 0; j < x; ++j) ans[i].push_back(v1[j]);
        for (int j = 0; j < y; ++j) ans[i+1].push_back(v2[j]);
        for (int j = 0; j < z; ++j) ans[i+2].push_back(v3[j]);
    }
    while (i < n) {
        vector<int> sexo(k, i);
        auto v = concatenar(sexo);
        int x = v.size() / k;
        for (int j = 0; j < x; ++j) ans[i].push_back(j);
        i++;
    }
    return ans;
}
