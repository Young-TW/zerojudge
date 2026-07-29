// a209 街友的寒冷夜晚 - self-written solution.
// Min number of all-1 squares covering all 1-cells (no square may touch a 0; overlaps allowed).
// Exact branch & bound set cover with reductions: dead/dominated squares, forced (unit) cells.
// Candidates restricted to maximal all-1 squares (a superset square is never worse).
#include <bits/stdc++.h>
using namespace std;
static const int MAXN=400;
typedef bitset<MAXN> BS;
int n,m,N;
vector<BS> masks;        // maximal square cell-sets
BS full;
int best;

int firstBit(const BS&b){return b._Find_first();}

// greedy upper bound on residual given active squares
int greedyUB(const vector<int>&act, BS uncovered){
    int c=0;
    while(uncovered.any()){
        int bi=-1,bg=-1;
        for(int idx:act){int g=(int)(masks[idx]&uncovered).count(); if(g>bg){bg=g;bi=idx;}}
        if(bi<0)return INT_MAX/2;
        uncovered&=~masks[bi]; c++;
    }
    return c;
}

// packing lower bound: greedy max independent set of cells (share-a-square graph, residual)
int packLB(const vector<int>&act, const BS&uncovered){
    // build residual reach per uncovered cell lazily via active squares
    BS work=uncovered;
    int lb=0;
    while(work.any()){
        int c=firstBit(work);
        // reach = union of active squares covering c, intersected with work
        BS reach; reach.set(c);
        for(int idx:act){ if(masks[idx].test(c)) reach|=masks[idx]; }
        lb++;
        work&=~reach;
    }
    return lb;
}

void reduceAndBranch(vector<int> act, BS uncovered, int cnt){
    // ---- reduction loop ----
    for(;;){
        if(cnt>=best) return;
        if(uncovered.none()){ best=min(best,cnt); return; }
        // residual masks; drop dead squares
        vector<int> na; na.reserve(act.size());
        for(int idx:act){ if((masks[idx]&uncovered).any()) na.push_back(idx); }
        act.swap(na);
        // per-cell cover count + witness
        static int cover[MAXN]; static int witness[MAXN];
        for(int c=uncovered._Find_first();c<N;c=uncovered._Find_next(c)){cover[c]=0;witness[c]=-1;}
        for(int idx:act){
            BS r=masks[idx]&uncovered;
            for(int c=r._Find_first();c<N;c=r._Find_next(c)){ cover[c]++; witness[c]=idx; }
        }
        // forced cells (unique cover)
        bool changed=false;
        // collect forced square indices (dedup)
        vector<int> forced;
        for(int c=uncovered._Find_first();c<N;c=uncovered._Find_next(c)){
            if(cover[c]==1) forced.push_back(witness[c]);
        }
        if(!forced.empty()){
            sort(forced.begin(),forced.end()); forced.erase(unique(forced.begin(),forced.end()),forced.end());
            for(int idx:forced){ uncovered&=~masks[idx]; cnt++; }
            changed=true;
        }
        if(changed) continue;
        // square domination on residual: remove S if resid[S] subset resid[T]
        // compute residuals
        int A=act.size();
        vector<BS> resid(A);
        for(int i=0;i<A;i++) resid[i]=masks[act[i]]&uncovered;
        vector<char> dead(A,0);
        for(int i=0;i<A;i++) if(!dead[i]){
            for(int j=0;j<A;j++) if(i!=j && !dead[j]){
                // resid[i] subset resid[j] ?  and not (equal & i<j to avoid mutual kill)
                if((resid[i]&~resid[j]).none()){
                    // if equal, keep the one with larger original mask (more future value) -> keep j if masks bigger; simplest: kill i unless equal and i<j keep i
                    if(resid[i]==resid[j]){ if(i<j){dead[i]=1;break;} else continue; }
                    dead[i]=1; break;
                }
            }
        }
        bool anyDead=false;
        na.clear();
        for(int i=0;i<A;i++){ if(dead[i]) anyDead=true; else na.push_back(act[i]); }
        if(anyDead){ act.swap(na); changed=true; }
        if(changed) continue;
        break;
    }
    if(cnt>=best) return;
    if(uncovered.none()){ best=min(best,cnt); return; }

    // bounds
    int lb=packLB(act,uncovered);
    if(cnt+lb>=best) return;
    int ub=greedyUB(act,uncovered);
    if(cnt+ub<best) best=cnt+ub; // improve incumbent
    if(cnt+lb>=best) return;

    // branch on most-constrained uncovered cell
    static int cover2[MAXN];
    for(int c=uncovered._Find_first();c<N;c=uncovered._Find_next(c)) cover2[c]=0;
    for(int idx:act){ BS r=masks[idx]&uncovered; for(int c=r._Find_first();c<N;c=r._Find_next(c)) cover2[c]++; }
    int chosen=-1,mn=INT_MAX;
    for(int c=uncovered._Find_first();c<N;c=uncovered._Find_next(c)){ if(cover2[c]<mn){mn=cover2[c];chosen=c;} }
    // candidate squares covering chosen, sorted by residual coverage desc
    vector<pair<int,int>> cands; // (-residcount, idx)
    for(int idx:act){ if(masks[idx].test(chosen)){ int rc=(int)(masks[idx]&uncovered).count(); cands.push_back({-rc,idx}); } }
    sort(cands.begin(),cands.end());
    for(auto&pr:cands){
        int idx=pr.second;
        reduceAndBranch(act, uncovered&~masks[idx], cnt+1);
        if(best<=cnt+lb) return;
    }
}

int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    while(cin>>m>>n){
        if(m==0&&n==0)break;
        vector<vector<int>> g(n,vector<int>(m));
        for(auto&r:g)for(auto&x:r)cin>>x;
        N=n*m;
        vector<vector<int>> P(n+1,vector<int>(m+1,0));
        for(int i=0;i<n;i++)for(int j=0;j<m;j++)P[i+1][j+1]=P[i][j+1]+P[i+1][j]-P[i][j]+g[i][j];
        auto allOnes=[&](int r,int c,int s)->bool{
            if(r<0||c<0||r+s>n||c+s>m)return false;
            return P[r+s][c+s]-P[r][c+s]-P[r+s][c]+P[r][c]==s*s;
        };
        full.reset();
        for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(g[i][j])full.set(i*m+j);
        masks.clear();
        for(int i=0;i<n;i++)for(int j=0;j<m;j++){
            int mx=min(n-i,m-j);
            for(int s=1;s<=mx;s++){
                if(!allOnes(i,j,s))break;
                bool grow=allOnes(i-1,j-1,s+1)||allOnes(i-1,j,s+1)||allOnes(i,j-1,s+1)||allOnes(i,j,s+1);
                if(grow)continue;
                BS b; for(int r=i;r<i+s;r++)for(int c=j;c<j+s;c++)b.set(r*m+c);
                masks.push_back(b);
            }
        }
        if(full.none()){cout<<0<<"\n";continue;}
        vector<int> act(masks.size()); iota(act.begin(),act.end(),0);
        best=INT_MAX;
        reduceAndBranch(act, full, 0);
        cout<<best<<"\n";
    }
}
