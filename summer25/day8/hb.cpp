#include <bits/stdc++.h> 
 
using namespace std; 
 
#define _ ios_base::sync_with_stdio(0);cin.tie(0); 
#define endl '\n' 
 
typedef long long ll; 
 
const int INF = 0x3f3f3f3f; 
const ll LINF = 0x3f3f3f3f3f3f3f3fll; 
 
template<typename T> vector<int> pi(T s) { 
 vector<int> p(s.size()); 
 for (int i = 1, j = 0; i < s.size(); i++) { 
  while (j and s[j] != s[i]) j = p[j-1]; 
  if (s[j] == s[i]) j++; 
  p[i] = j; 
 } 
 return p; 
} 
 
template<typename T> vector<int> matching(T& s, const T& t) { 
 vector<int> p = pi(s), match(t.size()); 
 for (int i = 0, j = 0; i < t.size(); i++) { 
  while (j and s[j] != t[i]) j = p[j-1]; 
  if (s[j] == t[i]) j++; 
  if (j == s.size()) match[i-j+1] = 1, j = p[j-1]; 
 } 
 return match; 
} 
 
vector<int> match_left(string s, string t, string p) { 
 auto pi_p = pi(p); 
 auto pi_tp = pi(t + '#' + p); 
 vector<int> valid(p.size()+1); 
 for (int i = pi_tp.back(); i; i = pi_tp[i-1]) valid[i] = 1; 
 
 vector<int> acc(p.size()); 
 for (int i = 1; i < p.size(); i++) acc[i] += valid[p.size()-i] + acc[pi_p[i-1]]; 
 
 vector<int> ans; 
 int j = 0; 
 for (int i = 0; i+1 < s.size(); i++) { 
  while (j and s[i] != p[j]) j = pi_p[j-1]; 
  if (s[i] == p[j]) j++; 
  if (j == p.size()) j = pi_p[j-1]; 
  ans.push_back(acc[j]); 
 } 
 return ans; 
} 
 
vector<int> match_bordas(string s, string t, string p) { 
 auto ans = match_left(s, t, p); 
 reverse(s.begin(), s.end()); 
 reverse(t.begin(), t.end()); 
 reverse(p.begin(), p.end()); 
 auto ans_ = match_left(s, t, p); 
 int n = ans.size(); 
 for (int i = 0; i < n; i++) ans[i] += ans_[n-1-i]; 
 return ans; 
} 
 
vector<int> match_contem(string s, string t, string p) { 
 auto pi_p = pi(p); 
 auto pi_tp = pi(t + '#' + p); 
 vector<int> valid(p.size()+1); 
 for (int i = pi_tp.back(); i; i = pi_tp[i-1]) valid[i] = 1; 
 
 vector<int> acc(p.size()); 
 for (int i = 1; i < p.size(); i++) acc[i] += valid[p.size()-i] + acc[pi_p[i-1]]; 
 
 vector<int> ans(s.size()-1); 
 return ans; 
 int j = 0; 
 for (int i = 0; i+1 < s.size(); i++) { 
  while (j and s[i] != p[j]) j = pi_p[j-1]; 
  if (s[i] == p[j]) j++; 
  if (j == p.size()) j = pi_p[j-1]; 
  if (i >= t.size()) ans[i - t.size()] = acc[j]; 
 } 
 return ans; 
} 
 
vector<ll> match_all_left(string s, string t, string p) { 
 auto m = matching(p, s); 
 vector<ll> ans(s.size()-1); 
 for (int i = 0; i+1 < s.size(); i++) { 
  ans[i] = (i ? ans[i-1] : 0); 
  if (i >= p.size()-1) ans[i] += m[i+1-p.size()]; 
 } 
 return ans; 
} 
 
vector<ll> match_full(string s, string t, string p) { 
 auto m_b = match_bordas(s, t, p); 
 auto m_l = match_all_left(s, t, p); 
 reverse(s.begin(), s.end()); 
 reverse(t.begin(), t.end()); 
 reverse(p.begin(), p.end()); 
 int n = m_b.size(); 
 vector<int> m_meio = matching(p, t); 
 int meio = accumulate(m_meio.begin(), m_meio.end(), 0); 
 auto m_r = match_all_left(s, t, p); 
 reverse(m_r.begin(), m_r.end()); 
 auto m_c = match_contem(s, t, p); 
 vector<ll> ans(n, meio); 
 for (int i = 0; i < n; i++) ans[i] += m_l[i] + m_b[i] + m_r[i] + m_c[i]; 
 return ans; 
} 
 
int main() { _ 
 string s, t, p; cin >> s >> t >> p; 
 s = '@' + s + '$'; 
 auto b = match_full(s, t, p); 
 int ma = *max_element(b.begin(), b.end()); 
 int qt_ma = 0, fi = -1, la; 
 for (int i = 0; i < b.size(); i++) if (b[i] == ma) { 
  qt_ma++; 
  if (fi == -1) fi = i; 
  la = i; 
 } 
 cout << ma << " " << qt_ma << " " << fi << " " << la << endl; 
 exit(0); 
}
