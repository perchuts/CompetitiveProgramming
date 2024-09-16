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

double calcarea(double x1,double x2,double x3,double y1,double y2,double y3){
    return (abs(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2)))/2;
}
const double eps = 1e-8;
int main(){_
    double x1,y1,x2,y2,x3,y3;cin>>x1>>y1>>x2>>y2>>x3>>y3;
    double area = calcarea(x1,x2,x3,y1,y2,y3);
    cout<<fixed<<setprecision(1)<<area<<endl;
    int n,ans=0;cin>>n;
    for(int i=1;i<=n;i++){
        double a,b;cin>>a>>b;
        double a1 = calcarea(x1,x2,a,y1,y2,b);
        double a2 = calcarea(x1,a,x3,y1,b,y3);
        double a3 = calcarea(a,x2,x3,b,y2,y3);
        if(abs(area-a1-a2-a3)<eps)ans++;
    }
    cout<<ans<<endl;
}