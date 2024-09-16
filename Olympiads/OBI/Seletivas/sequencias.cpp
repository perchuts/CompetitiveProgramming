/*
    Seletiva IOI 2020
    Sequências
    https://drive.google.com/file/d/1c4qnnCpdd-FlATMwjxR0nNXFYTiFNFKd/view
    por Gabriel Lucas    

    isso pega 88.1 pontos
*/

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
 
int main(){_
    int l;cin>>l;
    vector<int>esq, dir;//so uma opcao, 2^x
    dir.pb(2), dir.pb(1);
    int logn = 32 - __builtin_clz(l), falta = logn-2;
    if(logn<3){
        cout<<l<<endl;
        for(int i=l;i>=1;--i)cout<<i<<" \n"[i==1];
        return 0;
    }
    for(int i=logn-2;~i;--i){
        if((l&((1<<(i+1))-1))==0)break;        
        int pode = (l>>i)&1;
        int mn = 3*(logn-i-1);
        if(i==0){
            esq.pb(mn);
            break;
        }
        if(pode)esq.pb(mn), dir.pb(mn+2), dir.pb(mn+1);
        else esq.pb(mn+2), dir.pb(mn+1), dir.pb(mn);
        --falta;
    }
    while(falta--){
        int now = dir[sz(dir)-2]+1;
        dir.pb(now+1), dir.pb(now);
    }
    for(auto x:dir)esq.pb(x);
    if(sz(esq)>l){
        cout<<l<<endl;
        for(int i=l;i>=1;--i)cout<<i<<" \n"[i==1];
    }else{
        cout<<sz(esq)<<endl;
        for(auto x:esq)cout<<x<<" ";
        cout<<endl;
    }
}