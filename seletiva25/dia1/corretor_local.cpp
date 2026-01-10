#include <bits/stdc++.h>
using namespace std;
#include "arrays.h"

/*
Esse não exatamente o mesmo grader do juiz.
Esse código serve apenas para testar sua solução.
*/

bool DEBUG_MODE;
int n, k;
vector<vector<int>> v;
int QUERY_LIMIT;
int query_number = 0;

void CountQuery() {
    ++query_number;

    // se passar do limite, retorna WA
    if (query_number > QUERY_LIMIT) {
        cout << "WA, número de queries excedeu o limite\n";
        exit(0);
    }
}

vector<int> concatenar(vector<int> ids) {
    CountQuery();
    
    if (DEBUG_MODE) 
    {
        cout << "Consulta #" << query_number << ": ";
        for (auto x : ids) cout << x << " "; cout << '\n';
    } 
    
    if ((int)ids.size() != k) {
        cout << "WA, tamanho da query foi " << (int)ids.size() << ", mas deveria ser " << k << "\n";
        exit(0);
    }

    for (auto i : ids) {
        if (!(0 <= i and i <= n - 1)) {
            cout << "WA, um dos índices do array foi " << i << ", sendo fora do limite de 0 até " << n - 1 << "\n";
            exit(0);
        }
    }


    vector<int> ans;
    for (auto i : ids) {
        for (auto x : v[i]) {
            ans.push_back(x);
        }
    }
    cout << "Resposta: " << '\n';
    for (auto x : ans) cout << x << " "; cout << '\n'; 
    return ans;
}

int check_answer(vector<vector<int>> ans_player) {
	for (auto x : ans_player) {
		for (auto y : x) cout << y << ' ';
		cout << endl;
	}
    if (ans_player != v) {
        return -1;
    } else {
        return query_number;
    }
}

int main() {
    cout << "Para DEBUG digite 1, caso contrário digite 0: "; cin >> DEBUG_MODE;
    if (DEBUG_MODE) cout << "Digite o número de arrays (N) e o número de indices por consulta (K): ";
    cin >> n >> k;

    QUERY_LIMIT = n; // Mude aqui o limite de queries, por padrão é N

    v.resize(n);
    for (int i = 0; i < n; i++) {
        if (DEBUG_MODE) cout << "Digite o tamanho do array #" << i << ": ";
        int t;
        cin >> t;
        v[i].resize(t);
        if (DEBUG_MODE) cout << "Digite o array #" << i << ": ";
        for (int j = 0; j < t; j++) {
            cin >> v[i][j];
        }
    }

	vector<vector<int>> ans_player = arrays_secretos(n, k);

	int cnt_query = check_answer(ans_player);

	if (cnt_query == -1) {
		cout << "WA, arrays retornados incorretos\n";
		return 0;
	} else {
		// se for uma certa parcial, é pra ser gradual
		cout << "AC, você fez " << cnt_query << " queries\n";
	}

	return 0;
}
