#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while(cin >> n){
        vector<vector<int>> a(n, vector<int>(n));
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin >> a[i][j];
        int best = INT_MIN;
        for(int r1=0;r1<n;r1++){
            vector<int> col(n, 0);
            for(int r2=r1;r2<n;r2++){
                for(int j=0;j<n;j++) col[j] += a[r2][j];
                int cur = 0, mx = INT_MIN;
                for(int j=0;j<n;j++){
                    cur = max(col[j], cur + col[j]);
                    mx = max(mx, cur);
                }
                best = max(best, mx);
            }
        }
        cout << best << "\n";
    }
    return 0;
}
