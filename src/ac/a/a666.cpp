#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n; ll K;
vector<int> P; vector<ll> T;
vector<char> onCycle;
vector<vector<pair<int,ll>>> adj;
vector<char> cdRemoved;
vector<int> visTok; int curTok=0;
vector<int> par; vector<int> subSize;
ll partA;

// count unordered pairs (i!=j) with d[i]+d[j] <= K
ll countPairsVec(vector<ll>& d){
  sort(d.begin(),d.end());
  ll c=0; int l=0,r=(int)d.size()-1;
  while(l<r){ if(d[l]+d[r]<=K){ c += (ll)(r-l); l++; } else r--; }
  return c;
}

void decompose(int root){
  // gather component (iterative DFS)
  curTok++; int tk=curTok;
  vector<int> order;
  { stack<int> st; st.push(root); par[root]=0; visTok[root]=tk;
    while(!st.empty()){ int u=st.top(); st.pop(); order.push_back(u);
      for(auto&e:adj[u]){ int v=e.first; if(!cdRemoved[v]&&visTok[v]!=tk){ visTok[v]=tk; par[v]=u; st.push(v);} }
    }
  }
  int total=order.size();
  for(int u:order) subSize[u]=1;
  for(int i=total-1;i>=1;i--){ int u=order[i]; subSize[par[u]]+=subSize[u]; }
  // find centroid
  int centroid=root, best=INT_MAX;
  for(int u:order){
     int mx=total-subSize[u];
     for(auto&e:adj[u]){ int v=e.first; if(!cdRemoved[v]&&par[v]==u) mx=max(mx,subSize[v]); }
     if(mx<best){best=mx;centroid=u;}
  }
  // distances from centroid
  curTok++; int tk2=curTok; visTok[centroid]=tk2;
  vector<ll> allD; allD.push_back(0);
  for(auto&e:adj[centroid]){ int nb=e.first; ll w=e.second; if(cdRemoved[nb]||visTok[nb]==tk2) continue;
     vector<ll> sub;
     stack<pair<int,ll>> st; visTok[nb]=tk2; st.push({nb,w});
     while(!st.empty()){ auto pr=st.top(); st.pop(); int u=pr.first; ll d=pr.second;
        if(d<=K){ sub.push_back(d); allD.push_back(d);
           for(auto&e2:adj[u]){ int v=e2.first; if(!cdRemoved[v]&&visTok[v]!=tk2){ visTok[v]=tk2; st.push({v,d+e2.second}); } }
        }
     }
     partA -= countPairsVec(sub);
  }
  partA += countPairsVec(allD);
  cdRemoved[centroid]=1;
  for(auto&e:adj[centroid]){ int nb=e.first; if(!cdRemoved[nb]) decompose(nb); }
}

// count unordered pairs (u,v) in comp with h_u+h_v+cycleDist(x_u,x_v) <= K
ll countFormula(vector<pair<ll,ll>>& nodes, ll C, ll Kv){
   int m=nodes.size();
   if(m<2) return 0;
   sort(nodes.begin(),nodes.end());
   vector<ll> X(m),H(m),A(m),Pp(m);
   for(int i=0;i<m;i++){ X[i]=nodes[i].first; H[i]=nodes[i].second; A[i]=H[i]-X[i]; Pp[i]=H[i]+X[i]; }
   vector<int> loArr(m); { int p2=0; for(int j=0;j<m;j++){ ll target=2*X[j]-C; while(p2<m && 2*X[p2]<target) p2++; loArr[j]=p2; } }
   ll res=0;
   // NEAR: i in [loArr[j], j-1], gap<=C/2, cond A[i] <= Kv-(H[j]+X[j])
   {
     vector<ll> s(A.begin(),A.end()); sort(s.begin(),s.end()); s.erase(unique(s.begin(),s.end()),s.end());
     int sz=s.size(); vector<int> fen(sz+1,0);
     auto add=[&](ll val,int delta){ int pos=lower_bound(s.begin(),s.end(),val)-s.begin()+1; for(;pos<=sz;pos+=pos&-pos) fen[pos]+=delta; };
     auto qpref=[&](int pos){ int r=0; for(;pos>0;pos-=pos&-pos) r+=fen[pos]; return r; };
     auto countLE=[&](ll thr)->int{ int pos=upper_bound(s.begin(),s.end(),thr)-s.begin(); return qpref(pos); };
     int addPtr=0, lp=0;
     for(int j=0;j<m;j++){
        while(addPtr<j){ add(A[addPtr],1); addPtr++; }
        while(lp<loArr[j]){ add(A[lp],-1); lp++; }
        res += countLE(Kv - (H[j]+X[j]));
     }
   }
   // FAR: i in [0, loArr[j]-1], gap>C/2, cond Pp[i] <= Kv-C-(H[j]-X[j])
   {
     vector<ll> s(Pp.begin(),Pp.end()); sort(s.begin(),s.end()); s.erase(unique(s.begin(),s.end()),s.end());
     int sz=s.size(); vector<int> fen(sz+1,0);
     auto add=[&](ll val,int delta){ int pos=lower_bound(s.begin(),s.end(),val)-s.begin()+1; for(;pos<=sz;pos+=pos&-pos) fen[pos]+=delta; };
     auto qpref=[&](int pos){ int r=0; for(;pos>0;pos-=pos&-pos) r+=fen[pos]; return r; };
     auto countLE=[&](ll thr)->int{ int pos=upper_bound(s.begin(),s.end(),thr)-s.begin(); return qpref(pos); };
     int fp=0;
     for(int j=0;j<m;j++){
        while(fp<loArr[j]){ add(Pp[fp],1); fp++; }
        res += countLE(Kv - C - (H[j]-X[j]));
     }
   }
   return res;
}

int main(){
  int Tt;
  if(scanf("%d",&Tt)!=1) return 0;
  while(Tt--){
    scanf("%d %lld",&n,&K);
    P.assign(n+1,0); T.assign(n+1,0);
    for(int i=1;i<=n;i++){ ll pp,tt; scanf("%lld %lld",&pp,&tt); P[i]=(int)pp; T[i]=tt; }
    // cycle detection (Kahn peeling on directed functional graph i->P[i])
    vector<int> indeg(n+1,0);
    for(int i=1;i<=n;i++) indeg[P[i]]++;
    vector<char> removed(n+1,0);
    queue<int> q;
    for(int i=1;i<=n;i++) if(indeg[i]==0) q.push(i);
    while(!q.empty()){ int u=q.front();q.pop(); removed[u]=1; int v=P[u]; if(!removed[v]){ if(--indeg[v]==0) q.push(v); } }
    onCycle.assign(n+1,0);
    for(int i=1;i<=n;i++) onCycle[i]=!removed[i];
    // cycle positions & comp ids
    vector<ll> pos(n+1,0); vector<int> compId(n+1,-1); vector<int> idxAtt(n+1,0); vector<ll> h(n+1,0);
    vector<ll> compC;
    for(int i=1;i<=n;i++){
       if(onCycle[i] && compId[i]==-1){
          int cid=compC.size(); ll accum=0; int cur=i;
          do{ compId[cur]=cid; pos[cur]=accum; idxAtt[cur]=cur; h[cur]=0; accum+=T[cur]; cur=P[cur]; }while(cur!=i);
          compC.push_back(accum);
       }
    }
    // heights via BFS from cycle nodes over reverse (tree) edges
    vector<vector<int>> children(n+1);
    for(int i=1;i<=n;i++) if(!onCycle[i]) children[P[i]].push_back(i);
    {
      queue<int> bq;
      for(int i=1;i<=n;i++) if(onCycle[i]) bq.push(i);
      while(!bq.empty()){ int u=bq.front();bq.pop();
         for(int c:children[u]){ h[c]=h[u]+T[c]; idxAtt[c]=idxAtt[u]; compId[c]=compId[u]; bq.push(c); }
      }
    }
    // Part A: centroid decomposition on forest (same-tree pairs, true tree distance)
    adj.assign(n+1,{});
    for(int i=1;i<=n;i++) if(!onCycle[i]){ adj[i].push_back({P[i],T[i]}); adj[P[i]].push_back({i,T[i]}); }
    cdRemoved.assign(n+1,0);
    visTok.assign(n+1,0); curTok=0;
    par.assign(n+1,0); subSize.assign(n+1,0);
    partA=0;
    for(int i=1;i<=n;i++) if(!cdRemoved[i]) decompose(i);
    // Part B: cross-tree same-component pairs = sumFormula - sameIdx
    int ncomp=compC.size();
    vector<vector<pair<ll,ll>>> compNodes(ncomp);
    for(int i=1;i<=n;i++){ int cid=compId[i]; compNodes[cid].push_back({pos[idxAtt[i]], h[i]}); }
    ll sumFormula=0;
    for(int c=0;c<ncomp;c++) sumFormula += countFormula(compNodes[c], compC[c], K);
    vector<vector<ll>> byIdx(n+1);
    for(int i=1;i<=n;i++) byIdx[idxAtt[i]].push_back(h[i]);
    ll sameIdx=0;
    for(int j=1;j<=n;j++) if(!byIdx[j].empty()) sameIdx += countPairsVec(byIdx[j]);

    ll ans = partA + sumFormula - sameIdx;
    printf("%lld\n", ans);
  }
  return 0;
}
