#include <bits/stdc++.h>
#include "combo.h"
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
char b[4]={'A','B','X','Y'}; 
 
string guess_sequence(int n){
    
    string ans = "";
 
    char first;
 
    int q = press("AB");
    if(q){
        q = press("A");
        if(q)first='A';
        else first='B';
    }else{
        q = press("X");
        if(q)first='X';
        else first='Y';
    }
    ans+=first;
    string um="",dois="",last="",x1,x2,x3;
    
    for(int i=0;i<4;++i){
        if(b[i]==first)continue;
        if(!sz(um))um += b[i];
        else if(!sz(dois))dois += b[i];
        else last += b[i];
    }
 
    x1+=um+um,x2+=um+dois,x3+=um+last;
 
    for(int i=3;i<=n;++i){
        string query = "";
        query+=ans+dois;
        query+=ans+x1;
        query+=ans+x2;
        query+=ans+x3;
        q = press(query);
        if(q==sz(ans))ans+=last;
        else if(q==i)ans+=um;
        else ans+=dois;
    }
 
    if(n==1)return ans;
    string query="";
    query+=ans+um;
    query+=ans+dois;
    q = press(query);
    if(q==n){
        if(press(ans+um)==n)ans+=um;
        else ans+=dois;
    }else ans+=last;
    
    return ans;
}
