#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while(cin >> N >> M){
        vector<double> diag(N+1, 0.0);
        // off-diagonal conductances: L[i][j] = -sum of conductances between i,j
        // We'll build a dense matrix for nodes excluding T.
        // First read all edges, accumulate.
        // We need S and T too, read at end. But edges come first.
        // Use map for off-diagonals? N could be large; but typical test data small-ish.
        // Use dense matrix N+1.
        vector<vector<double>> g(N+1, vector<double>(N+1, 0.0));
        for(int i=0;i<M;i++){
            int x,y; double r;
            cin >> x >> y >> r;
            double c = 1.0/r;
            g[x][y] += c;
            g[y][x] += c;
            diag[x] += c;
            diag[y] += c;
        }
        int S,T;
        cin >> S >> T;
        // 只保留 S 所在連通分量的節點：孤立/不連通節點會使 Laplacian 奇異(nan)
        vector<char> reach(N+1, 0);
        {
            vector<int> stk = {S};
            reach[S] = 1;
            while(!stk.empty()){
                int u = stk.back(); stk.pop_back();
                for(int v=1; v<=N; v++)
                    if(!reach[v] && g[u][v]!=0.0){ reach[v]=1; stk.push_back(v); }
            }
        }
        // Build reduced Laplacian: 連通分量內、除 T 以外的節點。
        vector<int> idx(N+1,-1);
        int n=0;
        for(int v=1; v<=N; v++){
            if(v==T || !reach[v]) continue;
            idx[v]=n++;
        }
        // A: n x n
        vector<vector<double>> A(n, vector<double>(n, 0.0));
        for(int u=1; u<=N; u++){
            if(u==T || !reach[u]) continue;
            int i=idx[u];
            A[i][i] = diag[u];
            for(int v=1; v<=N; v++){
                if(v==u) continue;
                if(g[u][v]!=0.0){
                    if(v==T || idx[v]<0) continue; // grounded 或不在分量內
                    int j=idx[v];
                    A[i][j] -= g[u][v];
                }
            }
        }
        // RHS: current injection 1 at S, 0 elsewhere. V_T=0.
        vector<double> b(n,0.0);
        b[idx[S]] = 1.0;
        // Gaussian elimination with partial pivoting
        for(int col=0; col<n; col++){
            int piv=col;
            for(int r=col+1;r<n;r++){
                if(fabs(A[r][col])>fabs(A[piv][col])) piv=r;
            }
            if(piv!=col){ swap(A[piv],A[col]); swap(b[piv],b[col]); }
            double pv=A[col][col];
            // pv should be nonzero
            for(int r=col+1;r<n;r++){
                double f=A[r][col]/pv;
                if(f!=0.0){
                    for(int c=col;c<n;c++) A[r][c]-=f*A[col][c];
                    b[r]-=f*b[col];
                }
            }
        }
        // back substitution
        vector<double> V(n,0.0);
        for(int i=n-1;i>=0;i--){
            double s=b[i];
            for(int j=i+1;j<n;j++) s-=A[i][j]*V[j];
            V[i]=s/A[i][i];
        }
        double R = V[idx[S]]; // V_S - V_T(=0), current=1
        cout << fixed << setprecision(2) << R << "\n";
    }
    return 0;
}
