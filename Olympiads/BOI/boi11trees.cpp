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

int N,m,bit[maxn];

void insert(int x,int d){
    while(x<=N)bit[x]+=d,x+=x&(-x);
}

void add(int l,int r,int d){
    insert(l,d);
    insert(r+1,-d);
}

int query(int x){
    int ans = 0;
    while(x){
        ans += bit[x];
        x -= x&(-x);
    }
    return ans;
}

vector<int> solve(int n,int m,vector<int>v,vector<pair<char,ii>>operations){
    N = n;
    for(int i=1;i<n+10;++i)bit[i] = 0;
    sort(all(v));
    for(int i=0;i<n;++i)add(i+1,i+1,v[i]);
    vector<int>answers;
    for(int i=0;i<m;++i){
        auto [op, p] = operations[i];
        if(op=='F'){
            auto [c,h] = p;
            // cerr<<"adding to "<<c<<" smallest elements starting from "<<h<<endl;
            int l = 1, r = n, ans = inf;
            while(l<=r) {
                int md = l + (r-l+1)/2;
                if(query(md)>=h)ans = md, r = md-1;
                else l = md + 1;
            }
            if(ans==inf)continue;
            int lo = ans, hi = min(n,ans + c - 1);
            int biggest = query(hi);
            // cerr<<"found "<<lo<<" as min index >=h"<<endl;
            // cerr<<"biggest height to be added is "<<biggest<<endl;
            if(biggest!=query(lo)){
                l = 1, r = n, ans = inf;
                while(l<=r){
                    int md = l + (r-l+1)/2;
                    if(query(md)>=biggest)ans = md, r = md - 1;
                    else l = md + 1;
                }
                ans--;
                add(lo,ans,1);  
                // cerr<<"max index < biggest is"<<ans<<endl;
            }else ans = lo-1;
            int left = c - (ans-lo+1), fi = ans + 1;
            l = 1, r = n, ans = inf;
            while(l<=r){
                int md = l + (r-l+1)/2;
                if(query(md)<=biggest)ans = md, l = md + 1;
                else r = md - 1;
            }
            // cerr<<"now, adding from "<<max(ans-left+1,lo)<<" to "<<ans<<endl;
            add(max(ans-left+1,fi),ans,1);
        }else{
            auto [le,ri] = p;
            int l = 1, r = n, ans = inf;
            while(l<=r){
                int md = l + (r-l+1)/2;
                if(query(md)>=le)ans = md, r = md - 1;
                else l = md + 1;
            }
            int lo = ans;
            l = 1, r = n, ans = inf;
            while(l<=r){
                int md = l + (r-l+1)/2;
                if(query(md)<=ri)ans = md, l = md + 1;
                else r = md - 1;
            }
            int hi = ans;
            if(max(lo,hi)==inf)answers.pb(0);
            else answers.pb(hi-lo+1);
        }
        //for(int i=1;i<=n;++i)cerr<<query(i)<<" \n"[i==n];
    }
    return answers;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r){
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int main(){
    int nice = 1;
    for(int t=1;t<=1;++t){
        int n = 20, m = n;
        vector<int>v(n);
        vector<pair<char,ii>>operations(m);
        for(int j=0;j<n;++j)v[j] = rand(1,n);
        for(int j=0;j<m;++j){
            operations[j].first = "FC"[rand(0,1)];
            if(operations[j].first=='F'){
                operations[j].second.first = rand(1,n);
                operations[j].second.second = rand(1,2*n);
            }else{
                operations[j].second.first = rand(1,n);
                operations[j].second.second = rand(operations[j].second.first,n);
            }
        }
        // cout<<"Testcase #"<<t<<endl;
        // cout<<n<<" "<<m<<endl;
        // for(int i=0;i<n;++i)cout<<v[i]<<" \n"[i==n-1];
        // for(auto [op,c]:operations)cout<<op<<" "<<c.first<<" "<<c.second<<endl;
        vector<int>myanswers = solve(n,m,v,operations);
        vector<int>correct;
        sort(all(v));
        for(auto [op,p]:operations){
            if(op=='F'){
                auto [c,h] = p;
                int x = lower_bound(all(v),h) - begin(v);
                for(int i=x;i<min(n,x+c);++i)v[i]++;
                sort(all(v));
            }else{
                auto [l,r] = p;
                int x = lower_bound(all(v),l) - begin(v);
                int y = lower_bound(all(v),r+1) - begin(v);
                correct.pb(y-x);
            }
        }
        bool ok = 1;
        for(int i=0;i<sz(correct);++i){
            if(correct[i]!=myanswers[i])ok = 0;            
        }
        if(!ok){
            nice = 0;
            cout<<"Wrong Answer"<<endl;
            cout<<"Your output: ";
            for(auto x:myanswers)cout<<x<<" ";
            cout<<endl;
            cout<<"Correct output: ";
            for(auto x:correct)cout<<x<<" ";
            cout<<endl; 
        }
        cout<<endl;
    }
    if(nice)cout<<"Accepted"<<endl;
}