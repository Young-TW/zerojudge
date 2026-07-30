#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m){
        // read matrix
        vector<vector<long long>> a(n, vector<long long>(m));
        for (int i=0;i<n;i++) for(int j=0;j<m;j++) cin>>a[i][j];
        // ensure m <= n by transpose
        if (m > n){
            vector<vector<long long>> b(m, vector<long long>(n));
            for(int i=0;i<n;i++) for(int j=0;j<m;j++) b[j][i]=a[i][j];
            a.swap(b);
            swap(n,m);
        }
        // compress values
        vector<long long> vals;
        vals.reserve((size_t)n*m);
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) vals.push_back(a[i][j]);
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int V = vals.size();
        vector<vector<int>> id(n, vector<int>(m));
        for(int i=0;i<n;i++) for(int j=0;j<m;j++)
            id[i][j] = (int)(lower_bound(vals.begin(), vals.end(), a[i][j]) - vals.begin());

        // lastRow[j*V + v] = last row (1-indexed) where column j had value id v, 0 if none
        vector<int> lastRow((size_t)m*V, 0);
        // B, C, D as m x m
        vector<int> B((size_t)m*m,0), C((size_t)m*m,0), D((size_t)m*m,0);
        auto IDX=[&](int j,int k){ return (size_t)j*m+k; };

        long long ans=0;
        vector<int> vid(m);
        for(int ri=1; ri<=n; ri++){
            int i=ri-1;
            for(int j=0;j<m;j++) vid[j]=id[i][j];
            // B
            for(int j=0;j<m;j++){
                for(int k=0;k<m;k++){
                    int b;
                    if(j==k){
                        b = lastRow[(size_t)j*V + vid[j]];
                    } else {
                        if(vid[j]!=vid[k]){
                            b = lastRow[(size_t)k*V + vid[j]];
                        } else {
                            b = ri; // a_ij == a_ik -> l=i works
                        }
                    }
                    B[IDX(j,k)] = b;
                }
            }
            // C by increasing length
            for(int j=0;j<m;j++) C[IDX(j,j)] = B[IDX(j,j)];
            for(int len=2; len<=m; len++){
                for(int j=0; j+len-1<m; j++){
                    int k=j+len-1;
                    int c = C[IDX(j,k-1)];
                    c = max(c, C[IDX(j+1,k)]);
                    c = max(c, B[IDX(j,k)]);
                    c = max(c, B[IDX(k,j)]);
                    C[IDX(j,k)] = c;
                }
            }
            // D update and answer
            for(int j=0;j<m;j++){
                for(int k=j;k<m;k++){
                    int d = max(D[IDX(j,k)], C[IDX(j,k)]);
                    D[IDX(j,k)] = d;
                    long long area = (long long)(ri - d) * (k-j+1);
                    if(area>ans) ans=area;
                }
            }
            // update lastRow
            for(int j=0;j<m;j++) lastRow[(size_t)j*V + vid[j]] = ri;
        }
        cout << ans << "\n";
    }
    return 0;
}
