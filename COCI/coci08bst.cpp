#include <bits/stdc++.h>
#define maxn (int)(1e5+51)
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define ll long long
#define pb push_back
#define ull unsigned long long
#define ii pair<int,int>
#define iii tuple<int,int,int>
#define inf 2000000001
#define mod 1000000007 //998244353
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

ll c, lvl[3*maxn];

set<int>added;

int main(){_
    int n,root;cin>>n>>root;
    cout<<c<<endl;
    added.insert(root);
    for(int i=1;i<n;i++){
        int x;cin>>x;
        auto it = added.lower_bound(x);
        if(it==added.end()){
            it = prev(end(added));
            lvl[x] = lvl[*it]+1ll;
        }else{
            lvl[x] = lvl[*it]+1ll;
            if(it!=begin(added))ckmax(lvl[x],lvl[*prev(it)]+1ll);
        }
        c+=lvl[x];
        cout<<c<<endl;
        added.insert(x);
    }    
}