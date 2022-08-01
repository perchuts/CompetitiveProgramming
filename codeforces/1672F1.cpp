#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;
 
const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 2e5+100;
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
vector<int>cycle[maxn], where[maxn];
void solve(){
    //permutation: set of disjoint cycles
    //lets consider the number with most reps = x.
    //i want to separate numbers in at least x cycles.
    //if this is not possible i.e. x>n/2, then just separate them in n/2 cycles.
    //all other numbers can be put each one in one cycle.
    int n;cin>>n;
    vector<int>qnt(n+1), v(n+1), ans(n+1);
    int mx=0;
    for(int i=1;i<=n;++i){
        cin>>v[i];
        qnt[v[i]]++;
        ckmax(mx,qnt[v[i]]);
        where[v[i]].pb(i);
    }
    if(n==1){
        ans[1] = v[1];
    }else{
        mx = min(n/2,mx);
        int cur=0;
        for(int i=1;i<=n;++i){
            for(auto x:where[i]){
                cycle[cur].pb(x);
                cur = (cur+1)%mx;
            }
        }
        for(int i=0;i<mx;++i){
            for(int j=0;j<sz(cycle[i])-1;++j)ans[cycle[i][j]] = v[cycle[i][j+1]];
            ans[cycle[i][sz(cycle[i])-1]] = v[cycle[i][0]];
        }
    }
    for(int i=1;i<=n;++i){
        cout<<ans[i]<<" \n"[i==n];
        cycle[i-1].clear();
        where[i].clear();
    }
}
 
 
int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}