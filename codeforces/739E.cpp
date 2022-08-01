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
 
double x[2001], y[2001]; 
int n,a,b;
pair<double,ii>dp[2001];
 
pair<double,ii> best(pair<double,ii>a,pair<double,ii>b){
    if(a.first!=b.first)return max(a,b);
    if(a.second.second<b.second.second)return a;
    if(a.second.second>b.second.second)return b;
    if(a.second.first<b.second.first)return a;
    return b;
}
 
pair<double,ii>compute(double lambda1, double lambda2){
    for(int i=1;i<=n;++i){
        //tenho 4 opcoes: nao pegar nada, pegar 1, pegar 2, pegar 1,2
        dp[i] = dp[i-1];//nao pegar nada
        pair<double,ii>tmp = dp[i];
        if(best(dp[i],{tmp.first+x[i]-lambda1,{tmp.second.first+1,tmp.second.second}})!=dp[i]){
            dp[i] = {tmp.first+x[i]-lambda1,{tmp.second.first+1,tmp.second.second}};
        }
        if(best(dp[i],{tmp.first+y[i]-lambda2,{tmp.second.first,tmp.second.second+1}})!=dp[i]){
            dp[i] = {tmp.first+y[i]-lambda2,{tmp.second.first,tmp.second.second+1}};
        }
        double prob = 1 - (1-x[i])*(1-y[i]);
        if(best(dp[i],{tmp.first+prob-lambda1-lambda2,{tmp.second.first+1,tmp.second.second+1}})!=dp[i]){
            dp[i] = {tmp.first+prob-lambda1-lambda2,{tmp.second.first+1,tmp.second.second+1}};
        }
    }
    return dp[n];
}
 
int main(){_
    cin>>n>>a>>b;
    for(int i=1;i<=n;++i)cin>>x[i];
    for(int i=1;i<=n;++i)cin>>y[i];
    double l1 = 0, r1 = 1, lambda1, lambda2;
 
    for(int __=1;__<=60;++__){
        double md1 = (l1+r1)/2;
        double l2 = 0, r2 = 1;
        for(int __=1;__<=60;++__){
            double md2 = (l2+r2)/2;
            pair<double,ii>cur = compute(md1,md2);
            if(cur.second.second>b)l2 = md2;
            else r2 = md2;
        }
        pair<double,ii>cur = compute(md1,r2);
        if(cur.second.first>a)l1 = md1;
        else r1 = md1;
        lambda1 = r1, lambda2 = r2;
    }
 
    cout<<fixed<<setprecision(4)<<compute(lambda1,lambda2).first+lambda1*(double)a+lambda2*(double)b<<endl;
    // cout<<compute(lambda1,lambda2).second.first<<" "<<compute(lambda1,lambda2).second.second<<endl;
    // cout<<lambda1<<" "<<lambda2<<endl;
    // cout<<best(dp[1],{dp[1].first+y[2],{dp[1].second.first,dp[1].second.second+1}}).first<<endl;
}