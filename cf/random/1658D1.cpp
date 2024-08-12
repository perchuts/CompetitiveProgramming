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
const int maxn = 1e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int v[(1<<18)], qnt[30][2], qnt2[30][2];
void solve(){
    int l,r;cin>>l>>r;
    for(int i=1;i<=r-l+1;++i)cin>>v[i];
    for(int i=0;i<30;++i)qnt[i][0] = qnt[i][1] = qnt2[i][0] = qnt2[i][1] = 0;
    for(int i=l;i<=r;++i){
        for(int j=0;j<30;++j){
            if((i&(1<<j)))qnt[j][1]++;
            else qnt[j][0]++;
        }
    }
    for(int i=1;i<=r-l+1;++i){
        for(int j=0;j<30;++j){
            if((v[i]&(1<<j)))qnt2[j][1]++;
            else qnt2[j][0]++;
        }
    }
    // for(int i=0;i<3;++i)cout<<qnt[i][0]<<" "<<qnt[i][1]<<endl;
    // cout<<endl;
    // for(int i=0;i<3;++i)cout<<qnt2[i][0]<<" "<<qnt2[i][1]<<endl;
    int x = 0;
    for(int i=0;i<30;++i)if(qnt2[i][1]!=qnt[i][1])x|=(1<<i);
    cout<<x<<endl;

}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}