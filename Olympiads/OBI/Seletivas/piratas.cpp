/*
    Seletiva IOI 2020
    Piratas
    https://codeforces.com/group/2k70zKp2Ci/contest/352573/problem/A
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
int main(){_
    int n,k,resp,ind;cin>>n>>k;
    int ok = 0;
    int receberam = 0;
    for(int i=1;i<=n;i++){
        int zeros = i-1-receberam,preciso = (i+1)/2-1-ok,tenho = k - preciso;
        if(preciso<=zeros&&tenho>=0){
            ok=0, resp = tenho, ind = i;
            receberam = preciso + tenho>0;
        }else ok++;
        
    }
    cout<<n-ind<<" "<<resp<<endl;
}