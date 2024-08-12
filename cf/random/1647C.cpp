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

struct operation{
    int x1,y1,x2,y2;
};

void solve(){
    int n,m;cin>>n>>m;
    vector<vector<char>> grid(n+1,vector<char>(m+1));
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)cin>>grid[i][j];
    if(grid[1][1]=='1'){
        cout<<-1<<endl;
    }else{
        vector<operation>q;
        for(int i=n;i>=1;--i){
            for(int j=m;j>=1;--j){
                if(grid[i][j]=='1'){
                    if(j==1)q.pb({i-1,j,i,j});
                    else q.pb({i,j-1,i,j});
                }else{
                    q.pb({i,j,i,j});
                }
            }
        }
        cout<<n*m<<endl;
        for(auto op:q){
            cout<<op.x1<<" "<<op.y1<<" "<<op.x2<<" "<<op.y2<<endl;
        }
    }
}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t;cin>>t;
    while(t--)solve();
}