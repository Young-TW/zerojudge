#include <bits/stdc++.h>
using namespace std;

// Ribbon buying = bin packing.
// Lengths (mult of 8) -> units: A..I = 1,2,3,4,5,6,7,8,10
// Bin capacity K = N/8 (only multiples of 8 usable).
// Reduction: size-1 items are perfect unit fillers, so
//   answer = max( Bmin(sizes 2..10), ceil(total_all / K) ).
// Bmin computed via strong lower bound (Martello-Toth L2) + BFD/FFD upper bound,
// closing any residual gap with bounded exact feasibility search.

static const int U[9] = {1,2,3,4,5,6,7,8,10};

int K;                       // capacity in units
// big-item sizes (units) present: 2,3,4,5,6,7,8,10
// counts for these (index 0..7 -> sizes 2,3,4,5,6,7,8,10)
static const int BS[8] = {2,3,4,5,6,7,8,10};

// ---- exact bounded feasibility search ----
long long nodeBudget;
bool budgetExceeded;
long long sumRemain;         // remaining total size of big items
int cnt[8];                  // counts by big-size index (fixed order BS)

// try to pack all remaining big items into `binsLeft` bins
bool solve(int binsLeft);

// fill remaining capacity of the currently-open bin (which already holds an item),
// added sizes must be non-increasing (index <= maxIdx), then close & recurse.
bool fillRest(int cap, int maxIdx, int binsLeft){
    if(--nodeBudget < 0){ budgetExceeded = true; return false; }
    // option: close current bin, move to next
    if(solve(binsLeft - 1)) return true;
    if(budgetExceeded) return false;
    // option: add another item of size BS[t] <= cap, t <= maxIdx
    for(int t = maxIdx; t >= 0; --t){
        if(cnt[t] > 0 && BS[t] <= cap){
            cnt[t]--; sumRemain -= BS[t];
            bool r = fillRest(cap - BS[t], t, binsLeft);
            cnt[t]++; sumRemain += BS[t];
            if(r) return true;
            if(budgetExceeded) return false;
        }
    }
    return false;
}

bool solve(int binsLeft){
    if(sumRemain == 0) return true;
    if(binsLeft <= 0) return false;
    // lower bound prune
    if((sumRemain + (long long)K - 1) / K > binsLeft) return false;
    if(--nodeBudget < 0){ budgetExceeded = true; return false; }
    // open a new bin with the largest remaining item (symmetry breaking)
    for(int s = 7; s >= 0; --s){
        if(cnt[s] > 0){
            cnt[s]--; sumRemain -= BS[s];
            bool r = fillRest(K - BS[s], s, binsLeft);
            cnt[s]++; sumRemain += BS[s];
            return r; // largest item MUST go somewhere; this bin is representative
        }
    }
    return true; // no items
}

// Martello-Toth L2 lower bound for bin packing given item list & capacity c
long long L2bound(const vector<int>& items, int c){
    if(items.empty()) return 0;
    // items sorted desc assumed by caller? compute generally
    vector<int> w = items;
    sort(w.begin(), w.end(), greater<int>());
    long long best = (accumulate(w.begin(), w.end(), 0LL) + c - 1) / c; // trivial
    int n = w.size();
    for(int alpha = 0; alpha <= c/2; ++alpha){
        long long N1=0,N2=0; long long sumN2=0,sumN3=0;
        for(int i=0;i<n;i++){
            int wi=w[i];
            if(wi > c - alpha) N1++;
            else if(wi > c/2) { N2++; sumN2 += wi; }
            else if(wi >= alpha) { sumN3 += wi; }
        }
        long long freeInN2 = N2*(long long)c - sumN2;
        long long extra = sumN3 - freeInN2;
        long long add = extra > 0 ? (extra + c - 1)/c : 0;
        long long L = N1 + N2 + add;
        if(L > best) best = L;
    }
    return best;
}

// BFD (best fit decreasing) upper bound
long long BFD(const vector<int>& itemsDesc, int c){
    vector<int> rem; // remaining capacities of open bins
    for(int w : itemsDesc){
        int bestj=-1, bestleft=INT_MAX;
        for(int j=0;j<(int)rem.size();j++){
            if(rem[j]>=w){ int left=rem[j]-w; if(left<bestleft){bestleft=left;bestj=j;} }
        }
        if(bestj<0){ rem.push_back(c-w); }
        else rem[bestj]-=w;
    }
    return (long long)rem.size();
}
// FFD
long long FFD(const vector<int>& itemsDesc, int c){
    vector<int> rem;
    for(int w: itemsDesc){
        int j=0; for(;j<(int)rem.size();j++) if(rem[j]>=w){ rem[j]-=w; break; }
        if(j==(int)rem.size()) rem.push_back(c-w);
    }
    return (long long)rem.size();
}

int main(){
    // robust parse: read all whitespace-separated tokens
    long long N;
    if(!(cin >> N)) return 0;
    while(true){
        long long c[9];
        bool ok=true;
        for(int i=0;i<9;i++){ if(!(cin>>c[i])){ ok=false; break; } }
        if(!ok) break;

        K = (int)(N / 8);

        // NO SOLUTION if any required item longer than ribbon
        bool nosol=false;
        for(int i=0;i<9;i++) if(c[i]>0 && U[i] > K){ nosol=true; break; }

        if(nosol){
            printf("NO SOLUTION!!\n");
        } else {
            // total including size-1 fillers
            long long total_all=0;
            for(int i=0;i<9;i++) total_all += c[i]*(long long)U[i];

            if(total_all==0){
                printf("0\n");
            } else {
                // big items: sizes 2..10 (indices 1..8 of U -> BS)
                for(int t=0;t<8;t++) cnt[t]=(int)c[t+1];
                long long sumBig=0;
                vector<int> itemsDesc;
                for(int t=7;t>=0;--t){
                    sumBig += (long long)cnt[t]*BS[t];
                    for(int k=0;k<cnt[t];k++) itemsDesc.push_back(BS[t]);
                }
                // itemsDesc currently sizes from large index... ensure sorted desc
                sort(itemsDesc.begin(), itemsDesc.end(), greater<int>());

                long long Bmin;
                if(itemsDesc.empty()){
                    Bmin = 0;
                } else {
                    long long lb = L2bound(itemsDesc, K);
                    long long ub = min(BFD(itemsDesc,K), FFD(itemsDesc,K));
                    if(ub<=lb){ Bmin = lb; }
                    else {
                        // bounded exact search from lb upward
                        Bmin = ub; // fallback
                        nodeBudget = 20000000LL;
                        budgetExceeded=false;
                        for(long long m=lb; m<ub; ++m){
                            sumRemain = sumBig;
                            budgetExceeded=false;
                            bool f = solve((int)m);
                            if(budgetExceeded){ break; } // can't prove; keep ub
                            if(f){ Bmin=m; break; }
                        }
                    }
                }

                long long ceilTotal = (total_all + K - 1)/K;
                long long ans = max(Bmin, ceilTotal);
                printf("%lld\n", ans);
            }
        }

        if(!(cin >> N)) break; // next dataset or EOF
    }
    return 0;
}
