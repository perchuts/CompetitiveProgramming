/*
    Seletiva IOI 2020
    Doceria
    https://codeforces.com/group/2k70zKp2Ci/contest/352783/problem/A
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
 
template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }
 
int w[1001],v[1001],knapsack1[1001][30001],knapsack2[1001][30001],
cnv[1001],w2[1001],v2[1001];

int main(){_
    int n,r;cin>>n>>r;
    for(int i=1;i<=n;++i)cin>>w[i]>>v[i];    
    for(int i=1;i<=n;++i){
        int x,a,b;cin>>x>>w2[x]>>v2[x];
        cnv[n+1-i] = x;
    }
 
    for(int i=1;i<=n;++i){
        int act1=cnv[i],act2 = cnv[n+1-i];
        for(int j=0;j<=r;++j){
            knapsack1[i][j]=knapsack1[i-1][j],knapsack2[i][j]=knapsack2[i-1][j];
            if(j>=w[act1])ckmax(knapsack1[i][j],knapsack1[i-1][j-w[act1]]+v[act1]);
            if(j>=w2[act2])ckmax(knapsack2[i][j],knapsack2[i-1][j-w2[act2]]+v2[act2]);
        }
    }
 
    for(int i=n;~i;--i){
        int mx = 0;
        for(int j=0;j<=r;++j){
            ckmax(mx,knapsack1[i][j]+knapsack2[n-i][r-j]);
        }
        cout<<mx<<endl;
    }
 
    
    
}