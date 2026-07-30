#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, k;
    while(cin >> n >> k){
    vector<int> A(n+1);
    for(int i=1;i<=n;i++) cin >> A[i];
    // functional graph: edge i -> A[i]
    // find cycle nodes via Kahn peeling
    vector<int> indeg(n+1,0);
    for(int i=1;i<=n;i++) indeg[A[i]]++;
    vector<char> peeled(n+1,0);
    vector<int> order; order.reserve(n);
    // queue of indeg==0
    vector<int> st;
    for(int i=1;i<=n;i++) if(indeg[i]==0) st.push_back(i);
    while(!st.empty()){
        int u=st.back(); st.pop_back();
        peeled[u]=1; order.push_back(u);
        int p=A[u];
        if(--indeg[p]==0) st.push_back(p);
    }
    // cycle nodes = not peeled
    // assign cycle ids
    vector<int> cycId(n+1,-1);
    int c=0;
    long long cycleNodeCount=0;
    for(int i=1;i<=n;i++){
        if(!peeled[i] && cycId[i]==-1){
            // traverse cycle
            int cur=i;
            while(cycId[cur]==-1){
                cycId[cur]=c;
                cycleNodeCount++;
                cur=A[cur];
            }
            c++;
        }
    }
    if(k==1){
        // answer = c-1
        cout << (c-1) << "\n";
        continue;
    }
    // k>1
    // long-path decomposition of tree part; height for tree nodes
    vector<long long> height(n+1,0);      // height of tree node's inherited path
    vector<long long> bestChildTree(n+1,0); // running max child height for tree parents
    vector<long long> cycMax; cycMax.assign(c,0);
    vector<long long> candidates;
    // process in peel order: children before parents
    for(int idx=0; idx<(int)order.size(); idx++){
        int u=order[idx];
        height[u] = 1 + bestChildTree[u];
        int p=A[u];
        long long x=height[u];
        if(peeled[p]){
            // tree parent: running max
            if(x > bestChildTree[p]){
                if(bestChildTree[p]>0) candidates.push_back(bestChildTree[p]);
                bestChildTree[p]=x;
            } else {
                candidates.push_back(x);
            }
        } else {
            // cycle parent, top tree node entering cycle X
            int X=cycId[p];
            if(x > cycMax[X]){
                if(cycMax[X]>0) candidates.push_back(cycMax[X]);
                cycMax[X]=x;
            } else {
                candidates.push_back(x);
            }
        }
    }
    long long T = cycleNodeCount;
    for(int i=0;i<c;i++) T += cycMax[i];
    long long ans;
    if(T >= k){
        ans = c;
    } else {
        long long D = k - T;
        sort(candidates.rbegin(), candidates.rend());
        long long sum=0; long long m=0;
        for(long long v : candidates){
            if(sum>=D) break;
            sum += v; m++;
        }
        ans = c + m;
    }
    cout << ans << "\n";
    }
    return 0;
}
