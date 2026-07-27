#include <bits/stdc++.h>
using namespace std;

const int NEG = -1000000000;

int main(){
    int n;
    while (scanf("%d", &n) == 1) {
        vector<long long> S(n), E(n);
        vector<long long> pts;
        for (int i=0;i<n;i++){
            long long s,t; scanf("%lld %lld",&s,&t);
            S[i]=s; E[i]=s+t;
            pts.push_back(S[i]); pts.push_back(E[i]);
        }
        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
        int m = pts.size(); // point indices 0..m-1
        auto idx=[&](long long v){ return (int)(lower_bound(pts.begin(),pts.end(),v)-pts.begin()); };
        vector<int> sIdx(n), eIdx(n);
        // occ[a][b]: count activities with start idx a, end idx b
        // rowPre[a][j] = sum_{b<=j} occ[a][b]
        vector<vector<int>> rowPre(m, vector<int>(m,0));
        for (int i=0;i<n;i++){
            int a=idx(S[i]), b=idx(E[i]);
            sIdx[i]=a; eIdx[i]=b;
            rowPre[a][b]+=1;
        }
        for (int a=0;a<m;a++) for(int j=1;j<m;j++) rowPre[a][j]+=rowPre[a][j-1];
        // cnt[i][j] = # activities with start idx>=i and end idx<=j = f[i][j]
        // f[i][j] = f[i+1][j] + rowPre[i][j]
        vector<vector<int>> cnt(m, vector<int>(m,0));
        for (int i=m-1;i>=0;i--){
            for (int j=0;j<m;j++){
                int below = (i+1<m)? cnt[i+1][j] : 0;
                cnt[i][j] = below + rowPre[i][j];
            }
        }

        // pre[i][j]: prefix ending at point i, max venueB given venueA=j
        vector<vector<int>> pre(m, vector<int>(n+1, NEG));
        pre[0][0]=0;
        for (int i=0;i<m;i++){
            for (int j=0;j<=n;j++) if (pre[i][j]>NEG){
                int base=pre[i][j];
                for (int k=i+1;k<m;k++){
                    int c=cnt[i][k];
                    // block [i,k] -> A
                    if (j+c<=n && base>pre[k][j+c]) pre[k][j+c]=base;
                    // block -> B
                    if (base+c>pre[k][j]) pre[k][j]=base+c;
                }
            }
        }
        // suf[i][j]: suffix starting at point i, max venueB given venueA=j
        vector<vector<int>> suf(m, vector<int>(n+1, NEG));
        suf[m-1][0]=0;
        for (int i=m-1;i>=0;i--){
            for (int j=0;j<=n;j++) if (suf[i][j]>NEG){
                int base=suf[i][j];
                for (int k=i-1;k>=0;k--){
                    int c=cnt[k][i];
                    // block [k,i] -> A
                    if (j+c<=n && base>suf[k][j+c]) suf[k][j+c]=base;
                    // block -> B
                    if (base+c>suf[k][j]) suf[k][j]=base+c;
                }
            }
        }

        // first answer
        int ans1=0;
        for (int j=0;j<=n;j++) if (pre[m-1][j]>NEG) ans1=max(ans1, min(j, pre[m-1][j]));

        // combine: max over a,b of min(a+b+C1, P[a]+Q[b]+C2)
        // P=pre[l], Q=suf[r]
        auto combine=[&](const vector<int>&P, const vector<int>&Q, int C1, int C2)->int{
            // build compact lists
            static vector<pair<int,int>> LP, LQ;
            LP.clear(); LQ.clear();
            for (int a=0;a<=n;a++) if (P[a]>NEG) LP.push_back({a,P[a]});
            for (int b=0;b<=n;b++) if (Q[b]>NEG) LQ.push_back({b,Q[b]});
            if (LP.empty()||LQ.empty()) return NEG;
            int best=NEG;
            int jp=(int)LQ.size()-1;
            for (int ip=0; ip<(int)LP.size(); ip++){
                int a=LP[ip].first, Pa=LP[ip].second;
                // first = a+b+C1, second = Pa+Qb+C2 ; move jp down while second<first
                while (jp>0){
                    int b=LQ[jp].first, Qb=LQ[jp].second;
                    int first=a+b+C1, second=Pa+Qb+C2;
                    if (second<first) jp--; else break;
                }
                // evaluate jp-1, jp, jp+1
                for (int d=-1; d<=1; d++){
                    int t=jp+d;
                    if (t<0||t>=(int)LQ.size()) continue;
                    int b=LQ[t].first, Qb=LQ[t].second;
                    int v=min(a+b+C1, Pa+Qb+C2);
                    if (v>best) best=v;
                }
            }
            return best;
        };

        // best[l][r] for l<r (point indices)
        // BM[l][r] = max over l'<=l, r'>=r of best[l'][r']
        vector<vector<int>> BM(m, vector<int>(m, NEG));
        // compute best into a temp, then 2D max
        vector<vector<int>> best(m, vector<int>(m, NEG));
        for (int l=0;l<m;l++){
            for (int r=l+1;r<m;r++){
                int c=cnt[l][r];
                int vA=combine(pre[l], suf[r], c, 0); // block->A
                int vB=combine(pre[l], suf[r], 0, c); // block->B
                best[l][r]=max(vA,vB);
            }
        }
        // 2D suffix/prefix max: G[l][r]=max over l'<=l,r'>=r
        for (int l=0;l<m;l++){
            for (int r=m-1;r>=0;r--){
                int v=best[l][r];
                if (l>0) v=max(v, BM[l-1][r]);
                if (r+1<m) v=max(v, BM[l][r+1]);
                BM[l][r]=v;
            }
        }

        // output
        printf("%d\n", ans1);
        for (int i=0;i<n;i++){
            int sk=sIdx[i], ek=eIdx[i];
            int res=BM[sk][ek];
            if (res<0) res=0;
            printf("%d\n", res);
        }
    }
    return 0;
}
