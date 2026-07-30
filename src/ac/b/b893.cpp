#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// f(x) = a x^5 + b x^4 + c x^3 + d x^2 + e x + f, computed via __int128 (overflow-safe)
__int128 fval(ll x, ll a, ll b, ll c, ll d, ll e, ll f){
    __int128 X = x;
    return ((((a*X + b)*X + c)*X + d)*X + e)*X + f;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll a,b,c,d,e,f;
    string out;
    while(cin >> a >> b >> c >> d >> e >> f){
        // all coefficients zero -> identically zero -> infinitely many roots
        if(a==0 && b==0 && c==0 && d==0 && e==0 && f==0){
            cout << "Too many... = =\"" << "\n";
            continue;
        }
        vector<string> ans;
        // output integers n must satisfy n^6 <= 2147483647  => |n| <= 35
        for(int x=-35; x<=35; x++){
            __int128 fx = fval(x,a,b,c,d,e,f);
            if(fx == 0){
                ans.push_back(to_string(x) + " " + to_string(x));
            }
            if(x < 35){
                __int128 fn = fval(x+1,a,b,c,d,e,f);
                if((fx>0 && fn<0) || (fx<0 && fn>0)){
                    ans.push_back(to_string(x) + " " + to_string(x+1));
                }
            }
        }
        if(ans.empty()){
            cout << "N0THING! >\\\\\\<" << "\n";
        } else {
            for(auto &s : ans) cout << s << "\n";
        }
    }
    return 0;
}
