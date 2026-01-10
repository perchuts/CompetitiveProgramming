#include<bits/stdc++.h>
#include"arrays.h"
using namespace std;
 
vector<vector<int>> arrays_secretos(int n, int k){
    // ok, nao sei fazer direto. vou sair fazendo subtasks pra ganhar intuicao (e testar elas)
    // vou fazer n/2 perguntas
    vector<vector<int>> ans(n);
    // esse descobre parece ser bem util
    auto descobre = [&] (int i) {
        vector<int> sexo(k, i);
        auto v = concatenar(sexo);
        int x = v.size() / k;
        for (int j = 0; j < x; ++j) ans[i].push_back(v[j]);
    };
    // consigo descobrir K em 2 queries
    for (int i = 0; i + k - 1 < n; i += k) {
        vector<int> sexo(k); iota(begin(sexo), end(sexo), i);
        auto v1 = concatenar(sexo);
        reverse(begin(sexo), end(sexo));
        int ptr = 0;
        auto v2 = concatenar(sexo);
        for (int w = i; w < i + k; ++w) {
            int skate = v1[ptr], tam = 1;
            while (true) {
                if (v2[v2.size() - ptr - tam] == skate) break;
                tam++;
            }
            for (int j = ptr; j < ptr + tam; ++j) ans[w].push_back(v1[j]);
            ptr += tam;
        }
    }
    if (n % k) {
        int start = n - (n % k);
        if (n < k) descobre(0), start++;
        vector<int> sexo(k);
        int qt = n - start;
        for (int i = 0; i < k - qt; ++i) sexo[i] = 0;
        for (int i = k - qt; i < k; ++i) {
            sexo[i] = start + i - (k - qt);
        }
        auto v1 = concatenar(sexo);
        reverse(begin(sexo) + k - qt, end(sexo));
        auto v2 = concatenar(sexo);
        int ptr = (k - qt) * ans[0].size();
        int ini = ptr;
        for (int w = start; w < n; ++w) {
            int skate = v1[ptr], tam = 1;
            while (true) {
                if (v2[v2.size() - ptr - tam + ini] == skate) break;
                tam++;
            }
            for (int j = ptr; j < ptr + tam; ++j) ans[w].push_back(v1[j]);
            ptr += tam;
        }
    }
    return ans;
}
