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

//achar dois pares (x,y), (a,b) tal que xor(x,y) = n-1 e xor(a,b) = n-1
// e and(a,x) + and(b,y) = k ou and(a,y) + and(b,x) = k
// 
bool ok[(1<<20)];
int n,k;
int findxor(int a){//could just replace with (n-1)^a
    int b = 0;
    for(int i=0;(1<<i)<n;i++){
            if((a&(1<<i))==0)b+=(1<<i);
    }
    return b;
}

void solve(){
    cin>>n>>k;
    if(k==0){
        for(int i=0;i<n;i++){
            if(ok[i])continue;
            int j = findxor(i);
            cout<<i<<" "<<j<<endl;
            ok[i] = ok[j] = 1;
        }
    }else if(k==n-1){
        if(n==4){
            cout<<-1<<endl;
        }else{
            cout<<n-1<<" "<<n-2<<endl;
            cout<<1<<" "<<3<<endl;
            cout<<0<<" "<<findxor(3)<<endl;
            ok[n-1] = ok[n-2] = ok[1] = ok[3] = ok[0] = ok[findxor(3)] = 1;
            for(int i=0;i<n;i++){
                if(ok[i])continue;
                int j = findxor(i);
                cout<<i<<" "<<j<<endl;
                ok[i] = ok[j] = 1;
            }
        }
    }else{
        int a = k&(-k),b=0,c=0,d=0;
        b = findxor(a);
        for(int i=0;(1<<i)<n;i++){
            if((k&(1<<i)))c+= (1<<i) * ((a&(1<<i))!=0);
            else c+= (1<<i) * ((b&(1<<i))!=0);    
        }
        d = findxor(c);
        cout<<a<<" "<<c<<endl;
        cout<<b<<" "<<d<<endl;
        ok[a] = ok[b] = ok[c] = ok[d] = 1;
        for(int i=0;i<n;i++){
            if(ok[i])continue;
            int j = findxor(i);
            cout<<i<<" "<<j<<endl;
            ok[i] = ok[j] = 1;
        }
    }
    for(int i=0;i<n;i++)ok[i] = 0;
}


int main(){_
    int t;cin>>t;
    while(t--)solve();
}