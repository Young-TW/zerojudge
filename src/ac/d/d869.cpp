// d869 NOIP2000 税收与补贴问题 — self-written by Young.
//
// Government expected price p0. We choose an integer z (z>0 subsidy, z<0 tax)
// added to per-unit profit. Profit at price p:  profit(p) = (p - cost + z) * s(p),
// where s(p) is the piecewise-linear sales curve (between given points), and for
// p above the largest given price sales drop by `dec` per +1 price (clamped >=0).
// We need z such that profit(p0) >= profit(p) for every valid integer price p>=cost.
// Output the feasible z with minimum |z| (0 preferred); else "NO SOLUTION".
//
// For each price p the constraint profit(p0) >= profit(p) is linear in z:
//   (p0-cost+z)*s0 >= (p-cost+z)*s_p
//   z*(s0 - s_p) >= (p-cost)*s_p - (p0-cost)*s0
// Let d = s0 - s_p, R = (p-cost)*s_p - (p0-cost)*s0:
//   d>0 : z >= ceil(R/d)   -> lower bound
//   d<0 : z <= floor(R/d)  -> upper bound
//   d==0: need R<=0, else infeasible.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// floor/ceil division with strictly positive denominator b.
ll fdiv(ll a, ll b){ ll q=a/b, r=a%b; if(r!=0 && ((r<0)!=(b<0))) --q; return q; }
ll cdiv(ll a, ll b){ ll q=a/b, r=a%b; if(r!=0 && ((r<0)==(b<0))) ++q; return q; }

vector<pair<ll,ll>> pts; // sorted by price
ll dec_;

// sales at integer price p (>= cost). clamp negative to 0.
ll salesAt(ll p){
    if(p <= pts.front().first) return pts.front().second;
    if(p >= pts.back().first){
        ll s = pts.back().second - dec_*(p - pts.back().first);
        return s>0? s : 0;
    }
    // find segment
    for(size_t i=0;i+1<pts.size();++i){
        if(p>=pts[i].first && p<=pts[i+1].first){
            ll x0=pts[i].first, y0=pts[i].second, x1=pts[i+1].first, y1=pts[i+1].second;
            // guaranteed integer by problem statement
            ll s = y0 + (y1-y0)*(p-x0)/(x1-x0);
            return s>0? s:0;
        }
    }
    return 0; // unreachable
}

int main(){
    // Robust tokenizer: extract signed integers, ignore any non-ascii junk
    // (sample shows an en-dash for the terminating "-1"). We read line by line.
    ll p0;
    ll cost, scost;
    if(!(cin>>p0)) return 0;
    cin>>cost>>scost;
    pts.push_back({cost,scost});
    while(true){
        // read first token as string to survive weird characters
        string tok;
        if(!(cin>>tok)) break;
        // parse leading integer from tok
        // if it starts with '-' or non-digit that's the terminator
        bool neg=false; size_t i=0;
        if(i<tok.size() && (tok[i]=='-'|| (unsigned char)tok[i]>127)){ neg=true; }
        if(neg){
            // terminator: consume second token (junk) and stop
            string junk; cin>>junk; break;
        }
        // it is a normal price
        ll a = stoll(tok);
        ll b; if(!(cin>>b)) break;
        pts.push_back({a,b});
    }
    cin>>dec_;
    sort(pts.begin(), pts.end());

    ll s0 = salesAt(p0);

    // upper bound of prices to examine: until sales reaches 0 beyond last point,
    // plus include p0.
    ll pmax = pts.back().first;
    if(dec_>0) pmax = pts.back().first + (pts.back().second + dec_ - 1)/dec_ + 1;
    pmax = max(pmax, p0);
    ll pmin = min(cost, p0);

    ll lo = LLONG_MIN, hi = LLONG_MAX;
    bool feasible = true;
    for(ll p=pmin; p<=pmax; ++p){
        ll sp = salesAt(p);
        ll d = s0 - sp;
        ll R = (p-cost)*sp - (p0-cost)*s0;
        if(d>0){ lo = max(lo, cdiv(R,d)); }
        else if(d<0){ hi = min(hi, fdiv(-R,-d)); } // z <= (-R)/(-d)
        else { if(R>0){ feasible=false; break; } }
    }

    if(!feasible || lo>hi){ cout << "NO SOLUTION\n"; return 0; }
    ll ans;
    if(lo<=0 && 0<=hi) ans=0;
    else if(lo>0) ans=lo;
    else ans=hi; // hi<0
    cout << ans << "\n";
    return 0;
}
