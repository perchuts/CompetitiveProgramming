#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const ll ILL=2167167167167167167;
const int INF=2100000000;
#define rep(i,a,b) for (int i=(int)(a);i<(int)(b);i++)
#define all(p) p.begin(),p.end()
template<class T> using pq_ = priority_queue<T, vector<T>, greater<T>>;
template<class T> int LB(vector<T> &v,T a){return lower_bound(v.begin(),v.end(),a)-v.begin();}
template<class T> int UB(vector<T> &v,T a){return upper_bound(v.begin(),v.end(),a)-v.begin();}
template<class T> bool chmin(T &a,T b){if(b<a){a=b;return 1;}else return 0;}
template<class T> bool chmax(T &a,T b){if(a<b){a=b;return 1;}else return 0;}
template<class T> void So(vector<T> &v) {sort(v.begin(),v.end());}
template<class T> void Sore(vector<T> &v) {sort(v.begin(),v.end(),[](T x,T y){return x>y;});}
bool yneos(bool a,bool upp=false){if(a){cout<<(upp?"YES\n":"Yes\n");}else{cout<<(upp?"NO\n":"No\n");}return a;}
template<class T> void vec_out(vector<T> &p,int ty=0){
    if(ty==2){cout<<'{';for(int i=0;i<(int)p.size();i++){if(i){cout<<",";}cout<<'"'<<p[i]<<'"';}cout<<"}\n";}
    else{if(ty==1){cout<<p.size()<<"\n";}for(int i=0;i<(int)(p.size());i++){if(i) cout<<" ";cout<<p[i];}cout<<"\n";}}
template<class T> T vec_min(vector<T> &a){assert(!a.empty());T ans=a[0];for(auto &x:a) chmin(ans,x);return ans;}
template<class T> T vec_max(vector<T> &a){assert(!a.empty());T ans=a[0];for(auto &x:a) chmax(ans,x);return ans;}
template<class T> T vec_sum(vector<T> &a){T ans=T(0);for(auto &x:a) ans+=x;return ans;}
int pop_count(long long a){int res=0;while(a){res+=(int)(a&1),a>>=1;}return res;}
template<class T> T square(T a){return a * a;}



void solve();
// DEAR MYSTERIES / TOMOO
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    rep(i, 0, t) solve();
}

void solve(){
    string X, Y;
    cin >> X >> Y;
    const int M = 26;
    const int L = 100;
    vector<array<ll, M>> base(L);
    vector<vector<array<ll, M>>> p(2);
    vector<ll> len(L);
    auto f = [&](int ind, string S) -> void {
        len[ind] = S.size();
        rep(i, 0, M) base[ind][i] = 0;
        p[ind].push_back(base[ind]);
        for (auto c : S){
            base[ind][c - 'a']++;
            p[ind].push_back(base[ind]);
        }
    };
    f(0, X);
    f(1, Y);
    rep(i, 2, L){
        len[i] = min(ILL, len[i - 1] + len[i - 2]);
        rep(j, 0, M) base[i][j] = base[i - 1][j] + base[i - 2][j];
    }
    // vec_out(len);
    auto g = [&](auto self, ll l, int ind, int c) -> ll {
        // cout << ind << " " << l << endl;
        if (ind < 2){
            return p[ind][l][c];
        }
        if (len[ind] == l) return base[ind][c];
        ll tmp = min(l, len[ind - 1]);
        ll res = self(self, tmp, ind - 1, c);
        l -= tmp;
        if (l > 0) res += self(self, l, ind - 2, c);
        return res;
    };
    int Q;
    cin >> Q;
    while (Q--){
        ll l, r;
        char c;
        cin >> l >> r;
        cin >> c;
        cout << g(g, r, L - 1, c - 'a') - g(g, l - 1, L - 1, c - 'a') << "\n";
    }
}


