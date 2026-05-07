// testando o poder do Gemini

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int X; // Valor alvo global

// Estrutura do nó da Árvore de Segmentos
struct Node {
    long long count_X;
    int pref_sz;
    pair<int, int> pref[20]; // {valor_gcd, comprimento}
    int suff_sz;
    pair<int, int> suff[20]; // {valor_gcd, comprimento}
    
    Node() : count_X(0), pref_sz(0), suff_sz(0) {}
};

// Função para criar um nó folha (1 único elemento)
Node make_node(int val) {
    Node res;
    res.count_X = (val == X ? 1 : 0);
    res.pref[0] = {val, 1};
    res.pref_sz = 1;
    res.suff[0] = {val, 1};
    res.suff_sz = 1;
    return res;
}

// Função para fundir (merge) dois nós
Node merge_nodes(const Node& l, const Node& r) {
    // Se um dos nós for vazio (usado nas consultas)
    if (l.pref_sz == 0) return r;
    if (r.pref_sz == 0) return l;

    Node res;
    // Soma os subsegmentos já válidos nos filhos esquerdo e direito
    res.count_X = l.count_X + r.count_X;
    
    // Conta os subsegmentos válidos que cruzam a divisa
    for (int i = 0; i < l.suff_sz; ++i) {
        for (int j = 0; j < r.pref_sz; ++j) {
            if (std::gcd(l.suff[i].first, r.pref[j].first) == X) {
                res.count_X += 1LL * l.suff[i].second * r.pref[j].second;
            }
        }
    }
    
    // Atualiza os prefixos do novo nó
    res.pref_sz = 0;
    for (int i = 0; i < l.pref_sz; ++i) {
        res.pref[res.pref_sz++] = l.pref[i];
    }
    for (int i = 0; i < r.pref_sz; ++i) {
        int g = std::gcd(res.pref[res.pref_sz - 1].first, r.pref[i].first);
        if (g == res.pref[res.pref_sz - 1].first) {
            res.pref[res.pref_sz - 1].second += r.pref[i].second;
        } else {
            res.pref[res.pref_sz++] = {g, r.pref[i].second};
        }
    }
    
    // Atualiza os sufixos do novo nó
    res.suff_sz = 0;
    for (int i = 0; i < r.suff_sz; ++i) {
        res.suff[res.suff_sz++] = r.suff[i];
    }
    for (int i = 0; i < l.suff_sz; ++i) {
        int g = std::gcd(res.suff[res.suff_sz - 1].first, l.suff[i].first);
        if (g == res.suff[res.suff_sz - 1].first) {
            res.suff[res.suff_sz - 1].second += l.suff[i].second;
        } else {
            res.suff[res.suff_sz++] = {g, l.suff[i].second};
        }
    }
    
    return res;
}

const int MAXN = 100005;
Node tree[4 * MAXN];
int A[MAXN];

// Constrói a Segment Tree inicial
void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = make_node(A[start]);
        return;
    }
    int mid = start + (end - start) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
}

// Atualiza a Segment Tree quando A[idx] é modificado para val
void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = make_node(val);
        return;
    }
    int mid = start + (end - start) / 2;
    if (idx <= mid) {
        update(2 * node, start, mid, idx, val);
    } else {
        update(2 * node + 1, mid + 1, end, idx, val);
    }
    tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
}

// Consulta na Segment Tree a resposta para o intervalo [l, r]
Node query(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = start + (end - start) / 2;
    if (r <= mid) {
        return query(2 * node, start, mid, l, r);
    }
    if (l > mid) {
        return query(2 * node + 1, mid + 1, end, l, r);
    }
    return merge_nodes(query(2 * node, start, mid, l, r), 
                       query(2 * node + 1, mid + 1, end, l, r));
}

int main() {
    // Otimiza as operações de I/O em C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, Q;
    if (!(cin >> N >> Q >> X)) return 0;
    
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
    }
    
    build(1, 1, N);
    
    for (int q = 0; q < Q; ++q) {
        int type;
        cin >> type;
        if (type == 1) {
            int i, y;
            cin >> i >> y;
            update(1, 1, N, i, y);
        } else if (type == 2) {
            int l, r;
            cin >> l >> r;
            Node res = query(1, 1, N, l, r);
            cout << res.count_X << "\n";
        }
    }
    
    return 0;
}
