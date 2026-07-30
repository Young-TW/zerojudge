// c824. 背包問題 EX -- self-written solution
//
// Knapsack where every item weight is 2^a and capacity is 2^M (a,M up to 1e9,
// N up to 1e6). Because weights are powers of two, two items of weight 2^e can
// be combined into one "packet" of weight 2^(e+1) (value = sum). Greedy /
// binomial-heap style:
//
//   Process exponent levels from low to high, keeping `cur` = values of packets
//   at the current level, sorted descending. To climb one level we pair the two
//   largest packets (their sum stays largest => the top packet always hoards the
//   highest values); an odd leftover (smallest) is carried up as a lone packet.
//   Every packet built at claimed level L has real weight <= 2^L, so the single
//   best packet at level M has weight <= 2^M and is a feasible selection; its
//   value is the answer. Empty levels between buckets are skipped in O(log) time
//   (repeated pairing shrinks `cur` to size 1, after which climbing is a no-op).
//
// This is O(N log N) (dominated by the sort); merges are O(total items) overall.
// Verified against brute force for correctness and equivalent to the reference.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// fast input
static char ibuf[1 << 25];
static int ipos, ilen;
static inline int rd(){ ipos=0; ilen=(int)fread(ibuf,1,sizeof(ibuf),stdin); return ilen; }
static inline bool nextLong(ll &out){
    // skip non-digits
    while(ipos<ilen && (ibuf[ipos]<'0'||ibuf[ipos]>'9')) ipos++;
    if(ipos>=ilen) return false;
    ll v=0;
    while(ipos<ilen && ibuf[ipos]>='0' && ibuf[ipos]<='9'){ v=v*10+(ibuf[ipos]-'0'); ipos++; }
    out=v; return true;
}

int main(){
    if(!rd()) return 0;
    ll N, M;
    if(!nextLong(N)) return 0;
    while(true){
        if(!nextLong(M)) break;   // reads M for current test (N already read)
        // read N items
        vector<pair<ll,ll>> items; items.reserve((size_t)N);
        for(ll i=0;i<N;i++){
            ll a=0,b=0; nextLong(a); nextLong(b);
            if(a<=M) items.push_back({a,b});
        }
        // sort by exponent ascending; within same exponent value order handled in merge
        sort(items.begin(), items.end(), [](const pair<ll,ll>&x,const pair<ll,ll>&y){
            return x.first < y.first;
        });

        // cur: packet values at level cur_a, sorted descending
        vector<ll> cur, buf;
        ll cur_a = -1;
        size_t idx = 0;
        size_t nItems = items.size();

        auto climb = [&](ll target){
            // promote cur from cur_a up to target by pairing largest-first
            ll gap = target - cur_a;
            while(gap>0 && cur.size()>1){
                // pair adjacent (cur is desc): buf[i]=cur[2i]+cur[2i+1]
                buf.clear();
                size_t sz=cur.size();
                size_t pairs = sz/2;
                buf.reserve(pairs + (sz&1));
                for(size_t i=0;i+1<sz;i+=2) buf.push_back(cur[i]+cur[i+1]);
                if(sz&1){
                    // insert leftover (smallest) into desc-sorted buf at its position
                    ll rem=cur.back();
                    // buf is descending; find first position where buf<rem
                    size_t p=0; while(p<buf.size() && buf[p]>=rem) p++;
                    buf.insert(buf.begin()+p, rem);
                }
                swap(cur,buf);
                gap--;
            }
            cur_a = target;
        };

        while(idx<nItems){
            ll a = items[idx].first;
            // collect this bucket's values, sorted descending
            size_t j=idx;
            vector<ll> bucket;
            while(j<nItems && items[j].first==a){ bucket.push_back(items[j].second); j++; }
            sort(bucket.rbegin(), bucket.rend());
            idx=j;

            if(cur_a<0){ cur.swap(bucket); cur_a=a; }
            else{
                climb(a);
                // merge cur (desc) with bucket (desc) into buf
                buf.clear(); buf.reserve(cur.size()+bucket.size());
                size_t p=0,q=0;
                while(p<cur.size() && q<bucket.size()){
                    if(cur[p]>=bucket[q]) buf.push_back(cur[p++]);
                    else buf.push_back(bucket[q++]);
                }
                while(p<cur.size()) buf.push_back(cur[p++]);
                while(q<bucket.size()) buf.push_back(bucket[q++]);
                swap(cur,buf);
            }
        }
        if(cur_a>=0 && cur_a<M) climb(M);

        ll ans = cur.empty()? 0 : cur[0];
        printf("%lld\n", ans);

        // next test: read its N (if any)
        if(!nextLong(N)) break;
    }
    return 0;
}
