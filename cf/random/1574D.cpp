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

int c[11];
vector<int>v[11];

int n;
map<vector<ll>,bool>cant;
map<vector<ll>,vector<ll>>dp;

vector<ll> solve(vector<ll>x){
    if(!cant[x])return x;
    if(dp.find(x)!=dp.end())return dp[x];
    int mx = INT_MIN,tmp;
    vector<ll>resp,temp;
    for(int i=0;i<n;++i){
        if(x[i]>0){
            x[i]--;
            tmp=0,temp = solve(x);
            if(sz(temp)){
                for(int j=0;j<n;++j)tmp += v[j][temp[j]];
                if(ckmax(mx,tmp))resp = temp;
            }
            x[i]++;
        }   
    }
    return dp[x] = resp;
}

int main(){_
    cin>>n;
    for(int i=0;i<n;++i){
        cin>>c[i];
        v[i].resize(c[i]);
        for(int j=0;j<c[i];++j)cin>>v[i][j];
    }    
    int m;cin>>m;
    vector<ll>ban(n);
    while(m--){
        for(int j=0;j<n;j++){
            cin>>ban[j];ban[j]--;
        }
        cant[ban] = 1;
    }
    vector<ll>st(n);
    for(int i=0;i<n;++i)st[i] = c[i]-1;
    vector<ll>resp = solve(st);
    for(int i=0;i<n;++i)cout<<resp[i]+1<<" ";

}