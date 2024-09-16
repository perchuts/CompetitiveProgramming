/*
    Seletiva IOI 2019
    Saldo
    https://codeforces.com/group/2k70zKp2Ci/contest/263327/problem/A
    por Gabriel Lucas
*/
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

bool ckmin(int& a, int b){ return b < a ? a = b, true : false; }
bool ckmax(int& a, int b){ return b > a ? a = b, true : false; }

int r[maxn];

vector<ii>g[maxn];
vector<int>costs;

int dfs(int u,int p,int cost){
    int sum = r[u];
    for(auto [v,c]:g[u])
        if(v!=p)
            sum+=dfs(v,u,c);    
    if(sum==0&&u!=1)costs.pb(cost);
    return sum;
}



int main(){_
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    int n,k;cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>r[i];
    for(int i=1;i<n;i++){
        int a,b,c;cin>>a>>b>>c;
        g[a].pb({b,c});
        g[b].pb({a,c});
    }
    int top = dfs(1,-1,0);
    if(k==0)cout<<(top ? -1 : 0)<<endl;
    else{
        if(sz(costs)<k||top){
            cout<<-1<<endl;
        }else{
            sort(all(costs));
            cout<<accumulate(begin(costs),begin(costs)+k,0)<<endl;
        }
    }
    
}