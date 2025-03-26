#include <bits/stdc++.h>
#include "books.h"

using namespace std;
//
// --- Sample implementation for the task books ---
//
// To compile this program with the sample grader, place:
//     books.h books_sample.cpp sample_grader.cpp
// in a single folder and run:
//     g++ books_sample.cpp sample_grader.cpp
// in this folder.
//

void solvar(int n, int k, long long a, int s) {
#define int long long
    vector<int> v(n);
    for (int i = 0; i < k; ++i) v[i] = skim(i+1);
    int cur = 0; 
    set<int> ans;
    for (int i = 0; i < k-1; ++i) ans.insert(i+1), cur += v[i];
    int l = k, r = n-1, lim = n-1;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (v[md] == 0) v[md] = skim(md+1);
        if (cur + v[md] >= a) lim = md, r = md-1;
        else l = md+1;
    }
    if (cur + v[lim] < a) {}
    else if (cur + v[lim] > 2*a) {
        lim--;
        if (v[lim] == 0) v[lim] = skim(lim+1);
    }
    auto go = [&] () {
        vector<int32_t> resp;
        for (auto x : ans) resp.push_back(x);
        answer(resp);
    };
    cur += v[k-1], ans.insert(k);
    if (a <= cur and cur <= 2*a) go();
    if (2*a < cur) impossible();
    for (int i = lim-1; i > lim-k; --i) if (v[i] == 0) v[i] = skim(i+1);
    for (int i = k-1; ~i; --i) {
        for (int j = i+1; j <= lim-(k-1-i); ++j) {
            cur += v[j] - v[j-1];
            ans.insert(j+1);
            ans.erase(j);
            if (a <= cur) go();
        }
    }
    impossible();
#undef int
}

void solve(int n, int k, long long a, int s) {
    s = min(s, n);
    solvar(n, k, a, s);    
}
