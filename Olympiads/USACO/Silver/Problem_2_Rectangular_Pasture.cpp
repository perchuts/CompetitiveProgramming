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

ll grid[3000][3000];
ii cor[3000];
vector<int>a,b;
map<int,int>coordx,coordy;

ll query(int x1,int y1,int x2,int y2){
    return grid[x2][y2]-grid[x1-1][y2]-grid[x2][y1-1]+grid[x1-1][y1-1];
}

bool sorting(ii x,ii y){return x.second<y.second;}

void solve(){
    ll n;cin>>n;
    ll ans = n+1LL;
    for(int i=1;i<=n;i++){
        int x,y;cin>>x>>y;
        cor[i]={x,y};
        a.pb(x);
        b.pb(y);
    }
    sort(all(a));
    sort(all(b));
    int cnt=1;
    for(auto x:a){
        coordx[x]=cnt++;
    }
    cnt=1;
    for(auto y:b){
        coordy[y]=cnt++;
    }
    
    for(int i=1;i<=n;i++){
        auto [x,y] = cor[i];
        grid[coordx[x]][coordy[y]]=1LL;
    }

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            grid[i][j]+=grid[i-1][j]+grid[i][j-1]-grid[i-1][j-1];
    sort(cor+1,cor+1+n,sorting);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            auto x = cor[i], y = cor[j]; 
            ans += query(1,coordy[x.second],coordx[min(x.first,y.first)],coordy[y.second]) * query(coordx[max(x.first,y.first)],coordy[x.second],n,coordy[y.second]);
        }
    }
    cout<<ans<<endl;


}


int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int t=1;//cin>>t;
    while(t--)solve();
}