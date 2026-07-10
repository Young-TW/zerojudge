#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,x,y,z;
    while(cin>>a>>b>>c>>d>>e>>f>>g>>h>>i>>j>>k>>l>>m>>n>>o>>p>>q>>r>>s>>t>>u>>v>>x>>y>>z){
        const long long INF = (long long)4e18;
        int N = (int)n;
        if(N < 1){
            cout << 0 << " " << 0 << " " << 0 << "\n";
            continue;
        }
        vector<long long> A(N+1, INF), B(N+1, INF), C(N+1, INF);
        A[1]=x; B[1]=y; C[1]=z;
        for(int sz=2; sz<=N; ++sz){
            long long bestA = INF;
            if(sz-2>=1) bestA = min(bestA, a*B[sz-2] + b*C[sz-1] + c);
            if(sz-1>=1) bestA = min(bestA, d*C[sz-1] + e);
            if(sz-1>=1) bestA = min(bestA, f*A[sz-1] + g);
            A[sz] = bestA;

            long long bestB = INF;
            if(sz-2>=1) bestB = min(bestB, h*C[sz-2] + i*A[sz-1] + j);
            if(sz-1>=1) bestB = min(bestB, k*C[sz-1] + l);
            if(sz-2>=1) bestB = min(bestB, m*A[sz-2] + o);
            B[sz] = bestB;

            long long bestC = INF;
            if(sz-3>=1) bestC = min(bestC, p*A[sz-3] + q*B[sz-1] + r);
            if(sz-1>=1) bestC = min(bestC, s*B[sz-1] + t);
            if(sz-2>=1) bestC = min(bestC, u*C[sz-2] + v);
            C[sz] = bestC;
        }
        cout << A[N] << " " << B[N] << " " << C[N] << "\n";
    }
    return 0;
}
